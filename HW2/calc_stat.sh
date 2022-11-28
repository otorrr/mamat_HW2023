#!/bin/bash

[[ $# -ne 1 ]] && >&2 echo "Wrong number of arguments" && exit 1; 
	 


[[ `ls -l | grep "$1".txt | wc -l` -ne 1 ]] && >&2 echo "Course not found" && exit 1; 
	


if [[ -d "$1"_stat ]]; then
	rm -rf "$1"_stat
fi

mkdir "$1"_stat

cat "$1".txt | grep -v grade | cut -f2 > "$1"_stat/histogram.txt 

echo -n "" > statistics.txt

cat "$1".txt | ./median.exe >>statistics.txt
cat "$1".txt | ./mean.exe >>statistics.txt
cat "$1".txt | ./max.exe >>statistics.txt
cat "$1".txt | ./min.exe >>statistics.txt

cat statistics.txt
