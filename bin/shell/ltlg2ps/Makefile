.SUFFIXES:  .ltlgps

test.ltlgps:
		echo test
#		ltlgDataInfo -i $*.ltlg -m 4 > $*.data
		ltlgps.sh $*.data
		ltlgps.count.awk $*.data > COUNT
		cat ltlgps.S | \
		sed -e 's/SRCDEFAULT/$*.data/' \
			-e 's/DSTDEFAULT/$*.ltlgps/' \
			-e 's/MAINTITLE/$*.ltlgps/' \
		| Splus
#		rm -f $*.data
#		rm -f $*.data.*
#		rm -f COUNT 


