#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("void\n");
	printf("controlFileRead(%sInfo* info)\n", ToolName);
	printf("{\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		if($Importance=="Variable") {
			if(Type=="Integer") {
				printf("    info->%s = NULL;",     Name);
			} else if (Type=="Real") { 
				printf("    info->%s = NULL;",       Name);
			} else if (Type=="File") {
				printf("    info->%s[0] = '\\0';", Name);
				printf("    info->fpt%s = %s;",    Name, Init);
			} else if (Type=="FileList") {
				printf("    info->%s[0] = '\\0';", Name);
				printf("    info->fpt%s = %s;" ,   Name, Init);
			} else if (Type=="Character") {
				printf("    info->%s = '%c';",     Name, Init);
			} else if (Type=="String") {
				printf("    info->%s = stringGetNthWord(\"%s\", 1, \"\\0\");", Name, Init);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
		} else if($Importance=="Essential" || $Importance=="Optional") {
			if(Type=="Integer") {
				printf("    info->%s = %d;",       Name, Init);
			} else if (Type=="Real") {
				printf("    info->%s = %g;",       Name, Init);
			} else if (Type=="File") {
				printf("    info->%s[0] = '\\0';", Name);
				printf("    info->fpt%s = %s;",    Name, Init);
			} else if (Type=="FileList") {
				printf("    info->%s[0] = '\\0';", Name);
				printf("    info->fpt%s = %s;",    Name, Init);
			} else if (Type=="Character") {
				printf("    info->%s = '%c';",     Name, Init);
			} else if (Type=="String") {
				printf("    info->%s = stringGetNthWord(\"%s\", 1, \"\\0\");", Name, Init);
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
