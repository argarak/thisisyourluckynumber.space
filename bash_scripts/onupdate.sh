#!/bin/bash

exec 3<>/dev/ttyACM0;
sleep 1s;

inotifywait -q -m -e modify user |
while read -r filename event; do

stty -F /dev/ttyACM0 ispeed 9600 ospeed 9600 -ignpar cs8 -cstopb -echo;
cat user >&3;

done
