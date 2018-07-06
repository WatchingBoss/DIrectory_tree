#!/bin/bash

if [ $1 == "" ]; then
	echo "Print count of numeric directories"
	echo "remove.sh N"
	exit 0
fi

COUNT="$1"

while [[ $COUNT -gt 0 ]]; do
	rm -r "$COUNT"
	COUNT=$[ $COUNT - 1 ]
done

echo "Complete"
