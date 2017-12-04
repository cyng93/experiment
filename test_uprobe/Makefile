MODULE_NAME = test_uprobe

SRCS := $(MODULE_NAME).c

obj-m += $(MODULE_NAME).o

all: $(MODULE_NAME).ko

$(MODULE_NAME).ko: $(SRCS) Makefile
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) clean

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

tail: insert
	sudo tail -f /var/log/kern.log

.PHONY: all clean insert remove tail
