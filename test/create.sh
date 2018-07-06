#! /bin/bash

if [ $1 == "" ]; then
	echo "Print amount of numeric directories"
	echo "create.sh N"
	exit 0
fi

i=1
j=1
f=1
COUNT="$1"

while [ $i -le $COUNT ]; do
	j=1
	mkdir "$i"
	while [ $j -le $COUNT ]; do
		f=1
		mkdir ./"$i"/"$j"
		while [ $f -le $COUNT ]; do
			touch ./"$i"/"$j"/"$f"
			f=$[ $f + 1 ]
		done
		j=$[ $j + 1 ]
	done
	i=$[ $i + 1 ]
done

echo "Complete"
