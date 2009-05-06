FLAG=-std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2

all: main

generator.o: Generator.cpp
	g++ -c Generator.cpp $(FLAG)

equipement.o: Equipement.cpp
	g++ -c Equipement.cpp $(FLAG)

link.o: Link.cpp
	g++ -c Link.cpp $(FLAG)

hub.o: Hub.cpp
	g++ -c Hub.cpp $(FLAG)

pointtopoint.o: PointToPoint.cpp
	g++ -c PointToPoint.cpp $(FLAG)

bridge.o: Bridge.cpp
	g++ -c Bridge.cpp $(FLAG)
  
main.o: main.cpp
	g++ -c main.cpp $(FLAG)

main: generator.o equipement.o link.o hub.o pointtopoint.o bridge.o main.o
	g++ -o main Generator.o Equipement.o Link.o Hub.o PointToPoint.o Bridge.o  main.o $(FLAG)
	
doc:
	doxygen
	
clean:
	rm -f *.o
	rm -f main

