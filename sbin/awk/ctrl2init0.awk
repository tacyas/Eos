#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n");
	printf("#include <string.h>\n");
	printf("#include <math.h>\n");
	printf("#include \"../inc/config.h\"\n");
	printf("#include \"genUtil.h\"\n");
	printf("#include \"eosString.h\"\n");
	printf("#include \"File.h\"\n");
	printf("#include \"Memory.h\"\n");
	printf("\n");
	printf("\n");
	printf("void\n");
	printf("init0(%sInfo* info)\n", ToolName);
	printf("{\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();	
	if(argNumber==0) {
		sub(/^-/, "", $FullOptionField);
		gsub(/\[|\]/, "", $FullOptionField); 
		printf("    info->%s=0;\n", $FullOptionField);
	}
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		if($Importance=="Variable") {
			if(Type=="Integer") {
				printf("    info->%s = NULL;",     Name);
			} else if (Type=="Real") { 
				printf("    info->%s = NULL;",       Name);
     		} else if (Type=="inFile"    || Type=="inFileNoOpen" \
	      			|| Type=="outFile"   || Type=="outFileNoOpen" \
		       		|| Type=="appendFile"|| Type=="appendFileNoOpen") {
				printf("    info->fpt%s = %s;",    Name, Init);
     		} else if (Type=="inFileList"    || Type=="inFileListNoOpen" \
	      			|| Type=="outFileList"   || Type=="outFileListNoOpen" \
		       		|| Type=="appendFileList"|| Type=="appendFileListNoOpen") {
				printf("    info->fpt%s     = %s;" ,   Name, Init);
				printf("    info->fpt%sList = %s;" ,   Name, Init);
			} else if (Type=="Character") {
				printf("    info->%s = '%c';",     Name, Init);
			} else if (Type=="String") {
				printf("    info->%s = stringGetNthWord(\"%s\", 1, \"\\0\");", Name, Init);
			} else if (Type=="StringAll") {
				printf("    info->%s = strdup(%s);", Name, Init);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
		} else if($Importance=="Essential" || $Importance=="Optional") {
			if(Type=="Integer") {
				printf("    info->%s = %s;",       Name, Init);
			} else if (Type=="Real") {
				printf("    info->%s = %s;",       Name, Init);
     		} else if (Type=="inFile"    || Type=="inFileNoOpen" \
	      			|| Type=="outFile"   || Type=="outFileNoOpen" \
		       		|| Type=="appendFile"|| Type=="appendFileNoOpen") {
				printf("    info->fpt%s = %s;",    Name, Init);
     		} else if (Type=="inFileList"    || Type=="inFileListNoOpen" \
	      			|| Type=="outFileList"   || Type=="outFileListNoOpen" \
		       		|| Type=="appendFileList"|| Type=="appendFileListNoOpen") {
				printf("    info->fpt%s     = %s;",    Name, Init);
				printf("    info->fpt%sList = %s;",    Name, Init);
			} else if (Type=="Character") {
				printf("    info->%s = '%s';",     Name, Init);
			} else if (Type=="String") {
				printf("    info->%s = stringGetNthWord(\"%s\", 1, \"\\0\");", Name, Init);
			} else if (Type=="StringAll") {
				printf("    info->%s = strdup(\"%s\");", Name, Init);
			} else {
				printf("Unsupported Type:%s\n",Name)
			}
		} else {
			printf("Unsupported Importance: %s\n", $Importance);
		}
		printf("    info->flag%s = 0;\n",    Name); 
	}
}

END {
	printf("}\n");
}
