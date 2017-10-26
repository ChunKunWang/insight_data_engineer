all: main.o IdvCon.o
	g++ -o find_political_donors main.o IdvCon.o
main.o IdvCon.o: main.cpp IdvCon.cpp
	g++ -c main.cpp IdvCon.cpp IdvCon.h
clean:
	rm -rf *.o *.gch find_political_donors

