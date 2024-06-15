#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: testImage [mrcImage]\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: refImage [mrcImage]\n");
    fprintf(stderr, "    [-nRot1              nRot1               (1         ).as(Integer             ) ] :Optional  :Rotation number of Ref for Rot1: Def 1\n");
    fprintf(stderr, "    [-nRot2              nRot2               (1         ).as(Integer             ) ] :Optional  :Rotation number of Ref for Rot2: Def 1\n");
    fprintf(stderr, "    [-nRot3              nRot3               (1         ).as(Integer             ) ] :Optional  :Rotation number of Ref for Rot3: Def 1\n");
    fprintf(stderr, "    [-dRot1              dRot1               (1.0       ).as(Real                ) ] :Optional  :Delta Angle [Degree] of Ref for Rot1; Def.: 360/nRot1\n");
    fprintf(stderr, "    [-dRot2              dRot2               (1.0       ).as(Real                ) ] :Optional  :Delta Angle [Degree] of Ref for Rot2; Def.: 360/nRot2\n");
    fprintf(stderr, "    [-dRot3              dRot3               (1.0       ).as(Real                ) ] :Optional  :Delta Angle [Degree] of Ref for Rot3; Def.: 360/nRot3\n");
    fprintf(stderr, "    [-startRot1          startRot1           (0.0       ).as(Real                ) ] :Optional  :Start Angle [Degree] of Ref for Rot1; Def.: 0\n");
    fprintf(stderr, "    [-startRot2          startRot2           (0.0       ).as(Real                ) ] :Optional  :Start Angle [Degree] of Ref for Rot2; Def.: 0\n");
    fprintf(stderr, "    [-startRot3          startRot3           (0.0       ).as(Real                ) ] :Optional  :Start Angle [Degree] of Ref for Rot3; Def.: 0\n");
    fprintf(stderr, "    [-StackOrder         StackOrder          (0         ).as(Integer             ) ] :Optional  :Stack Order for Stacked 2D of references, refer to attention\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Output: Parameter [mrcImage-format]\n");
    fprintf(stderr, "    [-O[utput]           OutASC              (stdout    ).as(outFile             ) ] :Optional  :Output: Parameter [ASCII] \n");
    fprintf(stderr, "    [-cor[relation]      corFile             (NULL      ).as(outFile             ) ] :Optional  :Correation Map at Maximum (Linear) [mrcImage-format]\n");
    fprintf(stderr, "    [-cor[relation]2     corFile2            (NULL      ).as(outFile             ) ] :Optional  :Correation Map2 at Maximum (Set Mode Correlation)[mrcImage-format]\n");
    fprintf(stderr, "    [-cor[relation]All   corAllFile          (NULL      ).as(outFile             ) ] :Optional  :Correation Map with All Rotation [mrcImage-format]\n");
    fprintf(stderr, "    [-fit[tedToRef]      fitFile             (NULL      ).as(outFile             ) ] :Optional  :Output: rotatedImage at Maximum(Linear Correlation) [mrcImage]\n");
    fprintf(stderr, "    [-fit[tedToRef]2     fitFile2            (NULL      ).as(outFile             ) ] :Optional  :Output: rotatedImage at Maximum(Set Correlation mode) [mrcImage]\n");
    fprintf(stderr, "    [-RefineMode         RefineMode          (0         ).as(Integer             ) ] :Optional  :RefinementStep: Linear:0 or SetMode:1\n");
    fprintf(stderr, "    [-n[umber]           Rot                 (36        ).as(Real                ) ] :Optional  :Input: Rotation around the vertical axis against image plane: dRot = 360/n [degree]\n");
    fprintf(stderr, "    [-range              minAngle            (-5.0      ).as(Real                ) \n                         maxAngle            (5.0       ).as(Real                ) ] :Optional  :Input: SearchRange: Rotation around the vertical axis against image plane \n");
    fprintf(stderr, "    [-refStep1           refStep1            (1         ).as(Integer             ) ] :Optional  :SearchStep for Ref: Each Image along Rot1\n");
    fprintf(stderr, "    [-refStep2           refStep2            (1         ).as(Integer             ) ] :Optional  :SearchStep for Ref: Each Image along Rot2\n");
    fprintf(stderr, "    [-refStep3           refStep3            (1         ).as(Integer             ) ] :Optional  :SearchStep for Ref: Each Image along Rot3\n");
    fprintf(stderr, "    [-nRot1Area          nRot1AreaMin        (-360      ).as(Real                ) \n                         nRot1AreaMax        (360       ).as(Real                ) \n                         nRot1AreaStep       (25        ).as(Real                ) ] :Optional  :number of Ref for Rot1\n");
    fprintf(stderr, "    [-nRot2Area          nRot2AreaMin        (-360      ).as(Real                ) \n                         nRot2AreaMax        (360       ).as(Real                ) \n                         nRot2AreaStep       (25        ).as(Real                ) ] :Optional  :number of Ref for Rot2\n");
    fprintf(stderr, "    [-nRot3Area          nRot3AreaMin        (-360      ).as(Real                ) \n                         nRot3AreaMax        (360       ).as(Real                ) \n                         nRot3AreaStep       (25        ).as(Real                ) ] :Optional  :number of Ref for Rot3\n");
    fprintf(stderr, "    [-MagRange           MagRangeMin         (1.0       ).as(Real                ) \n                         MagRangeMax         (1.0       ).as(Real                ) \n                         MagRangeStep        (0.1       ).as(Real                ) ] :Optional  :Magnification Range\n");
    fprintf(stderr, "    [-Iter[ation]        Iter                (1         ).as(Integer             ) ] :Optional  :Iteration for Rotation around the vertical axis against image plane\n");
    fprintf(stderr, "    [-Method             Method              (0         ).as(Integer             ) ] :Optional  :0: Correlation, 1: SSDA\n");
    fprintf(stderr, "    [-s[earchRegion]     sminx               (0         ).as(Real                ) \n                         sminy               (0         ).as(Real                ) \n                         smaxx               (0/*N.x-1*/).as(Real                ) \n                         smaxy               (0/*N.y-1*/).as(Real                ) ] :Optional  :SearchRegion [pixel]: used in lmrcImageAutoRotationCorrelation \n");
    fprintf(stderr, "    [-Shift                                                                        ] :Optional  :Image Shift, when in > ref\n");
    fprintf(stderr, "    [-RepeatX            RepeatX             (27.3      ).as(Real                ) ] :Optional  :RepeatX[A]\n");
    fprintf(stderr, "    [-RepeatXDelta       RepeatXDelta        (5         ).as(Real                ) ] :Optional  :RepeatXDelta[A]\n");
    fprintf(stderr, "    [-RepeatY            RepeatY             (27.3      ).as(Real                ) ] :Optional  :RepeatY[A]\n");
    fprintf(stderr, "    [-RepeatYDelta       RepeatYDelta        (5         ).as(Real                ) ] :Optional  :RepeatYDelta[A]\n");
    fprintf(stderr, "    [-Xshift                                                                       ] :Optional  :X-Shift Only\n");
    fprintf(stderr, "    [-NoShift                                                                      ] :Optional  :No-Shift\n");
    fprintf(stderr, "    [-Log                Log                 (stdout    ).as(outFile             ) ] :Optional  :Output: LogFile\n");
    fprintf(stderr, "    [-pvm                pvm                 (1         ).as(Integer             ) ] :Optional  :Task Number\n");
    fprintf(stderr, "    [-pvmList            pvmList             (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
