#! /bin/bash

face=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')


while read line
do
	
	laws=$(echo "$line" | tr -d ',' | tr -d ' ' | sed -e 's/#.*//' | sed -e 's/dst/,dst/g' | sed -e 's/src-port/,src-port/g' )
		
	
	if [[ "$laws" != "" ]]; then
	
	    dst_port=$(echo $laws | awk -F, '{print $4}')
		src_port=$(echo $laws | awk -F, '{print $3}')
		dst_ip=$(echo $laws | awk -F, '{print $2}')	
		src_ip=$(echo $laws | awk -F, '{print $1}')	
			
		
			
		output+=$(echo "$face" | ./firewall.exe "$src_ip" | ./firewall.exe "$dst_ip" | ./firewall.exe "$src_port" | ./firewall.exe "$dst_port" )
		output+="\n"
	fi


done < "$1"

echo -e "$output" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort | uniq

