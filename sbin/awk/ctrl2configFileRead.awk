#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#include <stdio.h>\n");
	printf("#include \"eosString.h\"\n");
	printf("#include \"Memory.h\"\n");
	printf("#include \"File.h\"\n");
	printf("void\n");
	printf("configFileRead(FILE* fpt, %sInfo* info)\n", ToolName);
	printf("{\n");
	printf("    char s[1024];\n");
	printf("    long i, j, k;\n");
	printf("    fseek(fpt, 0L, SEEK_SET);\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();	
	if($OptionField=="-c") {
		next;
	}
	if(argNumber==0) {
		sub(/^-/, "", $FullOptionField)
		gsub(/\[|\]/, "", $FullOptionField)
		Name = $FullOptionField
		printf("    stringGetFromFile(s, \"\", fpt, stdout, 3);\n", Name);
		printf("    if(!info->%s) {\n", Name);
		printf("        info->%s = stringGetNthIntegerData(s, 1, \" \\t,\");\n", Name);
		printf("    }\n", Name);
		printf("    \n");
		next;
	}

	for(i=0; i<argNumber; i++) {
		getEachField(i);
		if($Importance=="Variable") {
			if(i==0) {
				printf("    if(!info->flag%s) {\n", Name);
				printf("        j = ftell(fpt);\n");
				printf("        k = 0; \n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", fpt, stdout, 3)) {\n", Name);
				printf("            k++;\n", Name);
				printf("        }\n", Name);
				printf("        fseek(fpt, j, SEEK_SET);\n", Name);
				printf("        j = 0;\n");
				printf("        while(NULL!=stringGetFromFile(s, \"\", fpt, stdout, 3)) {\n", Name);
			}
			printf("            if(0==j) {\n");
			if(Type=="Integer") {
				printf("                info->%s = (long*)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="Real") {
				printf("                info->%s = (float*)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="inFile") {
				printf("                info->%s = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%s = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="outFile") {
				printf("                info->%s = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%s = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="appendFile") {
				printf("                info->%s = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%s = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="inFileList") {
				printf("                info->%sList = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%sList = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="outFileList") {
				printf("                info->%sList = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%sList = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="appendFileList") {
				printf("                info->%sList = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
				printf("                info->fpt%sList = (FILE**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="Character") {
				printf("                info->%s = (char*)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else if (Type=="String") {
				printf("                info->%s = (char**)memoryAllocate(sizeof(long)*k,\"configFileRead\");\n", Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
			printf("            }\n");
			if(Type=="Integer") {
				printf("            info->%s[j] = stringGetNthIntegerData(s, %d, \" \\t,\");\n", Name, i+1);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="Real") {
				printf("            info->%s[j] = stringGetNthRealData(s, %d, \" \\t,\");\n", Name, i+1);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="inFile") {
				printf("            info->%s[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%s[j] = fileOpen(info->%s[j], \"r\");\n", Name, Name);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="outFile") {
				printf("            info->%s[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%s[j] = fileOpen(info->%s[j], \"w\");\n", Name, Name);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="appendFile") {
				printf("            info->%s[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%s[j] = fileOpen(info->%s[j], \"r+\");\n", Name, Name);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="inFileList") {
				printf("            info->%sList[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%sList[j] = fileOpen(info->%sList[j], \"r\");\n", Name, Name);
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
				printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                i++;\n");
				printf("            }\n");
				printf("            info->fpt%s[j] = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("            info->%s[j]    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("            info->flag%s[j] = i;\n", Name)
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
			    printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                info->%s[j][i] = stringGetNthWord(s, 1, \" ,\");\n", Name);
				printf("                info->fpt%s[j][i] = fileOpen(info->%s[j][i],\"r\");\n", Name, Name);
				printf("                i++;\n");
				printf("            }\n");
			} else if (Type=="outFileList") {
				printf("            info->%sList[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%sList[j] = fileOpen(info->%sList[j], \"r\");\n", Name, Name);
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
				printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                i++;\n");
				printf("            }\n");
				printf("            info->fpt%s[j] = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("            info->%s[j]    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("            info->flag%s[j] = i;\n", Name)
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
			    printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                info->%s[j][i] = stringGetNthWord(s, 1, \" ,\");\n", Name);
				printf("                info->fpt%s[j][i] = fileOpen(info->%s[j][i],\"w\");\n", Name, Name);
				printf("                i++;\n");
				printf("            }\n");
			} else if (Type=="appendFileList") {
				printf("            info->%sList[j] = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("            info->fpt%sList[j] = fileOpen(info->%sList[j], \"r\");\n", Name, Name);
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
				printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                i++;\n");
				printf("            }\n");
				printf("            info->fpt%s[j] = (FILE**)memoryAllocate(i*sizeof(FILE*), \"in init1\");\n", Name);
				printf("            info->%s[j]    = (char**)memoryAllocate(i*sizeof(char*), \"in init1\");\n", Name);
				printf("            info->flag%s[j] = i;\n", Name)
				printf("            fseek(info->fpt%sList[j], 0L, SEEK_SET);\n", Name);
				printf("            i=0;\n");
			    printf("            while(NULL!=stringGetFromFile(s, \"\", info->fpt%sList[j], stdout, 1)) {\n", Name);
				printf("                info->%s[j][i] = stringGetNthWord(s, 1, \" ,\");\n", Name);
				printf("                info->fpt%s[j][i] = fileOpen(info->%s[j][i],\"r+\");\n", Name, Name);
				printf("                i++;\n");
				printf("            }\n");
			} else if (Type=="Character") {
				printf("            info->%s = *stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
				printf("            info->flag%s++;\n", Name);
			} else if (Type=="String") {
				printf("            info->%s = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
				printf("            info->flag%s++;\n", Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
			if(i==argNumber-1) {
				printf("        }\n");
				printf("        j++;\n");
				printf("    }\n");
			}
		} else if($Importance=="Essential" || $Importance=="Optional") {
			if(i==0) {
				printf("    stringGetFromFile(s, \"\", fpt, stdout, 3);\n", Name);
			}
			printf("    if(!info->flag%s) {\n", Name);
			if(Type=="Integer") {
				printf("        info->%s = stringGetNthIntegerData(s, %d, \" \\t,\");\n", Name, i+1);
				printf("        info->flag%s++;\n", Name);
			} else if (Type=="Real") {
				printf("        info->%s = stringGetNthRealData(s, %d, \" \\t,\");\n", Name, i+1);
				printf("        info->flag%s++;\n", Name);
			} else if (Type=="inFile") {
				printf("        info->%s = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("        info->fpt%s = fileOpen(info->%s, \"r\");\n", Name, Name);
				printf("        info->flag%s++;\n", Name);
			} else if (Type=="outFile") {
				printf("        info->%s = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
                printf("        info->fpt%s = fileOpen(info->%s, \"w\");\n", Name, Name);
				printf("        info->flag%s++;\n", Name);
			} else if (Type=="inFileList") {
				printf("        info->%sList = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
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
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\");\n", Name);
				printf("            info->fpt%s[i] = fileOpen(info->%s[i],\"r\");\n", Name, Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="outFileList") {
				printf("        info->%sList = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
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
				printf("            info->%s[i] = stringGetNthWord(s, 1, \" ,\");\n", Name);
				printf("            info->fpt%s[i] = fileOpen(info->%s[i],\"w\");\n", Name, Name);
				printf("            i++;\n");
				printf("        }\n");
			} else if (Type=="Character") {
				printf("        info->%s = *stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
				printf("        info->flag%s++;\n", Name);
			} else if (Type=="String") {
				printf("        info->%s = stringGetNthWord(s, %d, \" \\t,\");\n", Name, i+1);
				printf("        info->flag%s++;\n", Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
			printf("    }\n");
		} else {
			printf("Not supported Impotance: %s\n", $Importance);
		}
		printf("    \n");
	}
}


END {
	printf("}\n");
}
