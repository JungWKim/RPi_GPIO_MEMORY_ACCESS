obj-m = led.o
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules
	gcc -o ledApp ledApp.c

clean:
	rm led.o
	rm led.mod
	rm led.mod.c
	rm led.mod.o
	rm modules.order
	rm Module.symvers
	rm led.ko
