CC  	=	gcc
CFLAGS	=	-Wall -g

BINDIR	= 	../bin
LIBDIR 	=	../lib


queue_test: 
	gcc -o queue_test queue_test.c $(CFLAGS)

most_freq: $(OBJ)
	gcc -o most_freq most_freq.c $(CFLAGS)

