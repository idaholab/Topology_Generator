#!/bin/bash

SOURCE="Ap.o Application.o Bridge.o Emu.o Generator.o Hub.o Link.o Node.o Ping.o PointToPoint.o Tap.o TcpLargeTransfer.o UdpEcho.o utils.o";

if [ $# -eq 0 ]
then
  echo "Usage : ./$0 [compile|clean]";
  exit;
fi

if [ "$1" == "compile" ]
then
  for i in `ls ./kern/examples/ | grep -v "~"`
  do
    echo "g++ $SOURCE ./kern/examples/$i -o `echo $i | cut -d"." -f1`";
    g++ $SOURCE ./kern/examples/$i -o `echo $i | cut -d"." -f1`;
  done
elif [ "$1" == "clean" ]
then
  rm example-*;
else
  echo "Usage : ./$0 [compile|clean]";
  exit;
fi

