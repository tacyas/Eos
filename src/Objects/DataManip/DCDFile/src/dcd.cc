#include "../inc/DCDFile.h"
#include "mrcImage.h"

/*

*/

DCD::DCD()
{ 
  seek=0;
  fp = NULL; // Initialize the DCD file pointer
  x = NULL;
  y = NULL;
  z = NULL;
  XCenterPosition = NULL;
  YCenterPosition = NULL;
  ZCenterPosition = NULL;
  dist = NULL;
  coordinate_data = new float[1];
}

DCD::~DCD()
{
  delete coordinate_data;
}

int DCD::tagRead(FILE* fp, int seek)
{
	int tag=0;

	fseek(fp, seek, SEEK_SET);
	fread(&tag, sizeof(int), 1, fp);
	return tag;
}

void DCD::HeaderRead(char* in_filename)
{
  int i;
  char* head_data;
  int branch;
  int headerSize = 0;
  int tag_data;
  //int offSet;

  Open(in_filename, "r");
  //seek= ftell(fp);
  //offSet = seek;

  for(branch=0;branch<HeaderBranchNumber; branch++) {
    tag_data  = tagRead(fp, seek);
    head_data = (char*)malloc(sizeof(char)*tag_data); 
    fread(head_data,sizeof(char), tag_data+4, fp);
    seek      = ftell(fp);

    switch(branch) { 
      case 0: {
        nfile        = (int)*((int*)(head_data+4*1));
        step1        = (int)*((int*)(head_data+4*2));
        stepInterval = (int)*((int*)(head_data+4*3));
        totalRun     = (int)*((int*)(head_data+4*4));
        if((step1+stepInterval*(nfile-1))!=totalRun) totalRun=step1+stepInterval*(nfile-1);
	break;
      }
      case 1: {
        for(i=4;i<tag_data-4;i++) {    
          file_title[i-4]=head_data[i];
        }
        file_title[i] = '\0';
        break;	
      }
      case 2: {
        atomicity=(int)*((int*)(head_data));
	break;
      }
    }

    headerSize +=tag_data+tagSize*2;
    free(head_data);
  }
  Close();

  if(headerSize!=HeaderSize) {
    fprintf(stderr, "Something Strange!! HeaderSize is different: %d (current) != %d (expected)\n", headerSize, HeaderSize);
  }
}

void DCD::HeaderWrite(FILE* fp)
{
  for(int i=0; i<HeaderBranchNumber; i++) { 
    HeaderWrite(fp, i);
  }
}
   
void DCD::HeaderWrite(FILE* fp, int branch)
{
  switch(branch) {
    case 0: {
      fprintf(fp,"file = %d\n",  nfile);
      fprintf(fp,"step1 = %d\n", step1);
      fprintf(fp,"stepInterval = %d\n",stepInterval);
      fprintf(fp,"totalRun = %d\n", totalRun);
      break;
    }
    case 1: { 
      fprintf(fp,"title = << ");
      fprintf(fp,"%s",file_title);
      fprintf(fp," >>");
      fprintf(fp,"\n");
      break;
    }
    case 2: {
      fprintf(fp,"atomicity=%d\n",atomicity);
      break;
    }
  }
}
   
void DCD::Open(char* filename,char* mode)
{ 
  if((fp=fopen(filename,mode))==NULL)
  {
   if(mode=="r")
   {
     cout << "NOT INPUTFILE!!\n" << endl;   
     exit(1);
   }
   if(mode=="w" || mode=="a")
   {
     cout << "NOT OUTPUTFILE!!\n" << endl;   
     exit(1);
   }
  }
}

void DCD::Close()
{  
  fclose(fp);
  fp = NULL;
}

