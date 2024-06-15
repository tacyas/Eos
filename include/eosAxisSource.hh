#ifndef EOS_AXIS_SOURCE_HH
#define EOS_AXIS_SOURCE_HH


class eosAxisSourceCoord {
public:
  double X;
  double Y;
  double Z;
  float Xcolor[3];
  float Ycolor[3];
  float Zcolor[3];
public:
  eosAxisSourceCoord();
  void Usage();
};

class eosAxisSource{
private:
  vtkConeSource* arrowX;
  vtkConeSource* arrowY;
  vtkConeSource* arrowZ;
  vtkCylinderSource* axisX;
  vtkCylinderSource* axisY;
  vtkCylinderSource* axisZ;
  vtkSphereSource* origin;

  vtkPolyDataMapper* arrowXMapper;
  vtkPolyDataMapper* arrowYMapper;
  vtkPolyDataMapper* arrowZMapper;
  vtkPolyDataMapper* axisXMapper;
  vtkPolyDataMapper* axisYMapper;
  vtkPolyDataMapper* axisZMapper;
  vtkPolyDataMapper* originMapper;
 
  vtkActor* arrowXActor;
  vtkActor* arrowYActor;
  vtkActor* arrowZActor;
  vtkActor* axisXActor;
  vtkActor* axisYActor;
  vtkActor* axisZActor;
  vtkActor* originActor;

  vtkRenderer* renderer;

  vtkAssembly *assembly;

  double scale;
  double length;
  double originalSize;
  double axisRatio;
  double arrowRatio;
  int axisFace;
  int arrowFace;

  eosAxisSourceCoord axisLength;
  eosAxisSourceCoord axisRadius;
  //eosAxisSourceCoord axisFace;
  eosAxisSourceCoord axisColor;

  eosAxisSourceCoord arrowLength;
  eosAxisSourceCoord arrowRadius;
  // eosAxisSourceCoord arrowFace;
  eosAxisSourceCoord arrowColor;

  double originRadius;
  float  originColor[3];

  eosAxisSourceCoord axisPosition;
  eosAxisSourceCoord arrowPosition;

private:
  void reset();

public:
  eosAxisSource();
  void SetScale(double s);
  void SetLength(double l);
  void SetRenderer(vtkRenderer* ren); 
  void Draw(); 
  void Draw(vtkRenderer* ren); 
  void Usage();
};

#endif /* EOS_AXIS_SOURCE_HH */
