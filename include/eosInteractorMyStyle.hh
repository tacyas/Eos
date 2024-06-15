#ifndef EOS_INTERACTOR_MY_STYLE_HH
#define EOS_INTERACTOR_MY_STYLE_HH

#include <vtkInteractorStyle.h>
#include <stdio.h>
#include <math.h>

#include "tcl.h" 
#include "tk.h"

class eosStereoWindow;
extern int Vtktcl_SafeInit(Tcl_Interp *interp);
class VTK_RENDERING_EXPORT eosInteractorMyStyle : public vtkInteractorStyleSwitch
{
public:
  static eosInteractorMyStyle *New();

  vtkTypeMacro(eosInteractorMyStyle, vtkInteractorStyle);

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

  void SetRenderWindowData(vtkRenderer*,vtkRenderWindowInteractor*);
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

  void SetTclWindowInterp(Tcl_Interp *interp);

  Tcl_Interp* GetTclWindowInterp(void);
  eosInteractorMyStyle();  
  eosInteractorMyStyle(const eosInteractorMyStyle& myStyle);  
  ~eosInteractorMyStyle();  

protected:
  float MotionFactor;

private:
  void SetStereoWindowInformation();
  void ResetStereoWindowInformation();

  void JoyStickPan(void);
  void TrackballPan(void);
  void StereoCameraPanJoyStick();
  void StereoCameraPanTrackball();
  void StereoCameraDollyJoyStick();
  void StereoCameraDollyTrackball();
  static int StereoState;
  static int WindowButtonState;
  static int TJSwitchState;
  static vtkRenderer *Ren,*RenLeft,*RenRight;
  static vtkCamera  *Cam,*CamLeft,*CamRight;

  static vtkRenderWindowInteractor *rwiStereo;
  static vtkRenderWindowInteractor *rwiMain;

  eosStereoWindow *stereoWin;
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
};

#endif