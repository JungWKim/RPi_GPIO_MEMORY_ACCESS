#include <wiringPi.h>
#include <stdio.h>

#define LED 1

int main(int argc, char **argv)
{
    if(wiringPiSetup() < 0)
    {
        perror("[failed] wiringPisetup() : ");
        return -1;
    }

    pinMode(LED, OUTPUT);

    while(1)
    {
        digitalWrite(LED, 1);
        delay(1000);
        digitalWrite(LED, 0);
        delay(1000);
    }

    return 0;
}
