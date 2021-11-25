#!/bin/bash

if [ $# -ne 1 ] ; then
    echo 'Please give exactly one argument, your program name'
    exit 0
fi

if [ -f "$1" ] ; then
	correct=1
	for file in $(ls -v ./lab01/roadtrip2/input*.txt)
	do
		./$1 < $file > test.txt
		num=$(echo $file | sed 's/\.\/.*\/.*\/[^0-9]*//g')
		outputfile="./lab01/roadtrip2/output$num"
		DIFF=$(diff test.txt $outputfile)
		if [ "$DIFF" ] ; then
			echo "ERROR running $file"
			echo $DIFF
			correct=0
		fi
	done
	if [ $correct -eq 1 ] ; then
		echo "All good!"
	fi
	rm test.txt
else
	echo "File not found"
fi
