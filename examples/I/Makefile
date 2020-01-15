#
# Makefile for simple pmemkv C example
#
OBJS = pmemkv.o kvinit.o

LIBS = -lpmemkv

all: pmemkv

pmemkv: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) *.o core a.out

clobber: clean
	$(RM) pmemkv

.PHONY: all clean clobber
