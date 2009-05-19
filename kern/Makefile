CXX = g++
CFLAGS = -std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2 -g -I/core -I/gui
OBJS = Generator.o Equipement.o Link.o Hub.o PointToPoint.o Bridge.o Wifi.o Application.o Ping.o UdpEcho.o TcpLargeTransfer.o Tap.o Emu.o Configuration.o dragwidget.o Graph.o main.o

all: main

main: $(OBJS)
	$(CXX) -o $@ $^ 

main.o: main.cpp
	$(CXX) $(CFLAGS) -c $<
  
%.o: core/%.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: gui/%.cpp
	$(CXX) $(CFLAGS) -c $<

doc:
	doxygen

debug:
	 valgrind --leak-check=full --show-reachable=yes ./main

val:
	 valgrind --leak-check=full ./main

clean:
	rm -f *.o
	rm -f main


