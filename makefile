CC=gcc
CFLAGS=-I. -lwiringPi
DEPS = spiFunc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spiPractice: spiPractice.o spiFunc.o
	$(CC) -o spiPractice spiPractice.o spiFunc.o $(CFLAGS)
