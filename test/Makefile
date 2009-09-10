CXX = g++
CFLAGS = -std=c++98 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2 -g -lcppunit
OBJS = test-runner.o test-generator.o ../Generator.o ../Node.o ../Link.o ../Hub.o ../PointToPoint.o ../Bridge.o ../Ap.o ../Application.o ../Ping.o ../UdpEcho.o ../TcpLargeTransfer.o ../Tap.o ../Emu.o ../utils.o

all: test-runner

test-runner: $(OBJS)
	$(CXX) -o $@ $^ -lcppunit

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

doc:
	doxygen

debug:
	 valgrind --leak-check=full --show-reachable=yes ./test-runner

val:
	 valgrind --leak-check=full ./test-runner

clean:
	rm -f *.o
	rm -f test-runner

