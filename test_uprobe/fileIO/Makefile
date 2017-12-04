EXEC = fileIO
CFLAGS_COMM = -Wall

all: sys lib

sys:
	$(CC) $(CFLAGS_COMM) -DMODE=1 -o $(EXEC)_sys main.c

lib:
	$(CC) $(CFLAGS_COMM) -DMODE=2 -o $(EXEC)_lib main.c

clean:
	$(RM) $(EXEC)*
	@ls | grep .txt > /dev/null \
	&& rm -rf *.txt \
	|| exit 0

.PHONY: all clean run
