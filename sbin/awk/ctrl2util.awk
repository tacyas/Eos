#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n");
	printf("#include \"../inc/config.h\"\n");
	printf("\n");
}

/^[^#]/ && $1 ~ /^-/{
}

END {
}