void DCD::Authentication(int start,int end,int interval)
{
 if(nfile>=100)
 {
   if(start>end)
   {
    cout <<"****************" << endl;
    cout <<"<<Input error!>>" << endl;
    cout <<"  start > end   " << endl;
    cout <<"****************" << endl;
    exit(0);
   }
   for(STEP=step1;STEP<=totalRun;STEP+=stepInterval)
   { 
     if(start==STEP)
     {  
       for(STEP2=step1;STEP2<=totalRun;STEP2+=stepInterval)
       {       
 	 if(end==STEP2)
	 {   
           for(SINTERVAL=stepInterval;SINTERVAL<=totalRun;SINTERVAL+=stepInterval)
	   {
	     if(interval==SINTERVAL) return;
             else
             {	    
               cout <<"*************************" << endl;
	       cout <<"  <<Input error!>>" << endl;
	       cout <<"##Error--->stepInterval##" << endl;
	       cout <<"step1=" << step1 << endl;
	       cout <<"stepInterval=" << stepInterval << endl;
	       cout <<"totalRun=" << totalRun << endl;
               cout <<"*************************" << endl;
	       exit(0);
             }
	   }
	 }
	 if(STEP2+stepInterval>totalRun)
         { 
           for(SINTERVAL=stepInterval;SINTERVAL<=totalRun;SINTERVAL+=stepInterval)
	   {
             cout <<"*********************" << endl;
	     cout <<"  <<Input error!>>" << endl;
	     cout <<"##Error--->totalRun##" << endl;
	     cout <<"step1=" << step1 << endl;
	     cout <<"stepInterval=" << stepInterval << endl;
	     cout <<"totalRun=" << totalRun << endl;
             cout <<"*********************" << endl;
	     exit(0);
	   } 
	 }   
       }
     } 
   if(STEP+stepInterval>totalRun)
   { 
     cout <<"****************" << endl;
     cout <<"<<Input error!>>" << endl;
     cout <<"##Error--->step1" << endl;
     cout <<"step1=" << step1 << endl;
     cout <<"stepInterval=" << stepInterval << endl;
     cout <<"totalRun=" << totalRun << endl;
     cout <<"****************" << endl;
     exit(0);
   }
  }
 }

 if(nfile<100)
 {
   if(end==100)
   {
     end=nfile;
   }
   else
   {
     if(start>end)
     {
      cout <<"****************" << endl;
      cout <<"<<Input error!>>" << endl;
      cout <<"  start > end   " << endl;
      cout <<"****************" << endl;
      exit(0);
     }
     for(STEP=step1;STEP<=totalRun;STEP+=stepInterval)
     { 
       if(start==STEP)
       {  
         for(STEP2=step1;STEP2<=totalRun;STEP2+=stepInterval)
         {       
 	   if(end==STEP2)
	   {   
             for(SINTERVAL=stepInterval;SINTERVAL<=totalRun;SINTERVAL+=stepInterval)
	     {
	       if(interval==SINTERVAL) return;
               else
               { 	    
                 cout <<"*************************" << endl;
	         cout <<"     <<Input error!>>" << endl;
	         cout <<"##Error--->stepInterval##" << endl;
	         cout <<"step1=" << step1 << endl;
	         cout <<"stepInterval=" << stepInterval << endl;
	         cout <<"totalRun=" << totalRun << endl;
                 cout <<"*************************" << endl;
	         exit(0);
               }
	     }
	   }
	   if(STEP2+stepInterval>totalRun)
           { 
             for(SINTERVAL=stepInterval;SINTERVAL<=totalRun;SINTERVAL+=stepInterval)
	     {
               cout <<"*********************" << endl;
	       cout <<"   <<Input error!>>" << endl;
	       cout <<"##Erorr--->totalRun##" << endl;
	       cout <<"step1=" << step1 << endl;
	       cout <<"stepInterval=" << stepInterval << endl;
	       cout <<"totalRun=" << totalRun << endl;
               cout <<"*********************" << endl;
	       exit(0);
	     } 
	   }   
         }
       } 
     if(STEP+stepInterval>totalRun)
     { 
       cout <<"******************" << endl;
       cout <<" <<Input error!>>" << endl;
       cout <<"##Error--->step1##" << endl;
       cout <<"step1=" << step1 << endl;
       cout <<"stepInterval=" << stepInterval << endl;
       cout <<"totalRun=" << totalRun << endl;
       cout <<"******************" << endl;
       exit(0);
     }
    }
   }
 } 
} 

void DCD::CoordinateNew(int n, int natom)
{
  if(x!=NULL && y!=NULL && z != NULL) {
    CoordinateDelete();
  } 

  x = new float*[n*2];
  y = new float*[n*2];
  z = new float*[n*2];
  for(int ix=0; ix<n*2; ix++) {
    x[ix] = new float[natom];
    y[ix] = new float[natom];
    z[ix] = new float[natom];
  }
}

void DCD::CoordinateNew(int n)
{
  CoordinateNew(n, atomicity);
}

