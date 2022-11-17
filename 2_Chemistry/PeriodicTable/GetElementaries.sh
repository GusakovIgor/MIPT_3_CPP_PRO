#!/bin/bash


# Main

csv_file=$1

declare line

IFS=,


num_lines=$(wc -l $csv_file | sed -E "s|([0-9]*)(.*)|\1|g")

num_lines=$(echo "$num_lines - 1" | bc -l)

echo $num_lines

i=0

while read -a line
do
	if [[ $i == 0 ]]
	then
		i=$(echo "$i - 1" | bc -l)
		continue
	fi

	echo -n -e "${line[0]}\t"
	echo -n -e "${line[2]}\t"
	echo -n -e "${line[4]}\t"
	echo -n -e "${line[5]}\t"
	echo    -e "${line[6]}\n"
	
done < $csv_file