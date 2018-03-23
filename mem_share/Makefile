obj-m := memshare_mod.o
KDIR := /lib/modules/3.5.7/build
EXTRA_CFLAGS := -I/usr/realtime/include -I/usr/include
PWD := $(shell pwd)

default :
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean :
	make -C $(KDIR) SUBDIRS=$(PWD) clean
install:
	- insmod /usr/realtime/modules/rtai_hal.ko
	- insmod /usr/realtime/modules/rtai_ksched.ko
	- insmod /usr/realtime/modules/rtai_fifos.ko
	- insmod /usr/realtime/modules/rtai_shm.ko
on:
	- insmod memshare_mod.ko
off:
	- rmmod memshare_mod
