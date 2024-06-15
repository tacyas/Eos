#!/usr/bin/awk  -f
BEGIN {
	FS = " ";
	count = 0;
}

/^[^#]/ && $1 ~ /LayerCount/ {
	count++;
	flagNL = 1;
}

/^[^#]/ && $1 ~ /^[r]/ {
	flagNL = 0;
}

/^[^#]/ && $1 ~ /^[^r]/ && $1 ~ /^[^L]/ {
	#print $0
	if(count == desiredCount) {
		if(flagNL == 1) {
			printf("%15d %15d\n", $2, $3);
		} else {
			printf("%15.6f %15.6e %15.6f\n", $1, $4, $5);
		}
	}
}

END {

}
