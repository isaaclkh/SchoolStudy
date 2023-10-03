#!/bin/sh
num=$((RANDOM%100+1))

echo "Guess a number (1-100)"
read n

while [ $n -ne $num ]
do
	if [ $n -lt $num ]
	then
		echo "Higher"
	fi
	
	if [ $n -gt $num ]
	then
		echo "Lower"
	fi
	read n
done

echo "Correct! You pick the right number!"

