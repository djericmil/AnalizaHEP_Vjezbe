CC=g++
CFLAGS=-I.
CFLAGS += -std=c++11
DEPS = Stat.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: main.o Stat.o
	$(CC) -o main main.o Stat.o

clean:
	rm -rf *.o main
