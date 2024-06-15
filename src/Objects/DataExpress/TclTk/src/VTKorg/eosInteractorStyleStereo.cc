#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "./eosStereoWindow.hh"
#include "./eosInteractorStyleStereo.hh"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleSwitch.h"
#include "vtkProp3D.h"
#include "vtkCellPicker.h"
#include "vtkMath.h"

#undef DEBUG
#include "genUtil.h"

int           eosInteractorStyleStereo::StereoState = STEREO_OFF;
int           eosInteractorStyleStereo::TJSwitchState = JOYSTICK;
int           eosInteractorStyleStereo::WindowButtonState = VTKIS_ROTATE;

//---------------------------------------------------------------------------
eosInteractorStyleStereo *eosInteractorStyleStereo::New() 
{
#ifdef DEBUG
  fprintf(stdout, "vtkInteractorStyleStereo in New\n");
#endif
  return new eosInteractorStyleStereo();
}


//----------------------------------------------------------------------------
eosInteractorStyleStereo::eosInteractorStyleStereo():vtkInteractorStyleSwitch() 
{
#ifdef DEBUG
	fprintf(stderr, "vtkInteractorStyle in Constructor: P %p\n", this);
#endif
	this->State     = VTKIS_NONE;	
	this->AnimState = VTKIS_ANIM_OFF;
    this->UseTimers = 1;
	this->MotionFactor=60.0;
	this->Ren=NULL;
	this->RenRight=NULL;
	this->RenLeft=NULL;
	this->TclWindowInterp=NULL;
}

//----------------------------------------------------------------------------
eosInteractorStyleStereo::~eosInteractorStyleStereo() 
{
  vtkRenderWindowInteractor* rwi = this->Interactor;
  vtkCamera* cam = Ren->GetActiveCamera();
  vtkCamera* camRight = RenLeft->GetActiveCamera();
  vtkCamera* camLeft = RenRight->GetActiveCamera();
  
#ifdef DEBUG
	fprintf(stderr, "vtkInteractorStyle in Destructor: P %p\n", this);
#endif
	if(RenLeft!=NULL) {
		if ( this->OutlineActor ) {
		// if we change style when an object is selected, we must remove the
	    // actor from the renderer
			if (this->CurrentRenderer) {
	    		Ren->RemoveActor(this->OutlineActor);
	      		RenLeft->RemoveActor(this->OutlineActor);
	     		RenRight->RemoveActor(this->OutlineActor);
			}
			this->OutlineActor->Delete();
		}
		if ( this->OutlineMapper ) {
			this->OutlineMapper->Delete();
		}
		this->Outline->Delete();
		this->Outline = NULL;
      
		if(this->CurrentRenderer) {
			if(this->CurrentRenderer==Ren) {
				fprintf(stderr, "CurrentRendere: Ren      in ~eosInteractorStyleStereo\n");
			} else if(this->CurrentRenderer==RenLeft) {
				fprintf(stderr, "CurrentRendere: RenLeft  in ~eosInteractorStyleStereo\n");
			} else if(this->CurrentRenderer==RenRight) {
				fprintf(stderr, "CurrentRendere: RenRight in ~eosInteractorStyleStereo\n");
			}
			Ren->UnRegister(rwi);
			Ren = NULL;
			RenLeft->UnRegister(rwi);
			RenLeft = NULL;
			RenRight->UnRegister(rwi);
			RenRight = NULL;
		}
		if(cam!=NULL){
			cam->Delete();
		}
		if(camRight!=NULL){
			camRight->Delete();
		}
		if(camLeft!=NULL){
			camLeft->Delete();
		}
		//StereoState=STEREO_OFF;
	} else{
		if ( this->OutlineActor ) {
			// if we change style when an object is selected, we must remove the
			// actor from the renderer
			if (this->CurrentRenderer){
				this->CurrentRenderer->RemoveActor(this->OutlineActor);
			}
			this->OutlineActor->Delete();
		}
		if ( this->OutlineMapper ){
			this->OutlineMapper->Delete();
		}
		this->Outline->Delete();
		this->Outline = NULL;
      
		if ( this->CurrentRenderer){
			this->CurrentRenderer->UnRegister(this);
			this->CurrentRenderer = NULL;
		}
      
	}
}

//----------------------------------------------------------------------------

