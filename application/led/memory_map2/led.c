#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define GPIO_BASE 0xfe200000
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28

volatile unsigned int *gpioBase;
volatile unsigned int *gpfsel1;
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;

int main(void)
{
    int fd;
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        perror("[Error] open() : ");
        exit(-1);
    }

    //메모리장치파일에 가상메모리를 할당하는 작업
    char* gpio_memory_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if(gpio_memory_map == MAP_FAILED)
    {
        perror("[Error] mmap() : ");
        exit(-1);
    }

    gpioBase = (volatile unsigned int*)gpio_memory_map;
    gpfsel1 = gpioBase + (GPFSEL1/4);
    gpset0 = gpioBase + (GPSET0/4);
    gpclr0 = gpioBase + (GPCLR0/4);
    *gpfsel1 |= (1<<24);

    for(int i = 0; i<3; i++)
    {
        *gpset0 |= (1<<18);
        sleep(1);

        *gpclr0 |= (1<<18);
        sleep(1);
    }

    printf("gpio base : %p\n", gpioBase);
    printf("gpfsel1   : %p\n", gpfsel1);
    printf("gpset0    : %p\n", gpset0);
    printf("gpclr0    : %p\n", gpclr0);

    munmap(gpio_memory_map, 4096);
    close(fd);
    return 0;
}
