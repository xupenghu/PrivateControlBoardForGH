
#define LOG_TAG              "ultra"
#define LOG_LVL              LOG_LVL_DBG
#include <ulog.h>
#include "ultra.h"

#define ULTRA_UART_NAME       "uart2"  /* 串口设备名称 */
static rt_device_t serial;              /* 串口设备句柄 */
static struct rt_semaphore rx_sem;

static struct rt_semaphore get_ultra_data_sem;  //获取超声波数据的信号量
static struct rt_semaphore get_ultra_data_complete_sem;  //获取超声波数据完成的信号量

static ultra_t ultra;

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);
    return RT_EOK;
}

static void ultra_thread_entry(void *parameter)
{
    uint8_t tx_cmd;
    uint8_t rx_buffer[10] = {0};
    uint8_t *p_pos = rx_buffer;
    uint8_t rx_len = 0;
    int res = RT_EOK;
    
    while (1)
    {
        rt_sem_take(&get_ultra_data_sem, RT_WAITING_FOREVER); //等待此信号量才开始数据转换
        //获取温度值
        tx_cmd = 0x50;
        rt_device_write(serial, 0, &tx_cmd, 1); 
        LOG_D("get temperature.....");
         /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        do
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
            res = rt_device_read(serial,-1,p_pos,1);
            LOG_D("data is [%x]", rx_buffer[0]);
            rx_len++;
            p_pos++;
        }while((rx_len!=1));
        
        ultra.temp = rx_buffer[0] - 45; 
        LOG_D("temperature is [%d] ", ultra.temp);
        
        rx_len = 0;
        p_pos = rx_buffer;
        rt_memset(rx_buffer,0,sizeof(0));
        //获取测距结果
        tx_cmd = 0x55;
        rt_device_write(serial, 0, &tx_cmd, 1);
        LOG_D(" get distance......");
         /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        do
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
            res = rt_device_read(serial,-1,p_pos,1);
            LOG_D("data is [%x]", rx_buffer[0]);
            rx_len++;
            p_pos++;
        }while((rx_len!=2));
        
        ultra.distance = rx_buffer[0] * 256 + rx_buffer[1];
        LOG_D("distance is [%d] mm", ultra.distance);
        
        rx_len = 0;
        p_pos = rx_buffer;
        rt_memset(rx_buffer,0,sizeof(0));
        //转换完成释放信号量
        rt_sem_release(&get_ultra_data_complete_sem);
    }
}


int ultra_init(void)
{
    int ret = RT_EOK;
    /* 查找串口设备 */
    serial = rt_device_find(ULTRA_UART_NAME);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", ULTRA_UART_NAME);
        return RT_ERROR;
    }
    /* 以读写及中断接收方式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&get_ultra_data_sem, "get_ultra_data_sem", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&get_ultra_data_complete_sem, "get_ultra_data_sem", 0, RT_IPC_FLAG_FIFO);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);
    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("ultra_thread", ultra_thread_entry, RT_NULL, 512, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }
    return ret;
}


//获取数据
int get_ultra_data(ultra_t * p_ultra, uint16_t timeout)
{
    int res = RT_EOK;
    res = rt_sem_release(&get_ultra_data_sem);
    res = rt_sem_take(&get_ultra_data_complete_sem, timeout);
    if(res == RT_EOK)
    {
        p_ultra->temp = ultra.temp;
        p_ultra->distance = ultra.distance;
    }
    else
    {
        p_ultra->temp = 0xff;
        p_ultra->distance = 0xffff;        
    }
    return res;
}








