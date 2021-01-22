/*
 * writer : jung woo kim
 * 
 * usage : turn on and off led between 1 sec
 *
 * pin : gpio 18
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

//#define GPIO_BASE 0x3F200000
//#define GPIO_BASE 0x7e200000
//
//gpio 가상메모리 베이스주소
#define GPIO_BASE 0xfe200000
#define GPFSEL1 0x04
#define GPSET0 0x1C
#define GPCLR0 0X28

int main()
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(fd < 0)
    {
        perror("[error] open()");
        exit(-1);
    }

    //char*로 형변환하면 1바이트씩 접근해서 읽고 쓰겠다는 의미
    char* gpio_memory_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if(gpio_memory_map == MAP_FAILED)
    {
        perror("[error] mmap");
        exit(-1);
    }

    //int*로 형변환하면 4바이트씩 접근해서 읽고 쓰겠다는 의미
    volatile unsigned int* gpio = (volatile unsigned int*)gpio_memory_map;
    gpio[GPFSEL1/4] |= (1<<24);

    for(int i = 0; i < 5;i++)
    {
        gpio[GPSET0/4] |= (1<<18);
        sleep(1);

        gpio[GPCLR0/4] |= (1<<18);
        sleep(1);
    }

    munmap(gpio_memory_map, 4096);
    fclose((void *)fd);
    return 0;
}
