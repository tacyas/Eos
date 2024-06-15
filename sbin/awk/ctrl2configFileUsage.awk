#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#include <stdio.h>\n");
	printf("#include \"eosString.h\"\n");
	printf("#include \"File.h\"\n");
	printf("void\n");
	printf("configFileUsage(FILE* fpt)\n");
	printf("{\n");
	printf("    fprintf(fpt, \"----- Control File -----\\n\");\n");
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
		printf("    fprintf(fpt, \"%s[0or1]\");\n", Name);
	}
	printf("    fprintf(fpt, \"", Name, Type, $AdditionalMessage);
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		printf("%s[%s:%s]\\t", Name, Type, Init);
	}
	printf("\\t\\t\\t#%s\\n\");\n", $AdditionalMessage);
	if($Importance=="Variable") {
		printf("    fprintf(fpt, \"...............\\n\");\n");
	} else if($Importance=="Essential" || $Importance=="Optional") {
	} else {
		printf("Not supported Impotance: %s\n", $Importance);
	}	
}

END {
	printf("}\n");
}
