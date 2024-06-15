#!/bin/ksh
n=`./ltlgps.count.awk < $1`;
#echo $n
i=1
while [ $i -le $n ] ; do
#	echo $i
	./ltlgps.separate.awk desiredCount=$i < $1 > $1.$i
#	echo "scan($1.$i)" >>
	i=`expr $i + 1`
done

