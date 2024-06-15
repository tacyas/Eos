#include<iostream>
#include<string.h>
#include<stdio.h> 
#include<stdlib.h>
#include<math.h>

#include <pdbFile.h>

using namespace std;

class DCD
{
private:
	FILE* fp; 
	static const int HeaderSize = 276;
	static const int HeaderBranchNumber = 3;
	static const int tagSize = 4;
	static const int coordinatesDimension = 3;
// Header Information 
// First Branch
  int     nfile;         // The Number of coordinates files in a file 
  int     step1;         // The step of the first file 
  int     stepInterval;  // Step number between coordinates files
  int     totalRun;      // The step of the last file  
// Second Branch
  char    file_title[300];   
// Third Branch
  int     atomicity;

  int     NumOfLoadedFile;

  int     STEP;   
  int     STEP2;
  int     SINTERVAL;
  float*  coordinate_data;

  float** x;
  float** y;
  float** z;
  int     seek;
  float*  XCenterPosition;
  float*  YCenterPosition;
  float*  ZCenterPosition;
  int     selectAtom;
  float** XDistance; 
  float** YDistance; 
  float** ZDistance; 
  float** Distance;
  int**   dist;
  float*  AveXAtomPosi;
  float*  AveYAtomPosi;
  float*  AveZAtomPosi;
  float*  DistanceRMSD;
public:
  DCD();          
  ~DCD();

  int   tagRead(FILE* fp, int seek);
  void  atomNumberCheck(int tag);
  void  HeaderRead(char* in_filename);
  void  HeaderWrite(FILE* fp);
  void  HeaderWrite(FILE* fp, int branch);
  // DCD File Open/Close 
  void  Open(char* filename,char* mode);
  void  Close();
  // Check start/end/interval
  void  Authentication(int start,int end,int interval);
  // Coordinate Area for all files 	
  void  CoordinateNew();   
  void  CoordinateDelete();   
  void  CoordinateNew(int numOfFilesToBeLoaded);
  void  CoordinateNew(int numOfFilesToBeLoaded, int numOfAtoms);
  void  CenterPositionNew();
  void  CenterPositionDelete();
  void  DistNew();
  void  DistDelete();
  void  AveAtomPositionNew();
  void  AveAtomPositionDelete();

  // Read
  void  Read(int start,int end, int interval);
  void  Read(int step);
  void  Read();
  void  Read(int* step, int* Atom,int nStep, int nAtom);

  // Write 
  void  Write(int* step, int* Atom,int nStep, int nAtom);
  void  Write(int start, int end, int interval);
  void  Write();

  void  CenterPositionGet();
  void  CenterPositionWrite();
  
  // Get the coordinates of selected atoms 
  void  SelectedAtomGet(int* selectAtoms, int nAtom);
  void  SelectedAtomGet(int selectAtom);
  void  SelectedAtomsGet(int nAtoms);

  void  SelectedAtomWrite(int nAtoms);
  void  SelectedAtomWrite();
  void  SelectedAtomsWrite(int nAtoms);

  //Get the change of distance from center
  void  CenterSelectedAtomDistanceGet(int selectAtom);

  //Write the distance
  void  DistanceWrite();

  //Get the change of distance from atom
  void  AtomChangeFromAtomGet(int selectAtom, int selectAtom2);

  void  AtomAtomDistanceGet();
  void  DistanceDistribution();
  void  DistanceDistributionWrite();
  void  DistanceDistributionWriteToMRC(char* filename);

  void DistanceOfAtomFromAverageGet();
  void DistanceOfAtomFromAverageWrite();
  void AveragePositionOfAtomGet();
 
  // related to PDB
  void CoordinateFromPDB(pdbFile* pdb);
  void Write(FILE* fp, pdbFile* pdb, int start, int end, int interval);
  void CoordinatesIntoPDB(pdbFile* pdb, int step);
  void Write(FILE* fp, pdbFile* pdb,int* Step, int* Atom, int nStep, int nAtom);
  void SelectedCoordinatesIntoPDB(FILE* fp, pdbFile* pdb, int* Step, int* Atom, int nStep, int nAtom);
  long pdbFileIsSelectedAtom(pdbFile* pdb, int Atom, int nStep); 
};
