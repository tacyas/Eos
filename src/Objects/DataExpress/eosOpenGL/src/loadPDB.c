#include <stdlib.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "pdbFile.h"

void newPDBload(pdbFile* loadpdb)
{
	FILE* fptInPDB2;
	char loadfile[50];

	fprintf(stdout, "input load file:");
	scanf("%s", loadfile);

	fptInPDB2=fopen(loadfile, "r");
	if(NULL==fptInPDB2){
		fprintf(stderr, "FileNotOpend: %s\n", loadfile);
		exit(EXIT_FAILURE);
	}

	pdbFileRead(fptInPDB2, loadpdb);

	fprintf(stdout, "atom:%d\n", loadpdb->nAtom);

	fclose(fptInPDB2);
}