void DCD::CoordinateDelete()
{
  int ix;

  for(ix=0; ix<NumOfLoadedFile; ix++) {
    delete[] x[ix];
    delete[] y[ix];
    delete[] z[ix];
  }
  delete[] x;
  delete[] y;
  delete[] z;
}

void DCD::CoordinateNew()
{
  //CoordinateNew(nfile);

  XDistance = new float*[nfile];
  YDistance = new float*[nfile];
  ZDistance = new float*[nfile];
  Distance= new float*[nfile];
  for(int ix=0; ix<nfile; ix++)
  {
   XDistance [ix] = new float[atomicity];
   YDistance [ix] = new float[atomicity];
   ZDistance [ix] = new float[atomicity];
   Distance[ix] = new float[atomicity];
  }
}

void DCD::CenterPositionNew()
{ 
  if(XCenterPosition!=NULL && YCenterPosition!=NULL &&  ZCenterPosition!= NULL) {
    CenterPositionDelete();
  } 
  XCenterPosition = new float[nfile*100];
  YCenterPosition = new float[nfile*100];
  ZCenterPosition = new float[nfile*100];
 }

void DCD::CenterPositionDelete()
{
  delete[] XCenterPosition;
  delete[] YCenterPosition;
  delete[] ZCenterPosition;
}
 
void DCD::DistNew()
{
  if(dist!=NULL) {
    DistDelete();
  } 
  dist = new int*[200];
  for(int ix=0; ix<200; ix++)
  {
    dist[ix] = new int[nfile];
  }
}

void DCD::DistDelete()
{
  int ix;

  for(ix=0; ix<NumOfLoadedFile; ix++) {
    delete[] dist [ix];
  }
  delete[] dist;
}

void DCD::AveAtomPositionNew()
{
  AveXAtomPosi = new float[atomicity];
  AveYAtomPosi = new float[atomicity];
  AveZAtomPosi = new float[atomicity];
  DistanceRMSD = new float[atomicity];
}

void DCD::atomNumberCheck(int tag_data) 
{
  if(tag_data != atomicity*4) {
	fprintf(stderr, "Something Strange: atomicity (%d) is inconsitent to the tag (%d)\n", \
	    atomicity, tag_data);
	exit(EXIT_FAILURE);
  }
}

void DCD::Read(int start,int end,int interval)
{
  int i, j;
  int tag_data;
  int firstFile;
  int skipBytes;
 
  tag_data = tagRead(fp, HeaderSize); 
  atomNumberCheck(tag_data);
 
  firstFile = (start-step1)/stepInterval;
  skipBytes = HeaderSize + tagSize+(tag_data+tagSize*2)*coordinatesDimension*firstFile;
  fseek(fp, skipBytes, SEEK_SET);

  NumOfLoadedFile = (end-start)/interval + 1; 
  CoordinateNew(NumOfLoadedFile);

  skipBytes = tagSize*2 + (tag_data+2*tagSize)*coordinatesDimension*(interval/stepInterval-1);

  for(i=0; i<NumOfLoadedFile; i++) {
     fread(x[i], sizeof(float), atomicity, fp);

     fseek(fp, tagSize*2, SEEK_CUR);
     fread(y[i], sizeof(float), atomicity, fp);

     fseek(fp, tagSize*2, SEEK_CUR);
     fread(z[i], sizeof(float), atomicity, fp);

     fseek(fp, skipBytes, SEEK_CUR);
  }
}

void DCD::Read(int step)
{
  Read(step*stepInterval, step*stepInterval, stepInterval);
}

void DCD::Write(int start,int end,int interval)
{ 
  int k, i;

  fprintf(fp,"#<start=%d,end=%d,interval=%d>\n",start,end,interval);
    fprintf(fp,"          [X]            [Y]            [Z]\n");
  for(k=0;k<NumOfLoadedFile;k++) { 
    for(i=0;i<atomicity;i++) {  
      fprintf(fp,"%3d : %3.6e  %3.6e  %3.6e\n",i+1,x[k][i],y[k][i],z[k][i]);  
    } 
  }
}

void DCD::Read()
{
  Read(step1, totalRun, stepInterval);
}

void DCD::Write()
{
  Write(step1, totalRun, stepInterval);
}

