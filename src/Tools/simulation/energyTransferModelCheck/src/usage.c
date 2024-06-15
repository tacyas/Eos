#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-p[db]              PDB                 (NULL      ).as(inFile              ) ] :Optional  :Excluded Area by PDB: Input[PDB]\n");
    fprintf(stderr, "    [-P[dbs]             PDBs                (NULL      ).as(inFileList          ) ] :Optional  :Excluded Area by PDB: Input[PDBFileList]\n");
    fprintf(stderr, "    [-P[DBs]W[ithInfo]                                                             ] :Optional  :PDBFileList With Info: filename sigma[A]\n");
    fprintf(stderr, "    [-sigma              sigma               (1.0       ).as(Real                ) ] :Optional  :SigmaOfAtom for All: sigma [pixel]x delta[A/pixel]\n");
    fprintf(stderr, "    [-sigmaA             sigmaA              (1.0       ).as(Real                ) ] :Optional  :SigmaOfAtom for All: sigma [A]\n");
    fprintf(stderr, "    [-mrc                MRC                 (NULL      ).as(inFile              ) ] :Optional  :Excluded Area by mrc: Input[MRC]\n");
    fprintf(stderr, "    [-MRC                MRCs                (NULL      ).as(inFileList          ) ] :Optional  :Excluded Area by MRC: Input[MRCFileList]\n");
    fprintf(stderr, "    [-MRCW[ithInfo]                                                                ] :Optional  :MRCFileList with Info: filename contour near[A]\n");
    fprintf(stderr, "    [-C[ontour]          EContour            (10.       ).as(Real                ) ] :Optional  :ContourLevel for Exclusion: Density<ContourLevel -> 0\n");
    fprintf(stderr, "    [-Near               ENear               (1.        ).as(Real                ) ] :Optional  :Near [pixel]: Exclusion Area: near[pixel] x delta [A/pixel]\n");
    fprintf(stderr, "    [-NearA              ENearA              (1.        ).as(Real                ) ] :Optional  :Near [A]: Exclusion Area: near [A]\n");
    fprintf(stderr, "    [-r[estrict]         Rest                (NULL      ).as(inFile              ) ] :Optional  :Restricted Area: Input[mrc]\n");
    fprintf(stderr, "    [-R[estrict]         Rests               (NULL      ).as(inFileList          ) ] :Optional  :Restricted Area: InputDataFileList[mrcs]\n");
    fprintf(stderr, "    [-contour            Contour             (10.       ).as(Real                ) ] :Optional  :ContourLevel for Restriction\n");
    fprintf(stderr, "    [-near               Near                (1.        ).as(Real                ) ] :Optional  :Near [pixel]: Restriction Area: near[pixel] x delta [A/pixel]\n");
    fprintf(stderr, "    [-nearA              NearA               (1.        ).as(Real                ) ] :Optional  :Near [A]: Restriction Area: near[A] \n");
    fprintf(stderr, "    [-R[estrictWithInfo]                                                           ] :Optional  :WithInfo: filename contour near[A]\n");
    fprintf(stderr, "    [-r[estrict]P        RestP               (NULL      ).as(inFile              ) ] :Optional  :Restricted Area: InputDataFile[pdb]\n");
    fprintf(stderr, "    [-R[estrict]P        RestsP              (NULL      ).as(inFileList          ) ] :Optional  :Restricted Area: InputDataFileList[pdbs]: format: filename near[pixel]\n");
    fprintf(stderr, "    [-sigmaP             SigmaP              (1.        ).as(Real                ) ] :Optional  :Sigma[pixel]: Restriction Area: sigma x delta [A]\n");
    fprintf(stderr, "    [-sigmaPA            SigmaPA             (1.        ).as(Real                ) ] :Optional  :Sigma[A]: Restriction Area: sigma [A]\n");
    fprintf(stderr, "    [-nearP              NearP               (1.        ).as(Real                ) ] :Optional  :Near [pixel]: Restriction Area: near x delta [A]\n");
    fprintf(stderr, "    [-nearPA             NearPA              (1.        ).as(Real                ) ] :Optional  :Near [A]: Restriction Area: near [A]\n");
    fprintf(stderr, "    [-R[estrict]PW                                                                 ] :Optional  :WithInfo: filename near[A] sigma[A]\n");
    fprintf(stderr, "    [-delta              deltax              (5         ).as(Real                ) \n                         deltay              (5         ).as(Real                ) \n                         deltaz              (5         ).as(Real                ) ] :Optional  :delta [A]\n");
    fprintf(stderr, "    [-sdelta             sdeltax             (5         ).as(Real                ) \n                         sdeltay             (5         ).as(Real                ) \n                         sdeltaz             (5         ).as(Real                ) ] :Optional  :starting delta [A]\n");
    fprintf(stderr, "    [-start              startx              (5         ).as(Real                ) \n                         starty              (5         ).as(Real                ) \n                         startz              (5         ).as(Real                ) ] :Optional  :start [A]\n");
    fprintf(stderr, "    [-end                endx                (5         ).as(Real                ) \n                         endy                (5         ).as(Real                ) \n                         endz                (5         ).as(Real                ) ] :Optional  :end [A]\n");
    fprintf(stderr, "    [-maxIter            maxIter             (1         ).as(Integer             ) ] :Optional  :Max Iteration \n");
    fprintf(stderr, "    [-startIter          startIter           (0         ).as(Integer             ) ] :Optional  :Start Iteration \n");
    fprintf(stderr, "    [-neglect            neglect             (1e-4      ).as(Real                ) ] :Optional  :neglect: probability for each term: not final probability\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    additionalUsage();
}

void
htmlBeforeUsage(char* thisProgram)
{
    fprintf(stderr, "<HTML>\n");
    fprintf(stderr, "<HEAD>\n");
    fprintf(stderr, "<TITLE>%s</TITLE>\n", thisProgram);
    fprintf(stderr, "</HEAD>\n");
    fprintf(stderr, "<BODY>\n");
    fprintf(stderr, "<H1>%s</H1>\n", thisProgram);
    fprintf(stderr, "<H2>Usage</H2>\n");
    fprintf(stderr, "<PRE>\n");
}

void
htmlAfterUsage(char* thisProgram)
{
    fprintf(stderr, "</PRE>\n");
    fprintf(stderr, "</BODY>\n");
    fprintf(stderr, "</HTML>\n");
}
