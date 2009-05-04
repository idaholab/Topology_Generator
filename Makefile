all: main

generator.o: Generator.cpp
	g++ -c Generator.cpp

equipement.o: Equipement.cpp
	g++ -c Equipement.cpp
  
pc.o: Pc.cpp
	g++ -c Pc.cpp
  
main.o: main.cpp
	g++ -c main.cpp

main: generator.o equipement.o pc.o main.o
	g++ -o main Generator.o Equipement.o Pc.o main.o
	
	
	
clean:
	rm -f *.o
	rm -f main
