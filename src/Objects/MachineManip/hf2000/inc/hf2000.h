#ifndef HF2000_H
#define HF2000_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#define _POSIX_SOURCE 1

/* struct begin */
typedef int   hf2000ParaTypeInteger;
typedef float hf2000ParaTypeReal;

typedef struct hf2000Info {
	char* deviceName;
	struct termios IO;
	struct termios prevIO;
	int fd;
	int flagClient;	
	int flagServer;	
	int serverSocket;
	int serverFD;
	char* hostname;
	u_short port;
	u_short maxPort;
	u_short portSpeed;
} hf2000Info;
/* struct end */

#ifdef __HF2000INIT__
/* constant begin */
hf2000Info __hf2000;
char* __hf2000CommandList[] = {
    "*R", /* Initialize */
	"#Q", /* Specimen Position Get */
	"#A", /* Absolute Position Set */
	"#G", /* GO after #A #D #B */
	"#H", /* Speed down and stop*/
	"#X", /* Motor Information */
	"?30", /* C1 Get */   /* Lenz */
	"?31", /* C2 Get */
	"?32", /* C3 Get */
	"?33", /* OBJ Get */
	"?34", /* I1 Get */
	"?35", /* I2 Get */
	"?36", /* P1 Get */
	"?37", /* P2 Get */
	"?40", /* OS(X) Get */ /* BD Coil */
	"?41", /* OS(Y) Get */
	"?42", /* CS(X) Get */
	"?43", /* CS(Y) Get */
	"?44", /* IS(X) Get */
	"?45", /* IS(Y) Get */
	"?46", /* BT(X) Get */
	"?47", /* BT(Y) Get */
	"?48", /* BH(X) Get */
	"?49", /* BH(Y) Get */
	NULL
};
/* constant end */
#else
extern hf2000Info __hf2000;
extern char* __hf2000CommandList[]; 
#endif
/* constant begin */
#define HF2000CMD_Initialize   0
#define HF2000CMD_PositionGet  1
#define HF2000CMD_PositionSet  2 
#define HF2000CMD_PositionMove 3 
#define HF2000CMD_PositionStop 4 
#define HF2000CMD_PositionMotorInfo 5 
#define HF2000CMD_C1Get   6 
#define HF2000CMD_C2Get   7 
#define HF2000CMD_C3Get   8 
#define HF2000CMD_OBJGet  9 
#define HF2000CMD_I1Get   10 
#define HF2000CMD_I2Get   11 
#define HF2000CMD_P1Get   12 
#define HF2000CMD_P2Get   13 
#define HF2000CMD_OSXGet   14 
#define HF2000CMD_OSYGet   15 
#define HF2000CMD_CSXGet   16 
#define HF2000CMD_CSYGet   17 
#define HF2000CMD_ISXGet   18 
#define HF2000CMD_ISYGet   19 
#define HF2000CMD_BTXGet   18 
#define HF2000CMD_BTYGet   19 
#define HF2000CMD_BHXGet   20 
#define HF2000CMD_BHYGet   21 
/* constant end */

/* prototype begin */
extern void hf2000Init(hf2000Info* info);
extern void hf2000Close(hf2000Info* info);
extern void hf2000Read(hf2000Info* info, char* s);
extern void hf2000Write(hf2000Info* info, char* s);
extern void hf2000Command(hf2000Info* info, char* command, char* result);
/* prototype end */

#include <tk.h>
/* prototype begin */
extern int hf2000_TclAppInit(Tcl_Interp * interp);
/* prototype end   */

#endif HF2000_H
