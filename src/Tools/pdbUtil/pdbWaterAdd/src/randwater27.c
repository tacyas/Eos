#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PI 3.1415926535            /* 円周率πの設定 */
#define Avogadro 6.0221367e+23     /* アボガドロ数の設定 */
#define MAX_STRING 256             /* 最大の文字列数の設定 */
#define MAX_ATOM 9999              /* 最大の原子数の設定 */

/* * * * * * * *
* 構造体の作成 *
* * * * * * * */

/* 酸素原子の座標を格納するための構造体 */
typedef struct Coordinate{  
  float x;
  float y;
  float z;
} Coord;

/* 酸素原子に関する情報 */
typedef struct OxygenCoordinate{
  Coord *coordinate;
  int count;
} coor_info;

/* ２原子間の距離を計算するのに利用される構造体 */
typedef struct Distance{    
  float x1;
  float x2;
  float y1;
  float y2;
  float z1;
  float z2;
} Dist;

/* pdbファイルの各原子のための構造体 */
typedef struct atom_type{
       char type[4];        /* pdbファイルの各原子の種類 */ 
       char residue[4];     /* pdbファイルの各アミノ酸の種類 */
       int resnum;
       float x;             /* 各原子の座標値 */
       float y;
       float z;
       float num1;
       float num2;
} atom_type;

/* タンパク質分子の制御に必要なすべての情報を持つ構造体 */
typedef struct protein_info{
  atom_type *atoms;         /* atom_type構造体へのポインタ */
  int data;                 /* pdbファイル中の原子の個数 */
  int coor_info;            /* x, y, zの設定 */
  int select_number;        /* 水分子発生の単位を設定する変数 */
  float setup_radius;       /* 原点からの距離を設定する変数 */
  int rand_select_number;   /* 乱数発生の方法を設定する変数 */
  float volume;
} protein_info;

/* 関数プロトタイプ宣言 */
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
 
