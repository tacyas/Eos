#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("\n");
	printf("void\n");
	printf("init1(%sInfo* info)\n", ToolName);
	printf("{\n");
	printf("    char s[1024];\n");
	printf("    int i;\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		if($Importance=="Essential") {
		    printf("    if(!info->flag%s) {\n", Name);	
			if(Type=="Integer") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = stringGetNthIntegerData(s, 1, \", \\t\");\n", Name);
			} else if (Type=="Real") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = stringGetNthRealData(s, 1, \", \\t\");\n", Name);
     		} else if (Type=="inFile"    || Type=="inFileNoOpen" \
	      			|| Type=="outFile"   || Type=="outFileNoOpen" \
		       		|| Type=="appendFile"|| Type=="appendFileNoOpen") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = stringGetNthWord(s, 1, \" ,\\t\");\n",      Name);
     		} else if (Type=="inFileList"    || Type=="inFileListNoOpen" \
	      			|| Type=="outFileList"   || Type=="outFileListNoOpen" \
		       		|| Type=="appendFileList"|| Type=="appendFileListNoOpen") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%sList = stringGetNthWord(s, 1, \" ,\\t\");\n",  Name);
			} else if (Type=="Character") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = s[0];\n", Name);
			} else if (Type=="String") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = stringGetNthWord(s, 1, \" ,\\t\");\n", Name);
			} else if (Type=="StringAll") {
				printf("        stringGetFromFile(s, \"%s\", stdin, stdout, 0);\n", Name);
				printf("        info->%s = strdup(s);\n", Name);
			} else {
				printf("Unsupported Type:%s\n",Name)
			}
				printf("        info->flag%s++;\n", Name);
			printf("    }\n");
		} else if($Importance=="Variable") {
			printf("");
		} else if($Importance=="Optional") {
			printf("");
		} else {
			printf("    Not supported inportance (%s) in %s\n", $Importance, Name);
		}
#################
		if($Importance=="Essential" || $Importance=="Optional" || $Importance=="Variable" ) {
		    printf("    if(info->flag%s) {\n", Name);	
			if(Type=="Integer") {
			} else if (Type=="Real") {
			} else if (Type=="inFile") {
				printf("        info->fpt%s = fileOpen(info->%s, \"r\");\n", Name, Name);
			} else if (Type=="outFile") {
				printf("        info->fpt%s = fileOpen(info->%s, \"w\");\n", Name, Name);
			} else if (Type=="appendFile") {
				printf("        info->fpt%s = fopen(info->%s, \"a+\");\n", Name, Name);
			} else if (Type=="inFileNoOpen"  \
			        || Type=="outFileNoOpen" \
			        || Type=="appendFileNoOpen") { 

			} else if( Type=="inFileListNoOpen"  \
			        || Type=="outFileListNoOpen" \
			        || Type=="appendFileListNoOpen") {
				printf("        info->fpt%sList = fileOpen(info->%sList, \"r\");\n", Name, Name);
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            i++;\n");
				printf("        }\n");
				printf("        info->fpt%s = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("        info->%s    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("        info->flag%s = i;\n", Name)
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\\t\");\n", Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="inFileList") {
				printf("        info->fpt%sList = fileOpen(info->%sList, \"r\");\n", Name, Name);
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            i++;\n");
				printf("        }\n");
				printf("        info->fpt%s = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("        info->%s    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("        info->flag%s = i;\n", Name)
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\\t\");\n", Name);
				printf("            info->fpt%s[i] = fileOpen(info->%s[i],\"r\");\n", Name, Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="outFileList") {
				printf("        info->fpt%sList = fileOpen(info->%sList, \"r\");\n", Name, Name);
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            i++;\n");
				printf("        }\n");
				printf("        info->fpt%s = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("        info->%s    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("        info->flag%s = i;\n", Name); 
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\\t\");\n", Name);
				printf("            info->fpt%s[i] = fileOpen(info->%s[i],\"w\");\n", Name, Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="appendFileList") {
				printf("        info->fpt%sList = fileOpen(info->%sList, \"r\");\n", Name, Name);
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            i++;\n");
				printf("        }\n");
				printf("        info->fpt%s = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("        info->%s    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("        info->flag%s = i;\n", Name); 
				printf("        fseek(info->fpt%sList, 0L, SEEK_SET);\n", Name);
				printf("        i=0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList, stdout, 1)) {\n", Name);
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\\t\");\n", Name);
				printf("            info->fpt%s[i] = fileOpen(info->%s[i], \"a+\");\n", Name, Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="Character") {
			} else if (Type=="String") {
			} else if (Type=="StringAll") {
			} else {
				printf("Unsupported Type:%s\n",Name)
			}
			printf("    }\n");
		} else if($Importance=="Variable") {
			printf("");
		} else if($Importance=="Optional") {
			printf("");
		} else {
			printf("    Not supported inportance (%s) in %s\n", $Importance, Name);
		}
		printf("    \n");
	}
}

END {
	printf("}\n");
}