void DCD::Read(int* step,int* Atom,int nStep,int nAtom)
{
  int i,k,j;
  int tag_data=0;
  int skipBytesPre;	
  int skipBytesPost;	
  int skipBytesStep;	
  int skipBytesMid;
  int firstFile;

    tag_data = tagRead(fp, HeaderSize);
    fseek(fp,HeaderSize+tagSize, SEEK_SET);
    CoordinateNew(nStep);

    for(j=0;j<nStep;j++){
    step[j]=step[j]/stepInterval;
    }

    for(i=0; i<nStep; i++) {
    firstFile = step[i]-1;
    skipBytesStep = HeaderSize + tagSize +(tag_data+tagSize*2)*coordinatesDimension*firstFile;
  //  if(i!=0) skipBytesStep = HeaderSize +(step[i]-step[i-1])* tagSize+(tag_data+tagSize*2)*coordinatesDimension;
    fseek(fp, skipBytesStep, SEEK_SET);
	
    for(k=0; k<nAtom; k++) {
      skipBytesPre  =(Atom[k] - 1)*sizeof(float);
      skipBytesPost =(atomicity - Atom[k])*sizeof(float);
      skipBytesMid  =(Atom[k-1]-Atom[k])*tagSize;	
      
      fseek(fp, skipBytesStep, SEEK_SET);
     // if(k!=0) fseek(fp,skipBytesMid,SEEK_CUR);
      fseek(fp, skipBytesPre, SEEK_CUR);
      fread(&x[i][k], sizeof(float), 1, fp);
      fseek(fp, skipBytesPost, SEEK_CUR);

      fseek(fp, tagSize*2+skipBytesPre,SEEK_CUR);
      fread(&y[i][k], sizeof(float), 1, fp);
      fseek(fp, skipBytesPost, SEEK_CUR);

      fseek(fp, tagSize*2+skipBytesPre,SEEK_CUR);
      fread(&z[i][k], sizeof(float), 1, fp);
      fseek(fp, tagSize*2+skipBytesPre,SEEK_CUR);
      fseek(fp, skipBytesPost+tagSize*2, SEEK_CUR);
     cout << "i="<<i <<"k="<<k<< "x" << x[i][k]<<endl;
    }
  }
}

void DCD::Write(int* step,int* Atom,int nStep,int nAtom)
{
  int i,k;

     for(i=0;i<nStep;i++){
       for(k=0;k<nAtom;k++){
         fprintf(fp," %3d : %3.6e  %3.6e  %3.6e\n",Atom[k], x[i][k],y[i][k],z[i][k]);  
     }
   }
}

void DCD::SelectedAtomGet(int* selectedAtoms, int nAtoms)
{
  int i, k;
  int tag_data;
  int skipBytesPre;
  int skipBytesPost;
     cout <<nAtoms<<endl;
     cout <<selectedAtoms[0]<<endl;
     cout <<selectedAtoms[1] <<endl;
  for(k=0; k<nAtoms; k++) {
    if(selectedAtoms[k] > atomicity) { 
      cout << " << Too big protein !! Atom!! >>" << endl;
      cout << "    Atom = " << atomicity << ". But the selectedAtom is " << selectedAtoms[k] << endl;
    exit(0);
   }
  }

  tag_data = tagRead(fp, HeaderSize);
  atomNumberCheck(tag_data);
  CoordinateNew(nfile, nAtoms);

    for(k=0; k<nAtoms; k++) {
    //tag_data = tagRead(fp, HeaderSize);
    fseek(fp,HeaderSize+tagSize, SEEK_SET);
    skipBytesPre  =(selectedAtoms[k] - 1)*sizeof(float);
    skipBytesPost =(atomicity - selectedAtoms[k])*sizeof(float);
    for(i=0;i<nfile;i++) {
      fseek(fp, skipBytesPre, SEEK_CUR);
      fread(&x[i][k], sizeof(float), 1, fp);
      fseek(fp, skipBytesPost, SEEK_CUR);

      fseek(fp, tagSize*2+skipBytesPre,SEEK_CUR);
      fread(&y[i][k], sizeof(float), 1, fp);
      fseek(fp, skipBytesPost, SEEK_CUR);

      fseek(fp, tagSize*2+skipBytesPre,SEEK_CUR);
      fread(&z[i][k], sizeof(float), 1, fp);
      fseek(fp, skipBytesPost+tagSize*2, SEEK_CUR);
    }
  }
}

