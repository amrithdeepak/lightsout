CCBIN=/usr/bin/gcc
CC=$(CCBIN) -Wall -Wextra -Werror -std=c99 -pedantic -g 
CCD=$(CCBIN) -Wall -Wextra -Werror -std=c99 -pedantic -g -DDEBUG
C_LIBS=lib/xalloc.c lib/ht.c lib/stacks.c lib/queues.c lib/boardutil.c lib/heaps.c

default: lightsout lightsout-d

lightsout: $(C_LIBS) lib/*.h *.c 
	$(CC) -O3 -o lightsout $(C_LIBS) bitarray.c lightsout.c

lightsout-d: $(C_LIBS) lib/*.h *.c 
	$(CCD) -o lightsout-d $(C_LIBS) bitarray.c lightsout.c

bitarray-test: $(C_LIBS) lib/*.h *.c
	$(CCD) -o bitarray-test $(C_LIBS) bitarray.c bitarray-test.c

