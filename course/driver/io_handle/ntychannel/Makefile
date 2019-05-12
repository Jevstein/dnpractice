PWD = $(shell pwd)
KERNEL_SRC = /usr/src/linux-headers-4.2.0-27-generic/

obj-m := ntychannel.o
module-objs := ntychannel.o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	rm *.ko *.o
