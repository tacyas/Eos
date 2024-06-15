#ifndef EOS_INTERACTOR_STYLE_STEREO_HH
#define EOS_INTERACTOR_STYLE_STEREO_HH

#include <vtkInteractorStyle.h>
#include <vtkLightKit.h>
#include <stdio.h>
#include <math.h>

#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "eosStereoRenderer.hh"

#include "tcl.h" 
#include "tk.h"

extern int Vtktcl_SafeInit(Tcl_Interp *interp);
class VTK_RENDERING_EXPORT eosInteractorStyleStereo : public vtkInteractorStyleSwitch
{
public:
  static eosInteractorStyleStereo* New();

  vtkTypeMacro(eosInteractorStyleStereo, vtkInteractorStyle);

  virtual void OnMouseMove();
  void OnMouseMoveTrackball();
  void OnMouseMoveJoyStick();
  virtual void OnLeftButtonDown();
  virtual void OnLeftButtonUp();
  virtual void OnMiddleButtonDown();
  virtual void OnMiddleButtonUp();
  virtual void OnRightButtonDown();
  virtual void OnRightButtonUp();
  virtual void OnChar   ();

  virtual void OnButtonFromWindow (char* ButtonCode);
  
  void SetInteractor(vtkRenderWindowInteractor *iren);
  void SetStereoInteractor(vtkRenderWindowInteractor *iren);
  void SetAutoAdjustCameraClippingRange( int value );
  void ResetCameraClippingRange(void);

  virtual void StartState(int newstate);
  virtual void StopState();

  void OnTimer();
  void SetStereoCamera(vtkCamera*,vtkCamera*,double,double);
  void Rotate();
  void Spin();
  void Pan();
  void Dolly();
  void StereoCameraRotate(int,int);
  void StereoCameraPan(int,int);
  void StereoCameraDolly(int,int);
  void StereoCameraSpin(int,int);

  void DeleteXwindow(Display* disp, Window win);

  void DeleteStereoWindow(void);
  void CreateStereoWindow(void);

  void SetRenderer(eosStereoRenderer*);
  void SetRenderer(vtkRenderer*,vtkRenderer*,vtkRenderer*);
  void SetRenderer(vtkRenderer*);
 
  void SetTclWindowInterp(Tcl_Interp *interp);
  void CameraMove(double x,double y,double z);

  vtkRenderer* GetMainRenderer();
  vtkRenderer* GetRightRenderer();
  vtkRenderer* GetLeftRenderer();

  Tcl_Interp* GetTclWindowInterp(void);
  eosInteractorStyleStereo();  
  eosInteractorStyleStereo(const eosInteractorStyleStereo& myStyle);  
  ~eosInteractorStyleStereo();  

protected:
  float MotionFactor;

private:
  void JoyStickPan(void);
  void TrackballPan(void);
  void StereoCameraPanJoyStick();
  void StereoCameraPanTrackball();
  void StereoCameraDollyJoyStick();
  void StereoCameraDollyTrackball();

  static int StereoState;
  static int WindowButtonState;
  static int TJSwitchState;
 
  double EyeState;
 
  vtkRenderer *Ren,*RenLeft,*RenRight;
  vtkCamera *camRight,*camLeft;
  vtkLightKit *lightKitRight,*lightKitLeft;
  Tcl_Interp *TclWindowInterp;

  //static const int  VTKIS_CAMERA = 0;
  //static const int  VTKIS_ACTOR = 1;
  static const char SPACE = ' ';  
  static const int  VTKIS_STEREO = 8; 
  static const int  SPACE_ON = 1;
  static const int  SPACE_OFF = 0; 
  static const int  STEREO_ON = 1;
  static const int  STEREO_OFF = 0;
  static const int  TRACKBALL = 0;
  static const int  JOYSTICK = 1;
  static const double  CROSS_EYE = 1;
  static const double  PARALLEL_EYE = -1;
  static const double  NOMAL_EYE = 0;
};

#endif
