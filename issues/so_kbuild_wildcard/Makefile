MODULE_NAME = foo
obj-m += $(MODULE_NAME).o

MISC = $(wildcard $(src)/src/*.c)
SRCS := main.c $(MISC:$(src)/%=%)

$(MODULE_NAME)-objs += $(SRCS:.c=.o)

all:
	KCFLAGS="-I$(PWD)/include" \
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
