#include <stdio.h>
#include <unistd.h>

#define GPIO_BASE 0x7e200000
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28

volatile unsigned int *gpioBase;
volatile unsigned int *gpfsel1;
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;

int main(int argc, char *argv[])
{
    gpioBase = (volatile unsigned int*)GPIO_BASE;
    gpfsel1  = gpioBase + (GPFSEL1/4);
    gpset0   = gpioBase + (GPSET0/4);
    gpclr0   = gpioBase + (GPCLR0/4);

    *gpfsel1 |= (1<<24);

    for(int i = 0; i<3; i++)
    {
        *gpset0 |= (1<<18);
        sleep(1);
        *gpclr0 |= (1<<18);
        sleep(1);
    }
    
    return 0;
}
