#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFile(mrcImage:Fourier Space)\n");
    fprintf(stderr, "    [-I[nput]            InLLNea             (NULL      ).as(inFileListNoOpen    ) \n                         InLLFar             (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFile(llData:Already separated)\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Optional  :ReferenceData(llData:Gnl(R) Space)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile(llData: Average File)\n");
    fprintf(stderr, "    [-o2[utput]          Out2                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(llData: Each Filament which has the same orientation as average)\n");
    fprintf(stderr, "    [-o3[utput]          Out3                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(llData: Difference of each filament)\n");
    fprintf(stderr, "    [-o4[utput]          Out4                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(llData: Each Filament which has the same orientaion as original filament)\n");
    fprintf(stderr, "    [-o5[utput]          Out5                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(mrcImage: P-Value)\n");
    fprintf(stderr, "    [-o6[utput]          Out6                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(mrcImage: Q-Value)\n");
    fprintf(stderr, "    [-o7[utput]          Out7                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(Text: Two subsets for resolution estimation)\n");
    fprintf(stderr, "    [-o8[utput]          Out8                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(Text: For Back Projection)\n");
    fprintf(stderr, "    [-o9[utput]          Out9                (NULL      ).as(outFileListNoOpen   ) ] :Optional  :OutputDataFileList(Text: x shift, z shift and dY information)\n");
    fprintf(stderr, "    [-comment            InComment           (NULL      ).as(String              ) ] :Optional  :Comment\n");
    fprintf(stderr, "    [-symmetry           symmetry            (1.0       ).as(Real                ) ] :Optional  :Symmetry for back projection text file\n");
    fprintf(stderr, "    [-l[ayerInfo]        llInfo              (NULL      ).as(inFileListNoOpen    ) ] :Essential :LayerLineInformation\n");
    fprintf(stderr, "    [-l[ayerInfo]final   llInfoFinal         (NULL      ).as(inFile              ) ] :Optional  :LayerLineInformation(Final)\n");
    fprintf(stderr, "    [-li[ayerInfo]       llInfoImp           (NULL      ).as(inFileListNoOpen    ) ] :Optional  :LayerLineInformationImportant\n");
    fprintf(stderr, "    [-liw[ayerInfo]      liWeight            (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer\n");
    fprintf(stderr, "    [-liwStart[ayerInfo] liWeightStart       (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer\n");
    fprintf(stderr, "    [-liwStep[ayerInfo]  liWeightStep        (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer\n");
    fprintf(stderr, "    [-la[ayerInfo]       llInfoAxis          (NULL      ).as(inFileListNoOpen    ) ] :Optional  :LayerLineInformationForAxisSearch\n");
    fprintf(stderr, "    [-law[ayerInfo]      laWeight            (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer for AS\n");
    fprintf(stderr, "    [-lawStart[ayerInfo] laWeightStart       (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer for AS\n");
    fprintf(stderr, "    [-lawStep[ayerInfo]  laWeightStep        (1.0       ).as(Real                ) ] :Optional  :Weight of Important Layer for AS\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430.0     ).as(Real                ) ] :Essential :true pitch [A]\n");
    fprintf(stderr, "    [-rMax               rMax                (100.0     ).as(Real                ) ] :Essential :rMax [A]\n");
    fprintf(stderr, "    [-rMaxMin            rMaxMin             (100.0     ).as(Real                ) ] :Optional  :rMaxMin [A]\n");
    fprintf(stderr, "    [-RMax               RMax                (0.1       ).as(Real                ) ] :Optional  :RMax [/A]\n");
    fprintf(stderr, "    [-RMaxFirst          RMaxFirst           (0.04      ).as(Real                ) ] :Optional  :RMaxFirst [/A]: Def: RMax\n");
    fprintf(stderr, "    [-RMaxStep           RMaxStep            (0.02      ).as(Real                ) ] :Optional  :RMaxStep [/A]\n");
    fprintf(stderr, "    [-RRMax              RRMax               (0.1       ).as(Real                ) ] :Optional  :Radial RMax [/A]\n");
    fprintf(stderr, "    [-RRMaxFirst         RRMaxFirst          (0.04      ).as(Real                ) ] :Optional  :Radial RMaxFirst [/A]: Def: RMax\n");
    fprintf(stderr, "    [-RRMaxStep          RRMaxStep           (0.02      ).as(Real                ) ] :Optional  :Radial RMaxStep [/A]\n");
    fprintf(stderr, "    [-delBR              delBR               (0.0002    ).as(Real                ) ] :Optional  :delBR [/A]\n");
    fprintf(stderr, "    [-rms                rms                 (1e-6      ).as(Real                ) ] :Optional  :rms:\n");
    fprintf(stderr, "    [-narrowSearch       narrowSearch        (1.0       ).as(Real                ) ] :Optional  :narrowSearch[Degree]: P-Value and Q-Value\n");
    fprintf(stderr, "    [-nextTimes          nextTimes           (1e-4      ).as(Real                ) ] :Optional  :nextTimes: rms\n");
    fprintf(stderr, "    [-maxIter[ation]     MaxIteration        (10        ).as(Integer             ) ] :Optional  :max iteration:\n");
    fprintf(stderr, "    [-maxIter2[ation]    MaxIter2            (1         ).as(Integer             ) ] :Optional  :max iteration on the same RMax and RRMax:\n");
    fprintf(stderr, "    [-maxIter3[ation]    MaxIter3            (1         ).as(Integer             ) ] :Optional  :max iteration on the same RMax, RRMax, and Weight:\n");
    fprintf(stderr, "    [-lambda             lambda              (1.0       ).as(Real                ) ] :Optional  :labda:\n");
    fprintf(stderr, "    [-ctf                CTF                 (0         ).as(Integer             ) ] :Optional  :CTF Compensation\n");
    fprintf(stderr, "    [-WhiteNoise         WhiteNoise          (0.0       ).as(Real                ) ] :Optional  :White Noise\n");
    fprintf(stderr, "    [-below              below               (90.0      ).as(Real                ) ] :Optional  :below\n");
    fprintf(stderr, "    [-noantipole                                                                   ] :Optional  :No Antipole\n");
    fprintf(stderr, "    [-magLimit                                                                     ] :Optional  :magLimit\n");
    fprintf(stderr, "    [-eachTime                                                                     ] :Optional  :each time\n");
    fprintf(stderr, "    [-continue           Continue            (NULL      ).as(inFile              ) ] :Optional  :continue\n");
    fprintf(stderr, "    [-forContinue        ForContinue         (NULL      ).as(outFile             ) ] :Optional  :For continue\n");
    fprintf(stderr, "    [-phi                phimin              (0.0       ).as(Real                ) \n                         phimax              (360.0     ).as(Real                ) \n                         delphi              (10.0      ).as(Real                ) ] :Optional  :phi:[degree]\n");
    fprintf(stderr, "    [-z                  zmin                (0.0       ).as(Real                ) \n                         zmax                (30.0      ).as(Real                ) \n                         delz                (5.0       ).as(Real                ) ] :Optional  :z:[A]\n");
    fprintf(stderr, "    [-shift              shiftmin            (-10.0     ).as(Real                ) \n                         shiftmax            (10.0      ).as(Real                ) \n                         delshift            (1.0       ).as(Real                ) ] :Optional  :shift:[A]\n");
    fprintf(stderr, "    [-log                Log                 (stdout    ).as(outFile             ) ] :Optional  :LogFile\n");
    fprintf(stderr, "    [-Normalization                                                                ] :Optional  :Normalization\n");
    fprintf(stderr, "    [-pvm                pvm                 (0         ).as(Integer             ) ] :Optional  :pvmNumber\n");
    fprintf(stderr, "    [-pvmList            pvmList             (NULL      ).as(inFile              ) ] :Optional  :pvmList\n");
    fprintf(stderr, "    [-pvmServer                                                                    ] :Optional  :Work as a server !!\n");
    fprintf(stderr, "    [-pvmClient                                                                    ] :Optional  :Work as a client !!\n");
    fprintf(stderr, "    [-wd                 WorkingDir          (./        ).as(String              ) ] :Optional  :Working Directory !!\n");
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
