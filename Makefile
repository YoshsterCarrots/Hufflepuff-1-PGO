DBFLAGS= -g -std=c++20 -fsanitize=address -fsanitize=undefined -O0 --coverage
CCFLAGS= -g -std=c++26 -fsanitize=address -fsanitize=undefined -O0 --coverage
AFLAGS= -std=c++26 -fsanitize=address -fsanitize=undefined -O0
BFLAGS= -std=c++26 -O0
CFLAGS= -std=c++26 -fsanitize=address -fsanitize=undefined -O3
DFLAGS= -std=c++26 -O3
EFLAGS= -std=c++26 -O3 -fprofile-use
FFLAGS= -std=c++26 -O3 -fprofile-use -flto 
GFLAGS= -std=c++26 -O3 -fprofile-use -flto

EMFLAGS= -std=c++26 -O3 -fprofile-generate
ProfFLAGS= -std=c++26 -O3 -fprofile-use
OMPFLAGS= -std=c++26 -O3 -fopenmp

a.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(OMPFLAGS) main.o SortedCompilation.o Compilation.o Video.o

main.o: main.cc
	g++ $(OMPFLAGS) -c main.cc

SortedCompilation.o: SortedCompilation.cc SortedCompilation.h Compilation.o Video.o
	g++ $(OMPFLAGS) -c SortedCompilation.h SortedCompilation.cc

Compilation.o: Compilation.cc Compilation.h Video.o
	g++ $(OMPFLAGS) -c Compilation.h Compilation.cc

Video.o: Video.cc Video.h
	g++ $(OMPFLAGS) -c Video.h Video.cc

clean:
	rm -f a.out core *.o compiledVideos.txt

extrasuperclean:
	rm -f a.out core *.o *.gcda *.gcno *.gcov *.gch compiledVideos.txt