void eosInteractorStyleStereo::SetAutoAdjustCameraClippingRange( int value )
{
	if ( value == this->AutoAdjustCameraClippingRange ){
		return;
	}
  
	if ( value < 0 || value > 1 ){
    	vtkErrorMacro("Value must be between 0 and 1 for" <<
        	          " SetAutoAdjustCameraClippingRange");
   		 return;
	}
  
	this->AutoAdjustCameraClippingRange = value;
	this->Modified();
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::ResetCameraClippingRange()
{
	if ( this->AutoAdjustCameraClippingRange ){
		if (StereoState==STEREO_ON){
			RenLeft->ResetCameraClippingRange();
			RenRight->ResetCameraClippingRange();
		}   
		Ren->ResetCameraClippingRange();
	}
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnChar() 
{
	vtkRenderWindowInteractor* rwi = this->Interactor;

	int ctrl = rwi->GetControlKey();
	int shift = rwi->GetShiftKey();
    char keycode = rwi->GetKeyCode();

  switch (keycode) { 
  	case SPACE: { 
        if(StereoState==STEREO_OFF) { /* Create a stereo-view window */
			this->EyeState=CROSS_EYE;
	        this->CreateStereoWindow();
	    } else if(StereoState==STEREO_ON){ /* Delete the stereo-view window */
			this->DeleteStereoWindow();
			this->EyeState=NOMAL_EYE;
	    }
        break;
	}
	case 'c':{
		if(StereoState==STEREO_ON){
			if(this->EyeState==CROSS_EYE){
				this->EyeState=PARALLEL_EYE;
				this->RenRight->GetActiveCamera()->Azimuth(3.5*EyeState);
				this->RenLeft->GetActiveCamera()->Azimuth(-3.5*EyeState);
            	if(TclWindowInterp!=NULL){
            		Tcl_Eval(TclWindowInterp,"$vtkw configure -width 500  -height 250");
            	} else{ 
                	this->Interactor->GetRenderWindow()->SetSize(500,250);
            	}
			} else if(this->EyeState==PARALLEL_EYE){
				this->EyeState=CROSS_EYE;
				this->RenRight->GetActiveCamera()->Azimuth(3.5*EyeState);
				this->RenLeft->GetActiveCamera()->Azimuth(-3.5*EyeState);
				if(TclWindowInterp!=NULL){
				    Tcl_Eval(TclWindowInterp,"$vtkw configure -width 800  -height 400");
				} else{
					this->Interactor->GetRenderWindow()->SetSize(800,400);
				}
			}
		}
		break;
	}
	case 'q':
    case 'e':{
		fprintf(stdout,"Can't exit. If you want exit, you push 'Q' or 'E'. \n");
		break;
	}
    case 'Q':
    case 'E': {
		if(TclWindowInterp!=NULL){
		    Tcl_Eval(TclWindowInterp,"vtkCommand DeleteAllObjects");		
		    Tcl_Eval(TclWindowInterp,"exit");
		} else{
			rwi->TerminateApp();
		}
      	break;
	}
	case 'I': {
		fprintf(stderr, "priority: %g %g enabled: %d %d \n", 
			this->GetPriority(), rwi->GetInteractorStyle()->GetPriority(), 
			this->GetEnabled(),  rwi->GetInteractorStyle()->GetEnabled()); 
		break;
	}
	case 't':{
		TJSwitchState = TRACKBALL;
		break;
	}
	case 'j':{
		TJSwitchState = JOYSTICK;
		break;
	}
	
    case 'r' :
    case 'R' :{
		this->FindPokedRenderer(rwi->GetEventPosition()[0], 
    	                         rwi->GetEventPosition()[1]);
		Ren->ResetCamera();
		if (StereoState == STEREO_ON){
			RenRight->ResetCamera();
			RenLeft->ResetCamera();
		}

//		if(StereoState==STEREO_ON){
//			Ren->Render();
//		}else if(StereoState==STEREO_OFF){
//			RenRight->Render();
//			RenLeft->Render();
//		}else{
			rwi->Render();
//		}
		
		break;  
	}
	default: {
  		vtkInteractorStyle::OnChar();
		break;
	}
  }
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnButtonFromWindow (char* ButtonCode)
{
	DEBUGPRINT("Start OnButtonFromWindows\n");

	if(!strcmp(ButtonCode,"CrossMode")){
		DEBUGPRINT1("StereoON StereoState=%d\n",StereoState);
		if(this->EyeState != CROSS_EYE){
			this->EyeState = CROSS_EYE;
			if(StereoState==STEREO_OFF){
				this->CreateStereoWindow();
			} else{
				if(this->RenRight!=NULL && this->RenLeft!=NULL){
					this->RenRight->GetActiveCamera()->Azimuth(3.5*EyeState);
					this->RenLeft->GetActiveCamera()->Azimuth(-3.5*EyeState);
					if(TclWindowInterp!=NULL){
						Tcl_Eval(TclWindowInterp,"$vtkw configure -width 800  -height 400");
					} else{
						this->Interactor->GetRenderWindow()->SetSize(800,400);
					}
				}
			}		
		}
    } else if(!strcmp(ButtonCode,"NomalMode")){
        if(StereoState == STEREO_ON) {
            this->DeleteStereoWindow();
        } 
		this->EyeState=NOMAL_EYE;
    } else if(!strcmp(ButtonCode,"ParallelMode")){
	    if(this->EyeState != PARALLEL_EYE){
            this->EyeState = PARALLEL_EYE;
            if(StereoState==STEREO_OFF){
                this->CreateStereoWindow();
            } else{
				if(this->RenRight!=NULL && this->RenLeft!=NULL){
	                this->RenRight->GetActiveCamera()->Azimuth(3.5*EyeState);
    	            this->RenLeft->GetActiveCamera()->Azimuth(-3.5*EyeState);
					if(TclWindowInterp!=NULL){
						Tcl_Eval(TclWindowInterp,"$vtkw configure -width 500  -height 250");
					} else{
					   this->Interactor->GetRenderWindow()->SetSize(500,250);
					}
				}
            }
        }
	} else if(!strcmp(ButtonCode,"PanMode")){
		this->WindowButtonState=VTKIS_PAN;
    } else if(!strcmp(ButtonCode,"DollyMode")){
        this->WindowButtonState=VTKIS_DOLLY;
    } else if(!strcmp(ButtonCode,"SpinMode")){
        this->WindowButtonState=VTKIS_SPIN;
	} else if(!strcmp(ButtonCode,"RotateMode")){
        this->WindowButtonState=VTKIS_ROTATE;
    } else if(!strcmp(ButtonCode,"Reset")){
        this->Interactor->SetKeyCode('r');
	    this->OnChar();
    } else if(!strcmp(ButtonCode,"Trackball")){
		TJSwitchState = TRACKBALL;
    } else if(!strcmp(ButtonCode,"JoyStick")){
		TJSwitchState = JOYSTICK;
    }
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnMouseMove()
{
	if(TJSwitchState == JOYSTICK){
		this->OnMouseMoveJoyStick();
	} else if(TJSwitchState == TRACKBALL){
		this->OnMouseMoveTrackball();
	}
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnMouseMoveTrackball()
{
  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];

  switch (this->State)
    {
    case VTKIS_ROTATE:
      this->FindPokedRenderer(x, y);
      this->Rotate();
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;

    case VTKIS_PAN:
      this->FindPokedRenderer(x, y);
      this->Pan();
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;

    case VTKIS_DOLLY:
      this->FindPokedRenderer(x, y);
      this->Dolly();
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;

    case VTKIS_SPIN:
      this->FindPokedRenderer(x, y);
      this->Spin();
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;
    }

}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnMouseMoveJoyStick()
{
  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];

  switch (this->State)
    {
    case VTKIS_ROTATE:
    case VTKIS_PAN:
    case VTKIS_DOLLY:
    case VTKIS_SPIN:
      this->FindPokedRenderer(x, y);
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;
    }
}

//----------------------------------------------------------------------------

void eosInteractorStyleStereo::OnLeftButtonDown() 
{
	vtkRenderWindowInteractor* iren = this->Interactor;
	this->FindPokedRenderer(iren->GetEventPosition()[0], iren->GetEventPosition()[1]);

#ifdef DEBUG
	fprintf(stdout, "LeftButtonDown on is %p iren %p\n", this, iren);
	fprintf(stdout, "at (%d, %d)\n", iren->GetEventPosition()[0], iren->GetEventPosition()[1]);
	fprintf(stdout, "shift: %d ctrl: %d\n", iren->GetShiftKey(), iren->GetControlKey());
#endif

	if(this->CurrentRenderer == NULL) {
		fprintf(stderr, "LeftButtonDown But No Renderer\n");
		return;
	}
	
	if (iren->GetShiftKey()) { // I haven't got a Middle button !
		if (iren->GetControlKey()) {
			this->StartDolly();
		} else {
			this->StartPan();
		}
	} else {
		if (iren->GetControlKey()) {
			this->StartSpin();
		} else {
			switch(WindowButtonState) {
				case VTKIS_SPIN: {
					this->StartSpin();
					break;
				}
				case VTKIS_DOLLY: {
					this->StartDolly();
#ifdef DEBUG
fprintf(stdout, "In OnLeftButtonDown after StartDolly this->State=%d\n",this->State);
#endif
					break;
				}
				case VTKIS_PAN: {
					this->StartPan();
					break;
				}
				default : {	
					this->StartRotate();
					break;
				}
			}
		}
	}
#ifdef DEBUG
fprintf(stdout, "In OnLeftButtonDown  WindowButtonState:%d\n", WindowButtonState);
#endif
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnLeftButtonUp() 
{
	switch (this->State) {
		case VTKIS_DOLLY: {
	    	this->EndDolly();
	    	break;  
		}
	  	case VTKIS_PAN: {
	    	this->EndPan();
	    	break;  
		}
	  	case VTKIS_SPIN: {
	    	this->EndSpin();
	    	break;  
		}
	  	case VTKIS_ROTATE: {
#ifdef DEBUG
			fprintf(stderr, "OnLeftButtonUp: EndRotate: %d\n", this->State);
#endif 
			this->EndRotate() ;
	    	break;  
		}
		default: {
			fprintf(stderr, "Not supported Mode for State: %d\n", this->State);
			this->State = VTKIS_NONE;
			break;
		}
	}	
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnMiddleButtonDown()
{
  this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], 
                          this->Interactor->GetEventPosition()[1]);
  if (this->CurrentRenderer == NULL)
    {
    return;
    }
  
  this->StartPan();
}
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnMiddleButtonUp()
{
  switch (this->State)
    {
    case VTKIS_PAN:
      this->EndPan();
      break;
    }
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnRightButtonDown()
{
  this->FindPokedRenderer(this->Interactor->GetEventPosition()[0],
                          this->Interactor->GetEventPosition()[1]);
  if (this->CurrentRenderer == NULL)
    {
    return;
    }

  this->StartDolly();
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnRightButtonUp()
{
  switch (this->State)
    {
    case VTKIS_DOLLY:
      this->EndDolly();
      break;
    }
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetInteractor(vtkRenderWindowInteractor *iren)
{
  this->vtkInteractorStyle::SetInteractor(iren);
}

//----------------------------------------------------------------------------
void  eosInteractorStyleStereo::StartState(int newstate) 
{
	this->vtkInteractorStyle::StartState(newstate); 
}

//----------------------------------------------------------------------------
void  eosInteractorStyleStereo::StopState() 
{
	this->vtkInteractorStyle::StopState();
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::OnTimer(void) 
{
  vtkRenderWindowInteractor *rwi = this->Interactor;
  switch (this->State) 
    {
	case VTKIS_NONE:
      // JCP Animation control
		if (this->AnimState == VTKIS_ANIM_ON) {
			if(this->UseTimers) {
				rwi->DestroyTimer();
			}

			if(StereoState==STEREO_ON){
            	Ren->Render();
        	}else if(StereoState==STEREO_OFF){
            	RenRight->Render();
           	 	RenLeft->Render();
        	}else{  
            	rwi->Render();
        	}
       
			if(this->UseTimers) {
				rwi->CreateTimer(VTKI_TIMER_FIRST);
			}
		}
      	// JCP Animation control 
      break;
	  
    case VTKIS_ROTATE:  // rotate with respect to an axis perp to look
	  switch(StereoState) {
			case STEREO_ON: {
      			this->StereoCameraRotate(rwi->GetLastEventPosition()[0], 
				                         rwi->GetLastEventPosition()[1]);
				break;
			}
			case STEREO_OFF: {
				this->Rotate();
				break;
			}
		}
		if(this->UseTimers) {
			rwi->CreateTimer(VTKI_TIMER_UPDATE);
		}	
	  
      break;
	 
    case VTKIS_PAN: // move perpendicular to camera's look vector
      switch(StereoState){
			case STEREO_ON:{
				this->StereoCameraPan(rwi->GetLastEventPosition()[0],
									  rwi->GetLastEventPosition()[1]);
	 			break;
			}
			case STEREO_OFF:{
      			this->Pan();
				break;
			}
	  }
	  if(this->UseTimers) {
      	  rwi->CreateTimer(VTKI_TIMER_UPDATE);
	  }
     break;
      //-----
    case VTKIS_ZOOM:
      this->Dolly();
	  if(this->UseTimers) {
	  	rwi->CreateTimer(VTKI_TIMER_UPDATE);
	  }
      break;
      //-----
    case VTKIS_SPIN:
      switch(StereoState){
            case STEREO_ON:{
                this->StereoCameraSpin(rwi->GetLastEventPosition()[0],
                                       rwi->GetLastEventPosition()[1]);
                break;
            }
            case STEREO_OFF:{
                this->Spin();
				break;
			}
		}
		if(this->UseTimers) {
        	rwi->CreateTimer(VTKI_TIMER_UPDATE);
		}   
      break;
      //-----
    case VTKIS_DOLLY:  // move along camera's view vector
      switch(StereoState){
            case STEREO_ON:{
                this->StereoCameraDolly(rwi->GetLastEventPosition()[0],
                                        rwi->GetLastEventPosition()[1]);
                break;  
            }       
            case STEREO_OFF:{
                this->Dolly();
				break;
			}
		}
		if(this->UseTimers) {
        	rwi->CreateTimer(VTKI_TIMER_UPDATE);
		}  
      break;
      //-----
    case VTKIS_USCALE:
      break;
      //-----
    case VTKIS_TIMER:
//      if(StereoState==STEREO_ON){
//          Ren->Render();
//      }else if(StereoState==STEREO_OFF){
//          RenRight->Render();
//          RenLeft->Render();
//      }else{  
          rwi->Render();
//      }       
	  if(this->UseTimers) {
      	rwi->CreateTimer(VTKI_TIMER_UPDATE);
	  }
      break;
	  
       //-----
    default :
      break;
    } 
}
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetStereoCamera(vtkCamera* cam2,vtkCamera* cam3,
                                           double rxf, double ryf)
{
#ifdef DEBUG
	fprintf(stderr, "CurrentCam: %p cam2: %p cam3: %p \n",
		this->CurrentRenderer->GetActiveCamera(), cam2, cam3);
#endif

	if(cam2 == NULL || cam3 ==NULL){
		return;
	}
	
	this->CurrentRenderer->GetActiveCamera()->Azimuth(rxf);
	this->CurrentRenderer->GetActiveCamera()->Elevation(ryf);
  	this->CurrentRenderer->GetActiveCamera()->OrthogonalizeViewUp();

	cam2->SetPosition(this->CurrentRenderer->GetActiveCamera()->GetPosition());
	cam2->SetFocalPoint(this->CurrentRenderer->GetActiveCamera()->GetFocalPoint());
	cam2->SetViewUp(this->CurrentRenderer->GetActiveCamera()->GetViewUp());
 	cam2->Elevation(ryf);
	cam2->OrthogonalizeViewUp();
    cam3->SetPosition(this->CurrentRenderer->GetActiveCamera()->GetPosition());
    cam3->SetFocalPoint(this->CurrentRenderer->GetActiveCamera()->GetFocalPoint());
    cam3->SetViewUp(this->CurrentRenderer->GetActiveCamera()->GetViewUp());
    cam3->Elevation(ryf);  
    cam3->OrthogonalizeViewUp();

}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::Rotate()
{
	if (Ren == NULL || StereoState == STEREO_ON){
		return;
	}

	vtkRenderWindowInteractor* rwi = this->Interactor;
	vtkCamera* cam = Ren->GetActiveCamera();

	if(TJSwitchState==JOYSTICK){
		float *center = Ren->GetCenter();

		float jdx = (float)rwi->GetEventPosition()[0] - center[0];
		float jdy = (float)rwi->GetEventPosition()[1] - center[1];

		float *vp = Ren->GetViewport();
		int *jsize = rwi->GetSize();

		float jde = (vp[3] - vp[1])*jsize[1];
		float jda = (vp[2] - vp[0])*jsize[0];

		if (jde == 0) jde = 1;
		if (jda == 0) jda = 1;

		float j_delta_elevation = -20.0/(jde);
		float j_delta_azimuth = -20.0/(jda);

		double jrxf = (double)jdx * j_delta_azimuth;
		double jryf = (double)jdy * j_delta_elevation;

		cam->Azimuth(jrxf);
		cam->Elevation(jryf);
		cam->OrthogonalizeViewUp();

	 } else if(TJSwitchState==TRACKBALL){
		int tdx = rwi->GetEventPosition()[0] - rwi->GetLastEventPosition()[0];
		int tdy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];
  
		int *tsize = Ren->GetRenderWindow()->GetSize();

		if (tsize[1] == 0) tsize[1] = 1;
		if (tsize[0] == 0) tsize[0] = 1;

		float t_delta_elevation = -20.0 / tsize[1];
		float t_delta_azimuth = -20.0 / tsize[0];
  
		double trxf = (double)tdx * t_delta_azimuth * this->MotionFactor;
		double tryf = (double)tdy * t_delta_elevation * this->MotionFactor;
  
		cam->Azimuth(trxf);
		cam->Elevation(tryf);
		cam->OrthogonalizeViewUp();
	}


	if (this->AutoAdjustCameraClippingRange){
		Ren->ResetCameraClippingRange();
	}

	if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
	}

//	if(StereoState==STEREO_ON){
//		RenRight->Render();
//		RenLeft->Render();
//	} else if(StereoState==STEREO_OFF){
//		Ren->Render();
//	} else{
		this->Interactor->Render();
//	}
}
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::Spin()
{
   if (Ren == NULL || StereoState == STEREO_ON){
        return;
    }

  vtkRenderWindowInteractor* rwi = this->Interactor;
  vtkCamera* cam = Ren->GetActiveCamera(); 
  float *center = Ren->GetCenter();
  double newAngle;

	if(TJSwitchState==JOYSTICK){
		// Spin is based on y value

		double yf = ((double)rwi->GetEventPosition()[1] - (double)center[1]);

		if(center[1] == 0.0) center[1] = 1.0;

		yf = yf / (double)(center[1]);

		if (yf > 1){
			yf = 1;
		} else if (yf < -1){
			yf = -1;
    	}

		newAngle = asin(yf) * vtkMath::RadiansToDegrees();
	} else if(TJSwitchState==TRACKBALL){
		newAngle =
			atan2((double)rwi->GetEventPosition()[1] - (double)center[1],
   				(double)rwi->GetEventPosition()[0] - (double)center[0]);
 		double oldAngle =
			atan2((double)rwi->GetLastEventPosition()[1] - (double)center[1],
          		(double)rwi->GetLastEventPosition()[0] - (double)center[0]);
  
		newAngle *= vtkMath::RadiansToDegrees();
		oldAngle *= vtkMath::RadiansToDegrees();
		newAngle = newAngle - oldAngle;
	}
#ifdef DEBUG
    fprintf(stderr,"In StereoCameraSpin Trackball newAngle = %g\n",newAngle);
#endif

  cam->Roll(newAngle);
  cam->OrthogonalizeViewUp();

//  if(StereoState==STEREO_ON){
//      Ren->Render();
//  }else if(StereoState==STEREO_OFF){
//      RenRight->Render();
//      RenLeft->Render();
//  }else{  
      rwi->Render();
//  }       

}
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::Pan()
{
	if (Ren == NULL || StereoState == STEREO_ON){
        return;
    }
	vtkRenderWindowInteractor* rwi = this->Interactor;
	
	if(TJSwitchState==JOYSTICK)this->JoyStickPan();
    if(TJSwitchState==TRACKBALL)this->TrackballPan();	
    if (this->Interactor->GetLightFollowCamera()){
          this->CurrentRenderer->UpdateLightsGeometryToFollowCamera();
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{  
        rwi->Render();
//    }       
}

void eosInteractorStyleStereo::JoyStickPan()
{
  vtkRenderWindowInteractor* rwi = this->Interactor;
  vtkCamera* cam = Ren->GetActiveCamera();
  double ViewFocus[4];
  double NewPickPoint[4];
  double focalDepth;
  double *ViewPoint;
  double MotionVector[3];

  // Calculate the focal depth since we'll be using it a lot

  cam->GetFocalPoint(ViewFocus);
  this->ComputeWorldToDisplay(ViewFocus[0], ViewFocus[1], ViewFocus[2],
                              ViewFocus);
  focalDepth = ViewFocus[2];

  this->ComputeDisplayToWorld((float)rwi->GetEventPosition()[0],
                              (float)rwi->GetEventPosition()[1],
                              focalDepth,
                              NewPickPoint);

  // Get the current focal point and position

  cam->GetFocalPoint(ViewFocus);
  ViewPoint = cam->GetPosition();

  // Compute a translation vector, moving everything 1/10
  // the distance to the cursor. (Arbitrary scale factor)

  MotionVector[0] = 0.1 * (ViewFocus[0] - NewPickPoint[0]);
  MotionVector[1] = 0.1 * (ViewFocus[1] - NewPickPoint[1]);
  MotionVector[2] = 0.1 * (ViewFocus[2] - NewPickPoint[2]);

  cam->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                        MotionVector[1] + ViewFocus[1],
                        MotionVector[2] + ViewFocus[2]);

  cam->SetPosition(MotionVector[0] + ViewPoint[0],
                      MotionVector[1] + ViewPoint[1],
                      MotionVector[2] + ViewPoint[2]);

  if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
  }
}

void eosInteractorStyleStereo::TrackballPan()
{
  vtkCamera* cam = Ren->GetActiveCamera();
  vtkRenderWindowInteractor* rwi = this->Interactor;
  double viewFocus[4], focalDepth, viewPoint[3];
  float newPickPoint[4], oldPickPoint[4], motionVector[3];
  
  // Calculate the focal depth since we'll be using it a lot

  cam->GetFocalPoint(viewFocus);
  this->ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2], 
                              viewFocus);
  focalDepth = viewFocus[2];

  this->ComputeDisplayToWorld((double)rwi->GetEventPosition()[0], 
                              (double)rwi->GetEventPosition()[1],
                              focalDepth, 
                              newPickPoint);
    
  // Has to recalc old mouse point since the viewport has moved,
  // so can't move it outside the loop

  this->ComputeDisplayToWorld((double)rwi->GetLastEventPosition()[0],
                              (double)rwi->GetLastEventPosition()[1],
                              focalDepth, 
                              oldPickPoint);
  
  // Camera motion is reversed

  motionVector[0] = oldPickPoint[0] - newPickPoint[0];
  motionVector[1] = oldPickPoint[1] - newPickPoint[1];
  motionVector[2] = oldPickPoint[2] - newPickPoint[2];
  
  cam->GetFocalPoint(viewFocus);
  cam->GetPosition(viewPoint);
  cam->SetFocalPoint(motionVector[0] + viewFocus[0],
                     motionVector[1] + viewFocus[1],
                     motionVector[2] + viewFocus[2]);

  cam->SetPosition(motionVector[0] + viewPoint[0],
                   motionVector[1] + viewPoint[1],
                   motionVector[2] + viewPoint[2]);
}
//----------------------------------------------------------------------------

void eosInteractorStyleStereo::Dolly()
{
   if (Ren == NULL || StereoState == STEREO_ON){
        return;
    }

    vtkRenderWindowInteractor* rwi = this->Interactor;
    vtkCamera* cam = Ren->GetActiveCamera();
	float *center = Ren->GetCenter();
    int    tdy;
    double jdy;
    double dyf;
    double zoomFactor;

	if(TJSwitchState==JOYSTICK){
		jdy = (double)rwi->GetEventPosition()[1] - (double)center[1];
		dyf = 0.5 * jdy;
		if (center[1] == 0) center[1] = 1;
		dyf = dyf / (double)center[1];
	} else if(TJSwitchState==TRACKBALL){
		tdy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];
		dyf = this->MotionFactor * (double)(tdy) / (double)(center[1]);
		zoomFactor = pow((double)1.1, dyf);
	}

	zoomFactor = pow((double)1.1, dyf);

	if(TJSwitchState==JOYSTICK){
		if (zoomFactor < 0.5 || zoomFactor > 1.5){
			vtkErrorMacro("Bad zoom factor encountered");
		}
	}


	if (cam->GetParallelProjection()){
		cam->SetParallelScale(cam->GetParallelScale() / zoomFactor);
	} else{
		cam->Dolly(zoomFactor);
		if (this->AutoAdjustCameraClippingRange){
			Ren->ResetCameraClippingRange();
		}
	}

	if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{  
        rwi->Render();
//    }       
}
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::StereoCameraRotate(int x,int y)
{
    if (RenRight == NULL || RenLeft == NULL ||StereoState == STEREO_OFF){
        return; 
    }

  vtkProp3D *InteractionProp = NULL;
  vtkCellPicker *InteractionPicker = vtkCellPicker::New();
  vtkRenderWindowInteractor *rwi = this->Interactor;
  vtkCamera* camRight = RenLeft->GetActiveCamera();
  vtkCamera* camLeft = RenRight->GetActiveCamera();
  vtkCamera* cam = Ren->GetActiveCamera();
  int *Size = rwi->GetSize();
	  
  float *vp = this->CurrentRenderer->GetViewport();
  float *Center = this->CurrentRenderer->GetCenter();

  double rxf;
  double ryf;
  int dx=1;
  int dy=1;

	if(TJSwitchState==JOYSTICK){
		  float de = (vp[3] - vp[1])*Size[1];
		  float da = (vp[2] - vp[0])*Size[0];

		if(de==0)de=1;
		if(da==0)da=1;
		float DeltaElevation = -20.0/de;
		float DeltaAzimuth = -20.0/da;
	
		InteractionPicker->Pick(x,y,0.0,this->CurrentRenderer);
		vtkProp *prop = InteractionPicker->GetProp();

		if(prop!=NULL){
			InteractionProp = vtkProp3D::SafeDownCast(prop);
		} else{
			InteractionProp = NULL;
		}

		//float* Center = InteractionProp->GetCenter();
     
		rxf = (double)(x - Center[0]) * DeltaAzimuth;
		ryf = (double)(y - Center[1]) * DeltaElevation;

	} else if(TJSwitchState==TRACKBALL){
        dx = rwi->GetEventPosition()[0] - rwi->GetLastEventPosition()[0];
        dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];

        int *size = this->CurrentRenderer->GetRenderWindow()->GetSize();

        if (size[1] == 0) size[1] = 1;
        if (size[0] == 0) size[0] = 1;

        float t_delta_elevation = -20.0 / size[1];
        float t_delta_azimuth = -20.0 / size[0];
  
        rxf = (double)dx * t_delta_azimuth * this->MotionFactor;
        ryf = (double)dy * t_delta_elevation * this->MotionFactor;

	}
	if(this->CurrentRenderer->GetActiveCamera()==cam){
		SetStereoCamera(camLeft,camRight,rxf,ryf);
		camLeft->Azimuth(3.5*EyeState+rxf);      
		camRight->Azimuth(-3.5*EyeState+rxf);      
	} else if(this->CurrentRenderer->GetActiveCamera()==camLeft){
		SetStereoCamera(cam,camRight,rxf,ryf);
		camRight->Azimuth(-7.0*EyeState+rxf);
		cam->Azimuth(-3.5*EyeState+rxf);         
	} else if(this->CurrentRenderer->GetActiveCamera()==camRight){
		SetStereoCamera(camLeft,cam,rxf,ryf);
		camLeft->Azimuth(7.0*EyeState+rxf);
		cam->Azimuth(3.5*EyeState+rxf);
	}
	
	if (this->AutoAdjustCameraClippingRange){
		Ren->ResetCameraClippingRange();
		RenLeft->ResetCameraClippingRange();
		RenRight->ResetCameraClippingRange();
	}

	if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
        RenRight->UpdateLightsGeometryToFollowCamera();
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{  
        rwi->Render();
//    }       
}

//----------------------------------------------------------------------------
 void eosInteractorStyleStereo::StereoCameraPan(int x,int y)
{
	if (this->CurrentRenderer == NULL){
		return;
	}

	if(TJSwitchState==JOYSTICK){
		this->StereoCameraPanJoyStick();
	} else if(TJSwitchState==TRACKBALL){
		this->StereoCameraPanTrackball();
	}
}

void eosInteractorStyleStereo::StereoCameraPanJoyStick()
{
	vtkRenderWindowInteractor *rwi = this->Interactor;
	vtkCamera* cam = Ren->GetActiveCamera();
	vtkCamera* camLeft = RenRight->GetActiveCamera();
	vtkCamera* camRight = RenLeft->GetActiveCamera();
	double ViewFocus[4];
	double NewPickPoint[4];
 
  // Calculate the focal depth since we'll be using it a lot
	vtkCamera* camera = this->CurrentRenderer->GetActiveCamera();
	camera->GetFocalPoint(ViewFocus);
	this->ComputeWorldToDisplay(ViewFocus[0], ViewFocus[1], ViewFocus[2],
                              ViewFocus);
	double focalDepth = ViewFocus[2];

	this->ComputeDisplayToWorld((float)rwi->GetEventPosition()[0],
  	                            (float)rwi->GetEventPosition()[1],
  	                            focalDepth,
  	                            NewPickPoint);

  // Get the current focal point and position
	cam->GetFocalPoint(ViewFocus);
    camRight->GetFocalPoint(ViewFocus);
    camLeft->GetFocalPoint(ViewFocus);
	double *ViewPoint = camera->GetPosition();

  // Compute a translation vector, moving everything 1/10
  // the distance to the cursor. (Arbitrary scale factor)
	double MotionVector[3];
	MotionVector[0] = 0.1 * (ViewFocus[0] - NewPickPoint[0]);
	MotionVector[1] = 0.1 * (ViewFocus[1] - NewPickPoint[1]);
	MotionVector[2] = 0.1 * (ViewFocus[2] - NewPickPoint[2]);

	cam     ->SetFocalPoint(MotionVector[0] + ViewFocus[0],
  	                        MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
    camRight->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                            MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
    camLeft ->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                            MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
  
	cam     ->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);
    camRight->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);
    camLeft ->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);


	if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
        RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{  
        rwi->Render();
//    }       
}

void eosInteractorStyleStereo::StereoCameraPanTrackball()
{
  vtkRenderWindowInteractor *rwi = this->Interactor;
  vtkCamera* cam = Ren->GetActiveCamera();
  vtkCamera* camRight = RenLeft->GetActiveCamera();
  vtkCamera* camLeft = RenRight->GetActiveCamera();

  double viewFocus[4], focalDepth, viewPoint[3];
  float newPickPoint[4], oldPickPoint[4], motionVector[3];
  
  // Calculate the focal depth since we'll be using it a lot

  vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
  camera->GetFocalPoint(viewFocus);
  this->ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2],
                              viewFocus);
  focalDepth = viewFocus[2];          

  this->ComputeDisplayToWorld((double)rwi->GetEventPosition()[0],
                              (double)rwi->GetEventPosition()[1],
                              focalDepth, 
                              newPickPoint);
    
  // Has to recalc old mouse point since the viewport has moved,
  // so can't move it outside the loop

  this->ComputeDisplayToWorld((double)rwi->GetLastEventPosition()[0],
                              (double)rwi->GetLastEventPosition()[1],
                              focalDepth, 
                              oldPickPoint);
  
  // Camera motion is reversed

  motionVector[0] = oldPickPoint[0] - newPickPoint[0];
  motionVector[1] = oldPickPoint[1] - newPickPoint[1];
  motionVector[2] = oldPickPoint[2] - newPickPoint[2];
  
  cam->GetFocalPoint(viewFocus);
  cam->GetPosition(viewPoint);
  cam->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  cam->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);

  camRight->GetFocalPoint(viewFocus);
  camRight->GetPosition(viewPoint);
  camRight->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  camRight->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);

  camLeft->GetFocalPoint(viewFocus);
  camLeft->GetPosition(viewPoint);
  camLeft->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  camLeft->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);
   
   
  if (rwi->GetLightFollowCamera()){
     	Ren->UpdateLightsGeometryToFollowCamera();
   		RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
  }

