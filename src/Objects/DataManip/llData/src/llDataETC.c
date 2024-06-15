#include "llData.h"

static char* RefernceData[] = {
"Amos,L.A. & Klug,A. J.Mol.Biol(1975),99,51-73",
"  Three-dimensional Image Reconstructions of the Contractile Tail of T4 Bacteriophage",
"  Appendix: Combination of Data from Helical Particles : Correlation and Selection",
"              Amos,L.A",
"              delta(theta)= -n*delta(phi) + 2*PI*Z*delta(z)",
"                Klug,A. Crick,A., F.H.C. & Wyckoff,H.W. Acta Crystallogr.sect.(1958),11,199-213",
NULL
}; 

void
printLLDataRefernceData(FILE* fpt, llDataParaTypeInteger mode)
{
  int i;
  i=0;
  while(NULL!=RefernceData[i]) {
    fprintf(fpt, "%s\n", llDataReferenceData[i]);
    i++;
  }
}
