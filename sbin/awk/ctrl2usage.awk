#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n");
	printf("#include \"../inc/config.h\"\n");
	printf("\n");
	printf("void\n");
	printf("usage(char* thisProgram)\n");
	printf("{\n");
	printf("    fprintf(stderr, \"Usage: %%s\\n\", thisProgram);\n");
	printf("    fprintf(stderr, \"Options:\\n\");\n");
}

/^[^#]/ && $1 ~ /^-/{
	initFieldIndex();
	argNumber = $StartField; # Get number of argumentNumber 
	printf("    fprintf(stderr, \"    [%-20s", $FullOptionField);
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		gsub(/%/,"%%", Init);
		if(1<=i) {
			printf("%-25s", " ");
		}
		printf("%-20s(%-10s).as(%-20s) ", Name, Init, TypeAll);
		if(i!=argNumber-1) {
		printf("\\n");
		}
	}
	if(0==argNumber) {
		printf("%-57s ", "");
	}
	if ($Importance=="Variable") {
		printf("... ] :%-10s:%s\\n\");\n", $Importance, $AdditionalMessage);
	} else {
		printf("] :%-10s:%s\\n\");\n", $Importance, $AdditionalMessage);
	}
}

END {
	printf("    additionalUsage();\n");
	printf("}\n");
	printf("\n");
	printf("void\n");
	printf("htmlBeforeUsage(char* thisProgram)\n");
	printf("{\n");
	printf("    fprintf(stderr, \"<HTML>\\n\");\n");
	printf("    fprintf(stderr, \"<HEAD>\\n\");\n");
	printf("    fprintf(stderr, \"<TITLE>%%s</TITLE>\\n\", thisProgram);\n");
	printf("    fprintf(stderr, \"</HEAD>\\n\");\n");
	printf("    fprintf(stderr, \"<BODY>\\n\");\n");
	printf("    fprintf(stderr, \"<H1>%%s</H1>\\n\", thisProgram);\n");
	printf("    fprintf(stderr, \"<H2>Usage</H2>\\n\");\n");
	printf("    fprintf(stderr, \"<PRE>\\n\");\n");
	printf("}\n");
	printf("\n");
	printf("void\n");
	printf("htmlAfterUsage(char* thisProgram)\n");
	printf("{\n");
	printf("    fprintf(stderr, \"</PRE>\\n\");\n");
	printf("    fprintf(stderr, \"</BODY>\\n\");\n");
	printf("    fprintf(stderr, \"</HTML>\\n\");\n");
	printf("}\n");
}
