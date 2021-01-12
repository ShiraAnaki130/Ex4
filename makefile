CC=gcc
AR=ar
FLAGS= -Wall -g

all: libmyEx4.a frequency
frequency: frequency.o libmyEx4.a
	$(CC) $(FLAGS) -o frequency frequency.o libmyEx4.a
libmyEx4.a: frequency.o
	$(AR) -rcs libmyEx4.a frequency.o 
frequency.o: frequency.c
	$(CC) $(FLAGS) -c $< -o $@
.PHONY: clean all
clean:
	rm *.o *.a 