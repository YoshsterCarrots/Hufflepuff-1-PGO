CCFLAGS= -g -fsanitize=address -fsanitize=undefined -O0

a.out: main.o
	g++ $(CCFLAGS) main.o

main.o: main.cc
	g++ $(CCFLAGS) -c main.cc

clean:
	rm -f a.out core *.o
