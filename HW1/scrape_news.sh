#!/bin/bash


site="https://www.ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
		   grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+")
		   		   
echo -n "" > results.csv

echo "$articles" > results.csv


cat results.csv | sort | uniq > tmp.txt	#removes duplicated files


cat tmp.txt | wc -l  > results.csv	#num of overall links


i=0
for line in $(cat tmp.txt)	#this loop is for visiting every link and write the num of occurrences for each link
do
    wget -O "link_result.txt" $line
    echo -n $line >> results.csv
    
	if [[($(cat link_result.txt | grep "Netanyahu" | wc -l) -eq 0) && ($(cat link_result.txt | grep "Gantz" | wc -l) -eq 0) && ($(cat link_result.txt | grep "Lapid" | wc -l) -eq 0) && ($(cat link_result.txt | grep "Ben-gvir" | wc -l) -eq 0)]]; then	#no accurrences, neither one of them
	    echo ", -" >> results.csv
    else
        echo -n ", Netanyahu, " >> results.csv
        cat link_result.txt | grep "Netanyahu" | wc -l | tr -d '\n'  >> results.csv
        echo -n ", Gantz, " >> results.csv
        cat link_result.txt | grep "Gantz" | wc -l | tr -d '\n' >> results.csv
        echo -n ", Lapid, " >> results.csv
        cat link_result.txt | grep "Lapid" | wc -l | tr -d '\n' >> results.csv
        echo -n ", Ben-gvir, " >> results.csv
        cat link_result.txt | grep "Ben-gvir" | wc -l >> results.csv
	fi
	
	i=$((i+1))
done

rm link_result.txt tmp.txt
