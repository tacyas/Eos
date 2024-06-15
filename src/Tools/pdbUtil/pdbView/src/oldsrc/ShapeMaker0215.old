#include "./ShapeMaker.hh"
#include <string.h>

SphereMaker::SphereMaker()
{
  moleculeRadius = 1.6;
  thetaResolution = 4;
  phiResolution = 4;
  position[0] = 0;
  position[1] = 0;
  position[2] = 0;
}

void SphereMaker::SetPosition(float xx, float yy, float zz)
{
  position[0] = xx;
  position[1] = yy;
  position[2] = zz;

  //cout << form ("SetPosition = %f : %f : %f\n", position[0], position[1], position[2]);
}

void SphereMaker::SetMapper(void* m)
{
  mapper = (vtkPolyDataMapper*)m;
}

vtkPolyDataMapper* SphereMaker::GetMapper()
{
  return mapper;
}

void SphereMaker::SetRadius(double radius)
{
  moleculeRadius = radius;
}

void SphereMaker::SetRadius(char* AtomName)
{
  double radius = 1.75;

  switch(AtomName[strspn(AtomName," ")]){
  case 'C':
    radius = 1.75;
    break;
    
  case 'H':
    radius = 1.17;
    break;
    
  case 'O':
    radius = 1.4;
    break;
    
  case 'S':
    radius = 1.80;
    break;
    
  case 'N':
    radius = 1.55;
    break;
    
  default:
    radius = 1.6;
    break;
    
  }
  moleculeRadius = radius;
  
}





void SphereMaker::SetResolution(int theta, int phi)
{
  thetaResolution = theta;
  phiResolution = phi;
}

void SphereMaker::MAKE()
{

  float temp[3];

  source = vtkSphereSource::New();
  source->SetRadius(moleculeRadius);
  source->SetThetaResolution(thetaResolution);
  source->SetPhiResolution(phiResolution);
  source->SetCenter(position[0] , position[1], position[2]);
  source->GetCenter(temp);

  //cout << form ("GetCenter = %f : %f : %f\n", temp[0], temp[1], temp[2]);
  //cout << form ("Position = %f : %f : %f\n", position[0], position[1], position[2]);

  //  if( mapper == NULL){
    mapper = vtkPolyDataMapper::New();
    // }
  mapper->SetInput(source->GetOutput());


}





CubeMaker::CubeMaker()
{
  Xlength = 1.6;
  Ylength = 1.6;
  Zlength = 1.6;
}

void CubeMaker::SetMapper(void* m)
{
  mapper = (vtkPolyDataMapper*)m;
}

void CubeMaker::SetLength(float x, float y, float z)
{
  Xlength = x;
  Ylength = y;
  Zlength = z;
}

void CubeMaker::MAKE()
{
  source = vtkCubeSource::New();
  source->SetXLength( Xlength );
  source->SetYLength( Ylength );
  source->SetZLength( Zlength );
  source->SetCenter(0,0,0);
  mapper->SetInput(source->GetOutput());
}





CrossMaker::CrossMaker()
{
  length = 1.6;
}

void CrossMaker::SetMapper(void* m)
{
  mapper = (vtkPolyDataMapper*)m;
}

void CrossMaker::SetLength(float x)
{
  length = x;
}

void CrossMaker::MAKE()
{
  source = vtkLineSource::New();
  source->SetPoint1(-1*length, length, 0);
  source->SetPoint2( length, -1*length, 0);
  mapper->SetInput(source->GetOutput());
}


LineMaker::LineMaker()
{

}


void LineMaker::SetMapper(void* m)
{
  mapper = (vtkPolyDataMapper*)m;
}


vtkPolyDataMapper* LineMaker::GetMapper()
{
  return mapper;
}

void LineMaker::MAKE(float point1[3], float point2[3])
{
  source = vtkLineSource::New();
  source->SetPoint1(point1[0], point1[1], point1[2]);
  source->SetPoint2(point2[0], point2[1], point2[2]);
  mapper = vtkPolyDataMapper::New();
  mapper->SetInput(source->GetOutput());
}


