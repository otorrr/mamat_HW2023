#!/bin/bash

x=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')


while read line
do
	
	rules=$(echo "$line" | tr -d ',' | tr -d ' ' | sed -e 's/#.*//' | sed -e 's/dst/,dst/g' | sed -e 's/src-port/,src-port/g' )
		
	
	if [[ "$rules" != "" ]]; then
		
		src_port=$(echo $rules | awk -F, '{print $3}')	
		dst_port=$(echo $rules | awk -F, '{print $4}')	
		src_ip=$(echo $rules | awk -F, '{print $1}')	
		dst_ip=$(echo $rules | awk -F, '{print $2}')	
		
				
		output+=$(echo "$x" | ./firewall.exe "$src_ip" | ./firewall.exe "$dst_ip" | ./firewall.exe "$src_port" | ./firewall.exe "$dst_port" )
		output+="\n"
	fi


done < "$1"

echo -e "$output" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort | uniq
