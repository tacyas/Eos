#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#ifndef %s_H\n", toupper(ToolName));
	printf("#define %s_H\n", toupper(ToolName));
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n");
	printf("\n");
	printf("#define OPTION_FLAG     '-'\n");
	printf("#define OPTION_FLAG_POS (0)\n");
	printf("#define OPTION_POS      (1)\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("typedef struct %sInfo {\n", ToolName);
	printf("    long flagRedirect;\n");
	printf("\n");
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex();
	if(argNumber==0) {
		sub(/^-/, "", $FullOptionField)
		gsub(/\[|\]/, "", $FullOptionField)
		printf("    long %s;\n\n", $FullOptionField);
	}
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		printf("    long flag%s;\n", Name);
		if($Importance=="Variable") {
			if(Type=="Integer") {
				printf("    long* %s;\n",      Name);
			} else if (Type=="Real") {
				printf("    float* %s;\n",     Name);
			} else if (Type=="inFile"    || Type=="inFileNoOpen" \
			        || Type=="outFile"   || Type=="outFileNoOpen" \
			        || Type=="appendFile"|| Type=="appendFileNoOpen") { 
				printf("    char** %s;\n",     Name);
				printf("    FILE** fpt%s;\n",  Name);
			} else if (Type=="inFileList"    || Type=="inFileListNoOpen" \
			        || Type=="outFileList"   || Type=="outFileListNoOpen" \
			        || Type=="appendFileList"|| Type=="appendFileListNoOpen") { 
				printf("    char*** %s;\n",    Name);
				printf("    char** %sList;\n",    Name);
				printf("    FILE*** fpt%s;\n", Name);
				printf("    FILE** fpt%sList;\n", Name);
			} else if (Type=="Character") {
				printf("    char*  %s;\n",     Name);
			} else if (Type=="String") {
				printf("    char** %s;\n",     Name);
			} else if (Type=="StringAll") {
				printf("    char** %s;\n",     Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
		} else if($Importance=="Essential" || $Importance=="Optional") {
			if(Type=="Integer") {
				printf("    long %s;\n",      Name);
			} else if (Type=="Real") {
				printf("    float %s;\n",     Name);
			} else if (Type=="inFile"    || Type=="inFileNoOpen" \
			        || Type=="outFile"   || Type=="outFileNoOpen" \
			        || Type=="appendFile"|| Type=="appendFileNoOpen") { 
				printf("    char* %s;\n",     Name);
				printf("    FILE* fpt%s;\n",  Name);
			} else if (Type=="inFileList"    || Type=="inFileListNoOpen" \
			        || Type=="outFileList"   || Type=="outFileListNoOpen" \
			        || Type=="appendFileList"|| Type=="appendFileListNoOpen") { 
				printf("    char** %s;\n",    Name);
				printf("    char* %sList;\n", Name);
				printf("    FILE** fpt%s;\n", Name);
				printf("    FILE* fpt%sList;\n", Name);
			} else if (Type=="Character") {
				printf("    char  %s;\n",     Name);
			} else if (Type=="String") {
				printf("    char* %s;\n",     Name);
			} else if (Type=="StringAll") {
				printf("    char* %s;\n",     Name);
			} else {
				printf("Unsupported Type:%s\n", Name)
			}
		} else {
			printf("Not supported Impotance: %s\n", $Importance);
		}
		printf("    \n");
	}
}

END {
	printf("} %sInfo;\n", ToolName);
	printf("#ifdef __cplusplus\n");
	printf("extern \"C\" {\n");
	printf("#endif\n");
	printf("extern void argCheck(%sInfo* info, int argc, char* avgv[]);\n", ToolName);
	printf("extern void khorosInit(int argc, char* avgv[]);\n");
	printf("extern void init0(%sInfo* info);\n", ToolName);
	printf("extern void init1(%sInfo* info);\n", ToolName);
	printf("extern void usage(char* usage);\n");
	printf("extern void additionalUsage(void);\n");
	printf("extern void htmlBeforeUsage(char* usage);\n");
	printf("extern void htmlAfterUsage(char* usage);\n");
	printf("#ifdef __cplusplus\n");
	printf("};\n");
	printf("#endif\n");
	printf("#endif /* %s_H */\n", toupper(ToolName));
}
