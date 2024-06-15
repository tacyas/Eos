/*
# vectorImageNearestNeighborMethod : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : vectorImageNearestNeighborMethod
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
//#include <time.h>
#include "File.h"

#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
//#include "vectorImage.h"
#include "mrcImage.h"
#include "../inc/vectorImageNearestNeighborMethod.h"
#define LIMIT 500
#define eigenValueFile "eigenValue.txt"

typedef struct lvectorImageNearestNeighborMethodInfo {
	int* classes;
	int** className;
	double* distance;
	double* upperDistanceRate; 
	int** lowCorrelationClassName;

/*	long flageigenWeight;
	char eigenWeight[1024];
	FILE* fpteigenWeight;   */

	long flagOutClassificationIntegrationRate ;
	char OutClassificationIntegrationRate[1024] ;
	FILE* fptOutClassificationIntegrationRate ;
} lvectorImageNearestNeighborMethodInfo;

/*
typedef enum lvectorImageNearestNeighborMethodMode {
	a=0,
	b=1
} lvectorImageNearestNeighborMethodMode;
*/

#ifdef __cplusplus
    extern "C" {
#endif

void lvectorImageNearestNeighborMethod(mrcImage* In, int nIn, lvectorImageNearestNeighborMethodInfo* linfo, int mode);

#ifdef __cplusplus
     }
#endif	 

static int dim;
static int DMS;
double EW[100];
 int nEW=0;
 FILE *fp_in;

