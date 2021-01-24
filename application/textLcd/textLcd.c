#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

#define GPIO_BASE 0xfe200000
#define GPFSEL0   0x00
#define GPFSEL1   0x04
#define GPFSEL2   0x08
#define GPSET0    0x1c
#define GPCLR0    0x28

volatile unsigned int *gpioBase;
volatile unsigned int *gpfsel0;
volatile unsigned int *gpfsel1;
volatile unsigned int *gpfsel2;
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;

int main(void)
{
    int fd;
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        perror("[Error] open() : ");
        return -1;
    }

    char *gpio_memory_map;
    if((gpio_memory_map = (char*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE)) < 0)
    {
        perror("[Error] mmap() : ");
        close(fd);
        return -1;
    }

    gpioBase = (volatile unsigned int*)gpio_memory_map;
    gpfsel0 = gpioBase + (GPFSEL0/4);
    gpfsel1 = gpioBase + (GPFSEL1/4);
    gpfsel2 = gpioBase + (GPFSEL2/4);
    gpset0 = gpioBase + (GPSET0/4);
    gpclr0 = gpioBase + (GPCLR0/4);

    close(fd);
    return 0;
}
