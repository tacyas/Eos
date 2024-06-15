#ifndef SHAPE_MAKER_HH
#define SHAPE_MAKER_HH

#include "vtk.h"

class SphereMaker{
private:
  vtkSphereSource* source;
  vtkPolyDataMapper* mapper;
  double moleculeRadius;
  int thetaResolution;
  int phiResolution;
  float position[3];

public:
  SphereMaker();
  void SetMapper(void* m);
  void SetPosition(float xx, float yy, float zz);
  vtkPolyDataMapper* GetMapper();
  void SetRadius(double radius);
  void SphereMaker::SetRadius(char* AtomName);
  void SetResolution(int theta, int phi);
  void MAKE();
};


class CubeMaker{
private:
  vtkCubeSource* source;
  vtkPolyDataMapper* mapper;
  float Xlength;
  float Ylength;
  float Zlength;

public:
  CubeMaker();
  void SetMapper(void* m);
  void SetLength(float x , float y, float z);
  void MAKE();
};


class CrossMaker{
private:
  vtkLineSource* source;
  vtkPolyDataMapper* mapper;
  float length;

public:
  CrossMaker();
  void SetMapper(void* m);
  void SetLength(float x);
  void MAKE();
};



class LineMaker{
private:
  vtkLineSource* source;
  vtkPolyDataMapper* mapper;

public:
  LineMaker();
  void SetMapper(void* m);
  void MAKE(float point1[3], float point2[3]);
  vtkPolyDataMapper* GetMapper();
};




#endif /* SHAPE_MAKER_HH */
