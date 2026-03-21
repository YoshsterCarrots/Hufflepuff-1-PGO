CCFLAGS= -g -std=c++20 -fsanitize=address -fsanitize=undefined -O0 --coverage
AFLAGS= -std=c++26 -fsanitize=address -fsanitize=undefined -O0
BFLAGS= -std=c++26 -O0
CFLAGS= -std=c++26 -fsanitize=address -fsanitize=undefined -O3
DFLAGS= -std=c++26 -O3 -fprofile-generate
EFLAGS= -std=c++26 -O3 -fprofileuse
FFLAGS= -std=c++26 -O3
GFLAGS= -std=c++26 -O3

a.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(CCFLAGS) main.o SortedCompilation.o Compilation.o Video.o

PGOProfile.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(DFLAGS) main.o SortedCompilation.o Compilation.o Video.o

PGOUse.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(DFLAGS) main.o SortedCompilation.o Compilation.o Video.o

A_NoOptSANsOn.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(AFLAGS) main.o SortedCompilation.o Compilation.o Video.o

B_NoOptNoSANs.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(BFLAGS) main.o SortedCompilation.o Compilation.o Video.o

C_OptSANs.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(CFLAGS) main.o SortedCompilation.o Compilation.o Video.o

D_OptNoSANs.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(DFLAGS) main.o SortedCompilation.o Compilation.o Video.o

E_PgoOptNoSANs.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(EFLAGS) main.o SortedCompilation.o Compilation.o Video.o

F_PgoOptLtoNoSANs.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(FFLAGS) main.o SortedCompilation.o Compilation.o Video.o

G_Everything.out: main.o SortedCompilation.o Compilation.o Video.o
	g++ $(GFLAGS) main.o SortedCompilation.o Compilation.o Video.o

main.o: main.cc
	g++ $(DFLAGS) -c main.cc

SortedCompilation.o: SortedCompilation.cc SortedCompilation.h Compilation.o Video.o
	g++ $(DFLAGS) -c SortedCompilation.h SortedCompilation.cc

Compilation.o: Compilation.cc Compilation.h Video.o
	g++ $(DFLAGS) -c Compilation.h Compilation.cc

Video.o: Video.cc Video.h
	g++ $(DFLAGS) -c Video.h Video.cc

clean:
	rm -f a.out core *.o *.gcda *.gcno *.gcov *.gch compiledVideos.txt
