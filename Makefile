FLAG=-std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2 -g

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

wifi.o: Wifi.cpp
	g++ -c Wifi.cpp $(FLAG)
  
application.o: Application.cpp
	g++ -c Application.cpp $(FLAG)

ping.o: Ping.cpp
	g++ -c Ping.cpp $(FLAG)

main.o: main.cpp
	g++ -c main.cpp $(FLAG)

main: generator.o equipement.o link.o hub.o pointtopoint.o bridge.o wifi.o application.o ping.o main.o
	g++ -o main Generator.o Equipement.o Link.o Hub.o PointToPoint.o Bridge.o Wifi.o Application.o Ping.o main.o $(FLAG)
	
doc:
	doxygen

debug:
	 valgrind --leak-check=full --show-reachable=yes ./main

val:
	 valgrind --leak-check=full ./main

clean:
	rm -f *.o
	rm -f main

