#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main(void)
{
    int fd;
    if((fd = open("/dev/led", O_RDWR)) < 0)
    {
        perror("[failed] open() in ledApp.c(L6) : ");
        exit(-1);
    }

    int input;
    int led_state;
    char buffer;
    while(1)
    {
        printf("Enter command (1) led on (2) led off (3) reverse (4) exit >> ");
        scanf("%d", &input);
        switch(input)
        {
            case 1: ioctl(fd, input);
                    led_state = read(fd, &buffer, sizeof(buffer));
                    printf("Led State : %d\n", led_state);
                    break;
            case 2: ioctl(fd, input);
                    led_state = read(fd, &buffer, sizeof(buffer));
                    printf("Led State : %d\n", led_state);
                    break;
            case 3: ioctl(fd, input);
                    led_state = read(fd, &buffer, sizeof(buffer));
                    printf("Led State : %d\n", led_state);
                    break;
            case 4: close(fd);
                    printf("program exited\n");
                    return 0;
        }
    }
    return 0;
}
