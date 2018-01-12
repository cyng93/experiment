MODULE_NAME = foo
obj-m += $(MODULE_NAME).o

# [1-1]
# SRCS := main.c src/foo1.c

# [1-2]
SRCS := main.c $(wildcard src/*.c)

$(MODULE_NAME)-objs += main.o $(SRCS:.c=.o)

all:
	# [2] echo to check if foo-objs values changes
	echo $($(MODULE_NAME)-objs)
	KCFLAGS="-I$(PWD)/include" \
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