/* メイン */
int main( int argc, char *argv[] ) {
   FILE *fp1, *fp2;                /* ファイルポインタ */
   int i, j, k;                          /* 制御用の整数型変数 */
   atom_type atom[MAX_ATOM];             /* 構造体atom_typeの変数:読み込み用 */
   float max_distance;                   /* 原点から一番はなれた原子の距離 */
   int MAX;                              /* 水分子を発生させる最大値 */
   int count;                            /* 現在発生させた水分子数 */
   int data_counter;                     /* データの行数 */
   char filestring[MAX_STRING];          /* ファイルの１行を読み込む変数 */
   char datastring[MAX_STRING];          /* filestringのダミー */
   char typestring[4];                   /* 原子の種類をコピーする変数 */
   int case_number;                      /* 原子の固有番号 */
   protein_info protein;                 /* 最初のpdbファイルについての情報 */
   protein_info protein_next;            /* 平行移動後のpdbファイルの情報 */
   char output_file[MAX_STRING];         /* 出力するファイル名 */
   Coord *oxygen;                        /* 酸素原子の座標に対するポインタ */
   protein_info *p1, *p2;             /* 構造体protein_infoのためのポインタ */
   char header[7];                       /* pdbファイルの先頭文字列 */

   /* ファイルオープン */
   if( (fp1=fopen( argv[1] ,"r"))==NULL ) 
      fprintf(stderr, "Sorry! File open error! \n");

   /* fgets関数を使って１行ずつファイルを読み込み,データを変数に格納する */
   i = 0;
   data_counter = 0;
   while( fgets(filestring, 256, fp1) != NULL ){

      /* pdbファイルの先頭がATOMまたはHETATMかどうかを確認する */
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

   /* 構造体protein_infoに原子数と各原子の情報を格納する */
   protein.data = data_counter;
   protein.atoms = atom;
   p1 = &protein;

   /* pdbファイル中のx, y, z座標値を座標重心の分だけ補正する */
   protein_next.atoms  = Translation( p1 );
   protein_next.data = protein.data;
   protein_next.volume = TotalVolume( p1 );
   p2 = &protein_next;
   
   /* 原点中心から最も離れた原子までの距離を計算する */
   max_distance = AtomMaxDistance( p2 );

   /* 乱数の発生方法の選択 */
   p2 -> rand_select_number = RandSelect();

   /* 水分子の発生単位と原点からの距離を設定 */
   p2 -> select_number = WaterSetSelect();
   p2 -> setup_radius = SetMaxRadius( max_distance );
   MAX = Water( p2 );

   /* 乱数の初期化 */
   RandInit();

   /* 結果のファイルへの書きだし */
   fprintf(stdout, "Please write filename you want to output data : ");
   fgets(output_file, 80, stdin);

   /* ファイルオープン */
   if( (fp2 = fopen( output_file, "w")) == NULL ) 
      fprintf(stderr, "Sorry! File open error! \n");

   /* ファイルへの書きだし（平行移動したタンパク質分子）*/
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
 

   /* 原子間距離についてのチェック */
   oxygen = MainCheck( p2, MAX );

   /* ファイルへの書きだし（酸素原子） */
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
* 水分子の発生方法を選択するWaterSetSelect関数 *
* * * * * * * * * * * * * * * * * * * * * * * */
int WaterSetSelect( void ){    
   char input[80];    /* コンソールからの入力を文字列として格納する変数 */
   int number;

   /* コンソール上に設定方法を表示する */
   do{
     fprintf(stdout, "Second setup which unit you want to make water. \n");
     fprintf(stdout, "Select number : 1. molecule number \n");
     fprintf(stdout, "              : 2. mol/l \n" );
     fprintf(stdout, "Please input select number : ");
     number = atoi( fgets(input, 80, stdin) );
     fprintf(stdout, "\n");
     
     /* 入力が間違っていたらエラーを表示する */
     if( !( number == 1 || number == 2 ) )
       fprintf(stdout, "Input number is wrong. Try again.\n");
   }while( !( number ==1 || number == 2 ) );

   return number;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 発生した水分子の中心からの最大距離を設定するSetMaxRadius関数 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float SetMaxRadius( float max_distance ){       
   char input[80];        /* コンソールからの入力を文字列として格納する変数 */
   float value;

   /* コンソール上から入力した文字を浮動小数点数に換えて値を戻す */
   fprintf(stdout, "Max distance from zero point : %f \n", max_distance );
   fprintf(stdout, "Please input max distance from center : ");
   value = atof( fgets(input, 80, stdin) );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * *
* 水分子の発生数を設定するWater関数  *
* * * * * * * * * * * * * * * * * * */
int Water( protein_info *p ){     
  int value;
  float volume;           /* 水分子を実際に発生させる領域の体積を格納する変数 */
  float mol_number;       /* モル数を格納する変数 */
  char determine[80];     /* 画面上の入力を文字列として格納する変数 */

  switch( p -> select_number ){
  case 1 : /* 指定した領域の体積がタンパク質分子の体積より小さければ警告する */
           if( CalcVolume( p -> setup_radius, p -> rand_select_number ) < p -> volume ) 
	     VolumeWarning();
           value = WaterNumber();    /* 数を入力する方法 */
           break;
  case 2 : do{
              volume = SetVolume( p );
              mol_number = WaterMolNumber();     /* モル数を入力する方法 */
	      value = VolumeToNumber( mol_number, volume );   
	      fprintf( stdout, "Making water molecules is %d .\n", value );
	      fprintf( stdout, "Setup above number? [yes/no] : " );
	      fgets( determine, 80, stdin );     /* 画面上の入力を取り込む */

              /* 入力文字が間違っていたら警告する */
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
* 水分子の発生数を設定するWaterNumber関数（直接数を入力する方法）*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int WaterNumber( void ){      
   int value;
   char number[80];    /* コンソールからの入力を受ける変数 */

   /* 水分子の発生数を文字列として取得し、それを整数として返す */
   fprintf(stdout, "How many water molecules do you make : ");
   fgets( number, 80, stdin );
   value = atoi( number );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 水分子の発生数を設定するWaterMolNumber関数（mol濃度を入力する方法）*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
float WaterMolNumber( void ){   
   float value;
   char number[80];    /* コンソールからの入力を受ける変数 */

   /* 水分子の発生数(mol/l単位)を文字列として取得し,それを整数として返す */
   fprintf(stdout, "How many water molecules do you make( mol/l unit ) : ");
   fgets( number , 80, stdin );
   value = atof( number );
   fprintf(stdout, "\n");

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 発生させる水分子の領域の体積を設定するSetVolume関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * */
float SetVolume( protein_info *p ){  
   int value;
   float volume1;        /* 指定した半径を持つ領域の体積を表す変数 */
   float Radius;         /* ユーザーが指定した発生領域の半径を表す変数 */
   float volume2;        /* 最終的に採用された体積 */
 
   /* 発生させる空間の体積を計算する */
   volume1 = CalcVolume( p -> setup_radius, p -> rand_select_number );
 
   /* タンパク質分子の体積と指定された領域の体積を比較して警告する */
   if( volume1 < p -> volume ){
     VolumeWarning();
     volume2 = volume1;    /* 指定領域そのものを体積として使う */
   }
   else volume2 = volume1 - ( p -> volume ); /* 指定領域からタンパク質の体積を差し引く */

   return volume2;

}


/* * * * * * * * * * * * * * * * * * * * * * * *
* 体積に関する警告を発生するVolumeWarning関数  *
* * * * * * * * * * * * * * * * * * * * * * * */
void VolumeWarning( void ){
   char string[80];        /* コンソールからの入力を格納する変数 */

   fprintf( stdout, "Making region is smaller than protein volume.\n" );
   fprintf( stdout, "If continue, you probably need much time to get results.\n");
   fprintf( stdout, "\n" );
   fprintf( stdout, "Continue? [yes/no] : ");
   fgets( string, 80, stdin );

   /* 入力が間違っていたら警告する */
   for(; strncmp( string, "yes", 3 ) && strncmp( string, "no", 2 ); ){
     fprintf( stdout, "Please input yes or no. [yes/no] : ");
     fgets( string, 80, stdin );
   }

   /* 続行するならばそのまま次のステップに進む */
   if( !strncmp( string, "yes", 3 ) )
     fprintf( stdout, "Ok, use volume without reducing protein one.\n");
   else{
     /* 続行しないのならばプログラムを中止する */
     fprintf( stdout, "Sorry, program terminated.\n" );
     exit(EXIT_FAILURE);
   }

   fprintf( stdout, "\n");
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 体積を元に発生させる原子数を計算するVolumeToNumber関数 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int VolumeToNumber( float mol_number, float volume ){
   int value;
  
   /* 発生させる水分子数を体積を元にして計算する */
   value = ( int ) mol_number * Avogadro * volume * 1000;

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
* タンパク質分子の座標重心を求めるMoleculeCenter関数 *
* * * * * * * * * * * * * * * * * * * * * * * * * * */
float MoleculeCenter( protein_info *p ){  
      float total;               /* 各原子の座標の合計値 */
      float value;
      int i;                     /* ループ制御変数 */

      total = 0.0;
  
      /* 仮引数によって選択的にx, y, z座標の合計値を計算する */
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

      /* 座標重心の計算 */
      value = total / p -> data;

      return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* pdbファイルの各座標値を座標重心分だけ平行移動するTranslation関数 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct atom_type *Translation( protein_info *p ){  
   atom_type *atom_trans;    /* 平行移動した後の原子の情報を持つ構造体 */
   int i;                    /* ループ制御変数 */
   int num;                  /* 原子数を表す変数 */

   /* タンパク分子の原子数を格納する */
   num = p -> data;

   /* 構造体atom_transのためにメモリを確保する */
   atom_trans =( atom_type * ) malloc( sizeof( atom_type ) * num);
   if( NULL == atom_trans ){
     fprintf(stderr, "Memory not allocated in Translation \n");
     exit(EXIT_FAILURE);
   }

   /* 新しい構造体に平行移動した後のデータを格納する */
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

   /* 平行移動させた後の原子の情報をポインタで返す */ 
   return atom_trans;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* タンパク質分子の体積を近似的に計算するTotalVolume関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float TotalVolume( protein_info *p ){
   float volume;
   float radius;        /* 各原子の半径を格納する変数 */
   int case_number;     /* 原子の種類を示す変数 */
   int i;               /* ループ制御変数 */

   /* 変数の初期化 */
   volume = 0.0;

   for( i = 0; i < (p -> data); i++ ){
     /* 各原子の種類に応じて半径を設定する */
     case_number = TypeSet( ( (p -> atoms) + i ) -> type );
     radius = SetRadius( case_number );       

     volume = volume + CalcVolume( radius, 2 );      /* 全体の体積を計算する */
   }

   return volume;

}
  

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* 中心からの距離を引数として体積を返すCalcVolume関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * */
float CalcVolume( float r, int num ){
   float value;
 
   switch( num ){
   case 1: value = 8.0 * r * r * r * 1e-30;   /* 体積の計算(立方体) */
                   break;
   case 2: value = 4.0 / 3.0 * PI * r * r * r * 1e-30;   /* 体積の計算(球) */
                   break;
   }

   return value;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* 原点中心から最も離れた原子の距離を計算するAtomMaxDistance関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
float AtomMaxDistance( protein_info *p ){ 
   float x, y, z;            /* 各座標の値 */
   float value;              
   float distance[p -> data];    /* 各原子の中心からの距離を格納する配列 */
   float temp;                   /* ダミー変数 */
   int i, j;

   /* 各原子の原点からの距離を計算する */
   for( i = 0; i < p -> data; i++ ){
     x = ( (p -> atoms) + i ) -> x;
     y = ( (p -> atoms) + i ) -> y;
     z = ( (p -> atoms) + i ) -> z;
     distance[i] = sqrt( x * x + y * y + z * z );
   }

   /* 最も原点からの距離が大きいものを順番に探索する */
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
* 出力先のファイル名の入力を促すSetFileName関数  *
* * * * * * * * * * * * * * * * * * * * * * * * */
void *SetFileName( void ){
   char filename[80];    /* コンソールからの入力を受ける変数 */

   /* 出力先のファイルに対するポインタを返す */
   fprintf(stdout, "Please input filename you want to write the data in : ");
   return fgets( filename, 80, stdin );
}


/* * * * * * * * * * * * * * * *
* 乱数を初期化するRandInit関数 *
* * * * * * * * * * * * * * * */
void RandInit( void ){  
   long system_time;       /* システム時間を格納する変数 */
   int timeseed;

   /* システム時間を使ってrand()を初期化する */
   system_time = time( NULL );
   timeseed = (unsigned int) system_time / 2;
   srand(timeseed);

} 
 

/* * * * * * * * * * * * * * * * * * * * * 
* 乱数の発生方法を選択するRandSelect関数 *
* * * * * * * * * * * * * * * * * * * * */
int RandSelect(){    
   char input[80];          /* コンソールからの入力を格納する変数 */
   int number;

   /* コンソール上に設定方法を表示する */
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
* 乱数で座標を発生させるRandCoorOrtho関数（３次元直交座標系）*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float RandCoorOrtho( float Radius ) {  
   float random, value;
 
   /* 乱数を0から1までの値に変換する */
   random = rand() * 1.0 / ( RAND_MAX + 1.0 );

   /* 座標値を作成 */
   value = 2.0 * Radius * ( random - 0.5 );
 
   return value;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 乱数を使って３次元極座標値を発生させるRandCoorPolar関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *RandCoorPolar( float Radius ){  
   float radius;       /* 半径を表す変数 */
   float theta, phi;   /* 角度を表す変数 */
   Coord *oxygen_polar;   /* 極座標値を格納するCoord構造体に対するポインタ */
   float value;
   
   /* 極座標値を格納する構造体のためにメモリを確保する */
   oxygen_polar = ( Coord * ) malloc( sizeof( Coord ) );
   if( oxygen_polar == NULL ){
     fprintf(stderr, "Memory not allocated in RandCoorPolar.\n");
     exit(EXIT_FAILURE);
   }

   /* 動径方向の値を生成する */
   radius = Radius * rand() * 1.0 / ( RAND_MAX + 1.0 );

   /* 角度θ(0<=θ<=π)についての値を生成する */
   theta = Angle();

   /* 角度Φ(0<=Φ<=2π)についての値を生成する */
   phi = 2.0 * Angle();

   /* 極座標値をx, y, zそれぞれの場合について発生させる */
   oxygen_polar -> x = radius * sin( theta ) * cos( phi );
   oxygen_polar -> y = radius * sin( theta ) * sin( phi );
   oxygen_polar -> z = radius * cos( theta );

   return oxygen_polar;

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 一様な角度分布（0からπまで）を棄却法で発生させるAngle関数 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float Angle( void ){                    
   float rand_x, rand_y;   /* x, y座標の乱数値 */ 
   float value;
   int num = 0;

   while( num == 0 ){

      /* 0からπまでの間の乱数を発生させる */
      rand_x = rand() * 1.0 * PI / ( RAND_MAX + 1.0 );

      /* 0から1までの乱数を発生させる */
      rand_y = rand() * 1.0 / ( RAND_MAX + 1.0 );

      /* 条件を満たしていないものは棄却する */
      if( rand_y <= sin( rand_x ) ){
          value = rand_x;
          num = 1;
      }
   }

   return value;
}


/* * * * * * * * * * * * * * * * * * * * * *
* 水分子の半径を設定するSetWaterRadius関数 *
* * * * * * * * * * * * * * * * * * * * * */
float SetWaterRadius( void ){   
   float bond = 0.957;          /* 酸素原子と水素原子の共有結合半径 */
   float hydrogen;
   float value;

   hydrogen = bond / 2;
   value = bond + hydrogen;     /* 水分子を剛体球で仮定した時の半径 */

   return value;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 水分子と各原子が衝突しないかどうか確かめるAtomCheck関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *AtomCheck( protein_info *p ){    
   Coord *oxygen;              /* 酸素原子の座標を格納するためのポインタ */
   Coord *oxygen_polar;    /* 極座標で発生させた酸素原子座標に対するポインタ */
   Dist oxygen_atom;           /* ２原子間の距離を計算するための構造体 */
   Dist *oxygen_atom_distance; /* 上記の構造体へのポインタ */
   float distance;             /* ２原子間の距離 */
   float atom_radius;          /* 各原子を剛体球で近似した時の半径 */
   char typestring[4];         /* pdbファイルに記載された各原子の種類 */
   int i;                      /* ループ制御変数 */
   int num;                    /* 乱数発生方法を示す変数 */
   int case_number;            /* 原子の種類を表す番号 */
   int violate_count;          /* 衝突している原子の数 */

   /* 酸素原子の座標格納のためにメモリを確保 */
   oxygen = ( Coord * ) malloc( sizeof( Coord ) );
   if( NULL == oxygen ){
      fprintf( stderr, "Memory not allocated in AtomCheck \n" );
      exit(EXIT_FAILURE);
   }

   /* 乱数発生方法を設定 */
   num = p -> rand_select_number;
  
   do{
     violate_count = 0;
 
     /* 酸素原子座標を乱数で発生する */
     if( num == 1 ){
       /* 直交座標で酸素原子座標を発生させる */
       oxygen_atom.x1 = RandCoorOrtho( p -> setup_radius );
       oxygen_atom.y1 = RandCoorOrtho( p -> setup_radius );
       oxygen_atom.z1 = RandCoorOrtho( p -> setup_radius );
     }
     else if( num == 2 ){
       /* ３次元極座標で酸素原子を発生させる */
       oxygen_polar = RandCoorPolar( p -> setup_radius );
       oxygen_atom.x1 = oxygen_polar -> x;
       oxygen_atom.y1 = oxygen_polar -> y;
       oxygen_atom.z1 = oxygen_polar -> z;
     }

     /* pdbファイル中の各原子と衝突していないかのチェック */
     for( i = 0; i < p -> data; i++ ){
	oxygen_atom.x2 = ((p -> atoms) + i) -> x;
	oxygen_atom.y2 = ((p -> atoms) + i) -> y;
	oxygen_atom.z2 = ((p -> atoms) + i) -> z;
	oxygen_atom_distance = &oxygen_atom;

        /* ２原子間の距離を計算 */
	distance = SetDistance( oxygen_atom_distance );

        /* 原子の種類を調べてそれに適合した原子半径を返す */
	case_number = TypeSet(strncpy(typestring, (p->atoms + i) -> type, 4));
	atom_radius = SetRadius( case_number );

        /* 衝突した原子があればviolate_atomの値を増やす */
	if( Violation( distance, atom_radius ) ){
	  violate_count++;
          break;         /* violate_atomの値が1になったら即ループを抜ける */
	}
      }
   }while( !violate_count == 0 );     /* violate_atomの値が0になるまで続ける */

   /* 生き残ればこれを座標として格納する */
   oxygen -> x = oxygen_atom.x1;
   oxygen -> y = oxygen_atom.y1;
   oxygen -> z = oxygen_atom.z1;

   return oxygen;
    
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 発生させた酸素原子同士が衝突していないかを最終的に確かめるMainCheck関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Coord *MainCheck( protein_info *p, int MAX ){
    Coord *oxygen1;           /* AtomCheck関数から得た座標値に対するポインタ */
    Coord *water;             /* 最終的に獲得した座標値に対するポインタ */
    Dist oxygen_oxygen;       /* 酸素原子間の距離を計算するための構造体 */
    Dist *oxygen_oxygen_distance;   /* 上記の構造体に対するポインタ */
    float distance;           /* 酸素原子間の距離 */
    int count;                /* 現在までに発生させた酸素数を数える変数 */
    int violate_atom;         /* 衝突している酸素原子数 */
    int i;                    /* ループ制御変数 */

    /* 酸素原子の座標を指定した数だけ格納する構造体のためにメモリを確保する */
    water = ( Coord * ) malloc( sizeof( Coord ) * MAX );
    if( water == NULL ){
      fprintf( stderr, "Memory not allocated in MainCheck \n" );
      exit(EXIT_FAILURE);
    }

    /* ループ制御変数の初期化 */
    count = 0;

    /* 発生中であることを画面に表示する */
    fprintf( stdout, "Total water molecule number is %d.\n", MAX );
    fprintf( stdout, "Now making. Please wait...\n" );

    /* 発生酸素数がMAX値になるまでループを繰り返す */
    do{
      /* 衝突酸素原子数の初期化 */
      violate_atom = 0;

      /* タンパク質分子に衝突しない酸素原子の座標を発生させる */
      oxygen1 = AtomCheck( p );

      /* 構造体に座標値を格納する */
      (water + count) -> x = oxygen1 -> x;
      (water + count) -> y = oxygen1 -> y;
      (water + count) -> z = oxygen1 -> z;

      /* 酸素原子間の距離の計算のため座標値をDist構造体に代入 */
      oxygen_oxygen.x2 = (water + count) -> x;
      oxygen_oxygen.y2 = (water + count) -> y;
      oxygen_oxygen.z2 = (water + count) -> z;

      /* 酸素原子間の距離に対するチェックループの開始 */
      for( i = 0; i < count; i++ ){
        
        /* 酸素原子間の距離の計算 */
        oxygen_oxygen.x1 = (water + i) -> x;
        oxygen_oxygen.y1 = (water + i) -> y;
        oxygen_oxygen.z1 = (water + i) -> z;
        oxygen_oxygen_distance = &oxygen_oxygen;
        distance = SetDistance( oxygen_oxygen_distance );

        /* 水分子同士が衝突していれば変数violate_atomの値を増やす */
	if( Violation( distance, SetWaterRadius() ) ){
	  violate_atom++;
          break;     /* violate_atomの値が1になったら即ループを抜ける */
	}
      }

      /* 衝突している水分子が無ければ次の酸素原子のために数を一つ増やす */
      if( !violate_atom ) count++;
    } while( count < MAX );
        
    return water;

}
         
 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* タンパク質原子が酸素原子と衝突したならば１を返すViolation関数  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int Violation( float radius1, float radius2 ){  
   float water_radius;
   int value;

   /* valueの初期値を０にセット */
   value = 0;
   water_radius = SetWaterRadius();

   /* 原子間距離が半径の和より小さければvalueを１にセット*/
   if( radius1 < water_radius + radius2 ) value = 1;

   return value;

}
   

/* * * * * * * * * * * * * * * * * * * * *
* ２原子間の距離を求めるSetDistance関数  *
* * * * * * * * * * * * * * * * * * * * */
float SetDistance( Dist *p ){   
   float X, Y, Z;         /* ２原子間の座標の差を表す変数 */
   float distance;

   /* ２原子間の座標の差 */
   X = (p -> x1) - (p -> x2);
   Y = (p -> y1) - (p -> y2);
   Z = (p -> z1) - (p -> z2);

   /* 距離の計算 */
   distance = sqrt( X * X + Y * Y + Z * Z );
  
   return distance;
}


/* * * * * * * * * * * * * * * * * * * * * * * * *
* 原子の種類を調べて,原子半径を返すSetRadius関数 *
* * * * * * * * * * * * * * * * * * * * * * * * */
float SetRadius( int case_number ){       
    float radius_value;

    /* 原子の半径をファンデルワールス半径で近似する */
    switch( case_number ){
    case 1: radius_value = 1.55;  /* 窒素原子の半径 */
            break;
    case 2: radius_value = 1.52;  /* 酸素原子の半径 */
            break; 
    case 3: radius_value = 1.40;  /* 水素原子の半径 */
            break;  
    case 4: radius_value = 1.24;  /* 鉄原子の有効半径 */
            break;
    case 5: radius_value = 1.80;  /* リン原子の半径 */
            break;
    case 6: radius_value = 2.15;  /* ストロンチウム原子の有効半径 */
            break;
    case 7: radius_value = 1.80;  /* 硫黄原子の半径 */
            break;
    case 8: radius_value = 1.70;  /* 炭素原子の半径 */
            break;
    }

    return radius_value;
}


/* * * * * * * * * * * * * * * * * * *  
* 文字列を比較する関数TypeSetの作成  *
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
  





