#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PI 3.1415926535            /* $B1_<~N(&P$N@_Dj(B */
#define Avogadro 6.0221367e+23     /* $B%"%\%,%I%m?t$N@_Dj(B */
#define MAX_STRING 256             /* $B:GBg$NJ8;zNs?t$N@_Dj(B */
#define MAX_ATOM 9999              /* $B:GBg$N86;R?t$N@_Dj(B */

/* * * * * * * *
* $B9=B$BN$N:n@.(B *
* * * * * * * */

/* $B;@AG86;R$N:BI8$r3JG<$9$k$?$a$N9=B$BN(B */
typedef struct Coordinate{  
  float x;
  float y;
  float z;
} Coord;

/* $B;@AG86;R$K4X$9$k>pJs(B */
typedef struct OxygenCoordinate{
  Coord *coordinate;
  int count;
} coor_info;

/* $B#286;R4V$N5wN%$r7W;;$9$k$N$KMxMQ$5$l$k9=B$BN(B */
typedef struct Distance{    
  float x1;
  float x2;
  float y1;
  float y2;
  float z1;
  float z2;
} Dist;

/* pdb$B%U%!%$%k$N3F86;R$N$?$a$N9=B$BN(B */
typedef struct atom_type{
       char type[4];        /* pdb$B%U%!%$%k$N3F86;R$N<oN`(B */ 
       char residue[4];     /* pdb$B%U%!%$%k$N3F%"%_%N;@$N<oN`(B */
       int resnum;
       float x;             /* $B3F86;R$N:BI8CM(B */
       float y;
       float z;
       float num1;
       float num2;
} atom_type;

/* $B%?%s%Q%/<AJ,;R$N@)8f$KI,MW$J$9$Y$F$N>pJs$r;}$D9=B$BN(B */
typedef struct protein_info{
  atom_type *atoms;         /* atom_type$B9=B$BN$X$N%]%$%s%?(B */
  int data;                 /* pdb$B%U%!%$%kCf$N86;R$N8D?t(B */
  int coor_info;            /* x, y, z$B$N@_Dj(B */
  int select_number;        /* $B?eJ,;RH/@8$NC10L$r@_Dj$9$kJQ?t(B */
  float setup_radius;       /* $B86E@$+$i$N5wN%$r@_Dj$9$kJQ?t(B */
  int rand_select_number;   /* $BMp?tH/@8$NJ}K!$r@_Dj$9$kJQ?t(B */
  float volume;
} protein_info;

/* $B4X?t%W%m%H%?%$%W@k8@(B */
void *UseFileName( void );
int WaterSetSelect( void );  
float SetMaxRadius( float max_distance );                
int Water( protein_info *p );    
int WaterNumber( void );                 
float WaterMolNumber( void );            
float SetVolume( protein_info *p ); 
void VolumeWarning( void );
int VolumeToNumber( float mol_number, float volume );
float MoleculeCenter( protein_info *p );          
atom_type *Translation( protein_info *p );  
float TotalVolume( protein_info *p );
float CalcVolume( float r, int num );      
float AtomMaxDistance( protein_info *p );           
void *SetFileName( void );
void RandInit( void );                   
int RandSelect();                         
float RandCoor( int number, int coor, float Radius );
float RandCoorOrtho( float Radius );              
Coord *RandCoorPolar( float Radius );             
float Angle( void );                       
float SetWaterRadius( void );               
Coord *AtomCheck( protein_info *p );  
Coord *MainCheck( protein_info *p, int MAX );      
int Violation( float radius1, float radius2 );  
float SetDistance( Dist *p );               
float SetRadius( int case_number );        
int TypeSet( char *typestring );
 
