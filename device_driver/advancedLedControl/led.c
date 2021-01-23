#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/io.h>

#define GPIOBASE 0xfe200000
#define GPFSEL1  0x04
#define GPSET0   0x1c
#define GPCLR0   0x28

#define MAJOR_NUM 63

#define SETMODE_GPIO18_OUT (1<<24)
#define SET_GPIO18         (1<<18)
#define CLEAR_GPIO18       (0<<18)

volatile unsigned int* gpioBase;
volatile unsigned int* gpfsel1;
volatile unsigned int* gpset0;
volatile unsigned int* gpclr0;

unsigned int led_state = 0;

int device_open(struct inode *inode, struct file *filp)
{
    gpioBase = ioremap(GPIOBASE, 0xf4);
    printk("Gpio base : %p\n", gpioBase);
    gpfsel1 = (volatile unsigned int*)(gpioBase + GPFSEL1);
    gpset0 = (volatile unsigned int*)(gpioBase + GPSET0);
    gpclr0 = (volatile unsigned int*)(gpioBase + GPCLR0);
    *gpfsel1 |= SETMODE_GPIO18_OUT;
    printk("led module open\n");
    return 0;
}

int device_release(struct inode *inode, struct file *filp)
{
    iounmap((void *)gpioBase);
    printk("led module close\n");
    return 0;
}

ssize_t device_read(struct file *filp, char *user, size_t size, loff_t *pos)
{
    printk("Led state :%d", led_state);
    return led_state;
}

ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    switch(*(int *)buffer)
    {
        case 0: *gpclr0 |= CLEAR_GPIO18;
                printk("turn off led\n");
                led_state = 0;
                break;
        case 1: *gpset0 |= SET_GPIO18;
                printk("turn on led\n");
                led_state = 1;
                break;
    }
    return led_state;
}

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long addr)
{
    long value = 1.0;

    switch(cmd)
    {
        case 1: *gpset0 |= SET_GPIO18;
                led_state = 1;
                printk("turn on led\n");
                break;
        case 2: *gpclr0 |= CLEAR_GPIO18;
                led_state = 0;
                printk("turn off led\n");
                break;
        case 3: if(led_state == 1)
                {
                    *gpclr0 |= CLEAR_GPIO18;
                    printk("turn off led\n");
                }
                else
                {
                    *gpset0 |= SET_GPIO18;
                    printk("turn on led\n");
                }
                led_state = ~led_state;
                break;
    }
    return value;
}

struct file_operations device_fops = {
    .open    = device_open,
    .release = device_release,
    .read    = device_read,
    .write   = device_write,
    //ioctl만 적으면 에러발생, unlocked_ioctl이라 명시해야함
    .unlocked_ioctl   = device_ioctl
};

static int __init init_func(void)
{
    int result;
    if((result = register_chrdev(MAJOR_NUM, "led", &device_fops)) < 0)
    {
        printk(KERN_WARNING "led module register failed\n");
    }
    else
    {
        printk("led module register success\n");
    }
    return result;
}

static void __exit exit_func(void)
{
    unregister_chrdev(MAJOR_NUM, "led");
    printk("led module unregister success\n");
}

module_init(init_func);
module_exit(exit_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JUNG WOO KIM");
MODULE_DESCRIPTION("control a led through gpio 18 by typing cmd");
