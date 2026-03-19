CCFLAGS= -g -std=c++20 -fsanitize=address -fsanitize=undefined -O0

a.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ -O0 --coverage $(CCFLAGS) main.o SortedCompilation.o Compilation.o Video.o

main.o: main.cc
	g++ -O0 --coverage $(CCFLAGS) -c main.cc

SortedCompilation.o: SortedCompilation.cc SortedCompilation.h Compilation.o Video.o
	g++ -O0 --coverage $(CCFLAGS) -c SortedCompilation.h SortedCompilation.cc

Compilation.o: Compilation.cc Compilation.h Video.o
	g++ -O0 --coverage $(CCFLAGS) -c Compilation.h Compilation.cc

Video.o: Video.cc Video.h
	g++ -O0 --coverage $(CCFLAGS) -c Video.h Video.cc

clean:
	rm -f a.out core *.o *.gcda *.gno *.gcov *.gch compiledVideos.txt
