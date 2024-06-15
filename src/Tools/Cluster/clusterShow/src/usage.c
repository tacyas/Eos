#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputData: ASCII Log: Need -i, -i2, or -ib\n");
    fprintf(stderr, "    [-i[nput]2           In2                 (NULL      ).as(inFile              ) ] :Optional  :InputData: ASCII Log2\n");
    fprintf(stderr, "    [-i[nput]b[inary]    InB                 (NULL      ).as(String              ) ] :Optional  :InputData: BinaryLog: basename\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: All\n");
    fprintf(stderr, "    [-O[utput]           Out2                (stdout    ).as(outFile             ) ] :Optional  :Output: ClusterOnly\n");
    fprintf(stderr, "    [-PS[output]         OutPS               (stdout    ).as(outFile             ) ] :Optional  :Output: ClusterForPS: Need -I\n");
    fprintf(stderr, "    [-O[utput]L[ist]     OutOL               (stdout    ).as(outFile             ) ] :Optional  :Output: ClusterList \n");
    fprintf(stderr, "    [-O[utput]T[reeInfo] TreeInfo            (NULL      ).as(outFile             ) ] :Optional  :Output: TreeInfo\n");
    fprintf(stderr, "    [-A[verage]L[ist]    OutAL               (stdout    ).as(outFile             ) \n                         OutALRange          (0         ).as(Integer             ) \n                         OutALSuffix         (avg       ).as(String              ) ] :Optional  :Output: ClusterList range\n");
    fprintf(stderr, "    [-Last[ClusterNumber]LastNum             (1         ).as(Integer             ) ] :Optional  :Last: Num\n");
    fprintf(stderr, "    [-S[cale]            ShoulderScale       (1         ).as(Real                ) \n                         ArmScale            (1         ).as(Real                ) ] :Optional  :Scale: Shoulder Arm\n");
    fprintf(stderr, "    [-P[osition]         PosX                (0         ).as(Real                ) \n                         PosY                (0         ).as(Real                ) ] :Optional  :Position: X Y\n");
    fprintf(stderr, "    [-Offset             Offset              (1         ).as(Real                ) ] :Optional  :Offset: Arm\n");
    fprintf(stderr, "    [-I[nfileList]       InList              (NULL      ).as(inFileListNoOpen    ) ] :Optional  :FileList\n");
    fprintf(stderr, "    [-Log                                                                          ] :Optional  :Arm: Log Scale\n");
    fprintf(stderr, "    [-Scaling                                                                      ] :Optional  :with Scaling\n");
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
