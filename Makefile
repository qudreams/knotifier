.PHONY: all clean

DEBUG = 0
VER = 1.0.0
KVER = $(shell uname -r)
PWD = $(shell pwd)

EXTRA_CFLAGS := -DDEVICE_VERSION="\"${VER}\""

ifeq ($(DEBUG), 1)
	EXTRA_CFLAGS += -DDEBUG
endif

objs += proc_exit.o main.o
objs += mod_reg.o proc_exec.o

ifeq ($(KVER),$(shell uname -r))
    obj-m += knotifier.o
	knotifier-objs := $(objs)
else
    obj-m += knotifier-$(KVER).o
	knotifier-objs := $(objs)
endif

all:
	make -C /lib/modules/$(KVER)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVER)/build M=$(PWD) clean
