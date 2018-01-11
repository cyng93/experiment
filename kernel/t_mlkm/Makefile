MODULE_NAME = t_mlkm
obj-m += $(MODULE_NAME).o

SRCS := main.c 			\
	src/sample.c 		\

$(MODULE_NAME)-objs += $(SRCS:.c=.o)

all: $(MODULE_NAME).ko

$(MODULE_NAME).ko: $(SRCS) Makefile
	make \
	KCFLAGS="-I$(PWD)/include" \
	-C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: $(MODULE_NAME).ko
	@lsmod | grep -w $(MODULE_NAME) > /dev/null \
	&& { echo "Remove pre-inserted module"; sudo rmmod $(MODULE_NAME); } \
	|| { echo "No pre-inserted module"; }
	@echo "Inserting module '$(MODULE_NAME)'"
	@sudo insmod $(MODULE_NAME).ko

remove:
	@lsmod | grep -w $(MODULE_NAME) > /dev/null \
	&& { echo "Removing module '$(MODULE_NAME)'"; sudo rmmod $(MODULE_NAME); } \
	|| { echo "Module '$(MODULE_NAME)' wasn't inserted"; exit 2; }

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
