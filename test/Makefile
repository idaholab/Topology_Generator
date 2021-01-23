CXX = g++
CFLAGS = -std=c++11 -Wall -W -pedantic -Wredundant-decls -Wshadow -Werror -O2 -g -lcppunit
OBJS = test-runner.o test-generator.o ../generator.o ../node.o ../hub.o ../network-hardware.o ../point-to-point.o ../bridge.o ../ap.o ../application.o ../ping.o ../udp-echo.o ../tcp-large-transfer.o ../tap.o ../emu.o ../utils.o

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

