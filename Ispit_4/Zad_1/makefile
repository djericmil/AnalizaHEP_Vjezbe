CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Calculus.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyze: main.o Calculus.o
	$(CC) $(LDFLAGS) -o main main.o Calculus.o

clean:
	rm -rf *.o main
