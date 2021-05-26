/*
 * project name : led blinking
 * pin number : gpio 18
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define GPIO_BASE 0xfe200000
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28

int main(int argc, char **argv)
{
    int fd;
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        perror("[Error] open() : ");
        exit(-1);
    }

    //메모리장치파일에 가상메모리를 할당하는 작업
    //mmap은 가상메모리주소를 반환, 유저영역에선 물리주소를 알아도 가상주소로 변환해야지만 
    char* gpio_base_addr = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if(gpio_memory_map == MAP_FAILED)
    {
        perror("[Error] mmap() : ");
        exit(-1);
    }

    volatile unsigned int *gpio_virtual_addr;
    volatile unsigned int *gpfsel1;
    volatile unsigned int *gpset0;
    volatile unsigned int *gpclr0;

    gpio_virtual_addr = (volatile unsigned int*)gpio_base_addr;
    gpfsel1 = gpio_virtual_addr + (GPFSEL1/4);
    gpset0 = gpio_virtual_addr + (GPSET0/4);
    gpclr0 = gpio_virtual_addr + (GPCLR0/4);
    *gpfsel1 |= (1<<24);

    for(int i=0; i<3; i++)
    {
        *gpset0 |= (1<<18);
        sleep(1);

        *gpclr0 |= (1<<18);
        sleep(1);
    }

    printf("gpio base : %p\n", gpio_virtual_addr);
    printf("gpfsel1   : %p\n", gpfsel1);
    printf("gpset0    : %p\n", gpset0);
    printf("gpclr0    : %p\n", gpclr0);

    munmap(gpio_base_addr, 4096);
    close(fd);
    return 0;
}
