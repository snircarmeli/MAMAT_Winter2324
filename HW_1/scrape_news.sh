#!/bin/bash

# Step 1 - Getting source file
url="https://ynetnews.com/category/3082"
ynet_source=$(wget -qO- "$url" --no-check-certificate)

# Step 2 - Finding articles links
links=$(echo "$ynet_source" | grep -oP 'https://www.ynetnews.com/article/[0-9a-zA-Z]+')
#echo "$links"

# Step 3 - Removing duplications
links=$(echo "$links" | uniq)
#echo "$links"
link_cnt=$(echo "$links" | wc -l)
#echo "$link_cnt"

# Step 4 - accessing each article and printing counters
serch_N="Netanyahu"
search_G="Gantz"
for ((i=1; i<=link_cnt; i++)); do
	url=$(echo "$links" | sed -n "${i}p")
	source=$(wget -qO- "$art_url" --no-check-certificate)
	(( N=$(echo "$source" | grep -o "$search_N" | wc -l) ))
	(( G=$(echo "$source" | grep -o "$search_G" | wc -l) ))
	if [ $N -eq 0 ] && [ $G -eq 0 ]; then
		echo "$url,-"
	else
		echo "$url, Netanyahu, $N, Gantz, $G"
	fi
done
