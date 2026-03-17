CCFLAGS= -g -std=c++20 -fsanitize=address -fsanitize=undefined -O0

a.out: main.o VideoCompilation.o
	g++ $(CCFLAGS) main.o

main.o: main.cc
	g++ $(CCFLAGS) -c main.cc

VideoCompilation.o: VideoCompilation.h
	g++ $(CCFLAGS) -c VideoCompilation.h

clean:
	rm -f a.out core *.o compiledVideos.txt
