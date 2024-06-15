#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	argCount = 0;
	printf("-F 4.3 1 0 52x1+0+0 +0+0 'Cantata' cantata\n");
	printf("  -M 1 1 52x1+0+0 +1+0 ' ' subform\n");
	printf("    -P 1 0 52x1+0+1 +0+0 ' ' %s\n", ToolName);
	printf("      -D 1 0 9x1+0+0 'Options' _gui_options\n");
	printf("        -H 1  6x1+0+0 'License' 'license' $BOOTSTRAP/repos/license/License license\n");
	printf("        -E\n");
	printf("        -R 1 0 1 5x1+35+0 'Run' 'execute operation' $EOS/bin/%s\n", ToolName);
	printf("        -H 1  5x1+41+0 'Help' 'help page' $EOS/src/Tools/%s/%s/doc/%s.doc help\n", ClassName, ToolName, ToolName);
	printf("        -Q 1 0 5.25x1+47+0 'Close'\n")
}

/^[^#]/ && $1 ~ /^-/ {
	initFieldIndex()	

	argCount++;	

	if($Importance=="Essential") {
		vImportance=1;
	} else {
		vImportance=0;
	}
	if(argNumber==0) {
		sub(/^-/, "", $OptionField)
		printf("        -t 1 0 1 %d 0 6x1+1+%d '%s' '%s' %s\n", vImportance, argCount*1.5,
															$OptionField, 
															$AdditionalMessage, 
															$OptionField)
		next;
	} else if(argNumber==1) { 
		sub(/^-/, "", $OptionField)
		i = 0;
		getEachField(i);
		if(Type=="Integer") {
			printf("        -i 1 0 1 %d 0 -1x1+1+%f 0 0 %d 0 0 '%s' '%s' %s\n", vImportance, argCount*1.5, Init, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="Real") {
			printf("        -f 1 0 1 %d 0 -1x1+1+%f 0 0 %f 0 0 0 '%s' '%s' %s\n", vImportance, argCount*1.5, Init, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="outFile" || Type=="outFileNoOpen") {
			printf("        -O 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="inFile" || Type=="inFileNoOpen") {
			printf("        -I 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="appendFile" || Type=="appendFileNoOpen") {
			printf("        -I 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="outFileList" || Type=="outFileListNoOpen") {
			printf("        -O 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="inFileList"  || Type=="inFileListNoOpen") {
			printf("        -I 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="appendFileList" || Type=="appendFileListNoOpen") {
			printf("        -I 1 0 1 %d 0 1 -1x1+1+%f ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="Character") {
			printf("        -s 1 0 1 %d 0 -1x1+1+%f 0 0 %d 0 0 '%s' '%s' %s\n", vImportance, argCount*1.5, Init, Name, $AdditionalMessage, $OptionField)
		} else if(Type=="String") {
			printf("        -s 1 0 1 %d 0 -1x1+1+%f 0 0 %d 0 0 '%s' '%s' %s\n", vImportance, argCount*1.5, Init, Name, $AdditionalMessage, $OptionField)
		} else {
			printf("Unsupported Type:%s\n", Name)
		}
	} else {
		sub(/^-/, "", $OptionField)
		i = 0;
		getEachField(i);
		printf("        -I  1 0 %d 1 0 1 -1x1+1+%d ' ' '%s' '%s' %s\n", vImportance, argCount*1.5, Init, Name, $AdditionalMessage, $OptionField)
	}
}

END {
	printf("    -E\n");
	printf("  -E\n");
	printf("-E\n");
}
