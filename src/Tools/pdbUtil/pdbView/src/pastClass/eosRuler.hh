#ifndef EOS_RULER_HH
#define EOS_RULER_HH


class eosRuler{
  
public:
  
  vtkAssembly* assembly;

  vtkCylinderSource* rulerAxis;
  vtkPolyDataMapper* rulerAxisMapper;
  vtkActor* rulerAxisActor;
  
  vtkCylinderSource* ruler;
  vtkPolyDataMapper* rulerMapper;
  vtkActor* rulerActor;
  
  double division;
  double scaleLength;
  double scaleRadius;
  int scaleFace;
  
  int divisionFace;
  double divisionLength;
  double divisionRadius;
  
  int divisionNumber;
  
  int mark;
  double markLength;
  double markRadius;
  
  vtkRenderer* ren;
  
private:
  void reset();
  
  
public:
  eosRuler();
  void SetScaleLength(double l);
  void SetMark(int m);
  void SetDivision(double d);
  void Draw();
  void Draw(vtkRenderer* renderer); 
  
};

#endif /* EOS_RULER_HH */
