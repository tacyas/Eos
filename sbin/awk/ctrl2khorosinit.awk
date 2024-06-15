#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\""
	printf("#ifdef KHOROS\n");
	printf("#include <stdio.h>\n");
	printf("#include \"bootstrap.h\"\n");
	printf("#include \"dataserv.h\"\n");
	printf("#include \"datamanip.h\"\n");
	printf("extern void func_usage_additions(void);\n");
	printf("extern void func_free_args(kexit_status status, kaddr client_data);\n");
	printf("extern void func_get_args(kform* pane);\n");
	printf("\n");
	printf("void\n");
	printf("func_usage_additions(void)\n");
	printf("{\n");
	printf("}\n");
	printf("void\n");
	printf("func_free_args(kexit_status status, kaddr client_data)\n");
	printf("{\n");
	printf("}\n");
	printf("void\n");
	printf("func_get_args(kform* pane)\n", ToolName);
	printf("{\n");
	printf("}\n");
	printf("void\n");
	printf("khorosInit(int argc, char* argv[])\n");
	printf("{\n");
	printf("    char* eospath;\n");
	printf("    char  panepath[1024];\n");
	printf("    FILE* fpt;\n");
	printf("    \n");
	printf("    eospath = getenv(\"EOS_HOME\");\n");
	printf("    sprintf(panepath, \"%%s/src/Tools/%s/%s/src/%s.pane\", eospath);\n", ClassName, ToolName, ToolName);
	printf("    khoros_initialize(argc, argv, \"EOS\");\n");
	printf("    fpt = fopen(panepath, \"r\");");
	printf("    if(NULL!=fpt) {\n"); 
	printf("        fclose(fpt);\n"); 
	printf("        kclui_initialize(panepath, KGEN_NONE, \"EOS\", \"%s\",\n", ToolName);
	printf("                     func_usage_additions,\n");
	printf("                     func_get_args,\n");
	printf("                     func_free_args);\n")
	printf("    }\n");
	printf("}\n");
}

END {
	printf("#endif /* KHOROS */ \n");
}