/* $B%a%$%s(B */
int main( int argc, char *argv[] ) {
   FILE *fp1, *fp2;                /* $B%U%!%$%k%]%$%s%?(B */
   int i, j, k;                          /* $B@)8fMQ$N@0?t7?JQ?t(B */
   atom_type atom[MAX_ATOM];             /* $B9=B$BN(Batom_type$B$NJQ?t(B:$BFI$_9~$_MQ(B */
   float max_distance;                   /* $B86E@$+$i0lHV$O$J$l$?86;R$N5wN%(B */
   int MAX;                              /* $B?eJ,;R$rH/@8$5$;$k:GBgCM(B */
   int count;                            /* $B8=:_H/@8$5$;$??eJ,;R?t(B */
   int data_counter;                     /* $B%G!<%?$N9T?t(B */
   char filestring[MAX_STRING];          /* $B%U%!%$%k$N#19T$rFI$_9~$`JQ?t(B */
   char datastring[MAX_STRING];          /* filestring$B$N%@%_!<(B */
   char typestring[4];                   /* $B86;R$N<oN`$r%3%T!<$9$kJQ?t(B */
   int case_number;                      /* $B86;R$N8GM-HV9f(B */
   protein_info protein;                 /* $B:G=i$N(Bpdb$B%U%!%$%k$K$D$$$F$N>pJs(B */
   protein_info protein_next;            /* $BJ?9T0\F08e$N(Bpdb$B%U%!%$%k$N>pJs(B */
   char output_file[MAX_STRING];         /* $B=PNO$9$k%U%!%$%kL>(B */
   Coord *oxygen;                        /* $B;@AG86;R$N:BI8$KBP$9$k%]%$%s%?(B */
   protein_info *p1, *p2;             /* $B9=B$BN(Bprotein_info$B$N$?$a$N%]%$%s%?(B */
   char header[7];                       /* pdb$B%U%!%$%k$N@hF,J8;zNs(B */

   /* $B%U%!%$%k%*!<%W%s(B */
   if( (fp1=fopen( argv[1] ,"r"))==NULL ) 
      fprintf(stderr, "Sorry! File open error! \n");

   /* fgets$B4X?t$r;H$C$F#19T$:$D%U%!%$%k$rFI$_9~$_(B,$B%G!<%?$rJQ?t$K3JG<$9$k(B */
   i = 0;
   data_counter = 0;
   while( fgets(filestring, 256, fp1) != NULL ){

      /* pdb$B%U%!%$%k$N@hF,$,(BATOM$B$^$?$O(BHETATM$B$+$I$&$+$r3NG'$9$k(B */
      strncpy( header, filestring + 0, 6);
      if( strcmp( header, "ATOM  " ) == 0 ||
          strcmp( header, "HETATM" ) == 0 ){
	strncpy( atom[i].type, filestring + 13, 3 );
	strncpy( atom[i].residue, filestring + 17, 3 );
        atom[i].resnum = atoi( strncpy(datastring, filestring + 22, 5));
	atom[i].x = atof( strncpy(datastring, filestring + 31, 7 ));
	atom[i].y = atof( strncpy(datastring, filestring + 39, 7 ));
	atom[i].z = atof( strncpy(datastring, filestring + 47, 7 ));
        atom[i].num1 = atof( strncpy(datastring, filestring + 56, 5));
        atom[i].num2 = atof( strncpy(datastring, filestring + 63, 4));  
	i++;
	data_counter++;
      }
   }
   fclose(fp1);

   /* $B9=B$BN(Bprotein_info$B$K86;R?t$H3F86;R$N>pJs$r3JG<$9$k(B */
   protein.data = data_counter;
   protein.atoms = atom;
   p1 = &protein;

   /* pdb$B%U%!%$%kCf$N(Bx, y, z$B:BI8CM$r:BI8=E?4$NJ,$@$1Jd@5$9$k(B */
   protein_next.atoms  = Translation( p1 );
   protein_next.data = protein.data;
   protein_next.volume = TotalVolume( p1 );
   p2 = &protein_next;
   
   /* $B86E@Cf?4$+$i:G$bN%$l$?86;R$^$G$N5wN%$r7W;;$9$k(B */
   max_distance = AtomMaxDistance( p2 );

   /* $BMp?t$NH/@8J}K!$NA*Br(B */
   p2 -> rand_select_number = RandSelect();

   /* $B?eJ,;R$NH/@8C10L$H86E@$+$i$N5wN%$r@_Dj(B */
   p2 -> select_number = WaterSetSelect();
   p2 -> setup_radius = SetMaxRadius( max_distance );
   MAX = Water( p2 );

   /* $BMp?t$N=i4|2=(B */
   RandInit();

   /* $B7k2L$N%U%!%$%k$X$N=q$-$@$7(B */
   fprintf(stdout, "Please write filename you want to output data : ");
   fgets(output_file, 80, stdin);

   /* $B%U%!%$%k%*!<%W%s(B */
   if( (fp2 = fopen( output_file, "w")) == NULL ) 
      fprintf(stderr, "Sorry! File open error! \n");

   /* $B%U%!%$%k$X$N=q$-$@$7!JJ?9T0\F0$7$?%?%s%Q%/<AJ,;R!K(B*/
   for( i = 0; i < data_counter; i++ ){
     fprintf( fp2, 
           "ATOM  %5d  %3s %3s %5d     %7.3f %7.3f %7.3f  %5.1f  %4.1f\n",  
                  i + 1,
                  ((p2 -> atoms) + i) -> type,
                  ((p2 -> atoms) + i) -> residue,
                  ((p2 -> atoms) + i) -> resnum, 
                  ((p2 -> atoms) + i) -> x, 
                  ((p2 -> atoms) + i) -> y,
                  ((p2 -> atoms) + i) -> z,
                  ((p2 -> atoms) + i) -> num1,
                  ((p2 -> atoms) + i) -> num2);
   }
 

   /* $B86;R4V5wN%$K$D$$$F$N%A%'%C%/(B */
   oxygen = MainCheck( p2, MAX );

   /* $B%U%!%$%k$X$N=q$-$@$7!J;@AG86;R!K(B */
   for( i = 0; i < MAX; i++ ){
     fprintf( fp2, 
	     "HETATM%5d  OH2 HOH %5d     %7.3f %7.3f %7.3f    1.0  10.0 \n",
	      i + 1, 
	      i + 1, 
	      (oxygen + i) -> x, 
	      (oxygen + i) -> y, 
	      (oxygen + i) -> z);
   }
   fclose(fp2);

   return 0;

}