void DCD::SelectedAtomWrite(int nAtoms)
{
	int i,k;
  fprintf(fp,"#          [X]            [Y]            [Z]           \n");
   for(k=0;k<nAtoms;k++){
     for(i=0;i<nfile;i++){
       fprintf(fp," %3d : %3.6e  %3.6e  %3.6e\n",(i+1)*stepInterval, x[i][k],y[i][k],z[i][k]);  
     }
   }
}
void DCD::SelectedAtomGet(int selectedAtom)
{
  int Atoms[1];
  Atoms[0] = selectedAtom;
  SelectedAtomGet(Atoms, 1);	
}  

void DCD::SelectedAtomWrite()
{
  SelectedAtomWrite(1);
}
   
void DCD::SelectedAtomsGet(int nAtoms)
{
 int Atoms[nAtoms-1];
 int i;
 for(i=0;i<nAtoms;i++){
   cout << i+1 <<"th Atom? = ";
   cin >> Atoms[i] ;
 }
 SelectedAtomGet(Atoms,nAtoms);
}

void DCD::SelectedAtomsWrite(int nAtoms)
{
 SelectedAtomWrite(nAtoms);
}

void DCD::CenterPositionGet()
{
	int i;
        int j;
        int tag_data;
        double xsum;
        double ysum;
        double zsum;

  CenterPositionNew();
  //tag_data = tagRead(fp, HeaderSize); 
  //fread(&tag_data,sizeof(int),1,fp);
 
  for(i=0;i<nfile;i++){
    Read(i+1);
    xsum=ysum=zsum=0.0;
    for(j=0;j<atomicity;j++){
    xsum+=x[0][j];
    ysum+=y[0][j];
    zsum+=z[0][j];
    }
    XCenterPosition[i]=xsum/atomicity;
    YCenterPosition[i]=ysum/atomicity;
    ZCenterPosition[i]=zsum/atomicity;
   }
}

void DCD::CenterPositionWrite()
{
  int i;
  for(i=0;i<nfile;i++){
   fprintf(fp,"X-CenterPosition=%e\n",XCenterPosition[i]);
   fprintf(fp,"Y-CenterPosition=%e\n",YCenterPosition[i]);
   fprintf(fp,"Z-CenterPosition=%e\n",ZCenterPosition[i]);
  }
}

void DCD::AveragePositionOfAtomGet()
{
  int i,k;
  double xsum,ysum,zsum;
  x=NULL;
  y=NULL;
  x=NULL;

  AveAtomPositionNew();
  for(i=0; i<atomicity; i++){
  cout << "i" << i << endl;
    for(k=0; k<nfile; k++){
     SelectedAtomGet(i+1);
     xsum+=x[k][0];
     ysum+=y[k][0];
     zsum+=z[k][0];
    }
   AveXAtomPosi[i]+=xsum;
   AveYAtomPosi[i]+=ysum;
   AveZAtomPosi[i]+=zsum;
  }
}

void DCD::CenterSelectedAtomDistanceGet(int selectAtom)
{
  CoordinateNew();
  //CenterPositionGet();
  SelectedAtomGet(selectAtom);

  int i; 
  for(i=0; i<nfile; i++)
  {
     XDistance[0][i]=(x[i][0]-XCenterPosition[selectAtom-1])*(x[i][0]-XCenterPosition[selectAtom-1]);  
     YDistance[0][i]=(y[i][0]-YCenterPosition[selectAtom-1])*(y[i][0]-YCenterPosition[selectAtom-1]);  
     ZDistance[0][i]=(z[i][0]-ZCenterPosition[selectAtom-1])*(z[i][0]-ZCenterPosition[selectAtom-1]);
     Distance[0][i]=sqrt(XDistance[0][i]+YDistance[0][i]+ZDistance[0][i]);
  }
}

void DCD::DistanceWrite()
{
  int i;
  for(i=0; i<nfile; i++)
  {
   fprintf(fp,"%3d: %3.6e\n",(i+1)*stepInterval,Distance[0][i]);
  }
}