//  if(StereoState==STEREO_ON){
//      Ren->Render();
//  }else if(StereoState==STEREO_OFF){
//      RenRight->Render();
//      RenLeft->Render();
//  }else{  
      rwi->Render();
//  }       
}
//----------------------------------------------------------------------------
 void eosInteractorStyleStereo::StereoCameraDolly(int x,int y)
 {
    if (CurrentRenderer == NULL){
        return;
    }
	if(TJSwitchState==JOYSTICK){ 
		this->StereoCameraDollyJoyStick();
	} else if(TJSwitchState==TRACKBALL){
		this->StereoCameraDollyTrackball();
	}
 }

void eosInteractorStyleStereo::StereoCameraDollyJoyStick()
{ 
  vtkRenderWindowInteractor *rwi = this->Interactor;
  vtkCamera* cam = Ren->GetActiveCamera();
  vtkCamera* camRight = RenLeft->GetActiveCamera();
  vtkCamera* camLeft = RenRight->GetActiveCamera();

  float *center = this->CurrentRenderer->GetCenter();

  if(center[1]==0)center[1]=1;
  double dy = (double)rwi->GetEventPosition()[1] - (double)center[1];
  double dyf = 0.5 * dy / (double)center[1];
  double zoomFactor = pow((double)1.1, dyf);

  if (zoomFactor < 0.5 || zoomFactor > 1.5){
    vtkErrorMacro("Bad zoom factor encountered");
    }
  
  
	if (cam->GetParallelProjection()){
		cam->SetParallelScale(cam->GetParallelScale() / zoomFactor);
    } else{
        cam->Dolly(zoomFactor);
        if (((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
            ((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
        }
    }

	if (camRight->GetParallelProjection()){
        camRight->SetParallelScale(camRight->GetParallelScale() / zoomFactor);
    } else{
        camRight->Dolly(zoomFactor);
        if (((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
            ((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
        }
    }
 
	if (camLeft->GetParallelProjection()){
        camLeft->SetParallelScale(camLeft->GetParallelScale() / zoomFactor);
	} else{
		camLeft->Dolly(zoomFactor);
		if (((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
			((vtkInteractorStyle*)rwi->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
		}
    }

  if (rwi->GetLightFollowCamera()){
    Ren->UpdateLightsGeometryToFollowCamera();
	RenLeft->UpdateLightsGeometryToFollowCamera();
	RenRight->UpdateLightsGeometryToFollowCamera();
    }

//  if(StereoState==STEREO_ON){
//      Ren->Render();
//  }else if(StereoState==STEREO_OFF){
//      RenRight->Render();
//      RenLeft->Render();
//  }else{  
      rwi->Render();
//  }       
}
 
void eosInteractorStyleStereo::StereoCameraDollyTrackball()
{ 
	vtkRenderWindowInteractor *rwi = this->Interactor;
	vtkCamera* cam = Ren->GetActiveCamera();
	vtkCamera* camRight = RenLeft->GetActiveCamera();
	vtkCamera* camLeft = RenRight->GetActiveCamera();
	float *center = this->CurrentRenderer->GetCenter();

	int dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];
  
	if(center[1]==0)center[1]=1;

	double dyf = this->MotionFactor * (double)(dy) / (double)(center[1]);
	double zoomFactor = pow((double)1.1, dyf);

	if (cam->GetParallelProjection()){
    	cam->SetParallelScale(cam->GetParallelScale()/zoomFactor);
	} else{
		cam->Dolly(zoomFactor);
		if (this->AutoAdjustCameraClippingRange){
			Ren->ResetCameraClippingRange();
		}
	}

    if (camRight->GetParallelProjection()){
        camRight->SetParallelScale(camRight->GetParallelScale()/zoomFactor);
    } else{
        camRight->Dolly(zoomFactor);
        if (this->AutoAdjustCameraClippingRange){
            RenLeft->ResetCameraClippingRange();
        }
    }

    if (camLeft->GetParallelProjection()){
        camLeft->SetParallelScale(camLeft->GetParallelScale()/zoomFactor);
    } else{
        camLeft->Dolly(zoomFactor);
        if (this->AutoAdjustCameraClippingRange){
            RenRight->ResetCameraClippingRange();
        }
    }

 	if (rwi->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
		RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{  
        rwi->Render();
//    }       
}
 //----------------------------------------------------------------------------
  void eosInteractorStyleStereo::StereoCameraSpin(int x,int y)
  {
    if (this->CurrentRenderer == NULL){
        return;
    }

  vtkCamera* cam = Ren->GetActiveCamera();
  vtkCamera* camRight = RenLeft->GetActiveCamera();
  vtkCamera* camLeft = RenRight->GetActiveCamera();
  vtkRenderWindowInteractor *rwi = this->Interactor;
  float *center = this->CurrentRenderer->GetCenter();
   double newAngle;

  // Spin is based on y value

	if(TJSwitchState==JOYSTICK){
		double yf = ((double)rwi->GetEventPosition()[1] - (double)center[1]);
		if (center[1] == 0.0) center[1] = 1.0;
 		yf = yf / (double)(center[1]);
		
		if(yf > 1){
			yf = 1; 
		} else if(yf < -1){
			yf = -1;
    	}
		newAngle = asin(yf) * vtkMath::RadiansToDegrees();
#ifdef DEBUG
    fprintf(stderr,"In StereoCameraSpin JoyStick\n");
#endif	
	} else if(TJSwitchState==TRACKBALL){
		newAngle =
    		atan2((double)rwi->GetEventPosition()[1] - (double)center[1],
       		(double)rwi->GetEventPosition()[0] - (double)center[0]);
		double oldAngle =
  			atan2((double)rwi->GetLastEventPosition()[1] - (double)center[1],
       		(double)rwi->GetLastEventPosition()[0] - (double)center[0]);
rwi->SetEventInformation(rwi->GetEventPosition()[0],rwi->GetEventPosition()[1],rwi->GetControlKey(),rwi->GetShiftKey(),rwi->GetKeyCode(),rwi->GetRepeatCount(),rwi->GetKeySym()); 
		newAngle *= vtkMath::RadiansToDegrees();
		oldAngle *= vtkMath::RadiansToDegrees();
		newAngle = newAngle-oldAngle;
#ifdef DEBUG
    fprintf(stderr,"In StereoCameraSpin Trackball newAngle = %g curPos=%d,%d lasPos=%d,%d\n",newAngle,rwi->GetEventPosition()[0],rwi->GetEventPosition()[1],rwi->GetLastEventPosition()[0],rwi->GetLastEventPosition()[1]);
#endif
	
  }	
  cam->Roll(newAngle);
  cam->OrthogonalizeViewUp();
  camRight->Roll(newAngle);
  camRight->OrthogonalizeViewUp();
  camLeft->Roll(newAngle);
  camLeft->OrthogonalizeViewUp();

//  if(StereoState==STEREO_ON){
//      Ren->Render();
//  }else if(StereoState==STEREO_OFF){
//      RenRight->Render();
//      RenLeft->Render();
//  }else{  
      rwi->Render();
//  }       
}
  
//----------------------------------------------------------------------------
void eosInteractorStyleStereo::DeleteXwindow(Display* disp, Window win)
{
	XDestroyWindow(disp, win);
	XFlush(disp);
}

//          Create/Delete StereoWindow
//---------------------------------------------------------------------------
// 
void eosInteractorStyleStereo::DeleteStereoWindow()
{
	StereoState=STEREO_OFF;
	this->Interactor->GetRenderWindow()->RemoveRenderer(RenRight);
	this->Interactor->GetRenderWindow()->RemoveRenderer(RenLeft);
	this->Interactor->GetRenderWindow()->AddRenderer(Ren);
	this->Ren->GetActiveCamera()->SetFocalPoint(this->RenRight->GetActiveCamera()->GetFocalPoint());
	this->Ren->GetActiveCamera()->SetPosition(this->RenRight->GetActiveCamera()->GetPosition());
	this->Ren->GetActiveCamera()->SetViewUp(this->RenRight->GetActiveCamera()->GetViewUp());
	this->Ren->GetActiveCamera()->SetRoll(this->RenRight->GetActiveCamera()->GetRoll());
	this->Ren->GetActiveCamera()->SetViewAngle(this->RenRight->GetActiveCamera()->GetViewAngle());
	
	if(TclWindowInterp!=NULL){
   		Tcl_Eval(TclWindowInterp,"$vtkw configure -width 400  -height 400");
    	Tcl_Eval(TclWindowInterp,"$vtkw Render");
	} else{
		this->Interactor->GetRenderWindow()->SetSize(400,400);

//        if(StereoState==STEREO_ON){
//            Ren->Render();
//        }else if(StereoState==STEREO_OFF){
//            RenRight->Render();
//            RenLeft->Render();
//        }else{  
            this->Interactor->Render();
//        }       
	}
}

void eosInteractorStyleStereo::CreateStereoWindow()
{
	StereoState=STEREO_ON;
	this->Interactor->GetRenderWindow()->RemoveRenderer(Ren);
	this->Interactor->GetRenderWindow()->AddRenderer(RenRight);
	this->Interactor->GetRenderWindow()->AddRenderer(RenLeft);
	this->RenRight->GetActiveCamera()->SetFocalPoint(this->Ren->GetActiveCamera()->GetFocalPoint());
    this->RenLeft->GetActiveCamera()->SetFocalPoint(this->Ren->GetActiveCamera()->GetFocalPoint());
    this->RenRight->GetActiveCamera()->SetPosition(this->Ren->GetActiveCamera()->GetPosition());
    this->RenLeft->GetActiveCamera()->SetPosition(this->Ren->GetActiveCamera()->GetPosition());
    this->RenRight->GetActiveCamera()->SetViewUp(this->Ren->GetActiveCamera()->GetViewUp());
    this->RenLeft->GetActiveCamera()->SetViewUp(this->Ren->GetActiveCamera()->GetViewUp());
    this->RenRight->GetActiveCamera()->SetRoll(this->Ren->GetActiveCamera()->GetRoll());
    this->RenLeft->GetActiveCamera()->SetRoll(this->Ren->GetActiveCamera()->GetRoll());
    this->RenRight->GetActiveCamera()->SetViewAngle(this->Ren->GetActiveCamera()->GetViewAngle());
    this->RenLeft->GetActiveCamera()->SetViewAngle(this->Ren->GetActiveCamera()->GetViewAngle());
	this->RenRight->GetActiveCamera()->Azimuth(3.5*EyeState);
	this->RenLeft->GetActiveCamera()->Azimuth(-3.5*EyeState);
	
	if(TclWindowInterp!=NULL){
		if(EyeState==CROSS_EYE){
			Tcl_Eval(TclWindowInterp,"$vtkw configure -width 800  -height 400");
		} else if(EyeState==PARALLEL_EYE){
			Tcl_Eval(TclWindowInterp,"$vtkw configure -width 500  -height 250");
		}
	} else{
		this->Interactor->GetRenderWindow()->SetSize(800,400);
	}
	//Tcl_Eval(TclWindowInterp,"$vtkw Render");

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{
        this->Interactor->Render();
//    }
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetTclWindowInterp(Tcl_Interp *interp)
{
  if(interp!=NULL){
     this->TclWindowInterp = interp;
   } else {
   	 fprintf(stderr, "interp is NULL in SetTclWindowInterp");
   }
}
//----------------------------------------------------------------------------
Tcl_Interp* eosInteractorStyleStereo::GetTclWindowInterp()
{
 return TclWindowInterp;
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetRenderer(eosStereoRenderer* sren)
{
	#ifdef DEBUG
		printf("in SetRenderer for eosStereoRenderer\n");
	#endif
	
	Ren     = sren->GetMainRenderer();
	RenRight= sren->GetRightRenderer();
	RenLeft = sren->GetLeftRenderer();

    vtkCamera *camRight=vtkCamera::New();
    vtkCamera *camLeft=vtkCamera::New();
    camRight->SetFocalPoint(sren->GetActiveCamera()->GetFocalPoint());
    camLeft->SetFocalPoint(sren->GetActiveCamera()->GetFocalPoint());
    camRight->SetPosition(sren->GetActiveCamera()->GetPosition());
    camLeft->SetPosition(sren->GetActiveCamera()->GetPosition());
    camRight->ParallelProjectionOn();
    camLeft->ParallelProjectionOn();
    RenRight->SetActiveCamera(camLeft);
    RenLeft->SetActiveCamera(camRight);

	Ren->GetRenderWindow()->GetInteractor()->Render();
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetRenderer(vtkRenderer* ren,vtkRenderer* renRight,vtkRenderer* renLeft)
{
	Ren = ren;
	if(renRight!=NULL && renLeft!=NULL){
		RenRight = renRight;
		RenLeft  = renLeft;
	}
	if(this->Interactor!=NULL){
        this->Interactor->Render();
	}
#ifdef DEBUG
	fprintf(stderr,"in SetRenderer1 this->Interactor=%p\n",this->Interactor);
#endif
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::SetRenderer(vtkRenderer* ren)
{
	Ren=ren;
    RenRight = vtkRenderer::New();
    RenLeft  = vtkRenderer::New();

	camRight=vtkCamera::New();
	camLeft=vtkCamera::New();
	camRight->SetFocalPoint(ren->GetActiveCamera()->GetFocalPoint());
    camLeft->SetFocalPoint(ren->GetActiveCamera()->GetFocalPoint());
	camRight->SetPosition(ren->GetActiveCamera()->GetPosition());
    camLeft->SetPosition(ren->GetActiveCamera()->GetPosition());

	camRight->ParallelProjectionOn();
	camLeft->ParallelProjectionOn();
	RenRight->SetActiveCamera(camLeft);
	RenLeft->SetActiveCamera(camRight);
	
	//renRight->AddLight((vtkLight*)ren->GetLights()->GetItemAsObject(0));
   	//renLeft->AddLight((vtkLight*)ren->GetLights()->GetItemAsObject(0));

    //lightKitRight = vtkLightKit::New();
    //lightKitRight -> AddLightsToRenderer(RenLeft); 
    //lightKitRight -> SetKeyLightAzimuth(3.5);
    //lightKitLeft  = vtkLightKit::New();
    //lightKitLeft  -> AddLightsToRenderer(RenRight);
    //lightKitLeft  -> SetKeyLightAzimuth(-3.5);
		
	RenRight->SetViewport(0.0,0.0,0.5,1.0);
	RenLeft->SetViewport(0.5,0.0,1.0,1.0);

	for(int i=0;;i++){
		if((vtkActor*)ren->GetActors()->GetItemAsObject(i)==NULL) break;
		RenRight->AddActor((vtkActor*)ren->GetActors()->GetItemAsObject(i));
		RenLeft->AddActor((vtkActor*)ren->GetActors()->GetItemAsObject(i));
	}

    Ren->Render();
	
#ifdef DEBUG
    fprintf(stderr,"in SetRenderer2 this->Interactor=%p\n",this->Interactor);
#endif
}

//----------------------------------------------------------------------------
vtkRenderer* eosInteractorStyleStereo::GetMainRenderer()
{
	return Ren;
}
//----------------------------------------------------------------------------
vtkRenderer* eosInteractorStyleStereo::GetRightRenderer()
{
	return RenRight;
}

//----------------------------------------------------------------------------
vtkRenderer* eosInteractorStyleStereo::GetLeftRenderer()
{
	return RenLeft;
}

//----------------------------------------------------------------------------
void eosInteractorStyleStereo::CameraMove(double x,double y,double z)
{
	if(Ren!=NULL){
		this->Ren->GetActiveCamera()->SetPosition(x,y,z);
	}
	if(Ren!=NULL && RenRight!=NULL && RenLeft!=NULL){
		this->RenRight->GetActiveCamera()->SetPosition(x,y,z);
		this->RenLeft->GetActiveCamera()->SetPosition(x,y,z);
	}

//    if(StereoState==STEREO_ON){
//        Ren->Render();
//    }else if(StereoState==STEREO_OFF){
//        RenRight->Render();
//        RenLeft->Render();
//    }else{
        this->Interactor->Render();
//    }
	
}