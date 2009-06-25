#!/bin/bash

SOURCE="Ap.o Application.o Bridge.o Emu.o Generator.o Hub.o Link.o Node.o Ping.o PointToPoint.o Tap.o TcpLargeTransfer.o UdpEcho.o";

for i in `ls ./kern/examples/ | grep -v "~"`
do
  echo "g++ $SOURCE ./kern/examples/$i -o `echo $i | cut -d"." -f1`";
  g++ $SOURCE ./kern/examples/$i -o `echo $i | cut -d"." -f1`;
done
