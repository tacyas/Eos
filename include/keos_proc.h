/*
  * Khoros: $Id: keos_proc.h,v 1.1.1.1 2002/02/01 05:14:00 tacyas Exp $
  */


/*
 * Copyright (C) 1993 - 1996, Khoral Research, Inc., ("KRI").
 * All rights reserved.  See $BOOTSTRAP/repos/license/License or run klicense.
 */


/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<<
   >>>>
   >>>>       Purpose:
   >>>>
   >>>>    Written By: ghostwriter
   >>>>
   >>>>          Date: 
   >>>>
   >>>> Modifications:
   >>>>
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<< */

#ifndef _keos_proc_keos_proc_h_
#define _keos_proc_keos_proc_h_


	/*-------------------------------------*
	|       #include
	---------------------------------------*/


	/*-------------------------------------*
	|       #defines
	---------------------------------------*/

#define KFILT_LP		0
#define	KFILT_HP		1
#define KFILT_BP		2
#define KFILT_BS		3

#define KFILT_IDEAL		0
#define KFILT_BUTTERWORTH	1
#define KFILT_GAUSSIAN	        2
#define KFILT_CHEBYSHEV_I	3
#define KFILT_CHEBYSHEV_II	4

	/*-------------------------------------*
	|       typedefs
	---------------------------------------*/


	/*-------------------------------------*
	|       global variable declarations
	---------------------------------------*/


	/*-------------------------------------*
	|       macros
	---------------------------------------*/


	/*-------------------------------------*
	|       routine definitions
	---------------------------------------*/



	/* Ghostwriter Prototypes:  Do Not Erase This Comment */

int litexture PROTO((         kobject in_obj,         int L5L5,         int L5E5,         int L5S5,         int L5W5,         int L5R5,         int E5L5,         int E5E5,         int E5S5,         int E5W5,         int E5R5,         int S5L5,         int S5E5,         int S5S5,         int S5W5,         int S5R5,         int W5L5,         int W5E5,         int W5S5,         int W5W5,         int W5R5,         int R5L5,         int R5E5,         int R5S5,         int R5W5,         int R5R5,         kobject out_obj));

int limedian PROTO((kobject in_obj, int wsize, int hsize, int reps, kobject out_obj));

int lirotate PROTO((kobject, double, double, int, int, double, int, double, double, int, kobject));

int ligeowarp PROTO((kobject, double, double, double, double, double, double, double, double, int, kobject));

int ligradient PROTO((kobject,int,int,kobject));

int liflip PROTO((kobject, int, kobject));

int lifiltdesign PROTO((int, int, int, int, int, double, double, double, int, kobject));

int ligauss_func PROTO((kobject, int, int, int, int, double, double, double, double, int, int, kobject));

int lipostscr PROTO((kfile *, kobject, double, double, double, double, int, 
		     int, int, int, int, int, int));

#endif /* _keos_proc_keos_proc_h_ */
/* Don't add after this point */
