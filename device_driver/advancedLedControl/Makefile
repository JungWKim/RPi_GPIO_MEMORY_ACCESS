obj-m = led.o
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules
	gcc -o ledApp ledApp.c

driver:
	make -C $(KDIR) M=$(shell pwd) modules

app:
	gcc -o ledApp ledApp.c

clean:
	rm led.o led.ko led.mod led.mod.c led.mod.o modules.order Module.symvers ledApp
