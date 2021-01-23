#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>

#define GPIO_BASE 0xfe200000
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28
#define MAJOR_NUM 63

//ioremap의 데이터반환타입은 void __iomem*이므로 주의 해야함. 그렇지 않으면 시스템 다운됨
static void __iomem *gpio_base;
volatile unsigned int* gpfsel1;
volatile unsigned int* gpset0;
volatile unsigned int* gpclr0;

// 모듈이 사용중인데 이를 제거하면 큰 문제가 발생할 수 있으므로 커널은 모듈사용횟수를 항상 감시함
// MOD_INC_USE_COUNT : 모듈 사용 횟수 증가
// MOD_DEC_USE_COUNT : 모듈 사용 횟수 감소
// MOD_IN_USE : 모듈 사용횟수가 0이 아니면 참값 반환
int device_open(struct inode *inode, struct file *filp)
{
    //prefer to be used in first line
    //MOD_INC_USE_COUNT;
    //ioremap(physical address, size) returns virtual address
    gpio_base = ioremap(GPIO_BASE, 0xff);
    printk("gpio base : %p\n", gpio_base);
    *(volatile unsigned int*)(gpio_base + GPFSEL1) |= (1<<24);
    printk("led device open\n");
    return 0;
}

//if parameter is empty, must write void
int device_release(struct inode *inode, struct file *filp)
{
    //prefer to be used in first line
    //MOD_DEC_USE_COUNT;
    iounmap((void *)gpio_base);
    printk("led device close\n");
    return 0;
}

ssize_t device_read(struct file *filp, char *user, size_t size, loff_t *pos)
{
    printk("device read\n");
    return 0;
}

ssize_t device_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
    int state = *(int *)buffer;
    if(state == 1)
    {
        *(volatile unsigned int *)(gpio_base + GPSET0) |= (1<<18);
        printk("turn on led\n");
    }
    else
    {
        *(volatile unsigned int *)(gpio_base + GPCLR0) |= (1<<18);
        printk("turn off led\n");
    }
    return 0;
}

static struct file_operations device_fops = {
    .open    = device_open,
    .release = device_release,
    .read    = device_read,
    .write   = device_write
};

static int init_func(void)
{
    int result = register_chrdev(MAJOR_NUM, "led", &device_fops);
    if(result < 0)
        printk(KERN_WARNING "led register_chrdev() fail\n");
    else
        printk("led register_chrdev() success\n");

    //check_region()
    //request_region()

    return result;
}

static void exit_func(void)
{
    //unregister_chrdev returns void
    unregister_chrdev(MAJOR_NUM, "led");
    printk("led unregister_chrdev() success\n");

    //release_region()
}

module_init(init_func);
module_exit(exit_func);
