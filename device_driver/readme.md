< how to use >

1. sudo mknod /dev/led c [major number] [minor number]

2. sudo insmod(or modprobe) led.ko(this can be changed depending on its location)

3. execute application

4. sudo rmmod led(without .ko)
