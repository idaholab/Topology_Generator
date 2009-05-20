CXX = g++
CFLAGS = -std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2 -g
OBJS = ../Generator.o ../Equipement.o ../Link.o ../Hub.o ../PointToPoint.o ../Bridge.o ../Wifi.o ../Application.o ../Ping.o ../UdpEcho.o ../TcpLargeTransfer.o ../Tap.o ../Emu.o

all: main

main: 
	$(CXX) -o example-hub examples/example-hub.cpp $(OBJS)
	$(CXX) -o example-router examples/example-router.cpp $(OBJS) 
	$(CXX) -o example-bridge examples/example-bridge.cpp $(OBJS) 
	$(CXX) -o example-router-bridge examples/example-router-bridge.cpp $(OBJS)
	$(CXX) -o example-wifi-ap examples/example-wifi-ap.cpp $(OBJS)  
	$(CXX) -o example-p2p examples/example-p2p.cpp $(OBJS) 
	$(CXX) -o example-star examples/example-star.cpp $(OBJS)
	$(CXX) -o example-udpEcho examples/example-udpEcho.cpp $(OBJS)
	$(CXX) -o example-tcpLargeTransfer examples/example-tcpLargeTransfer.cpp $(OBJS) 

debug:
	 valgrind --leak-check=full --show-reachable=yes ./main

val:
	 valgrind --leak-check=full ./main

clean:
	rm -f *.o
	rm -f example-*


