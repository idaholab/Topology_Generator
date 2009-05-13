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

udpecho.o: UdpEcho.cpp
	g++ -c UdpEcho.cpp $(FLAG)

tcplargetransfer.o: TcpLargeTransfer.cpp
	g++ -c TcpLargeTransfer.cpp $(FLAG)

tap.o: Tap.cpp
	g++ -c Tap.cpp $(FLAG)

emu.o: Emu.cpp
	g++ -c Emu.cpp $(FLAG)

main.o: main.cpp
	g++ -c main.cpp $(FLAG)

main: generator.o equipement.o link.o hub.o pointtopoint.o bridge.o wifi.o application.o ping.o udpecho.o tcplargetransfer.o tap.o emu.o main.o
	g++ -o main Generator.o Equipement.o Link.o Hub.o PointToPoint.o Bridge.o Wifi.o Application.o Ping.o UdpEcho.o TcpLargeTransfer.o Tap.o Emu.o main.o $(FLAG)
	
doc:
	doxygen

debug:
	 valgrind --leak-check=full --show-reachable=yes ./main

val:
	 valgrind --leak-check=full ./main

clean:
	rm -f *.o
	rm -f main

