CC=g++
CFLAGS=-I. $(shell root-config --cflags) -lTMVA
LDFLAGS=$(shell root-config --libs) -lTMVA
DEPS = analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyze: analyze.o analyzer.o
	$(CC) $(LDFLAGS) -o analyze analyze.o analyzer.o

clean:
	rm -rf *.o analyze