/* * * * * * * * * * * * * * * * * * * * * * * * 
* $B?eJ,;R$NH/@8J}K!$rA*Br$9$k(BWaterSetSelect$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * */
int WaterSetSelect( void ){    
   char input[80];    /* $B%3%s%=!<%k$+$i$NF~NO$rJ8;zNs$H$7$F3JG<$9$kJQ?t(B */
   int number;

   /* $B%3%s%=!<%k>e$K@_DjJ}K!$rI=<($9$k(B */
   do{
     fprintf(stdout, "Second setup which unit you want to make water. \n");
     fprintf(stdout, "Select number : 1. molecule number \n");
     fprintf(stdout, "              : 2. mol/l \n" );
     fprintf(stdout, "Please input select number : ");
     number = atoi( fgets(input, 80, stdin) );
     fprintf(stdout, "\n");
     
     /* $BF~NO$,4V0c$C$F$$$?$i%(%i!<$rI=<($9$k(B */
     if( !( number == 1 || number == 2 ) )
       fprintf(stdout, "Input number is wrong. Try again.\n");
   }while( !( number ==1 || number == 2 ) );

   return number;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BH/@8$7$??eJ,;R$NCf?4$+$i$N:GBg5wN%$r@_Dj$9$k(BSetMaxRadius$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float SetMaxRadius( float max_distance ){       
   char input[80];        /* $B%3%s%=!<%k$+$i$NF~NO$rJ8;zNs$H$7$F3JG<$9$kJQ?t(B */
   float value;

   /* $B%3%s%=!<%k>e$+$iF~NO$7$?J8;z$rIbF0>.?tE@?t$K49$($FCM$rLa$9(B */
   fprintf(stdout, "Max distance from zero point : %f \n", max_distance );
   fprintf(stdout, "Please input max distance from center : ");
   value = atof( fgets(input, 80, stdin) );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * *
* $B?eJ,;R$NH/@8?t$r@_Dj$9$k(BWater$B4X?t(B  *
* * * * * * * * * * * * * * * * * * */
int Water( protein_info *p ){     
  int value;
  float volume;           /* $B?eJ,;R$r<B:]$KH/@8$5$;$kNN0h$NBN@Q$r3JG<$9$kJQ?t(B */
  float mol_number;       /* $B%b%k?t$r3JG<$9$kJQ?t(B */
  char determine[80];     /* $B2hLL>e$NF~NO$rJ8;zNs$H$7$F3JG<$9$kJQ?t(B */

  switch( p -> select_number ){
  case 1 : /* $B;XDj$7$?NN0h$NBN@Q$,%?%s%Q%/<AJ,;R$NBN@Q$h$j>.$5$1$l$P7Y9p$9$k(B */
           if( CalcVolume( p -> setup_radius, p -> rand_select_number ) < p -> volume ) 
	     VolumeWarning();
           value = WaterNumber();    /* $B?t$rF~NO$9$kJ}K!(B */
           break;
  case 2 : do{
              volume = SetVolume( p );
              mol_number = WaterMolNumber();     /* $B%b%k?t$rF~NO$9$kJ}K!(B */
	      value = VolumeToNumber( mol_number, volume );   
	      fprintf( stdout, "Making water molecules is %d .\n", value );
	      fprintf( stdout, "Setup above number? [yes/no] : " );
	      fgets( determine, 80, stdin );     /* $B2hLL>e$NF~NO$r<h$j9~$`(B */

              /* $BF~NOJ8;z$,4V0c$C$F$$$?$i7Y9p$9$k(B */
	      for(;strncmp(determine, "yes",3) && strncmp(determine, "no",2);){
		fprintf( stdout, "Please input yes or no. [yes/no] : " );
		fgets( determine, 80, stdin );
	      }
                  
	      if( !strncmp( determine, "no", 2 ) )
		fprintf( stdout, "Ok, setup once again.\n" );
           }while( strncmp( determine, "yes", 3 ) );
           fprintf( stdout, "\n" );
           break;
  }

  return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* $B?eJ,;R$NH/@8?t$r@_Dj$9$k(BWaterNumber$B4X?t!JD>@\?t$rF~NO$9$kJ}K!!K(B*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int WaterNumber( void ){      
   int value;
   char number[80];    /* $B%3%s%=!<%k$+$i$NF~NO$r<u$1$kJQ?t(B */

   /* $B?eJ,;R$NH/@8?t$rJ8;zNs$H$7$F<hF@$7!"$=$l$r@0?t$H$7$FJV$9(B */
   fprintf(stdout, "How many water molecules do you make : ");
   fgets( number, 80, stdin );
   value = atoi( number );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B?eJ,;R$NH/@8?t$r@_Dj$9$k(BWaterMolNumber$B4X?t!J(Bmol$BG;EY$rF~NO$9$kJ}K!!K(B*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
float WaterMolNumber( void ){   
   float value;
   char number[80];    /* $B%3%s%=!<%k$+$i$NF~NO$r<u$1$kJQ?t(B */

   /* $B?eJ,;R$NH/@8?t(B(mol/l$BC10L(B)$B$rJ8;zNs$H$7$F<hF@$7(B,$B$=$l$r@0?t$H$7$FJV$9(B */
   fprintf(stdout, "How many water molecules do you make( mol/l unit ) : ");
   fgets( number , 80, stdin );
   value = atof( number );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BH/@8$5$;$k?eJ,;R$NNN0h$NBN@Q$r@_Dj$9$k(BSetVolume$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * */
float SetVolume( protein_info *p ){  
   int value;
   float volume1;        /* $B;XDj$7$?H>7B$r;}$DNN0h$NBN@Q$rI=$9JQ?t(B */
   float Radius;         /* $B%f!<%6!<$,;XDj$7$?H/@8NN0h$NH>7B$rI=$9JQ?t(B */
   float volume2;        /* $B:G=*E*$K:NMQ$5$l$?BN@Q(B */
 
   /* $BH/@8$5$;$k6u4V$NBN@Q$r7W;;$9$k(B */
   volume1 = CalcVolume( p -> setup_radius, p -> rand_select_number );
 
   /* $B%?%s%Q%/<AJ,;R$NBN@Q$H;XDj$5$l$?NN0h$NBN@Q$rHf3S$7$F7Y9p$9$k(B */
   if( volume1 < p -> volume ){
     VolumeWarning();
     volume2 = volume1;    /* $B;XDjNN0h$=$N$b$N$rBN@Q$H$7$F;H$&(B */
   }
   else volume2 = volume1 - ( p -> volume ); /* $B;XDjNN0h$+$i%?%s%Q%/<A$NBN@Q$r:9$70z$/(B */

   return volume2;

}


/* * * * * * * * * * * * * * * * * * * * * * * *
* $BBN@Q$K4X$9$k7Y9p$rH/@8$9$k(BVolumeWarning$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * */
void VolumeWarning( void ){
   char string[80];        /* $B%3%s%=!<%k$+$i$NF~NO$r3JG<$9$kJQ?t(B */

   fprintf( stdout, "Making region is smaller than protein volume.\n" );
   fprintf( stdout, "If continue, you probably need much time to get results.\n");
   fprintf( stdout, "\n" );
   fprintf( stdout, "Continue? [yes/no] : ");
   fgets( string, 80, stdin );

   /* $BF~NO$,4V0c$C$F$$$?$i7Y9p$9$k(B */
   for(; strncmp( string, "yes", 3 ) && strncmp( string, "no", 2 ); ){
     fprintf( stdout, "Please input yes or no. [yes/no] : ");
     fgets( string, 80, stdin );
   }

   /* $BB39T$9$k$J$i$P$=$N$^$^<!$N%9%F%C%W$K?J$`(B */
   if( !strncmp( string, "yes", 3 ) )
     fprintf( stdout, "Ok, use volume without reducing protein one.\n");
   else{
     /* $BB39T$7$J$$$N$J$i$P%W%m%0%i%`$rCf;_$9$k(B */
     fprintf( stdout, "Sorry, program terminated.\n" );
     exit(EXIT_FAILURE);
   }

   fprintf( stdout, "\n");
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BBN@Q$r85$KH/@8$5$;$k86;R?t$r7W;;$9$k(BVolumeToNumber$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int VolumeToNumber( float mol_number, float volume ){
   int value;
  
   /* $BH/@8$5$;$k?eJ,;R?t$rBN@Q$r85$K$7$F7W;;$9$k(B */
   value = ( int ) mol_number * Avogadro * volume * 1000;

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B%?%s%Q%/<AJ,;R$N:BI8=E?4$r5a$a$k(BMoleculeCenter$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * * * */
float MoleculeCenter( protein_info *p ){  
      float total;               /* $B3F86;R$N:BI8$N9g7WCM(B */
      float value;
      int i;                     /* $B%k!<%W@)8fJQ?t(B */

      total = 0.0;
  
      /* $B2>0z?t$K$h$C$FA*BrE*$K(Bx, y, z$B:BI8$N9g7WCM$r7W;;$9$k(B */
      switch( p -> coor_info ){
      case 1 : for( i = 0; i < p -> data; i++ ){
                    total = total + ( (p -> atoms) + i )->x;
      }
      break;
      case 2 : for( i = 0; i < p -> data; i++ ){
                    total = total + ( (p -> atoms) + i )->y;
      }
      break;
      case 3 : for( i = 0; i < p -> data; i++ ){
                    total = total + ( (p -> atoms) + i )->z;
      }
      break;
      }

      /* $B:BI8=E?4$N7W;;(B */
      value = total / p -> data;

      return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* pdb$B%U%!%$%k$N3F:BI8CM$r:BI8=E?4J,$@$1J?9T0\F0$9$k(BTranslation$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct atom_type *Translation( protein_info *p ){  
   atom_type *atom_trans;    /* $BJ?9T0\F0$7$?8e$N86;R$N>pJs$r;}$D9=B$BN(B */
   int i;                    /* $B%k!<%W@)8fJQ?t(B */
   int num;                  /* $B86;R?t$rI=$9JQ?t(B */

   /* $B%?%s%Q%/J,;R$N86;R?t$r3JG<$9$k(B */
   num = p -> data;

   /* $B9=B$BN(Batom_trans$B$N$?$a$K%a%b%j$r3NJ]$9$k(B */
   atom_trans =( atom_type * ) malloc( sizeof( atom_type ) * num);
   if( NULL == atom_trans ){
     fprintf(stderr, "Memory not allocated in Translation \n");
     exit(EXIT_FAILURE);
   }

   /* $B?7$7$$9=B$BN$KJ?9T0\F0$7$?8e$N%G!<%?$r3JG<$9$k(B */
   for( i = 0; i < num; i++ ){
      strncpy( atom_trans[i].type, ( (p -> atoms) + i ) -> type, 4);
      strncpy( atom_trans[i].residue, ( (p -> atoms) + i ) -> residue, 4);
      atom_trans[i].resnum = ( (p -> atoms) + i ) -> resnum;
      p -> coor_info = 1;
      atom_trans[i].x = ( (p -> atoms) + i ) -> x - MoleculeCenter( p );
      p -> coor_info = 2;
      atom_trans[i].y = ( (p -> atoms) + i ) -> y - MoleculeCenter( p );
      p -> coor_info = 3;
      atom_trans[i].z = ( (p -> atoms) + i ) -> z - MoleculeCenter( p );
      atom_trans[i].num1 = ( (p -> atoms) + i ) -> num1;
      atom_trans[i].num2 = ( (p -> atoms) + i ) -> num2;
   }

   /* $BJ?9T0\F0$5$;$?8e$N86;R$N>pJs$r%]%$%s%?$GJV$9(B */ 
   return atom_trans;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B%?%s%Q%/<AJ,;R$NBN@Q$r6a;wE*$K7W;;$9$k(BTotalVolume$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float TotalVolume( protein_info *p ){
   float volume;
   float radius;        /* $B3F86;R$NH>7B$r3JG<$9$kJQ?t(B */
   int case_number;     /* $B86;R$N<oN`$r<($9JQ?t(B */
   int i;               /* $B%k!<%W@)8fJQ?t(B */

   /* $BJQ?t$N=i4|2=(B */
   volume = 0.0;

   for( i = 0; i < (p -> data); i++ ){
     /* $B3F86;R$N<oN`$K1~$8$FH>7B$r@_Dj$9$k(B */
     case_number = TypeSet( ( (p -> atoms) + i ) -> type );
     radius = SetRadius( case_number );       

     volume = volume + CalcVolume( radius, 2 );      /* $BA4BN$NBN@Q$r7W;;$9$k(B */
   }

   return volume;

}
  

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* $BCf?4$+$i$N5wN%$r0z?t$H$7$FBN@Q$rJV$9(BCalcVolume$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * */
float CalcVolume( float r, int num ){
   float value;
 
   switch( num ){
   case 1: value = 8.0 * r * r * r * 1e-30;   /* $BBN@Q$N7W;;(B($BN)J}BN(B) */
                   break;
   case 2: value = 4.0 / 3.0 * PI * r * r * r * 1e-30;   /* $BBN@Q$N7W;;(B($B5e(B) */
                   break;
   }

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* $B86E@Cf?4$+$i:G$bN%$l$?86;R$N5wN%$r7W;;$9$k(BAtomMaxDistance$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
float AtomMaxDistance( protein_info *p ){ 
   float x, y, z;            /* $B3F:BI8$NCM(B */
   float value;              
   float distance[p -> data];    /* $B3F86;R$NCf?4$+$i$N5wN%$r3JG<$9$kG[Ns(B */
   float temp;                   /* $B%@%_!<JQ?t(B */
   int i, j;

   /* $B3F86;R$N86E@$+$i$N5wN%$r7W;;$9$k(B */
   for( i = 0; i < p -> data; i++ ){
     x = ( (p -> atoms) + i ) -> x;
     y = ( (p -> atoms) + i ) -> y;
     z = ( (p -> atoms) + i ) -> z;
     distance[i] = sqrt( x * x + y * y + z * z );
   }

   /* $B:G$b86E@$+$i$N5wN%$,Bg$-$$$b$N$r=gHV$KC5:w$9$k(B */
   for( i = 1; i < p -> data; i++ ){
     if( distance[0] < distance[i] ){
       temp = distance[0];
       distance[0] = distance[i];
       distance[i] = temp;
     }
   }

   return distance[0];

}
   
       
/* * * * * * * * * * * * * * * * * * * * * * * * *
* $B=PNO@h$N%U%!%$%kL>$NF~NO$rB%$9(BSetFileName$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * */
void *SetFileName( void ){
   char filename[80];    /* $B%3%s%=!<%k$+$i$NF~NO$r<u$1$kJQ?t(B */

   /* $B=PNO@h$N%U%!%$%k$KBP$9$k%]%$%s%?$rJV$9(B */
   fprintf(stdout, "Please input filename you want to write the data in : ");
   return fgets( filename, 80, stdin );
}


/* * * * * * * * * * * * * * * *
* $BMp?t$r=i4|2=$9$k(BRandInit$B4X?t(B *
* * * * * * * * * * * * * * * */
void RandInit( void ){  
   long system_time;       /* $B%7%9%F%`;~4V$r3JG<$9$kJQ?t(B */
   int timeseed;

   /* $B%7%9%F%`;~4V$r;H$C$F(Brand()$B$r=i4|2=$9$k(B */
   system_time = time( NULL );
   timeseed = (unsigned int) system_time / 2;
   srand(timeseed);

} 
 

/* * * * * * * * * * * * * * * * * * * * * 
* $BMp?t$NH/@8J}K!$rA*Br$9$k(BRandSelect$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * */
int RandSelect(){    
   char input[80];          /* $B%3%s%=!<%k$+$i$NF~NO$r3JG<$9$kJQ?t(B */
   int number;

   /* $B%3%s%=!<%k>e$K@_DjJ}K!$rI=<($9$k(B */
   do{
     fprintf(stdout, "First setup how to make water molecules. \n");
     fprintf(stdout, "Select number : 1. orthogonal \n");
     fprintf(stdout, "              : 2. polar \n" );
     fprintf(stdout, "Please select the number : ");
     number = atoi( fgets(input, 80, stdin) );
     fprintf(stdout, "\n");
     
     if( !( number == 1 || number == 2 ) )
       fprintf(stdout, "Input number is wrong. Try again.\n");
   }while( !( number == 1 || number == 2 ) );

   return number;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BMp?t$G:BI8$rH/@8$5$;$k(BRandCoorOrtho$B4X?t!J#3<!85D>8r:BI87O!K(B*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float RandCoorOrtho( float Radius ) {  
   float random, value;
 
   /* $BMp?t$r(B0$B$+$i(B1$B$^$G$NCM$KJQ49$9$k(B */
   random = rand() * 1.0 / ( RAND_MAX + 1.0 );

   /* $B:BI8CM$r:n@.(B */
   value = 2.0 * Radius * ( random - 0.5 );
 
   return value;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BMp?t$r;H$C$F#3<!856K:BI8CM$rH/@8$5$;$k(BRandCoorPolar$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *RandCoorPolar( float Radius ){  
   float radius;       /* $BH>7B$rI=$9JQ?t(B */
   float theta, phi;   /* $B3QEY$rI=$9JQ?t(B */
   Coord *oxygen_polar;   /* $B6K:BI8CM$r3JG<$9$k(BCoord$B9=B$BN$KBP$9$k%]%$%s%?(B */
   float value;
   
   /* $B6K:BI8CM$r3JG<$9$k9=B$BN$N$?$a$K%a%b%j$r3NJ]$9$k(B */
   oxygen_polar = ( Coord * ) malloc( sizeof( Coord ) );
   if( oxygen_polar == NULL ){
     fprintf(stderr, "Memory not allocated in RandCoorPolar.\n");
     exit(EXIT_FAILURE);
   }

   /* $BF07BJ}8~$NCM$r@8@.$9$k(B */
   radius = Radius * rand() * 1.0 / ( RAND_MAX + 1.0 );

   /* $B3QEY&H(B(0<=$B&H(B<=$B&P(B)$B$K$D$$$F$NCM$r@8@.$9$k(B */
   theta = Angle();

   /* $B3QEY&5(B(0<=$B&5(B<=2$B&P(B)$B$K$D$$$F$NCM$r@8@.$9$k(B */
   phi = 2.0 * Angle();

   /* $B6K:BI8CM$r(Bx, y, z$B$=$l$>$l$N>l9g$K$D$$$FH/@8$5$;$k(B */
   oxygen_polar -> x = radius * sin( theta ) * cos( phi );
   oxygen_polar -> y = radius * sin( theta ) * sin( phi );
   oxygen_polar -> z = radius * cos( theta );

   return oxygen_polar;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B0lMM$J3QEYJ,I[!J(B0$B$+$i&P$^$G!K$r4~5QK!$GH/@8$5$;$k(BAngle$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float Angle( void ){                    
   float rand_x, rand_y;   /* x, y$B:BI8$NMp?tCM(B */ 
   float value;
   int num = 0;

   while( num == 0 ){

      /* 0$B$+$i&P$^$G$N4V$NMp?t$rH/@8$5$;$k(B */
      rand_x = rand() * 1.0 * PI / ( RAND_MAX + 1.0 );

      /* 0$B$+$i(B1$B$^$G$NMp?t$rH/@8$5$;$k(B */
      rand_y = rand() * 1.0 / ( RAND_MAX + 1.0 );

      /* $B>r7o$rK~$?$7$F$$$J$$$b$N$O4~5Q$9$k(B */
      if( rand_y <= sin( rand_x ) ){
          value = rand_x;
          num = 1;
      }
   }

   return value;
}


/* * * * * * * * * * * * * * * * * * * * * *
* $B?eJ,;R$NH>7B$r@_Dj$9$k(BSetWaterRadius$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * */
float SetWaterRadius( void ){   
   float bond = 0.957;          /* $B;@AG86;R$H?eAG86;R$N6&M-7k9gH>7B(B */
   float hydrogen;
   float value;

   hydrogen = bond / 2;
   value = bond + hydrogen;     /* $B?eJ,;R$r9dBN5e$G2>Dj$7$?;~$NH>7B(B */

   return value;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B?eJ,;R$H3F86;R$,>WFM$7$J$$$+$I$&$+3N$+$a$k(BAtomCheck$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *AtomCheck( protein_info *p ){    
   Coord *oxygen;              /* $B;@AG86;R$N:BI8$r3JG<$9$k$?$a$N%]%$%s%?(B */
   Coord *oxygen_polar;    /* $B6K:BI8$GH/@8$5$;$?;@AG86;R:BI8$KBP$9$k%]%$%s%?(B */
   Dist oxygen_atom;           /* $B#286;R4V$N5wN%$r7W;;$9$k$?$a$N9=B$BN(B */
   Dist *oxygen_atom_distance; /* $B>e5-$N9=B$BN$X$N%]%$%s%?(B */
   float distance;             /* $B#286;R4V$N5wN%(B */
   float atom_radius;          /* $B3F86;R$r9dBN5e$G6a;w$7$?;~$NH>7B(B */
   char typestring[4];         /* pdb$B%U%!%$%k$K5-:\$5$l$?3F86;R$N<oN`(B */
   int i;                      /* $B%k!<%W@)8fJQ?t(B */
   int num;                    /* $BMp?tH/@8J}K!$r<($9JQ?t(B */
   int case_number;            /* $B86;R$N<oN`$rI=$9HV9f(B */
   int violate_count;          /* $B>WFM$7$F$$$k86;R$N?t(B */

   /* $B;@AG86;R$N:BI83JG<$N$?$a$K%a%b%j$r3NJ](B */
   oxygen = ( Coord * ) malloc( sizeof( Coord ) );
   if( NULL == oxygen ){
      fprintf( stderr, "Memory not allocated in AtomCheck \n" );
      exit(EXIT_FAILURE);
   }

   /* $BMp?tH/@8J}K!$r@_Dj(B */
   num = p -> rand_select_number;
  
   do{
     violate_count = 0;
 
     /* $B;@AG86;R:BI8$rMp?t$GH/@8$9$k(B */
     if( num == 1 ){
       /* $BD>8r:BI8$G;@AG86;R:BI8$rH/@8$5$;$k(B */
       oxygen_atom.x1 = RandCoorOrtho( p -> setup_radius );
       oxygen_atom.y1 = RandCoorOrtho( p -> setup_radius );
       oxygen_atom.z1 = RandCoorOrtho( p -> setup_radius );
     }
     else if( num == 2 ){
       /* $B#3<!856K:BI8$G;@AG86;R$rH/@8$5$;$k(B */
       oxygen_polar = RandCoorPolar( p -> setup_radius );
       oxygen_atom.x1 = oxygen_polar -> x;
       oxygen_atom.y1 = oxygen_polar -> y;
       oxygen_atom.z1 = oxygen_polar -> z;
     }

     /* pdb$B%U%!%$%kCf$N3F86;R$H>WFM$7$F$$$J$$$+$N%A%'%C%/(B */
     for( i = 0; i < p -> data; i++ ){
	oxygen_atom.x2 = ((p -> atoms) + i) -> x;
	oxygen_atom.y2 = ((p -> atoms) + i) -> y;
	oxygen_atom.z2 = ((p -> atoms) + i) -> z;
	oxygen_atom_distance = &oxygen_atom;

        /* $B#286;R4V$N5wN%$r7W;;(B */
	distance = SetDistance( oxygen_atom_distance );

        /* $B86;R$N<oN`$rD4$Y$F$=$l$KE,9g$7$?86;RH>7B$rJV$9(B */
	case_number = TypeSet(strncpy(typestring, (p->atoms + i) -> type, 4));
	atom_radius = SetRadius( case_number );

        /* $B>WFM$7$?86;R$,$"$l$P(Bviolate_atom$B$NCM$rA}$d$9(B */
	if( Violation( distance, atom_radius ) ){
	  violate_count++;
          break;         /* violate_atom$B$NCM$,(B1$B$K$J$C$?$iB(%k!<%W$rH4$1$k(B */
	}
      }
   }while( !violate_count == 0 );     /* violate_atom$B$NCM$,(B0$B$K$J$k$^$GB3$1$k(B */

   /* $B@8$-;D$l$P$3$l$r:BI8$H$7$F3JG<$9$k(B */
   oxygen -> x = oxygen_atom.x1;
   oxygen -> y = oxygen_atom.y1;
   oxygen -> z = oxygen_atom.z1;

   return oxygen;
    
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $BH/@8$5$;$?;@AG86;RF1;N$,>WFM$7$F$$$J$$$+$r:G=*E*$K3N$+$a$k(BMainCheck$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *MainCheck( protein_info *p, int MAX ){
    Coord *oxygen1;           /* AtomCheck$B4X?t$+$iF@$?:BI8CM$KBP$9$k%]%$%s%?(B */
    Coord *water;             /* $B:G=*E*$K3MF@$7$?:BI8CM$KBP$9$k%]%$%s%?(B */
    Dist oxygen_oxygen;       /* $B;@AG86;R4V$N5wN%$r7W;;$9$k$?$a$N9=B$BN(B */
    Dist *oxygen_oxygen_distance;   /* $B>e5-$N9=B$BN$KBP$9$k%]%$%s%?(B */
    float distance;           /* $B;@AG86;R4V$N5wN%(B */
    int count;                /* $B8=:_$^$G$KH/@8$5$;$?;@AG?t$r?t$($kJQ?t(B */
    int violate_atom;         /* $B>WFM$7$F$$$k;@AG86;R?t(B */
    int i;                    /* $B%k!<%W@)8fJQ?t(B */

    /* $B;@AG86;R$N:BI8$r;XDj$7$??t$@$13JG<$9$k9=B$BN$N$?$a$K%a%b%j$r3NJ]$9$k(B */
    water = ( Coord * ) malloc( sizeof( Coord ) * MAX );
    if( water == NULL ){
      fprintf( stderr, "Memory not allocated in MainCheck \n" );
      exit(EXIT_FAILURE);
    }

    /* $B%k!<%W@)8fJQ?t$N=i4|2=(B */
    count = 0;

    /* $BH/@8Cf$G$"$k$3$H$r2hLL$KI=<($9$k(B */
    fprintf( stdout, "Total water molecule number is %d.\n", MAX );
    fprintf( stdout, "Now making. Please wait...\n" );

    /* $BH/@8;@AG?t$,(BMAX$BCM$K$J$k$^$G%k!<%W$r7+$jJV$9(B */
    do{
      /* $B>WFM;@AG86;R?t$N=i4|2=(B */
      violate_atom = 0;

      /* $B%?%s%Q%/<AJ,;R$K>WFM$7$J$$;@AG86;R$N:BI8$rH/@8$5$;$k(B */
      oxygen1 = AtomCheck( p );

      /* $B9=B$BN$K:BI8CM$r3JG<$9$k(B */
      (water + count) -> x = oxygen1 -> x;
      (water + count) -> y = oxygen1 -> y;
      (water + count) -> z = oxygen1 -> z;

      /* $B;@AG86;R4V$N5wN%$N7W;;$N$?$a:BI8CM$r(BDist$B9=B$BN$KBeF~(B */
      oxygen_oxygen.x2 = (water + count) -> x;
      oxygen_oxygen.y2 = (water + count) -> y;
      oxygen_oxygen.z2 = (water + count) -> z;

      /* $B;@AG86;R4V$N5wN%$KBP$9$k%A%'%C%/%k!<%W$N3+;O(B */
      for( i = 0; i < count; i++ ){
        
        /* $B;@AG86;R4V$N5wN%$N7W;;(B */
        oxygen_oxygen.x1 = (water + i) -> x;
        oxygen_oxygen.y1 = (water + i) -> y;
        oxygen_oxygen.z1 = (water + i) -> z;
        oxygen_oxygen_distance = &oxygen_oxygen;
        distance = SetDistance( oxygen_oxygen_distance );

        /* $B?eJ,;RF1;N$,>WFM$7$F$$$l$PJQ?t(Bviolate_atom$B$NCM$rA}$d$9(B */
	if( Violation( distance, SetWaterRadius() ) ){
	  violate_atom++;
          break;     /* violate_atom$B$NCM$,(B1$B$K$J$C$?$iB(%k!<%W$rH4$1$k(B */
	}
      }

      /* $B>WFM$7$F$$$k?eJ,;R$,L5$1$l$P<!$N;@AG86;R$N$?$a$K?t$r0l$DA}$d$9(B */
      if( !violate_atom ) count++;
    } while( count < MAX );
        
    return water;

}
         
 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* $B%?%s%Q%/<A86;R$,;@AG86;R$H>WFM$7$?$J$i$P#1$rJV$9(BViolation$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int Violation( float radius1, float radius2 ){  
   float water_radius;
   int value;

   /* value$B$N=i4|CM$r#0$K%;%C%H(B */
   value = 0;
   water_radius = SetWaterRadius();

   /* $B86;R4V5wN%$,H>7B$NOB$h$j>.$5$1$l$P(Bvalue$B$r#1$K%;%C%H(B*/
   if( radius1 < water_radius + radius2 ) value = 1;

   return value;

}
   

/* * * * * * * * * * * * * * * * * * * * *
* $B#286;R4V$N5wN%$r5a$a$k(BSetDistance$B4X?t(B  *
* * * * * * * * * * * * * * * * * * * * */
float SetDistance( Dist *p ){   
   float X, Y, Z;         /* $B#286;R4V$N:BI8$N:9$rI=$9JQ?t(B */
   float distance;

   /* $B#286;R4V$N:BI8$N:9(B */
   X = (p -> x1) - (p -> x2);
   Y = (p -> y1) - (p -> y2);
   Z = (p -> z1) - (p -> z2);

   /* $B5wN%$N7W;;(B */
   distance = sqrt( X * X + Y * Y + Z * Z );
  
   return distance;
}


/* * * * * * * * * * * * * * * * * * * * * * * * *
* $B86;R$N<oN`$rD4$Y$F(B,$B86;RH>7B$rJV$9(BSetRadius$B4X?t(B *
* * * * * * * * * * * * * * * * * * * * * * * * */
float SetRadius( int case_number ){       
    float radius_value;

    /* $B86;R$NH>7B$r%U%!%s%G%k%o!<%k%9H>7B$G6a;w$9$k(B */
    switch( case_number ){
    case 1: radius_value = 1.55;  /* $BCbAG86;R$NH>7B(B */
            break;
    case 2: radius_value = 1.52;  /* $B;@AG86;R$NH>7B(B */
            break; 
    case 3: radius_value = 1.40;  /* $B?eAG86;R$NH>7B(B */
            break;  
    case 4: radius_value = 1.24;  /* $BE486;R$NM-8zH>7B(B */
            break;
    case 5: radius_value = 1.80;  /* $B%j%s86;R$NH>7B(B */
            break;
    case 6: radius_value = 2.15;  /* $B%9%H%m%s%A%&%`86;R$NM-8zH>7B(B */
            break;
    case 7: radius_value = 1.80;  /* $BN22+86;R$NH>7B(B */
            break;
    case 8: radius_value = 1.70;  /* $BC:AG86;R$NH>7B(B */
            break;
    }

    return radius_value;
}


/* * * * * * * * * * * * * * * * * * *  
* $BJ8;zNs$rHf3S$9$k4X?t(BTypeSet$B$N:n@.(B  *
* * * * * * * * * * * * * * * * * * */
int TypeSet( char *typestring ){       
  int case_value = 1;
 
  if( !strncmp(typestring, "N", 1) ) case_value = 1;
  else if( !strncmp(typestring, "O", 1) ) case_value = 2;
  else if( !strncmp(typestring, "H", 1) ) case_value = 3;
  else if( !strncmp(typestring, "F", 1) ) case_value = 4;
  else if( !strncmp(typestring, "P", 1) ) case_value = 5;
  else if( !strncmp(typestring, "SR", 2) ) case_value = 6;
  else if( !strncmp(typestring, "S", 1) ) case_value = 7;
  else if( !strncmp(typestring, "C", 1) ) case_value = 8;

  return case_value;

}
  





