obj-m := hello.o

default:
	make -C$(KDIR) M=$(shell pwd) modules

clean:
	make -C$(KDIR) M=$(shell pwd) clean
