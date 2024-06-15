#!/usr/bin/awk  -f
BEGIN {
	FS = " ";
	count = 0;
}

/^[^#]/ && $1 ~ /LayerCount/ {
	count++;
}

END {
	print count
}
