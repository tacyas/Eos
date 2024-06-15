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
	printf("argCheck(%sInfo* info, int argc, char* argv[])\n", ToolName);
	printf("{\n");
	printf("    long i;\n");
	printf("    char s[1024];\n");
	printf("    FILE* fpt;\n");
	printf("    \n");
	printf("    if(NULL==(fpt=fopen(\"%s\", \"a+\"))) { \n", ".EosLog");
	printf("        \n");
	printf("    } else {\n");
	printf("        for(i=0; i<argc; i++) {\n");
	printf("            fprintf(fpt, \"%%s \", argv[i]);\n");
	printf("        }\n");
	printf("        fprintf(fpt, \"\\n\");\n");
	printf("        fclose(fpt);\n");
	printf("    }\n");
	printf("    for(i=1; i<argc; i++) {\n");
	printf("        if(OPTION_FLAG==argv[i][OPTION_FLAG_POS]) {\n");
	printf("            SSWITCH(argv[i]+OPTION_POS)\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();
	printf("                SCASE(\"%s\") {\n", substr($OptionField, 2));
	printf("                    if(i+%d<argc) {\n", argNumber);
	if(argNumber==0) {
		sub(/^-/, "", $FullOptionField)
		gsub(/\[|\]/, "", $FullOptionField)
		printf("                        info->%s++;\n", $FullOptionField);
	}
	if($Importance=="Variable") {
		printf("                        {\n");
		printf("                        int j, nv, check, count, nitem;\n");
		printf("                        nv    = argc - i - 1;\n");
		printf("                        nitem = %d ;\n", argNumber);
		printf("                        check = nv%nitem ;\n");
		printf("                        count = nv/nitem ;\n");
		printf("                        if(0!=check) { fprintf(stderr, \"Variable Number is strange. The number must be %%d-times. nv: %%d i\\n\", nitem, nv); usage(argv[0]); exit(EXIT_FAILURE);} \n");
		for(i=0; i<argNumber; i++) {
			getEachField(i);
			if(Type=="Integer") {
				printf("                        info->%s = (long*)memoryAllocate(sizeof(long)*count, \"in argCheck\");\n", Name);
			} else if(Type=="Real") { 
				printf("                        info->%s = (float*)memoryAllocate(sizeof(float)*count, \"in argCheck\");\n", Name);
			} else if(Type=="outFile"   || Type=="outFileNoOpen" \
			        ||Type=="inFile"    || Type=="inFileNoOpen" \
					||Type=="appendFile"|| Type=="appendFileNoOpen"  ) {
				printf("                        info->%s = (char**)memoryAllocate(sizeof(char*)*count, \"in argCheck\");\n", Name);
			} else if(Type=="outFileList"   || Type=="outFileListNoOpen" \
			        ||Type=="inFileList"    || Type=="inFileListNoOpen" \
					||Type=="appendFileList"|| Type=="appendFileListNoOpen"  ) {
				printf("                        info->%s = (char***)memoryAllocate(sizeof(char**)*count, \"in argCheck\");\n", Name);
			} else if(Type=="Character") {
				printf("                        info->%s = (char*)memoryAllocate(sizeof(char)*count, \"in argCheck\");\n", Name);
			} else if(Type=="String") {
				printf("                        info->%s = (char**)memoryAllocate(sizeof(char*)*count, \"in argCheck\");\n", Name);
			} else if(Type=="StringAll") {
				printf("                        info->%s = (char**)memoryAllocate(sizeof(char*)*count, \"in argCheck\");\n", Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
		}
	}	
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		if($Importance=="Variable") {
			if(Type=="Integer") {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = stringGetNthIntegerData(argv[i+j*nitem+1], 1, \" ,\");\n", Name);
				printf("                        }\n");
			} else if(Type=="Real") { 
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, \" ,\");\n", Name, i);
				printf("                        }\n");
			} else if(Type=="outFile"   || Type=="outFileNoOpen" \
			        ||Type=="inFile"    || Type=="inFileNoOpen" \
					||Type=="appendFile"|| Type=="appendFileNoOpen"  ) {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = stringGetNthWord(argv[i+j*nitem+1], 1, \" ,\");\n", Name, i);
				printf("                        }\n");
			} else if(Type=="outFileList"   || Type=="outFileListNoOpen" \
			        ||Type=="inFileList"    || Type=="inFileListNoOpen" \
					||Type=="appendFileList"|| Type=="appendFileListNoOpen"  ) {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%sList[j] = stringGetNthWord(argv[i+j*nitem+1], 1, \" ,\");\n", Name, i);
				printf("                        }\n");
			} else if(Type=="Character") {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = argv[i+j*nitem+1][0];\n", Name, i);
				printf("                        }\n");
			} else if(Type=="String") {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = stringGetNthWord(argv[i+j*nitem+1], 1, \" ,\");\n", Name, i);
				printf("                        }\n");
			} else if(Type=="StringAll") {
				printf("                        for(j=0; j<count; j++) {\n");
				printf("                            info->%s[j] = strdup(argv[i+j*nitem+1]);\n", Name, i);
				printf("                        }\n");
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
			printf("                        i++;\n");
			printf("                        info->flag%s=count;\n", Name);
		} else if($Importance="Essential" || $Importance="Optional") {
			if(Type=="Integer") {
				printf("                        info->%s = stringGetNthIntegerData(argv[i+1], 1, \" ,\");\n", Name);
			} else if(Type=="Real") { 
				printf("                        info->%s = stringGetNthRealData(argv[i+1], 1, \" ,\");\n", Name);
			} else if(Type=="outFile"    || Type=="outFileNoOpen" \
			       || Type=="inFile"     || Type=="inFileNoOpen"  \
			       || Type=="appendFile" || Type=="appendFileNoOpen") {
				printf("                        info->%s = stringGetNthWord(argv[i+1], 1, \" ,\");\n", Name);
			} else if(Type=="outFileList"    || Type=="outFileListNoOpen" \
			       || Type=="inFileList"     || Type=="inFileListNoOpen"  \
			       || Type=="appendFileList" || Type=="appendFileListNoOpen") {
				printf("                        info->%sList = stringGetNthWord(argv[i+1], 1, \" ,\");\n", Name);
			} else if(Type=="Character") {
				printf("                        info->%s = argv[i+1][0];\n", Name);
			} else if(Type=="String") {
				printf("                        info->%s = stringGetNthWord(argv[i+1], 1, \" ,\");\n", Name);
			} else if(Type=="StringAll") {
				printf("                        info->%s = strdup(argv[i+1]);\n", Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
			printf("                        i++;\n", Name);
			printf("                        info->flag%s++;\n", Name);
		}else {
			printf("Unsupported Importance: %s\n", Importance);	
		}
	}
	if($Importance=="Variable") {
		printf("                        }\n");
	}	
	printf("                    } else {\n");
	printf("                        usage(argv[0]);\n");
	printf("                        exit(EXIT_FAILURE);\n");
	printf("                    }\n");
	printf("                    SBREAK;\n");
	printf("                }\n");
}

END {
	printf("                SCASE(\"h\") {\n");
	printf("                    usage(argv[0]);\n");
	printf("                    exit(EXIT_SUCCESS);\n");
	printf("                    break;\n");
	printf("                }\n");
	printf("                SCASE(\"html\") {\n");
	printf("                    htmlBeforeUsage(argv[0]);\n");
	printf("                    usage(argv[0]);\n");
	printf("                    htmlAfterUsage(argv[0]);\n");
	printf("                    exit(EXIT_SUCCESS);\n");
	printf("                    break;\n");
	printf("                }\n");
	printf("                SDEFAULT {\n");
	printf("                    fprintf(stderr, \"Not Supported Options: :%%s\\n\", argv[i]);\n");
	printf("                    usage(argv[0]);\n");
	printf("                    exit(EXIT_FAILURE);\n");
	printf("                    break;\n");
	printf("                }\n");
	printf("            SSWITCHEND;\n");
	printf("        } \n");
	printf("    } \n");
	printf("} \n");
}
