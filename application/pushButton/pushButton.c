#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define GPIO_BASE 0xfe200000
#define GPLEV0 0x34
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28

int main()
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(fd < 0)
    {
        perror("[failed] open in pushButton 11 : ");
        exit(-1);
    }

    char* gpio_memory_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if(gpio_memory_map == MAP_FAILED)
    {
        perror("[failed] mmap in pushButton 18 : ");
        exit(-1);
    }

    volatile unsigned int* gpio = (volatile unsigned int*)gpio_memory_map;
    //i don't have to set 1 to gpfsel1 for gpio17 because default for input is 000
    gpio[GPFSEL1/4] |= (1<<24);

    while(1)
    {
        int signal = gpio[GPLEV0/4] & (1<<17);

        if(signal > 0)
            gpio[GPSET0/4] |= (1<<18);
        else
            gpio[GPCLR0/4] |= (1<<18);
    }

    munmap(gpio_memory_map, 4096);
    fclose((void *)fd);

    return 0;
}