void DCD::AtomAtomDistanceGet()
{
  int i,k,j;
  int tag_data; 
  int Atoms[1];

  tag_data = tagRead(fp, HeaderSize); 
  fread(&tag_data,sizeof(int),1,fp);

 for(j=0;j<2;j++){
   cout << j+1 <<"th Atom? = ";
   cin >> Atoms[j] ;
 }

  SelectedAtomGet(Atoms,2);
   cout << x[0][0]<<endl;
   cout << x[0][1]<<endl;
  CoordinateNew();
  for(k=0;k<nfile;k++)
 {
     XDistance[0][k]=(x[k][0]-x[k][1])*(x[k][0]-x[k][1]);  
     YDistance[0][k]=(y[k][0]-y[k][1])*(y[k][0]-y[k][1]);  
     ZDistance[0][k]=(z[k][0]-z[k][1])*(z[k][0]-z[k][1]);  
     Distance[0][k]=sqrt(XDistance[0][k]+YDistance[0][k]+ZDistance[0][k]);
  }  
  cout << "Distance" << Distance[0][0] << endl; 
}

void DCD::AtomChangeFromAtomGet(int selectAtom,int selectAtom2)
{
	int i;
        int tag_data;
        int Atoms[1];

  tag_data = tagRead(fp, HeaderSize); 
  fread(&tag_data,sizeof(int),1,fp);
  Atoms[0]=selectAtom;
  Atoms[1]=selectAtom2;
  
  SelectedAtomGet(Atoms,2);
  CoordinateNew();

  for(i=0; i<nfile; i++)
 {
     XDistance[0][i]=(x[0][0]-x[i][1])*(x[0][0]-x[i][1]);  
     YDistance[0][i]=(y[0][0]-y[i][1])*(y[0][0]-y[i][1]);  
     ZDistance[0][i]=(z[0][0]-z[i][1])*(z[0][0]-z[i][1]);  
     Distance[0][i]=sqrt(XDistance[0][i]+YDistance[0][i]+ZDistance[0][i]);
  }
  cout << "Distance" << Distance[0][0] << endl; 
} 

void DCD::DistanceDistribution()
{
	int k, i, j;
        int tag_data;
        int offSet;
		
  tag_data = tagRead(fp, HeaderSize); 
  CoordinateNew();
  DistNew();
  Read();
  seek= ftell(fp);
  offSet = seek;


  for(k=0;k<nfile;k+=100)
  {
  // fprintf(stderr,"file=%d\n",k+1); 
    int atomicity2=atomicity+1;

    for(i=0;i<atomicity;i++)
    {
  // fprintf(stderr,"Atom=%d\n",i+1); 
      atomicity2--;  
      for(j=1;j<atomicity2;j++)
      {
        XDistance[i][j-1]=(x[k][i]-x[k][i+j])*(x[k][i]-x[k][i+j]);  
        YDistance[i][j-1]=(y[k][i]-y[k][i+j])*(y[k][i]-y[k][i+j]);  
        ZDistance[i][j-1]=(z[k][i]-z[k][i+j])*(z[k][i]-z[k][i+j]);
        Distance[i][j-1]=sqrt(XDistance[i][j-1]+YDistance[i][j-1]+ZDistance[i][j-1]);

        float b=0.0;
        for(int a=1;a<200;a++)
        {
          if(Distance[i][j-1]>=b && Distance[i][j-1]<b+0.2)
          dist[a][k]++;
          b+=0.2;
        }
       }
     }
   }
  fseek(fp,offSet+HeaderSize,SEEK_SET);
}

void DCD::DistanceDistributionWriteToMRC(char* filename)
{
  mrcImage mrc;
  int i, j;
  
  mrc.HeaderN.x = 200;
  mrc.HeaderN.y = nfile/100;
  mrc.HeaderN.z = 1;
  mrc.HeaderLength.x = 2;
  mrc.HeaderLength.y = 2;
  mrc.HeaderLength.z = 2;
  mrc.HeaderMode = mrcFloatImage;
  mrcInit(&mrc, NULL);  
   
  for(i=0; i<200; i++) { 
  for(j=0; j<nfile; j+=100) { 
     mrcPixelDataSet(&mrc, i, j/100, 0, dist[i][j], mrcPixelRePart); 
  }
  }

  mrcFileWrite(&mrc, filename, "in DistanceDistributionWriteToMRC", 0);
}

void DCD::DistanceDistributionWrite()
{
	int k;
  for(k=0;k<nfile;k+=100)
  {
    for(int a=1;a<200;a++)
    {
     //fprintf(fp,"%d %d %d\n",(k+1)*stepInterval,a,dist[a][k]);
      fprintf(fp,"%d %d %d\n",a,(k+1)*stepInterval,dist[a][k]);
    }
      fprintf(fp,"\n");
  }
}

