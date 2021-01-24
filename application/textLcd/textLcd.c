#include <stdio.h>
#include <fcntl.h>

#define GPIO_BASE 0xfe200000
#define GPFSEL
#define GPSET

volatile unsigned int *gpioBase;
volatile unsigned int *gpioBase;
volatile unsigned int *gpioBase;
volatile unsigned int *gpioBase;

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



    close(fd);
    return 0;
}
