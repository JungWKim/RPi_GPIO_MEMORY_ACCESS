/*
 * description : 18번 led 5번 blink 
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd;
    if((fd = open("/dev/led", O_RDWR)) < 0)
    {
        perror("[failed] open in ledApp 12 : ");
        exit(-1);
    }

    int state;
    for(int i = 0; i<5; i++)
    {
        state = 1;
        write(fd, &state, sizeof(state));
        sleep(1);

        state = 0;
        write(fd, &state, sizeof(state));
        sleep(1);
    }
    close(fd);

    return 0;
}