void DCD::DistanceOfAtomFromAverageGet()
{
  int tag_data;
  int i,k;
  double xsum,ysum,zsum;

  tag_data = tagRead(fp, HeaderSize); 

 	
  AveragePositionOfAtomGet();
   
  for(i=0; i<atomicity;i++){
   SelectedAtomGet(i);
   for(k=0; k<nfile; k++){
     xsum+=(x[k][0]-AveXAtomPosi[i])*(x[k][0]-AveXAtomPosi[i]);
     ysum+=(y[k][0]-AveYAtomPosi[i])*(y[k][0]-AveYAtomPosi[i]);
     zsum+=(z[k][0]-AveZAtomPosi[i])*(z[k][0]-AveZAtomPosi[i]);
   }
   DistanceRMSD[i]= sqrt((xsum+ysum+zsum)/atomicity);	
  }
}	

void DCD::DistanceOfAtomFromAverageWrite()
{
  int i;

  for(i=0; i<atomicity; i++){
    fprintf(fp,"%d %3.6e\n",i+1,DistanceRMSD[i]);
  }
}
	
void DCD::Write(FILE* fp, pdbFile* pdb, int start, int end, int interval)
{
  int step;

  for(step=start; step<=end; step+=interval) {
    CoordinatesIntoPDB(pdb, step);
    pdbFileWrite(fp, pdb); 
  }
}

//  
// Set the coodinates at the specified step into PDB coordinates 
//
void DCD::CoordinatesIntoPDB(pdbFile* pdb, int step)
{
  int i;
  pdbFileParaTypeReal X, Y, Z;

  Read(step);
 
  pdbFileTop(pdb);
  i = 0;
  while(1) {
    if(pdbFileIsAtom(pdb)) {
      // pdb->PDB->AtomName
      X = x[0][i];
      Y = y[0][i];
      Z = z[0][i];
      pdbFileCoordSet(pdb, X, Y, Z);
      i++;
    }
    if(!pdbFileNextAtom(pdb)) {
	break;
    }
  }
}

void DCD::CoordinateFromPDB(pdbFile* pdb)
{
  int i=0;
  int Atom[1];
 
  cout << "Atom Number? =";
  cin  >>Atom[0]; 

  CenterPositionNew();    
  pdbFileTop(pdb);

  while(1){ 
    if(pdbFileIsAtom(pdb)){
      XCenterPosition[i]=pdb->PDB->Coord.x;
      YCenterPosition[i]=pdb->PDB->Coord.y;
      ZCenterPosition[i]=pdb->PDB->Coord.z;
      i++;
    }
    if(!pdbFileNextAtom(pdb)) {
	break;
   }
  }
    CenterSelectedAtomDistanceGet(Atom[0]);
}

void DCD::Write(FILE* fp, pdbFile* pdb,int* Step, int* Atom, int nStep,int nAtom)
{     
      SelectedCoordinatesIntoPDB(fp,pdb,Step,Atom,nStep,nAtom);
}	

//
//
void DCD::SelectedCoordinatesIntoPDB(FILE* fp,pdbFile* pdb, int* Step, int* Atom, int nStep, int nAtom)
{
  int i,k;
  pdbFileParaTypeReal X,Y,Z;

//  pdbFileWrite(fp,pdb);
  Read(Step,Atom,nStep,nAtom);
   for(k=0; k<nStep; k++){
    for(i=0; i<nAtom; i++){
      pdbFileTop(pdb);
      if(pdbFileIsSelectedAtom(pdb, Atom[i], nStep)){
        X = x[k][i];
        Y = y[k][i];
        Z = z[k][i];
        pdbFileCoordSet(pdb, X, Y, Z);
        pdbFileRecordPrint(fp, pdb);
        cout << x[k][i] <<endl;
      }
    }
//  pdbFileWrite(fp,pdb);
  }
}

long DCD::pdbFileIsSelectedAtom(pdbFile* pdb, int Atom, int nStep)
{
 do { 
    if( 0==strncmp(pdb->PDB->Record, pdbRecordAtom, PDB_FILE_RECORD_LENGTH)  \
        && pdb->PDB->AtomSerialNumber == Atom){
             return 1;
    }
   } while(NULL!=pdbFileNext(pdb));
  return 0;
}     


