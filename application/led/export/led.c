/*
 * 
 * description : 명령어 입력시 핀번호도 같이 인수로 넘겨야함
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void led(int gpioNum)
{
    int fd;
    // BUFSIZ : stdio.h에 정의된 매크로로, 최소 256 최대 512바이트까지 공간을 할당함
    char buf[BUFSIZ];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    sprintf(buf, "%d", gpioNum);
    write(fd, buf, strlen(buf));
    close(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpioNum);
    fd = open(buf, O_WRONLY);
    write(fd, "out", 4);
    close(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpioNum);
    fd = open(buf, O_WRONLY);
    for(int i = 0; i<5; i++)
    {
        write(fd, "1", 2);
        sleep(1);

        write(fd, "0", 2);
        sleep(1);
    }
    close(fd);
    return;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        perror("Usage : sudo ./led [pin number]");
        exit(-1);
    }

    int gpioNum = atoi(argv[1]);
    led(gpioNum);
    return 0;
}

//https://ironmask.net/406