int
main(int argc, char* argv[]) 
{
	vectorImageNearestNeighborMethodInfo info;
	lvectorImageNearestNeighborMethodInfo linfo;
	 mrcImage* In;
	 int i;

	DEBUGPRINT("Program Start\n");
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if((fp_in=fopen(eigenValueFile,"r"))==NULL){
		printf("No eigenValueFile\n");
	}

	In  = (mrcImage*)MemoryAllocate(mrcImage, info.flagInList, "in main");
	for(i=0; i<info.flagInList; i++) {
		mrcFileRead(&In[i], info.InList[i], "in main", 0);
		 if(i%1000==0)
		 	DEBUGPRINT1("mrcFileRead  %d th Read\n",i);
	}

//	linfo.fpteigenWeight = NULL;
//	linfo.flageigenWeight = 0;
//	if(info.flageigenWeight){
/*		sprintf(linfo.eigenWeight, "%s", info.eigenWeight);
		linfo.flageigenWeight = 1;
		linfo.fpteigenWeight = fileOpen(linfo.eigenWeight, "w");
		linfo.fpteigenWeight = info.fpteigenWeight ;  */
		for(i=0;i<100;i++){
			EW[i]=0;
		}

		while(fscanf(fp_in,"%lf",&EW[nEW])!=EOF){
			DEBUGPRINT1("%lf\n",EW[nEW]);
			nEW++;
		}

		for(i=0;i<100;i++){
			if(i>nEW){
				EW[i]=0.0;
			}
		}
//	}

	linfo.fptOutClassificationIntegrationRate = NULL;
	linfo.flagOutClassificationIntegrationRate = 0;
	if(info.flagOutClassificationIntegrationRate){
		sprintf(linfo.OutClassificationIntegrationRate, "%s", info.OutClassificationIntegrationRate);
		linfo.flagOutClassificationIntegrationRate = 1;
		linfo.fptOutClassificationIntegrationRate = fileOpen(linfo.OutClassificationIntegrationRate, "w");
		linfo.fptOutClassificationIntegrationRate = info.fptOutClassificationIntegrationRate ;
	}


	lvectorImageNearestNeighborMethod(In, info.flagInList, &linfo, 0);
	DEBUGPRINT("check1\n");
	 if(info.flagOutClassName) {
	 	for(i=0;i<info.flagInList;i++){
			//fprintf(info.fptOutClassName,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d\n",linfo.className[i][0],linfo.className[i][1],linfo.className[i][2],linfo.className[i][3],linfo.className[i][4],linfo.className[i][5],linfo.className[i][6],linfo.className[i][7],linfo.className[i][8],linfo.className[i][9],linfo.className[i][10],linfo.className[i][11],linfo.className[i][12],linfo.className[i][13],linfo.className[i][14],linfo.className[i][15],linfo.className[i][16],linfo.className[i][17],linfo.className[i][18],linfo.className[i][19],linfo.className[i][20],linfo.className[i][21],linfo.className[i][22],linfo.className[i][23],linfo.className[i][24],linfo.className[i][25],linfo.className[i][26],linfo.className[i][27],linfo.className[i][28],linfo.className[i][29],linfo.className[i][30],linfo.className[i][31],linfo.className[i][32],linfo.className[i][33],linfo.className[i][34],linfo.className[i][35],linfo.className[i][36],linfo.className[i][37],linfo.className[i][38],linfo.className[i][39],linfo.className[i][40],linfo.className[i][41],linfo.className[i][42],linfo.className[i][43],linfo.className[i][44],linfo.className[i][45],linfo.className[i][46],linfo.className[i][47],linfo.className[i][48],linfo.className[i][49]);
			fprintf(info.fptOutClassName,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d\n",linfo.className[i][0],linfo.className[i][1],linfo.className[i][2],linfo.className[i][3],linfo.className[i][4],linfo.className[i][5],linfo.className[i][6],linfo.className[i][7],linfo.className[i][8],linfo.className[i][9],linfo.className[i][10],linfo.className[i][11],linfo.className[i][12],linfo.className[i][13],linfo.className[i][14],linfo.className[i][15],linfo.className[i][16],linfo.className[i][17],linfo.className[i][18],linfo.className[i][19],linfo.className[i][20],linfo.className[i][21],linfo.className[i][22],linfo.className[i][23],linfo.className[i][24],linfo.className[i][25],linfo.className[i][26],linfo.className[i][27],linfo.className[i][28],linfo.className[i][29],linfo.className[i][30],linfo.className[i][31],linfo.className[i][32],linfo.className[i][33],linfo.className[i][34],linfo.className[i][35],linfo.className[i][36],linfo.className[i][37],linfo.className[i][38],linfo.className[i][39],linfo.className[i][40],linfo.className[i][41],linfo.className[i][42],linfo.className[i][43],linfo.className[i][44],linfo.className[i][45],linfo.className[i][46],linfo.className[i][47],linfo.className[i][48],linfo.className[i][49],linfo.className[i][50],linfo.className[i][51],linfo.className[i][52],linfo.className[i][53],linfo.className[i][54],linfo.className[i][55],linfo.className[i][56],linfo.className[i][57],linfo.className[i][58],linfo.className[i][59],linfo.className[i][60],linfo.className[i][61],linfo.className[i][62],linfo.className[i][63],linfo.className[i][64],linfo.className[i][65],linfo.className[i][66],linfo.className[i][67],linfo.className[i][68],linfo.className[i][69],linfo.className[i][70],linfo.className[i][71],linfo.className[i][72],linfo.className[i][73],linfo.className[i][74],linfo.className[i][75],linfo.className[i][76],linfo.className[i][77],linfo.className[i][78],linfo.className[i][79],linfo.className[i][80],linfo.className[i][81],linfo.className[i][82],linfo.className[i][83],linfo.className[i][84],linfo.className[i][85],linfo.className[i][86],linfo.className[i][87],linfo.className[i][88],linfo.className[i][89],linfo.className[i][90],linfo.className[i][91],linfo.className[i][92],linfo.className[i][93],linfo.className[i][94],linfo.className[i][95],linfo.className[i][96],linfo.className[i][97],linfo.className[i][98],linfo.className[i][99],linfo.className[i][100],linfo.className[i][101],linfo.className[i][102],linfo.className[i][103],linfo.className[i][104],linfo.className[i][105],linfo.className[i][106],linfo.className[i][107],linfo.className[i][108],linfo.className[i][109],linfo.className[i][110],linfo.className[i][111],linfo.className[i][112],linfo.className[i][113],linfo.className[i][114],linfo.className[i][115],linfo.className[i][116],linfo.className[i][117],linfo.className[i][118],linfo.className[i][119],linfo.className[i][120],linfo.className[i][121],linfo.className[i][122],linfo.className[i][123],linfo.className[i][124],linfo.className[i][125],linfo.className[i][126],linfo.className[i][127],linfo.className[i][128],linfo.className[i][129],linfo.className[i][130],linfo.className[i][131],linfo.className[i][132],linfo.className[i][133],linfo.className[i][134],linfo.className[i][135],linfo.className[i][136],linfo.className[i][137],linfo.className[i][138],linfo.className[i][139],linfo.className[i][140],linfo.className[i][141],linfo.className[i][142],linfo.className[i][143],linfo.className[i][144],linfo.className[i][145],linfo.className[i][146],linfo.className[i][147],linfo.className[i][148],linfo.className[i][149],linfo.className[i][150],linfo.className[i][151],linfo.className[i][152],linfo.className[i][153],linfo.className[i][154],linfo.className[i][155],linfo.className[i][156],linfo.className[i][157],linfo.className[i][158],linfo.className[i][159],linfo.className[i][160],linfo.className[i][161],linfo.className[i][162],linfo.className[i][163],linfo.className[i][164],linfo.className[i][165],linfo.className[i][166],linfo.className[i][167],linfo.className[i][168],linfo.className[i][169],linfo.className[i][170],linfo.className[i][171],linfo.className[i][172],linfo.className[i][173],linfo.className[i][174],linfo.className[i][175],linfo.className[i][176],linfo.className[i][177],linfo.className[i][178],linfo.className[i][179],linfo.className[i][180],linfo.className[i][181],linfo.className[i][182],linfo.className[i][183],linfo.className[i][184],linfo.className[i][185],linfo.className[i][186],linfo.className[i][187],linfo.className[i][188],linfo.className[i][189],linfo.className[i][190],linfo.className[i][191],linfo.className[i][192],linfo.className[i][193],linfo.className[i][194],linfo.className[i][195],linfo.className[i][196],linfo.className[i][197],linfo.className[i][198],linfo.className[i][199],linfo.className[i][200],linfo.className[i][201],linfo.className[i][202],linfo.className[i][203],linfo.className[i][204],linfo.className[i][205],linfo.className[i][206],linfo.className[i][207],linfo.className[i][208],linfo.className[i][209],linfo.className[i][210],linfo.className[i][211],linfo.className[i][212],linfo.className[i][213],linfo.className[i][214],linfo.className[i][215],linfo.className[i][216],linfo.className[i][217],linfo.className[i][218],linfo.className[i][219],linfo.className[i][220],linfo.className[i][221],linfo.className[i][222],linfo.className[i][223],linfo.className[i][224],linfo.className[i][225],linfo.className[i][226],linfo.className[i][227],linfo.className[i][228],linfo.className[i][229],linfo.className[i][230],linfo.className[i][231],linfo.className[i][232],linfo.className[i][233],linfo.className[i][234],linfo.className[i][235],linfo.className[i][236],linfo.className[i][237],linfo.className[i][238],linfo.className[i][239],linfo.className[i][240],linfo.className[i][241],linfo.className[i][242],linfo.className[i][243],linfo.className[i][244],linfo.className[i][245],linfo.className[i][246],linfo.className[i][247],linfo.className[i][248],linfo.className[i][249],linfo.className[i][250],linfo.className[i][251],linfo.className[i][252],linfo.className[i][253],linfo.className[i][254],linfo.className[i][255],linfo.className[i][256],linfo.className[i][257],linfo.className[i][258],linfo.className[i][259],linfo.className[i][260],linfo.className[i][261],linfo.className[i][262],linfo.className[i][263],linfo.className[i][264],linfo.className[i][265],linfo.className[i][266],linfo.className[i][267],linfo.className[i][268],linfo.className[i][269],linfo.className[i][270],linfo.className[i][271],linfo.className[i][272],linfo.className[i][273],linfo.className[i][274],linfo.className[i][275],linfo.className[i][276],linfo.className[i][277],linfo.className[i][278],linfo.className[i][279],linfo.className[i][280],linfo.className[i][281],linfo.className[i][282],linfo.className[i][283],linfo.className[i][284],linfo.className[i][285],linfo.className[i][286],linfo.className[i][287],linfo.className[i][288],linfo.className[i][289],linfo.className[i][290],linfo.className[i][291],linfo.className[i][292],linfo.className[i][293],linfo.className[i][294],linfo.className[i][295],linfo.className[i][296],linfo.className[i][297],linfo.className[i][298],linfo.className[i][299],linfo.className[i][300],linfo.className[i][301],linfo.className[i][302],linfo.className[i][303],linfo.className[i][304],linfo.className[i][305],linfo.className[i][306],linfo.className[i][307],linfo.className[i][308],linfo.className[i][309],linfo.className[i][310],linfo.className[i][311],linfo.className[i][312],linfo.className[i][313],linfo.className[i][314],linfo.className[i][315],linfo.className[i][316],linfo.className[i][317],linfo.className[i][318],linfo.className[i][319],linfo.className[i][320],linfo.className[i][321],linfo.className[i][322],linfo.className[i][323],linfo.className[i][324],linfo.className[i][325],linfo.className[i][326],linfo.className[i][327],linfo.className[i][328],linfo.className[i][329],linfo.className[i][330],linfo.className[i][331],linfo.className[i][332],linfo.className[i][333],linfo.className[i][334],linfo.className[i][335],linfo.className[i][336],linfo.className[i][337],linfo.className[i][338],linfo.className[i][339],linfo.className[i][340],linfo.className[i][341],linfo.className[i][342],linfo.className[i][343],linfo.className[i][344],linfo.className[i][345],linfo.className[i][346],linfo.className[i][347],linfo.className[i][348],linfo.className[i][349],linfo.className[i][350],linfo.className[i][351],linfo.className[i][352],linfo.className[i][353],linfo.className[i][354],linfo.className[i][355],linfo.className[i][356],linfo.className[i][357],linfo.className[i][358],linfo.className[i][359],linfo.className[i][360],linfo.className[i][361],linfo.className[i][362],linfo.className[i][363],linfo.className[i][364],linfo.className[i][365],linfo.className[i][366],linfo.className[i][367],linfo.className[i][368],linfo.className[i][369],linfo.className[i][370],linfo.className[i][371],linfo.className[i][372],linfo.className[i][373],linfo.className[i][374],linfo.className[i][375],linfo.className[i][376],linfo.className[i][377],linfo.className[i][378],linfo.className[i][379],linfo.className[i][380],linfo.className[i][381],linfo.className[i][382],linfo.className[i][383],linfo.className[i][384],linfo.className[i][385],linfo.className[i][386],linfo.className[i][387],linfo.className[i][388],linfo.className[i][389],linfo.className[i][390],linfo.className[i][391],linfo.className[i][392],linfo.className[i][393],linfo.className[i][394],linfo.className[i][395],linfo.className[i][396],linfo.className[i][397],linfo.className[i][398],linfo.className[i][399],linfo.className[i][400],linfo.className[i][401],linfo.className[i][402],linfo.className[i][403],linfo.className[i][404],linfo.className[i][405],linfo.className[i][406],linfo.className[i][407],linfo.className[i][408],linfo.className[i][409],linfo.className[i][410],linfo.className[i][411],linfo.className[i][412],linfo.className[i][413],linfo.className[i][414],linfo.className[i][415],linfo.className[i][416],linfo.className[i][417],linfo.className[i][418],linfo.className[i][419],linfo.className[i][420],linfo.className[i][421],linfo.className[i][422],linfo.className[i][423],linfo.className[i][424],linfo.className[i][425],linfo.className[i][426],linfo.className[i][427],linfo.className[i][428],linfo.className[i][429],linfo.className[i][430],linfo.className[i][431],linfo.className[i][432],linfo.className[i][433],linfo.className[i][434],linfo.className[i][435],linfo.className[i][436],linfo.className[i][437],linfo.className[i][438],linfo.className[i][439],linfo.className[i][440],linfo.className[i][441],linfo.className[i][442],linfo.className[i][443],linfo.className[i][444],linfo.className[i][445],linfo.className[i][446],linfo.className[i][447],linfo.className[i][448],linfo.className[i][449],linfo.className[i][450],linfo.className[i][451],linfo.className[i][452],linfo.className[i][453],linfo.className[i][454],linfo.className[i][455],linfo.className[i][456],linfo.className[i][457],linfo.className[i][458],linfo.className[i][459],linfo.className[i][460],linfo.className[i][461],linfo.className[i][462],linfo.className[i][463],linfo.className[i][464],linfo.className[i][465],linfo.className[i][466],linfo.className[i][467],linfo.className[i][468],linfo.className[i][469],linfo.className[i][470],linfo.className[i][471],linfo.className[i][472],linfo.className[i][473],linfo.className[i][474],linfo.className[i][475],linfo.className[i][476],linfo.className[i][477],linfo.className[i][478],linfo.className[i][479],linfo.className[i][480],linfo.className[i][481],linfo.className[i][482],linfo.className[i][483],linfo.className[i][484],linfo.className[i][485],linfo.className[i][486],linfo.className[i][487],linfo.className[i][488],linfo.className[i][489],linfo.className[i][490],linfo.className[i][491],linfo.className[i][492],linfo.className[i][493],linfo.className[i][494],linfo.className[i][495],linfo.className[i][496],linfo.className[i][497],linfo.className[i][498],linfo.className[i][499]);
		}	
	}
	//	fprintf(info.fptOutclassification,"\n");
	/*	fprintf(info.fptOutclassification,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d\n",
			linfo.classes[0],
			linfo.classes[1],
			linfo.classes[2],
			linfo.classes[3],
			linfo.classes[4],
			linfo.classes[5],
			linfo.classes[6],
			linfo.classes[7],
			linfo.classes[8],
			linfo.classes[9]
			);*/
	if(info.flagOutclassification){ 		
		for(i=0;i<info.flagInList;i++){	
			//fprintf(info.fptOutclassification,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d\n",linfo.lowCorrelationClassName[i][0],linfo.lowCorrelationClassName[i][1],linfo.lowCorrelationClassName[i][2],linfo.lowCorrelationClassName[i][3],linfo.lowCorrelationClassName[i][4],linfo.lowCorrelationClassName[i][5],linfo.lowCorrelationClassName[i][6],linfo.lowCorrelationClassName[i][7],linfo.lowCorrelationClassName[i][8],linfo.lowCorrelationClassName[i][9],linfo.lowCorrelationClassName[i][10],linfo.lowCorrelationClassName[i][11],linfo.lowCorrelationClassName[i][12],linfo.lowCorrelationClassName[i][13],linfo.lowCorrelationClassName[i][14],linfo.lowCorrelationClassName[i][15],linfo.lowCorrelationClassName[i][16],linfo.lowCorrelationClassName[i][17],linfo.lowCorrelationClassName[i][18],linfo.lowCorrelationClassName[i][19],linfo.lowCorrelationClassName[i][20],linfo.lowCorrelationClassName[i][21],linfo.lowCorrelationClassName[i][22],linfo.lowCorrelationClassName[i][23],linfo.lowCorrelationClassName[i][24],linfo.lowCorrelationClassName[i][25],linfo.lowCorrelationClassName[i][26],linfo.lowCorrelationClassName[i][27],linfo.lowCorrelationClassName[i][28],linfo.lowCorrelationClassName[i][29],linfo.lowCorrelationClassName[i][30],linfo.lowCorrelationClassName[i][31],linfo.lowCorrelationClassName[i][32],linfo.lowCorrelationClassName[i][33],linfo.lowCorrelationClassName[i][34],linfo.lowCorrelationClassName[i][35],linfo.lowCorrelationClassName[i][36],linfo.lowCorrelationClassName[i][37],linfo.lowCorrelationClassName[i][38],linfo.lowCorrelationClassName[i][39],linfo.lowCorrelationClassName[i][40],linfo.lowCorrelationClassName[i][41],linfo.lowCorrelationClassName[i][42],linfo.lowCorrelationClassName[i][43],linfo.lowCorrelationClassName[i][44],linfo.lowCorrelationClassName[i][45],linfo.lowCorrelationClassName[i][46],linfo.lowCorrelationClassName[i][47],linfo.lowCorrelationClassName[i][48],linfo.lowCorrelationClassName[i][49]);
			fprintf(info.fptOutclassification,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %4d\n",linfo.lowCorrelationClassName[i][0],linfo.lowCorrelationClassName[i][1],linfo.lowCorrelationClassName[i][2],linfo.lowCorrelationClassName[i][3],linfo.lowCorrelationClassName[i][4],linfo.lowCorrelationClassName[i][5],linfo.lowCorrelationClassName[i][6],linfo.lowCorrelationClassName[i][7],linfo.lowCorrelationClassName[i][8],linfo.lowCorrelationClassName[i][9],linfo.lowCorrelationClassName[i][10],linfo.lowCorrelationClassName[i][11],linfo.lowCorrelationClassName[i][12],linfo.lowCorrelationClassName[i][13],linfo.lowCorrelationClassName[i][14],linfo.lowCorrelationClassName[i][15],linfo.lowCorrelationClassName[i][16],linfo.lowCorrelationClassName[i][17],linfo.lowCorrelationClassName[i][18],linfo.lowCorrelationClassName[i][19],linfo.lowCorrelationClassName[i][20],linfo.lowCorrelationClassName[i][21],linfo.lowCorrelationClassName[i][22],linfo.lowCorrelationClassName[i][23],linfo.lowCorrelationClassName[i][24],linfo.lowCorrelationClassName[i][25],linfo.lowCorrelationClassName[i][26],linfo.lowCorrelationClassName[i][27],linfo.lowCorrelationClassName[i][28],linfo.lowCorrelationClassName[i][29],linfo.lowCorrelationClassName[i][30],linfo.lowCorrelationClassName[i][31],linfo.lowCorrelationClassName[i][32],linfo.lowCorrelationClassName[i][33],linfo.lowCorrelationClassName[i][34],linfo.lowCorrelationClassName[i][35],linfo.lowCorrelationClassName[i][36],linfo.lowCorrelationClassName[i][37],linfo.lowCorrelationClassName[i][38],linfo.lowCorrelationClassName[i][39],linfo.lowCorrelationClassName[i][40],linfo.lowCorrelationClassName[i][41],linfo.lowCorrelationClassName[i][42],linfo.lowCorrelationClassName[i][43],linfo.lowCorrelationClassName[i][44],linfo.lowCorrelationClassName[i][45],linfo.lowCorrelationClassName[i][46],linfo.lowCorrelationClassName[i][47],linfo.lowCorrelationClassName[i][48],linfo.lowCorrelationClassName[i][49],linfo.lowCorrelationClassName[i][50],linfo.lowCorrelationClassName[i][51],linfo.lowCorrelationClassName[i][52],linfo.lowCorrelationClassName[i][53],linfo.lowCorrelationClassName[i][54],linfo.lowCorrelationClassName[i][55],linfo.lowCorrelationClassName[i][56],linfo.lowCorrelationClassName[i][57],linfo.lowCorrelationClassName[i][58],linfo.lowCorrelationClassName[i][59],linfo.lowCorrelationClassName[i][60],linfo.lowCorrelationClassName[i][61],linfo.lowCorrelationClassName[i][62],linfo.lowCorrelationClassName[i][63],linfo.lowCorrelationClassName[i][64],linfo.lowCorrelationClassName[i][65],linfo.lowCorrelationClassName[i][66],linfo.lowCorrelationClassName[i][67],linfo.lowCorrelationClassName[i][68],linfo.lowCorrelationClassName[i][69],linfo.lowCorrelationClassName[i][70],linfo.lowCorrelationClassName[i][71],linfo.lowCorrelationClassName[i][72],linfo.lowCorrelationClassName[i][73],linfo.lowCorrelationClassName[i][74],linfo.lowCorrelationClassName[i][75],linfo.lowCorrelationClassName[i][76],linfo.lowCorrelationClassName[i][77],linfo.lowCorrelationClassName[i][78],linfo.lowCorrelationClassName[i][79],linfo.lowCorrelationClassName[i][80],linfo.lowCorrelationClassName[i][81],linfo.lowCorrelationClassName[i][82],linfo.lowCorrelationClassName[i][83],linfo.lowCorrelationClassName[i][84],linfo.lowCorrelationClassName[i][85],linfo.lowCorrelationClassName[i][86],linfo.lowCorrelationClassName[i][87],linfo.lowCorrelationClassName[i][88],linfo.lowCorrelationClassName[i][89],linfo.lowCorrelationClassName[i][90],linfo.lowCorrelationClassName[i][91],linfo.lowCorrelationClassName[i][92],linfo.lowCorrelationClassName[i][93],linfo.lowCorrelationClassName[i][94],linfo.lowCorrelationClassName[i][95],linfo.lowCorrelationClassName[i][96],linfo.lowCorrelationClassName[i][97],linfo.lowCorrelationClassName[i][98],linfo.lowCorrelationClassName[i][99],linfo.lowCorrelationClassName[i][100],linfo.lowCorrelationClassName[i][101],linfo.lowCorrelationClassName[i][102],linfo.lowCorrelationClassName[i][103],linfo.lowCorrelationClassName[i][104],linfo.lowCorrelationClassName[i][105],linfo.lowCorrelationClassName[i][106],linfo.lowCorrelationClassName[i][107],linfo.lowCorrelationClassName[i][108],linfo.lowCorrelationClassName[i][109],linfo.lowCorrelationClassName[i][110],linfo.lowCorrelationClassName[i][111],linfo.lowCorrelationClassName[i][112],linfo.lowCorrelationClassName[i][113],linfo.lowCorrelationClassName[i][114],linfo.lowCorrelationClassName[i][115],linfo.lowCorrelationClassName[i][116],linfo.lowCorrelationClassName[i][117],linfo.lowCorrelationClassName[i][118],linfo.lowCorrelationClassName[i][119],linfo.lowCorrelationClassName[i][120],linfo.lowCorrelationClassName[i][121],linfo.lowCorrelationClassName[i][122],linfo.lowCorrelationClassName[i][123],linfo.lowCorrelationClassName[i][124],linfo.lowCorrelationClassName[i][125],linfo.lowCorrelationClassName[i][126],linfo.lowCorrelationClassName[i][127],linfo.lowCorrelationClassName[i][128],linfo.lowCorrelationClassName[i][129],linfo.lowCorrelationClassName[i][130],linfo.lowCorrelationClassName[i][131],linfo.lowCorrelationClassName[i][132],linfo.lowCorrelationClassName[i][133],linfo.lowCorrelationClassName[i][134],linfo.lowCorrelationClassName[i][135],linfo.lowCorrelationClassName[i][136],linfo.lowCorrelationClassName[i][137],linfo.lowCorrelationClassName[i][138],linfo.lowCorrelationClassName[i][139],linfo.lowCorrelationClassName[i][140],linfo.lowCorrelationClassName[i][141],linfo.lowCorrelationClassName[i][142],linfo.lowCorrelationClassName[i][143],linfo.lowCorrelationClassName[i][144],linfo.lowCorrelationClassName[i][145],linfo.lowCorrelationClassName[i][146],linfo.lowCorrelationClassName[i][147],linfo.lowCorrelationClassName[i][148],linfo.lowCorrelationClassName[i][149],linfo.lowCorrelationClassName[i][150],linfo.lowCorrelationClassName[i][151],linfo.lowCorrelationClassName[i][152],linfo.lowCorrelationClassName[i][153],linfo.lowCorrelationClassName[i][154],linfo.lowCorrelationClassName[i][155],linfo.lowCorrelationClassName[i][156],linfo.lowCorrelationClassName[i][157],linfo.lowCorrelationClassName[i][158],linfo.lowCorrelationClassName[i][159],linfo.lowCorrelationClassName[i][160],linfo.lowCorrelationClassName[i][161],linfo.lowCorrelationClassName[i][162],linfo.lowCorrelationClassName[i][163],linfo.lowCorrelationClassName[i][164],linfo.lowCorrelationClassName[i][165],linfo.lowCorrelationClassName[i][166],linfo.lowCorrelationClassName[i][167],linfo.lowCorrelationClassName[i][168],linfo.lowCorrelationClassName[i][169],linfo.lowCorrelationClassName[i][170],linfo.lowCorrelationClassName[i][171],linfo.lowCorrelationClassName[i][172],linfo.lowCorrelationClassName[i][173],linfo.lowCorrelationClassName[i][174],linfo.lowCorrelationClassName[i][175],linfo.lowCorrelationClassName[i][176],linfo.lowCorrelationClassName[i][177],linfo.lowCorrelationClassName[i][178],linfo.lowCorrelationClassName[i][179],linfo.lowCorrelationClassName[i][180],linfo.lowCorrelationClassName[i][181],linfo.lowCorrelationClassName[i][182],linfo.lowCorrelationClassName[i][183],linfo.lowCorrelationClassName[i][184],linfo.lowCorrelationClassName[i][185],linfo.lowCorrelationClassName[i][186],linfo.lowCorrelationClassName[i][187],linfo.lowCorrelationClassName[i][188],linfo.lowCorrelationClassName[i][189],linfo.lowCorrelationClassName[i][190],linfo.lowCorrelationClassName[i][191],linfo.lowCorrelationClassName[i][192],linfo.lowCorrelationClassName[i][193],linfo.lowCorrelationClassName[i][194],linfo.lowCorrelationClassName[i][195],linfo.lowCorrelationClassName[i][196],linfo.lowCorrelationClassName[i][197],linfo.lowCorrelationClassName[i][198],linfo.lowCorrelationClassName[i][199],linfo.lowCorrelationClassName[i][200],linfo.lowCorrelationClassName[i][201],linfo.lowCorrelationClassName[i][202],linfo.lowCorrelationClassName[i][203],linfo.lowCorrelationClassName[i][204],linfo.lowCorrelationClassName[i][205],linfo.lowCorrelationClassName[i][206],linfo.lowCorrelationClassName[i][207],linfo.lowCorrelationClassName[i][208],linfo.lowCorrelationClassName[i][209],linfo.lowCorrelationClassName[i][210],linfo.lowCorrelationClassName[i][211],linfo.lowCorrelationClassName[i][212],linfo.lowCorrelationClassName[i][213],linfo.lowCorrelationClassName[i][214],linfo.lowCorrelationClassName[i][215],linfo.lowCorrelationClassName[i][216],linfo.lowCorrelationClassName[i][217],linfo.lowCorrelationClassName[i][218],linfo.lowCorrelationClassName[i][219],linfo.lowCorrelationClassName[i][220],linfo.lowCorrelationClassName[i][221],linfo.lowCorrelationClassName[i][222],linfo.lowCorrelationClassName[i][223],linfo.lowCorrelationClassName[i][224],linfo.lowCorrelationClassName[i][225],linfo.lowCorrelationClassName[i][226],linfo.lowCorrelationClassName[i][227],linfo.lowCorrelationClassName[i][228],linfo.lowCorrelationClassName[i][229],linfo.lowCorrelationClassName[i][230],linfo.lowCorrelationClassName[i][231],linfo.lowCorrelationClassName[i][232],linfo.lowCorrelationClassName[i][233],linfo.lowCorrelationClassName[i][234],linfo.lowCorrelationClassName[i][235],linfo.lowCorrelationClassName[i][236],linfo.lowCorrelationClassName[i][237],linfo.lowCorrelationClassName[i][238],linfo.lowCorrelationClassName[i][239],linfo.lowCorrelationClassName[i][240],linfo.lowCorrelationClassName[i][241],linfo.lowCorrelationClassName[i][242],linfo.lowCorrelationClassName[i][243],linfo.lowCorrelationClassName[i][244],linfo.lowCorrelationClassName[i][245],linfo.lowCorrelationClassName[i][246],linfo.lowCorrelationClassName[i][247],linfo.lowCorrelationClassName[i][248],linfo.lowCorrelationClassName[i][249],linfo.lowCorrelationClassName[i][250],linfo.lowCorrelationClassName[i][251],linfo.lowCorrelationClassName[i][252],linfo.lowCorrelationClassName[i][253],linfo.lowCorrelationClassName[i][254],linfo.lowCorrelationClassName[i][255],linfo.lowCorrelationClassName[i][256],linfo.lowCorrelationClassName[i][257],linfo.lowCorrelationClassName[i][258],linfo.lowCorrelationClassName[i][259],linfo.lowCorrelationClassName[i][260],linfo.lowCorrelationClassName[i][261],linfo.lowCorrelationClassName[i][262],linfo.lowCorrelationClassName[i][263],linfo.lowCorrelationClassName[i][264],linfo.lowCorrelationClassName[i][265],linfo.lowCorrelationClassName[i][266],linfo.lowCorrelationClassName[i][267],linfo.lowCorrelationClassName[i][268],linfo.lowCorrelationClassName[i][269],linfo.lowCorrelationClassName[i][270],linfo.lowCorrelationClassName[i][271],linfo.lowCorrelationClassName[i][272],linfo.lowCorrelationClassName[i][273],linfo.lowCorrelationClassName[i][274],linfo.lowCorrelationClassName[i][275],linfo.lowCorrelationClassName[i][276],linfo.lowCorrelationClassName[i][277],linfo.lowCorrelationClassName[i][278],linfo.lowCorrelationClassName[i][279],linfo.lowCorrelationClassName[i][280],linfo.lowCorrelationClassName[i][281],linfo.lowCorrelationClassName[i][282],linfo.lowCorrelationClassName[i][283],linfo.lowCorrelationClassName[i][284],linfo.lowCorrelationClassName[i][285],linfo.lowCorrelationClassName[i][286],linfo.lowCorrelationClassName[i][287],linfo.lowCorrelationClassName[i][288],linfo.lowCorrelationClassName[i][289],linfo.lowCorrelationClassName[i][290],linfo.lowCorrelationClassName[i][291],linfo.lowCorrelationClassName[i][292],linfo.lowCorrelationClassName[i][293],linfo.lowCorrelationClassName[i][294],linfo.lowCorrelationClassName[i][295],linfo.lowCorrelationClassName[i][296],linfo.lowCorrelationClassName[i][297],linfo.lowCorrelationClassName[i][298],linfo.lowCorrelationClassName[i][299],linfo.lowCorrelationClassName[i][300],linfo.lowCorrelationClassName[i][301],linfo.lowCorrelationClassName[i][302],linfo.lowCorrelationClassName[i][303],linfo.lowCorrelationClassName[i][304],linfo.lowCorrelationClassName[i][305],linfo.lowCorrelationClassName[i][306],linfo.lowCorrelationClassName[i][307],linfo.lowCorrelationClassName[i][308],linfo.lowCorrelationClassName[i][309],linfo.lowCorrelationClassName[i][310],linfo.lowCorrelationClassName[i][311],linfo.lowCorrelationClassName[i][312],linfo.lowCorrelationClassName[i][313],linfo.lowCorrelationClassName[i][314],linfo.lowCorrelationClassName[i][315],linfo.lowCorrelationClassName[i][316],linfo.lowCorrelationClassName[i][317],linfo.lowCorrelationClassName[i][318],linfo.lowCorrelationClassName[i][319],linfo.lowCorrelationClassName[i][320],linfo.lowCorrelationClassName[i][321],linfo.lowCorrelationClassName[i][322],linfo.lowCorrelationClassName[i][323],linfo.lowCorrelationClassName[i][324],linfo.lowCorrelationClassName[i][325],linfo.lowCorrelationClassName[i][326],linfo.lowCorrelationClassName[i][327],linfo.lowCorrelationClassName[i][328],linfo.lowCorrelationClassName[i][329],linfo.lowCorrelationClassName[i][330],linfo.lowCorrelationClassName[i][331],linfo.lowCorrelationClassName[i][332],linfo.lowCorrelationClassName[i][333],linfo.lowCorrelationClassName[i][334],linfo.lowCorrelationClassName[i][335],linfo.lowCorrelationClassName[i][336],linfo.lowCorrelationClassName[i][337],linfo.lowCorrelationClassName[i][338],linfo.lowCorrelationClassName[i][339],linfo.lowCorrelationClassName[i][340],linfo.lowCorrelationClassName[i][341],linfo.lowCorrelationClassName[i][342],linfo.lowCorrelationClassName[i][343],linfo.lowCorrelationClassName[i][344],linfo.lowCorrelationClassName[i][345],linfo.lowCorrelationClassName[i][346],linfo.lowCorrelationClassName[i][347],linfo.lowCorrelationClassName[i][348],linfo.lowCorrelationClassName[i][349],linfo.lowCorrelationClassName[i][350],linfo.lowCorrelationClassName[i][351],linfo.lowCorrelationClassName[i][352],linfo.lowCorrelationClassName[i][353],linfo.lowCorrelationClassName[i][354],linfo.lowCorrelationClassName[i][355],linfo.lowCorrelationClassName[i][356],linfo.lowCorrelationClassName[i][357],linfo.lowCorrelationClassName[i][358],linfo.lowCorrelationClassName[i][359],linfo.lowCorrelationClassName[i][360],linfo.lowCorrelationClassName[i][361],linfo.lowCorrelationClassName[i][362],linfo.lowCorrelationClassName[i][363],linfo.lowCorrelationClassName[i][364],linfo.lowCorrelationClassName[i][365],linfo.lowCorrelationClassName[i][366],linfo.lowCorrelationClassName[i][367],linfo.lowCorrelationClassName[i][368],linfo.lowCorrelationClassName[i][369],linfo.lowCorrelationClassName[i][370],linfo.lowCorrelationClassName[i][371],linfo.lowCorrelationClassName[i][372],linfo.lowCorrelationClassName[i][373],linfo.lowCorrelationClassName[i][374],linfo.lowCorrelationClassName[i][375],linfo.lowCorrelationClassName[i][376],linfo.lowCorrelationClassName[i][377],linfo.lowCorrelationClassName[i][378],linfo.lowCorrelationClassName[i][379],linfo.lowCorrelationClassName[i][380],linfo.lowCorrelationClassName[i][381],linfo.lowCorrelationClassName[i][382],linfo.lowCorrelationClassName[i][383],linfo.lowCorrelationClassName[i][384],linfo.lowCorrelationClassName[i][385],linfo.lowCorrelationClassName[i][386],linfo.lowCorrelationClassName[i][387],linfo.lowCorrelationClassName[i][388],linfo.lowCorrelationClassName[i][389],linfo.lowCorrelationClassName[i][390],linfo.lowCorrelationClassName[i][391],linfo.lowCorrelationClassName[i][392],linfo.lowCorrelationClassName[i][393],linfo.lowCorrelationClassName[i][394],linfo.lowCorrelationClassName[i][395],linfo.lowCorrelationClassName[i][396],linfo.lowCorrelationClassName[i][397],linfo.lowCorrelationClassName[i][398],linfo.lowCorrelationClassName[i][399],linfo.lowCorrelationClassName[i][400],linfo.lowCorrelationClassName[i][401],linfo.lowCorrelationClassName[i][402],linfo.lowCorrelationClassName[i][403],linfo.lowCorrelationClassName[i][404],linfo.lowCorrelationClassName[i][405],linfo.lowCorrelationClassName[i][406],linfo.lowCorrelationClassName[i][407],linfo.lowCorrelationClassName[i][408],linfo.lowCorrelationClassName[i][409],linfo.lowCorrelationClassName[i][410],linfo.lowCorrelationClassName[i][411],linfo.lowCorrelationClassName[i][412],linfo.lowCorrelationClassName[i][413],linfo.lowCorrelationClassName[i][414],linfo.lowCorrelationClassName[i][415],linfo.lowCorrelationClassName[i][416],linfo.lowCorrelationClassName[i][417],linfo.lowCorrelationClassName[i][418],linfo.lowCorrelationClassName[i][419],linfo.lowCorrelationClassName[i][420],linfo.lowCorrelationClassName[i][421],linfo.lowCorrelationClassName[i][422],linfo.lowCorrelationClassName[i][423],linfo.lowCorrelationClassName[i][424],linfo.lowCorrelationClassName[i][425],linfo.lowCorrelationClassName[i][426],linfo.lowCorrelationClassName[i][427],linfo.lowCorrelationClassName[i][428],linfo.lowCorrelationClassName[i][429],linfo.lowCorrelationClassName[i][430],linfo.lowCorrelationClassName[i][431],linfo.lowCorrelationClassName[i][432],linfo.lowCorrelationClassName[i][433],linfo.lowCorrelationClassName[i][434],linfo.lowCorrelationClassName[i][435],linfo.lowCorrelationClassName[i][436],linfo.lowCorrelationClassName[i][437],linfo.lowCorrelationClassName[i][438],linfo.lowCorrelationClassName[i][439],linfo.lowCorrelationClassName[i][440],linfo.lowCorrelationClassName[i][441],linfo.lowCorrelationClassName[i][442],linfo.lowCorrelationClassName[i][443],linfo.lowCorrelationClassName[i][444],linfo.lowCorrelationClassName[i][445],linfo.lowCorrelationClassName[i][446],linfo.lowCorrelationClassName[i][447],linfo.lowCorrelationClassName[i][448],linfo.lowCorrelationClassName[i][449],linfo.lowCorrelationClassName[i][450],linfo.lowCorrelationClassName[i][451],linfo.lowCorrelationClassName[i][452],linfo.lowCorrelationClassName[i][453],linfo.lowCorrelationClassName[i][454],linfo.lowCorrelationClassName[i][455],linfo.lowCorrelationClassName[i][456],linfo.lowCorrelationClassName[i][457],linfo.lowCorrelationClassName[i][458],linfo.lowCorrelationClassName[i][459],linfo.lowCorrelationClassName[i][460],linfo.lowCorrelationClassName[i][461],linfo.lowCorrelationClassName[i][462],linfo.lowCorrelationClassName[i][463],linfo.lowCorrelationClassName[i][464],linfo.lowCorrelationClassName[i][465],linfo.lowCorrelationClassName[i][466],linfo.lowCorrelationClassName[i][467],linfo.lowCorrelationClassName[i][468],linfo.lowCorrelationClassName[i][469],linfo.lowCorrelationClassName[i][470],linfo.lowCorrelationClassName[i][471],linfo.lowCorrelationClassName[i][472],linfo.lowCorrelationClassName[i][473],linfo.lowCorrelationClassName[i][474],linfo.lowCorrelationClassName[i][475],linfo.lowCorrelationClassName[i][476],linfo.lowCorrelationClassName[i][477],linfo.lowCorrelationClassName[i][478],linfo.lowCorrelationClassName[i][479],linfo.lowCorrelationClassName[i][480],linfo.lowCorrelationClassName[i][481],linfo.lowCorrelationClassName[i][482],linfo.lowCorrelationClassName[i][483],linfo.lowCorrelationClassName[i][484],linfo.lowCorrelationClassName[i][485],linfo.lowCorrelationClassName[i][486],linfo.lowCorrelationClassName[i][487],linfo.lowCorrelationClassName[i][488],linfo.lowCorrelationClassName[i][489],linfo.lowCorrelationClassName[i][490],linfo.lowCorrelationClassName[i][491],linfo.lowCorrelationClassName[i][492],linfo.lowCorrelationClassName[i][493],linfo.lowCorrelationClassName[i][494],linfo.lowCorrelationClassName[i][495],linfo.lowCorrelationClassName[i][496],linfo.lowCorrelationClassName[i][497],linfo.lowCorrelationClassName[i][498],linfo.lowCorrelationClassName[i][499]);
		}
	}	
	 if(info.flagOutDistanceRate){
		for(i=1;i<info.flagInList-1;i++){
		 	fprintf(info.fptOutDistanceRate,"%4d  %7.2lf\n",(info.flagInList-1-i),(linfo.distance[i]/linfo.distance[i-1]));
		}
	}	
	 if(info.flagOutUpperDistanceRate){
		for(i=0;i<LIMIT;i++){
			fprintf(info.fptOutUpperDistanceRate,"%4d  %7.2lf\n",linfo.classes[i],linfo.upperDistanceRate[i]);
		}
	}
	 if(info.flagOutDistance){
		for(i=0;i<info.flagInList-1;i++){
			 fprintf(info.fptOutDistance,"%4d  %7.2lf\n",(info.flagInList-1-i),linfo.distance[i]);
		}
	}


	exit(EXIT_SUCCESS);

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void  lvectorImageNearestNeighborMethod(mrcImage* In, int nIn, lvectorImageNearestNeighborMethodInfo* linfo, int mode)
{
	int i,j,k,l,loop,count,count1,count2,height,width;
	double count3 ;
	double data;
	float x;
	float y;
	float z;

	DMS = nIn*(nIn-1)/2;
	
	int class_transformedImage;
	int transformingClassNumber;
	int oldClassNumber;
	double maxDistance=0.0;
	double curtateDistanceRate;

	int* upperNclass; 
	//upperNclass = new int[LIMIT];
	upperNclass = (int*)memoryAllocate(sizeof(int)*LIMIT, "in");

	double* curtateDistance ;
	//curtateDistance = new double[nIn-1];
	curtateDistance = (double*)memoryAllocate(sizeof(double)*(nIn-1), "in ");
	
	double* upperCurtateDistanceRate ;
	//upperCurtateDistanceRate = new double[LIMIT];
	upperCurtateDistanceRate = (double*)memoryAllocate(sizeof(double)*LIMIT, "in");
	for(i=0; i<LIMIT; i++)
		upperCurtateDistanceRate[i] = 0.0;
	
	int** upperClassNumber ;
	//upperClassNumber=new int*[nIn];
	upperClassNumber= (int**)memoryAllocate(sizeof(int*)*nIn, "in ");
	for(i=0; i<nIn; i++){
		//upperClassNumber[i]=new int[LIMIT];
		upperClassNumber[i]=(int*)memoryAllocate(sizeof(int)*LIMIT, "in");
	}

	int** lowCorrelationClassNumber ; 
	lowCorrelationClassNumber = (int**)memoryAllocate(sizeof(int*)*nIn, "int");
	for(i=0; i<nIn; i++){
		//lowCorrelationClassNumber[i]=new int[LIMIT];
		lowCorrelationClassNumber[i]=(int*)memoryAllocate(sizeof(int)*LIMIT, "in");
	}

	int* currentClassNumber;
	//currentClassNumber=new int[nIn];
	currentClassNumber=(int*)memoryAllocate(sizeof(int)*nIn, "in");
	for(i=0;i<nIn;i++){
		currentClassNumber[i]=i+1;
	}

	int** classificationIntegration ;
	classificationIntegration=(int**)memoryAllocate(sizeof(int*)*(nIn-1), "in"); 
	for(i=0; i<nIn-1; i++){
		//classificationIntegration[i] = new (int)[2];
		classificationIntegration[i] = (int*)memoryAllocate(sizeof(int)*2, "in");
	}

/*	int* nextClassNumber;
	nextClassNumber=new int[nIn];
	for(i=0;i<nIn;i++){ 
		nextClassNumber[i]=i+1;
	}      */

	dim = In[0].HeaderN.x*In[0].HeaderN.y*In[0].HeaderN.z;

	double** pData;
	//pData=new double*[nIn];
	pData=(double**)memoryAllocate(sizeof(double*)*nIn, "in ");
	for(i=0;i<nIn;i++) {
		//pData[i]=new double[dim];
		pData[i]= (double*)memoryAllocate(sizeof(double)*dim, "in");
	}
	double* distanceMap; 
	//distanceMap=new double[DMS];
	distanceMap=(double*)memoryAllocate(sizeof(double)*DMS, "in");

	for(i=0; i<nIn; i++){
		count=0;
		for(z=0;z<In->HeaderN.z;z++){
		for(y=0;y<In->HeaderN.y;y++){
		for(x=0;x<In->HeaderN.x;x++){
		/*	if(count%1000==0)
				DEBUGPRINT2("count=%d i=%d\n",count,i);     */
			mrcPixelDataGet(&In[i], x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			pData[i][count]=data;
			count++;
		}
		}
		}
	}
	 DEBUGPRINT("maxDistance\n");
	j=nIn-1;
	height=0;
	count=0;
//	for(height=0;height<nIn-1;height++){
	while(height<nIn-1){
		width=0;
		while(width<j){
//			distanceMap[height][width]=0.0;
			distanceMap[count+width]=0.0;
			for(k=0;k<dim;k++){
//				if(linfo->flageigenWeight==1){
					distanceMap[count+width]+=EW[k]*((pData[height][k]-pData[height+1+width][k])*(pData[height][k]-pData[height+1+width][k]));             
//				}
//				else{
//					distanceMap[count+width]+=(pData[height][k]-pData[height+1+width][k])*(pData[height][k]-pData[height+1+width][k]);
//				}
			}
/*			if(height>nIn-6 && j<=4 && width<1800)
				DEBUGPRINT5("height=%d  width=%d  distanceMap=%lf  j=%d  nIn=%d\n",height,width,distanceMap[count+width],j,nIn);    */
				
			if(maxDistance <= distanceMap[count+width]){
				maxDistance = distanceMap[count+width];
			}
			width++;
		}
		count += j;
		height++;
		j--;
/*		if(i<LIMIT)	
			DEBUGPRINT1("macDistance=%lf\n",maxDistance);   */
	}
	DEBUGPRINT("curtateDistance\n");
	for(loop=1;loop<nIn;loop++){
		// curtateDistance[loop-1]=distanceMap[0][0];
		curtateDistance[loop-1]= maxDistance;
		j=nIn-1;
		height=0;
		count=0;
//		for(height=0;height<nIn-1;height++){
		while(height<nIn-1){
			width=0;
			while(width<j){
				if(currentClassNumber[height]!=currentClassNumber[height+1+width]){
					if(distanceMap[count+width] < curtateDistance[loop-1]){
						curtateDistance[loop-1]=distanceMap[count+width];
						if(currentClassNumber[height] < currentClassNumber[height+1+width]){
							class_transformedImage = height+1+width;
							oldClassNumber = currentClassNumber[height+1+width];
							transformingClassNumber = currentClassNumber[height];	
						}
						else{
							class_transformedImage = height;
							oldClassNumber = currentClassNumber[height];
							transformingClassNumber = currentClassNumber[height+1+width];
						}
					}
				}
				width++;
			}
			count += j;
			height++;
			j--;
		}
		count1 = 0;
		count2 = 0;
		count3 = 0;
		for(k=0;k<nIn;k++){
			if(currentClassNumber[k] == transformingClassNumber){
				count1++;
			}
			if(currentClassNumber[k] == oldClassNumber){
			//	nextClassNumber[k] = transformingClassNumber;
				currentClassNumber[k] = transformingClassNumber;
				count2++;
			}
			else if(currentClassNumber[k] > oldClassNumber){
			//	nextClassNumber[k] = currentClassNumber[k]-1;
				currentClassNumber[k]--;
			}
			/*else{
				nextClassNumber[k] = currentClassNumber[k];
			}	*/
		}

		if(linfo->flagOutClassificationIntegrationRate==1){
			if(count1<=count2){
				count3 = ((double)count1 / (double)(count1 + count2)) * 100.0;
				fprintf(linfo->fptOutClassificationIntegrationRate,"%d/%d = %3.2lf %%  %d -> %d class  %d  %d\n",count1,(count1+count2),count3,(nIn+1-loop),(nIn-loop),transformingClassNumber,oldClassNumber);
			}
			else {
				count3 = ((double)count2 / (double)(count1 + count2)) * 100.0;
				fprintf(linfo->fptOutClassificationIntegrationRate,"%d/%d = %3.2lf %%  %d -> %d class  %d  %d\n",count2,(count1+count2),count3,(nIn+1-loop),(nIn-loop),transformingClassNumber,oldClassNumber);
			}
		}  

		// DEBUGPRINT1("loop = %d\n",loop);
		if(loop==1){
			curtateDistanceRate = 1.0;
			upperCurtateDistanceRate[0] = curtateDistanceRate;
			k=0;
		}
		else{
			curtateDistanceRate =  curtateDistance[loop-1]/ curtateDistance[loop-2];
			k=-1;
			while(k<LIMIT){
				k++;
				if(curtateDistanceRate > upperCurtateDistanceRate[k]){
					break;
				}
			}
		}
		
		//j=k;
		//l=0;
		if(k!=LIMIT-1){
			j=k;
			l=0;
			while(j < LIMIT-1 ){
				upperNclass[LIMIT-1-l] = upperNclass[LIMIT-2-l];
				upperCurtateDistanceRate[LIMIT-1-l] = upperCurtateDistanceRate[LIMIT-2-l];
				for(i=0;i<nIn;i++){
					upperClassNumber[i][LIMIT-1-l] = upperClassNumber[i][LIMIT-2-l];
				}
				j++;
				l++;
			}
		}
		upperNclass[k] = nIn-loop;
		upperCurtateDistanceRate[k] = curtateDistanceRate;
		for(i=0;i<nIn;i++){
			upperClassNumber[i][k] = currentClassNumber[i];
			if(loop >= nIn-LIMIT){
				lowCorrelationClassNumber[i][nIn-1-loop] = currentClassNumber[i];
			}
		}

		//  currentClassNumber[k] = nextClassNumber[k];
	}

	DEBUGPRINT("linfo\n");
	linfo->classes  = upperNclass;
	linfo->className = upperClassNumber;
	linfo-> distance = curtateDistance;
	linfo->upperDistanceRate = upperCurtateDistanceRate;
	linfo->lowCorrelationClassName = lowCorrelationClassNumber;
}
