#!/bin/bash

course="$1" # First input is the name of file
argc=$#
if [[ "$argc" -ne 1 ]]; then
    echo -e "Wrong number of arguments" >&2
    exit 1
fi

if [[ ! -f "$course" ]]; then
    echo "Course not found" >&2
    exit 1
fi

d_name="${course}_stat"
if [[ -d "$d_name" ]]; then # Erase directory if exists
    rm  -r "$d_name"
    echo Directory_removed
fi
mkdir "$d_name"

./hist.exe "${course}" -nbins 10 > "$d_name"/histogram.txt
mean=$(./mean.exe "$course")
median=$(./median.exe "$course")
min=$(./min.exe "$course")
max=$(./max.exe "$course")

output="$mean\t$median\t$min\t$max"
echo -e $output > "${d_name}/statistics.txt"