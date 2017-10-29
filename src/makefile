all: main.o IdvCon.o
	g++ -o find_political_donors main.o IdvCon.o -lm
main.o IdvCon.o: main.cpp IdvCon.cpp
	g++ -c main.cpp IdvCon.cpp IdvCon.h -lm
clean:
	rm -rf *.o *.gch find_political_donors

