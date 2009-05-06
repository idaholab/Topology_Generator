FLAG=-std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2

all: main

generator.o: Generator.cpp
	g++ -c Generator.cpp $(FLAG)

equipement.o: Equipement.cpp
	g++ -c Equipement.cpp $(FLAG)
  
main.o: main.cpp
	g++ -c main.cpp $(FLAG)

main: generator.o equipement.o  main.o
	g++ -o main Generator.o Equipement.o main.o $(FLAG)
	
doc:
	doxygen
	
clean:
	rm -f *.o
	rm -f main

