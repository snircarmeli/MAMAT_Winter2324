
#!/bin/bash

website="https://www.ynetnews.com/category/3082"
content=$(wget -q -O - "$website")

visited_links=()  # Array to store visited links

links=$(echo "$content" | grep -oE "https://www\.ynetnews\.com/article/[a-zA-Z0-9_/-]*")

for link in $links; do
    # Check if the link has been visited before
    if [[ " ${visited_links[@]} " =~ " $link " ]]; then
        continue  # Skip if link has been visited
    fi

    visited_links+=("$link")  # Mark the link as visited

    page_content=$(wget -q -O - "$link")

    netanyahu_count=$(echo "$page_content" | grep -o "Netanyahu" | wc -l)
    gantz_count=$(echo "$page_content" | grep -o "Gantz" | wc -l)

    if [[ $netanyahu_count == 0 && $gantz_count == 0 ]]; then
        printf "%s, %s\n" "$link" "-"
    else
        printf "%s, %s, %d, %s, %d\n" "$link" "Netanyahu" "$netanyahu_count" "Gantz" "$gantz_count"
    fi
done
