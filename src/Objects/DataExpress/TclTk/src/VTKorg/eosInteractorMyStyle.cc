#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "./eosStereoWindow.hh"
#include "./eosInteractorMyStyle.hh"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleSwitch.h"
#include "vtkProp3D.h"
#include "vtkRenderer.h"
#include "vtkCellPicker.h"
#include "vtkMath.h"

#define DEBUG
#include "genUtil.h"

int           eosInteractorMyStyle::StereoState = STEREO_OFF;
int           eosInteractorMyStyle::TJSwitchState = JOYSTICK;
int           eosInteractorMyStyle::WindowButtonState = VTKIS_ROTATE;
vtkRenderer*  eosInteractorMyStyle::Ren=NULL;
vtkRenderer*  eosInteractorMyStyle::RenLeft=NULL;
vtkRenderer*  eosInteractorMyStyle::RenRight=NULL;
vtkCamera*    eosInteractorMyStyle::Cam=NULL;
vtkCamera*    eosInteractorMyStyle::CamLeft=NULL;
vtkCamera*    eosInteractorMyStyle::CamRight=NULL;
vtkRenderWindowInteractor* eosInteractorMyStyle::rwiStereo=NULL;
vtkRenderWindowInteractor* eosInteractorMyStyle::rwiMain=NULL;

//---------------------------------------------------------------------------
eosInteractorMyStyle *eosInteractorMyStyle::New() 
{
#ifdef DEBUG
  fprintf(stdout, "vtkInteractorStyle in New\n");
#endif
  return new eosInteractorMyStyle();
}


//----------------------------------------------------------------------------
eosInteractorMyStyle::eosInteractorMyStyle():vtkInteractorStyleSwitch() 
{
#ifdef DEBUG
	fprintf(stderr, "vtkInteractorStyle in Constructor: P %p\n", this);
#endif
	this->State     = VTKIS_NONE;	
	this->AnimState = VTKIS_ANIM_OFF;
    this->UseTimers = 1;
	this->MotionFactor=60.0;
}

//----------------------------------------------------------------------------
eosInteractorMyStyle::~eosInteractorMyStyle() 
{
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
				fprintf(stderr, "CurrentRendere: Ren      in ~eosInteractorMyStyle\n");
			} else if(this->CurrentRenderer==RenLeft) {
				fprintf(stderr, "CurrentRendere: RenLeft  in ~eosInteractorMyStyle\n");
			} else if(this->CurrentRenderer==RenRight) {
				fprintf(stderr, "CurrentRendere: RenRight in ~eosInteractorMyStyle\n");
			}
	
			RenLeft->UnRegister(rwiStereo);
			RenLeft = NULL;
			RenRight->UnRegister(rwiStereo);
			RenRight = NULL;
		}
		StereoState=STEREO_OFF;
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

void eosInteractorMyStyle::SetAutoAdjustCameraClippingRange( int value )
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
void eosInteractorMyStyle::ResetCameraClippingRange()
{
	if (StereoState==STEREO_ON){
		if ( this->AutoAdjustCameraClippingRange )
		{
			Ren->ResetCameraClippingRange();
			RenLeft->ResetCameraClippingRange();
			RenRight->ResetCameraClippingRange();
		}     
	} else{
		if ( this->AutoAdjustCameraClippingRange ){
			this->CurrentRenderer->ResetCameraClippingRange();
		}
	}
}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::OnChar() 
{
	vtkRenderWindowInteractor* tmpI = this->Interactor;

	int ctrl = tmpI->GetControlKey();
	int shift = tmpI->GetShiftKey();
    char keycode = tmpI->GetKeyCode();

#ifdef DEBUG
  fprintf(stderr, "in OnChar: %d %d %c on MyStyle:%p MyInteractor:%p\n", 
	ctrl, shift, keycode, this, this->Interactor);
#endif

  switch (keycode) { 
  	case SPACE: { 
		StereoState=(~StereoState)&1;
      
        if(StereoState==STEREO_ON) { /* Create a stereo-view window */
	        this->CreateStereoWindow();
	    } else {                     /* Delete the stereo-view window */
#ifdef DEBUG
			fprintf(stderr, "rwiStereo: %p rwiMain: %p\n", rwiStereo, rwiMain);
#endif
			if(rwiStereo!=NULL){
            	this->DeleteStereoWindow();
			}
			rwiMain->Start();
	    }
        break;
	}
	case 'q':
    case 'e':
    case 'Q':
    case 'E': {
#ifdef DEBUG
  		fprintf(stderr, "I wish QUIT!!: %d %d %c on MyStyle:%p MyInteractor:%p rwiMain:%p\n", 
			ctrl, shift, keycode, this,this->Interactor,rwiMain);
#endif
      	if(StereoState==STEREO_ON) {
			StereoState=(~StereoState)&1;
			this->DeleteStereoWindow();
      	}
#ifdef DEBUG
        fprintf(stderr, "I wish MainWindow QUIT!! TclWindowInterp:%p \n",TclWindowInterp);
#endif
		if(TclWindowInterp!=NULL){
		    Tcl_Eval(TclWindowInterp,"vtkCommand DeleteAllObjects");		
		    Tcl_Eval(TclWindowInterp,"exit");
		} else{
			rwiMain->TerminateApp();
		}
      	break;
	}
	case 'I': {
		fprintf(stderr, "priority: %g %g enabled: %d %d \n", 
			this->GetPriority(), rwiMain->GetInteractorStyle()->GetPriority(), 
			this->GetEnabled(),  rwiMain->GetInteractorStyle()->GetEnabled()); 
		break;
	}
    case 'r' :
    case 'R' :{
		this->FindPokedRenderer(rwiMain->GetEventPosition()[0], 
    	                          rwiMain->GetEventPosition()[1]);
		Ren->ResetCamera();
		rwiMain->Render();
#ifdef DEBUG     
    fprintf(stderr, "== In eosInteractorMyStyle OnChar ==\n");
    fprintf(stderr, "Psition cam:%f,%f,%f \n",Cam->GetPosition()[0],Cam->GetPosition()[1],Cam->GetPosition()[2]);
#endif
		if (StereoState == STEREO_ON){
	        this->FindPokedRenderer(rwiStereo->GetEventPosition()[0],
    	                          rwiStereo->GetEventPosition()[1]);
			RenRight->ResetCamera();
			RenLeft->ResetCamera();
			rwiStereo->Render();
#ifdef DEBUG     
    fprintf(stderr, "Psition camRight:%f,%f,%f   camLeft:%f,%f,%f \n",CamRight->GetPosition()[0],CamRight->GetPosition()[1],CamRight->GetPosition()[2],CamLeft->GetPosition()[0],CamLeft->GetPosition()[1],CamLeft->GetPosition()[2]);
#endif

		}
		break;  
	}
	default: {
  		vtkInteractorStyle::OnChar();
		break;
	}
  }
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::OnButtonFromWindow (char* ButtonCode)
{
	DEBUGPRINT("Start OnButtonFromWindows\n");
/*
	switch(ButtonCode){
		case "StereoMode" : {
			StereoState=(~StereoState)&1;
			if(StereoState==STEREO_ON) {
				this->CreateStereoWindow();
			} else {
				StereoState=(~StereoState)&1;
				this->DeleteStereoWindow();
			}
			break;
		}
		case "PanMode" : {
			this->WindowButtonState=VTKIS_PAN;
			break;
		}
		case "DollyMode" : {
			this->WindowButtonState=VTKIS_DOLLY;
			break;
		}
		case "SpinMode" : {
			this->WindowButtonState=VTKIS_SPIN;
			break;
		}
		case "RotateMode" : {
			this->WindowButtonState=VTKIS_ROTATE;
			break;
		}
		case "Reset" : {
			this->Interactor->SetKeyCode('r');
			this->OnChar();
			break;
		}
        case "Trackball" : {
            this->Interactor->SetKeyCode('r');
            this->OnChar();
			break;
        }
        case "JoyStick" : {
            this->Interactor->SetKeyCode('r');
            this->OnChar();
			break;
        }
	}
*/

	if(!strcmp(ButtonCode,"StereoMode")){
		StereoState=(~StereoState)&1;
        if(StereoState==STEREO_ON) {
			DEBUGPRINT1("StereoON StereoState=%d\n",StereoState);
        	this->CreateStereoWindow();
       	} else {
			DEBUGPRINT1("StereoOFF StereoState=%d\n",StereoState);
			StereoState=(~StereoState)&1;
            this->DeleteStereoWindow();
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
void eosInteractorMyStyle::OnMouseMove()
{
	if(TJSwitchState == JOYSTICK){
		this->OnMouseMoveJoyStick();
	} else if(TJSwitchState == TRACKBALL){
		this->OnMouseMoveTrackball();
	}
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::OnMouseMoveTrackball()
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
void eosInteractorMyStyle::OnMouseMoveJoyStick()
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

void eosInteractorMyStyle::OnLeftButtonDown() 
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
void eosInteractorMyStyle::OnLeftButtonUp() 
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
void eosInteractorMyStyle::OnMiddleButtonDown()
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
void eosInteractorMyStyle::OnMiddleButtonUp()
{
  switch (this->State)
    {
    case VTKIS_PAN:
      this->EndPan();
      break;
    }
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::OnRightButtonDown()
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
void eosInteractorMyStyle::OnRightButtonUp()
{
  switch (this->State)
    {
    case VTKIS_DOLLY:
      this->EndDolly();
      break;
    }
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::SetInteractor(vtkRenderWindowInteractor *iren)
{
  this->vtkInteractorStyle::SetInteractor(iren);
}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::SetStereoInteractor(vtkRenderWindowInteractor *irenStereo)
{
  if(this->StereoState==STEREO_ON) {
	rwiStereo = irenStereo; 
  } else {
    rwiStereo = NULL;
  }
}


//----------------------------------------------------------------------------
void  eosInteractorMyStyle::StartState(int newstate) 
{
#ifdef DEBUG
	fprintf(stderr, "Rotate in eosInteractorMyStyle\n");
#endif
	this->State = newstate;

	switch(StereoState) {
		case STEREO_ON: {
	    	if (this->AnimState == VTKIS_ANIM_OFF) {
				rwiMain->GetRenderWindow()->SetDesiredUpdateRate(rwiMain->GetDesiredUpdateRate());
				rwiStereo->GetRenderWindow()->SetDesiredUpdateRate(rwiStereo->GetDesiredUpdateRate());
				this->InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
				if (this->UseTimers &&
                    !rwiMain->CreateTimer(VTKI_TIMER_FIRST) 
				  ||!rwiStereo->CreateTimer(VTKI_TIMER_FIRST)) {
		    		vtkErrorMacro(<< "Timer start failed");
		    		this->State = VTKIS_NONE;
	    		}	
			}
			break;
		}	
  		case STEREO_OFF: {
#ifdef DEBUG
			fprintf(stderr, "Not STEREO StartState in eosInteractorMyStyle: Call vtkInteractorStyle::StartState(%d)\n", newstate);
#endif
			//vtkInteractorStyleSwitch::StartState(VTKIS_ROTATE);
	    	if (this->AnimState == VTKIS_ANIM_OFF) {
				rwiMain->GetRenderWindow()->SetDesiredUpdateRate(rwiMain->GetDesiredUpdateRate());
				this->InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
				if(this->UseTimers && !rwiMain->CreateTimer(VTKI_TIMER_FIRST)) {
		    		vtkErrorMacro(<< "Timer start failed");
		    		this->State = VTKIS_NONE;
	    		}	
			}
			break;
		}
   } 
}
//----------------------------------------------------------------------------
void  eosInteractorMyStyle::StopState() 
{
#ifdef DEBUG
	fprintf(stderr, "StopState in eosInteractorMyStyle\n");
#endif
  this->State = VTKIS_NONE;
  if(StereoState==STEREO_ON) {
#ifdef DEBUG
	  fprintf(stderr, "StereoON\n");
#endif
      if (this->AnimState == VTKIS_ANIM_OFF) {   
	      rwiMain->GetRenderWindow()->SetDesiredUpdateRate(rwiMain->GetStillUpdateRate());
	      rwiStereo->GetRenderWindow()->SetDesiredUpdateRate(rwiStereo->GetStillUpdateRate());

		  if (this->UseTimers && (!rwiMain->DestroyTimer() ||  !rwiStereo->DestroyTimer())) {
		  	vtkErrorMacro(<< "Timer stop failed");
		  }
		  this->InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	      rwiMain->Render();
	      rwiStereo->Render();
	    }   
  } else {
	  vtkInteractorStyle::StopState();
  }
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::OnTimer(void) 
{
#ifdef DEBUG
	fprintf(stderr, "OnTimer: this->State=%d AnimState=%d UseTimers=%d\n", 
		this->State, this->AnimState, this->UseTimers);
#endif
  vtkRenderWindowInteractor *rwI = this->Interactor;
  switch (this->State) 
    {
	case VTKIS_NONE:
      // JCP Animation control
		if (this->AnimState == VTKIS_ANIM_ON) {
			if(StereoState==STEREO_ON) {
				if(this->UseTimers) {
	      			rwiMain->DestroyTimer();
					rwiStereo->DestroyTimer();
				}
				rwiMain->Render();
				rwiStereo->Render();
				if(this->UseTimers) {
				  rwiMain->CreateTimer(VTKI_TIMER_FIRST);
				  rwiStereo->CreateTimer(VTKI_TIMER_FIRST);
				}
	    	} else {
				if(this->UseTimers) {
					rwI->DestroyTimer();
				}
				rwI->Render();
				if(this->UseTimers) {
				  rwI->CreateTimer(VTKI_TIMER_FIRST);
				}
	    	}
		}
      	// JCP Animation control 
      break;
	  
    case VTKIS_ROTATE:  // rotate with respect to an axis perp to look
	  switch(StereoState) {
			case STEREO_ON: {
      			this->StereoCameraRotate(this->Interactor->GetLastEventPosition()[0], 
				                   this->Interactor->GetLastEventPosition()[1]);
				if(this->UseTimers) {
      				rwiMain->CreateTimer(VTKI_TIMER_UPDATE);
      				rwiStereo->CreateTimer(VTKI_TIMER_UPDATE);
				}
				break;
			}
			case STEREO_OFF: {
#ifdef DEBUG
				fprintf(stderr, "---Rotate\n");
#endif
/*				switch(this->JoystickOrTrackball) {
					case VTKIS_JOYSTICK: {
						this->TrackballCamera->SetInteractor(0);	
						this->JoystickCamera->SetInteractor(rwiMain);
						this->JoystickCamera->Rotate();
						break;
					}
					case VTKIS_TRACKBALL: {
						this->JoystickCamera->SetInteractor(0);
						this->TrackballCamera->SetInteractor(rwiMain);
						this->TrackballCamera->Rotate();
						break;
					}
				}
*/
				this->Rotate();
				if(this->UseTimers) {
					rwI->CreateTimer(VTKI_TIMER_UPDATE);
				}	
				break;
			}
	  }

      break;
	 
    case VTKIS_PAN: // move perpendicular to camera's look vector
      //this->PanCamera(this->Interactor->GetLastEventPosition()[0], this->Interactor->GetLastEventPosition()[1]);
      switch(StereoState){
			case STEREO_ON:{
				this->StereoCameraPan(this->Interactor->GetLastEventPosition()[0],
									  this->Interactor->GetLastEventPosition()[1]);
				if(this->UseTimers) {
					rwiMain->CreateTimer(VTKI_TIMER_UPDATE);
                	rwiStereo->CreateTimer(VTKI_TIMER_UPDATE);
				}
	 			break;
			}
			case STEREO_OFF:{
      			this->Pan();
				if(this->UseTimers) {
      				rwI->CreateTimer(VTKI_TIMER_UPDATE);
				}
      			break;
			}
       }
     break;
      //-----
    case VTKIS_ZOOM:
      this->Dolly();
	  if(this->UseTimers) {
	  	rwI->CreateTimer(VTKI_TIMER_UPDATE);
	  }
      break;
      //-----
    case VTKIS_SPIN:
      switch(StereoState){
            case STEREO_ON:{
                this->StereoCameraSpin(this->Interactor->GetLastEventPosition()[0],
                                       this->Interactor->GetLastEventPosition()[1]);
				if(this->UseTimers) {
                	rwiMain->CreateTimer(VTKI_TIMER_UPDATE);
                	rwiStereo->CreateTimer(VTKI_TIMER_UPDATE);
				}
                break;
            }
            case STEREO_OFF:{
                this->Spin();
				if(this->UseTimers) {
                	rwI->CreateTimer(VTKI_TIMER_UPDATE);
				}
                break;
            }
       }   
      break;
      //-----
    case VTKIS_DOLLY:  // move along camera's view vector
      switch(StereoState){
            case STEREO_ON:{
                this->StereoCameraDolly(this->Interactor->GetLastEventPosition()[0],
                                      this->Interactor->GetLastEventPosition()[1]);
				if(this->UseTimers) {
                	rwiMain->CreateTimer(VTKI_TIMER_UPDATE);
                	rwiStereo->CreateTimer(VTKI_TIMER_UPDATE);
				}
                break;  
            }       
            case STEREO_OFF:{
                this->Dolly();
				if(this->UseTimers) {
                	rwI->CreateTimer(VTKI_TIMER_UPDATE);
				}
                break;  
            }       
       }       

      break;
      //-----
    case VTKIS_USCALE:
      break;
      //-----
    case VTKIS_TIMER:
      rwI->Render();
	  if(this->UseTimers) {
      	rwI->CreateTimer(VTKI_TIMER_UPDATE);
	  }
      break;
	  
       //-----
    default :
      break;
    } 
}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::SetStereoCamera(vtkCamera* cam2,vtkCamera* cam3,
                                           double rxf, double ryf)
{
#ifdef DEBUG
	fprintf(stderr, "CurrentCam: %p cam2: %p cam3: %p \n",
		this->GetCurrentRenderer()->GetActiveCamera(), cam2, cam3);
#endif

	this->GetCurrentRenderer()->GetActiveCamera()->Azimuth(rxf);
	this->GetCurrentRenderer()->GetActiveCamera()->Elevation(ryf);
  	this->GetCurrentRenderer()->GetActiveCamera()->OrthogonalizeViewUp();

	cam2->SetPosition(this->GetCurrentRenderer()->GetActiveCamera()->GetPosition());
	cam2->SetFocalPoint(this->GetCurrentRenderer()->GetActiveCamera()->GetFocalPoint());
	cam2->SetViewUp(this->GetCurrentRenderer()->GetActiveCamera()->GetViewUp());
 	cam2->Elevation(ryf);
	cam2->OrthogonalizeViewUp();
    cam3->SetPosition(this->GetCurrentRenderer()->GetActiveCamera()->GetPosition());
    cam3->SetFocalPoint(this->GetCurrentRenderer()->GetActiveCamera()->GetFocalPoint());
    cam3->SetViewUp(this->GetCurrentRenderer()->GetActiveCamera()->GetViewUp());
    cam3->Elevation(ryf);  
    cam3->OrthogonalizeViewUp();

}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::Rotate()
{
	if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
	    || StereoState == STEREO_ON){
		return;
	}

 	vtkRenderer * MainRenderer = rwiMain->GetInteractorStyle()->GetCurrentRenderer();


	if(TJSwitchState==JOYSTICK){
		float *center = MainRenderer->GetCenter();

		float jdx = (float)rwiMain->GetEventPosition()[0] - center[0];
		float jdy = (float)rwiMain->GetEventPosition()[1] - center[1];

		float *vp = MainRenderer->GetViewport();
		int *jsize = rwiMain->GetSize();

		float jde = (vp[3] - vp[1])*jsize[1];
		float jda = (vp[2] - vp[0])*jsize[0];

		if (jde == 0) jde = 1;
		if (jda == 0) jda = 1;

		float j_delta_elevation = -20.0/(jde);
		float j_delta_azimuth = -20.0/(jda);

		double jrxf = (double)jdx * j_delta_azimuth;
		double jryf = (double)jdy * j_delta_elevation;

		Cam->Azimuth(jrxf);
		Cam->Elevation(jryf);
		Cam->OrthogonalizeViewUp();

	 } else if(TJSwitchState==TRACKBALL){
		int tdx = rwiMain->GetEventPosition()[0] - rwiMain->GetLastEventPosition()[0];
		int tdy = rwiMain->GetEventPosition()[1] - rwiMain->GetLastEventPosition()[1];
  
		int *tsize = MainRenderer->GetRenderWindow()->GetSize();

		if (tsize[1] == 0) tsize[1] = 1;
		if (tsize[0] == 0) tsize[0] = 1;

		float t_delta_elevation = -20.0 / tsize[1];
		float t_delta_azimuth = -20.0 / tsize[0];
  
		double trxf = (double)tdx * t_delta_azimuth * this->MotionFactor;
		double tryf = (double)tdy * t_delta_elevation * this->MotionFactor;
  
		Cam->Azimuth(trxf);
		Cam->Elevation(tryf);
		Cam->OrthogonalizeViewUp();
#ifdef DEBUG
    fprintf(stderr, "In Rotate  Trackball tdx=%d tdy=%d trxf=%f tryf=%f curPos=%d,%d  lasPos=%d,%d\n",tdx,tdy,trxf,tryf,rwiMain->GetEventPosition()[0],rwiMain->GetEventPosition()[1],rwiMain->GetLastEventPosition()[0],rwiMain->GetLastEventPosition()[1]);
#endif
	}


	if (this->AutoAdjustCameraClippingRange){
		MainRenderer->ResetCameraClippingRange();
	}

	if (rwiMain->GetLightFollowCamera()){
		MainRenderer->UpdateLightsGeometryToFollowCamera();
	}

  rwiMain->Render();

}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::Spin()
{
   if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
        || StereoState == STEREO_ON){
        return;
    }

  vtkRenderer * MainRenderer = rwiMain->GetInteractorStyle()->GetCurrentRenderer();
  float *center = MainRenderer->GetCenter();
  double newAngle;

	if(TJSwitchState==JOYSTICK){
		// Spin is based on y value

		double yf = ((double)rwiMain->GetEventPosition()[1] - (double)center[1]);

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
			atan2((double)rwiMain->GetEventPosition()[1] - (double)center[1],
   				(double)rwiMain->GetEventPosition()[0] - (double)center[0]);
 		double oldAngle =
			atan2((double)rwiMain->GetLastEventPosition()[1] - (double)center[1],
          		(double)rwiMain->GetLastEventPosition()[0] - (double)center[0]);
  
		newAngle *= vtkMath::RadiansToDegrees();
		oldAngle *= vtkMath::RadiansToDegrees();
		newAngle = newAngle - oldAngle;
	}
#ifdef DEBUG
    fprintf(stderr,"In StereoCameraSpin Trackball newAngle = %g\n",newAngle);
#endif

  Cam->Roll(newAngle);
  Cam->OrthogonalizeViewUp();

  rwiMain->Render();

}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::Pan()
{
	if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
		 || StereoState == STEREO_ON){
        return;
    }

	if(TJSwitchState==JOYSTICK)this->JoyStickPan();
    if(TJSwitchState==TRACKBALL)this->TrackballPan();	
    if (rwiMain->GetLightFollowCamera()){
          Ren->UpdateLightsGeometryToFollowCamera();
	}
    rwiMain->Render();
}

void eosInteractorMyStyle::JoyStickPan()
{
  vtkRenderer* MainRenderer = rwiMain->GetInteractorStyle()->GetCurrentRenderer();
  double ViewFocus[4];
  double NewPickPoint[4];
  double focalDepth;
  double *ViewPoint;
  double MotionVector[3];

  // Calculate the focal depth since we'll be using it a lot

  Cam->GetFocalPoint(ViewFocus);
  this->ComputeWorldToDisplay(ViewFocus[0], ViewFocus[1], ViewFocus[2],
                              ViewFocus);
  focalDepth = ViewFocus[2];

  this->ComputeDisplayToWorld((float)rwiMain->GetEventPosition()[0],
                              (float)rwiMain->GetEventPosition()[1],
                              focalDepth,
                              NewPickPoint);

  // Get the current focal point and position

  Cam->GetFocalPoint(ViewFocus);
  ViewPoint = Cam->GetPosition();

  // Compute a translation vector, moving everything 1/10
  // the distance to the cursor. (Arbitrary scale factor)

  MotionVector[0] = 0.1 * (ViewFocus[0] - NewPickPoint[0]);
  MotionVector[1] = 0.1 * (ViewFocus[1] - NewPickPoint[1]);
  MotionVector[2] = 0.1 * (ViewFocus[2] - NewPickPoint[2]);

  Cam->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                        MotionVector[1] + ViewFocus[1],
                        MotionVector[2] + ViewFocus[2]);

  Cam->SetPosition(MotionVector[0] + ViewPoint[0],
                      MotionVector[1] + ViewPoint[1],
                      MotionVector[2] + ViewPoint[2]);

  if (rwiMain->GetLightFollowCamera()){
		MainRenderer->UpdateLightsGeometryToFollowCamera();
  }
}

void eosInteractorMyStyle::TrackballPan()
{
  double viewFocus[4], focalDepth, viewPoint[3];
  float newPickPoint[4], oldPickPoint[4], motionVector[3];
  
  // Calculate the focal depth since we'll be using it a lot

  Cam->GetFocalPoint(viewFocus);
  this->ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2], 
                              viewFocus);
  focalDepth = viewFocus[2];

  this->ComputeDisplayToWorld((double)rwiMain->GetEventPosition()[0], 
                              (double)rwiMain->GetEventPosition()[1],
                              focalDepth, 
                              newPickPoint);
    
  // Has to recalc old mouse point since the viewport has moved,
  // so can't move it outside the loop

  this->ComputeDisplayToWorld((double)rwiMain->GetLastEventPosition()[0],
                              (double)rwiMain->GetLastEventPosition()[1],
                              focalDepth, 
                              oldPickPoint);
  
  // Camera motion is reversed

  motionVector[0] = oldPickPoint[0] - newPickPoint[0];
  motionVector[1] = oldPickPoint[1] - newPickPoint[1];
  motionVector[2] = oldPickPoint[2] - newPickPoint[2];
  
  Cam->GetFocalPoint(viewFocus);
  Cam->GetPosition(viewPoint);
  Cam->SetFocalPoint(motionVector[0] + viewFocus[0],
                     motionVector[1] + viewFocus[1],
                     motionVector[2] + viewFocus[2]);

  Cam->SetPosition(motionVector[0] + viewPoint[0],
                   motionVector[1] + viewPoint[1],
                   motionVector[2] + viewPoint[2]);
}
//----------------------------------------------------------------------------

void eosInteractorMyStyle::Dolly()
{
   if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
        || StereoState == STEREO_ON){
        return;
    }

	vtkRenderer* MainRenderer= rwiMain->GetInteractorStyle()->GetCurrentRenderer();
	float *center = MainRenderer->GetCenter();
    int    tdy;
    double jdy;
    double dyf;
    double zoomFactor;

	if(TJSwitchState==JOYSTICK){
		jdy = (double)rwiMain->GetEventPosition()[1] - (double)center[1];
		dyf = 0.5 * jdy;
		if (center[1] == 0) center[1] = 1;
		dyf = dyf / (double)center[1];
	} else if(TJSwitchState==TRACKBALL){
		tdy = rwiMain->GetEventPosition()[1] - rwiMain->GetLastEventPosition()[1];
		dyf = this->MotionFactor * (double)(tdy) / (double)(center[1]);
		zoomFactor = pow((double)1.1, dyf);
	}

	zoomFactor = pow((double)1.1, dyf);

	if(TJSwitchState==JOYSTICK){
		if (zoomFactor < 0.5 || zoomFactor > 1.5){
			vtkErrorMacro("Bad zoom factor encountered");
		}
	}


	if (Cam->GetParallelProjection()){
		Cam->SetParallelScale(Cam->GetParallelScale() / zoomFactor);
	} else{
		Cam->Dolly(zoomFactor);
		if (this->AutoAdjustCameraClippingRange){
			MainRenderer->ResetCameraClippingRange();
		}
	}

	if (rwiMain->GetLightFollowCamera()){
		MainRenderer->UpdateLightsGeometryToFollowCamera();
	}

	rwiMain->Render();
}
//----------------------------------------------------------------------------
void eosInteractorMyStyle::StereoCameraRotate(int x,int y)
{
    if (Ren == NULL || RenRight == NULL || RenLeft == NULL ||StereoState == STEREO_OFF){
        return; 
    }

  vtkProp3D *InteractionProp = NULL;
  vtkCellPicker *InteractionPicker = vtkCellPicker::New();
  vtkRenderWindowInteractor *rwI = this->Interactor;

  int *Size = this->Interactor->GetSize();
	  
  float *vp = this->GetCurrentRenderer()->GetViewport();
  float *Center = this->GetCurrentRenderer()->GetCenter();

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
	
		InteractionPicker->Pick(x,y,0.0,this->GetCurrentRenderer());
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
        dx = rwI->GetEventPosition()[0] - rwI->GetLastEventPosition()[0];
        dy = rwI->GetEventPosition()[1] - rwI->GetLastEventPosition()[1];

        int *size = this->GetCurrentRenderer()->GetRenderWindow()->GetSize();

        if (size[1] == 0) size[1] = 1;
        if (size[0] == 0) size[0] = 1;

        float t_delta_elevation = -20.0 / size[1];
        float t_delta_azimuth = -20.0 / size[0];
  
        rxf = (double)dx * t_delta_azimuth * this->MotionFactor;
        ryf = (double)dy * t_delta_elevation * this->MotionFactor;

#ifdef DEBUG
    fprintf(stderr, "In StereoCameraRotate  Trackball dx=%d dy=%d rxf=%f ryf=%f curPos=%d,%d  lasPos=%d,%d\n",dx,dy,rxf,ryf,rwI->GetEventPosition()[0],rwI->GetEventPosition()[1],rwI->GetLastEventPosition()[0],rwI->GetLastEventPosition()[1]);
#endif

	}
#ifdef DEBUG2
	fprintf(stderr, "CurrentCam: %p Cam: %p CamLeft: %p CamRight: %p\n",
		this->GetCurrentRenderer()->GetActiveCamera(), Cam, CamLeft, CamRight);
#endif
	if(this->GetCurrentRenderer()->GetActiveCamera()==Cam){
		SetStereoCamera(CamLeft,CamRight,rxf,ryf);
		CamLeft->Azimuth(-3.5+rxf);      
		CamRight->Azimuth(3.5+rxf);      
	} else if(this->GetCurrentRenderer()->GetActiveCamera()==CamLeft){
		SetStereoCamera(Cam,CamRight,rxf,ryf);
		CamRight->Azimuth(7.0+rxf);
		Cam->Azimuth(3.5+rxf);         
	} else if(this->GetCurrentRenderer()->GetActiveCamera()==CamRight){
		SetStereoCamera(CamLeft,Cam,rxf,ryf);
		CamLeft->Azimuth(-7.0+rxf);
		Cam->Azimuth(-3.5+rxf);
	}
	
	if (this->AutoAdjustCameraClippingRange){
		Ren->ResetCameraClippingRange();
		RenLeft->ResetCameraClippingRange();
		RenRight->ResetCameraClippingRange();
	}

	if (rwiMain->GetLightFollowCamera() || rwiStereo->GetLightFollowCamera()) {
		Ren->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
        RenRight->UpdateLightsGeometryToFollowCamera();
	}

  rwiMain->Render();
  rwiStereo->Render(); 
  //rwiMain->SetInteractorStyle(rwiMain->GetInteractorStyle());
  //rwiStereo->SetInteractorStyle(rwiStereo->GetInteractorStyle());
}

//----------------------------------------------------------------------------
 void eosInteractorMyStyle::StereoCameraPan(int x,int y)
{
	if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL 
		|| rwiStereo->GetInteractorStyle()->GetCurrentRenderer() == NULL){
		return;
	}

	if(TJSwitchState==JOYSTICK){
		this->StereoCameraPanJoyStick();
	} else if(TJSwitchState==TRACKBALL){
		this->StereoCameraPanTrackball();
	}
}

void eosInteractorMyStyle::StereoCameraPanJoyStick()
{
	vtkRenderWindowInteractor *rwi = this->Interactor;
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
	Cam->GetFocalPoint(ViewFocus);
    CamRight->GetFocalPoint(ViewFocus);
    CamLeft->GetFocalPoint(ViewFocus);
	double *ViewPoint = camera->GetPosition();

  // Compute a translation vector, moving everything 1/10
  // the distance to the cursor. (Arbitrary scale factor)
	double MotionVector[3];
	MotionVector[0] = 0.1 * (ViewFocus[0] - NewPickPoint[0]);
	MotionVector[1] = 0.1 * (ViewFocus[1] - NewPickPoint[1]);
	MotionVector[2] = 0.1 * (ViewFocus[2] - NewPickPoint[2]);

	Cam     ->SetFocalPoint(MotionVector[0] + ViewFocus[0],
  	                        MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
    CamRight->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                            MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
    CamLeft ->SetFocalPoint(MotionVector[0] + ViewFocus[0],
                            MotionVector[1] + ViewFocus[1],
                            MotionVector[2] + ViewFocus[2]);
  
	Cam     ->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);
    CamRight->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);
    CamLeft ->SetPosition(MotionVector[0] + ViewPoint[0],
                          MotionVector[1] + ViewPoint[1],
                          MotionVector[2] + ViewPoint[2]);


	if (rwiMain->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
	}
	if (rwiStereo->GetLightFollowCamera()){
        RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
	}

	rwiMain->Render();
    rwiStereo->Render();
}

void eosInteractorMyStyle::StereoCameraPanTrackball()
{
  vtkRenderWindowInteractor *rwi = this->Interactor;

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
  
  Cam->GetFocalPoint(viewFocus);
  Cam->GetPosition(viewPoint);
  Cam->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  Cam->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);

  CamRight->GetFocalPoint(viewFocus);
  CamRight->GetPosition(viewPoint);
  CamRight->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  CamRight->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);

  CamLeft->GetFocalPoint(viewFocus);
  CamLeft->GetPosition(viewPoint);
  CamLeft->SetFocalPoint(motionVector[0] + viewFocus[0],
                        motionVector[1] + viewFocus[1],
                        motionVector[2] + viewFocus[2]);

  CamLeft->SetPosition(motionVector[0] + viewPoint[0],
                      motionVector[1] + viewPoint[1],
                      motionVector[2] + viewPoint[2]);
   
   
  if (rwiMain->GetLightFollowCamera()){
     	Ren->UpdateLightsGeometryToFollowCamera();
  }
  if (rwiStereo->GetLightFollowCamera()){
   		RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
  }

  rwiMain->Render();
  rwiStereo->Render();
}
//----------------------------------------------------------------------------
 void eosInteractorMyStyle::StereoCameraDolly(int x,int y)
 {
    if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
        || rwiStereo->GetInteractorStyle()->GetCurrentRenderer() == NULL){
        return;
    }
	this->StereoCameraDollyJoyStick();
	this->StereoCameraDollyTrackball();
 }

void eosInteractorMyStyle::StereoCameraDollyJoyStick()
{ 
  vtkRenderWindowInteractor *rwi = this->Interactor;
  float *center = this->CurrentRenderer->GetCenter();

  if(center[1]==0)center[1]=1;
  double dy = (double)rwi->GetEventPosition()[1] - (double)center[1];
  double dyf = 0.5 * dy / (double)center[1];
  double zoomFactor = pow((double)1.1, dyf);

  if (zoomFactor < 0.5 || zoomFactor > 1.5){
    vtkErrorMacro("Bad zoom factor encountered");
    }
  
  
	if (Cam->GetParallelProjection()){
		Cam->SetParallelScale(Cam->GetParallelScale() / zoomFactor);
    } else{
        Cam->Dolly(zoomFactor);
        if (((vtkInteractorStyle*)rwiMain->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
            ((vtkInteractorStyle*)rwiMain->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
        }
    }

	if (CamRight->GetParallelProjection()){
        CamRight->SetParallelScale(CamRight->GetParallelScale() / zoomFactor);
    } else{
        CamRight->Dolly(zoomFactor);
        if (((vtkInteractorStyle*)rwiStereo->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
            ((vtkInteractorStyle*)rwiStereo->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
        }
    }
 
	if (CamLeft->GetParallelProjection()){
        CamLeft->SetParallelScale(CamLeft->GetParallelScale() / zoomFactor);
	} else{
		CamLeft->Dolly(zoomFactor);
		if (((vtkInteractorStyle*)rwiStereo->GetInteractorStyle())->GetAutoAdjustCameraClippingRange()){
			((vtkInteractorStyle*)rwiStereo->GetInteractorStyle())->GetCurrentRenderer()->ResetCameraClippingRange();
		}
    }

  if (rwi->GetLightFollowCamera())
    {
    //rwiMain->GetInteractorStyle()->GetCurrentRenderer()->UpdateLightsGeometryToFollowCamera();
	//rwiStereo->GetInteractorStyle()->GetCurrentRenderer()->UpdateLightsGeometryToFollowCamera();
    Ren->UpdateLightsGeometryToFollowCamera();
	RenLeft->UpdateLightsGeometryToFollowCamera();
	RenRight->UpdateLightsGeometryToFollowCamera();
    }

  rwiMain->Render();
  rwiStereo->Render();
 }
 
void eosInteractorMyStyle::StereoCameraDollyTrackball()
{ 
	vtkRenderWindowInteractor *rwi = this->Interactor;
	float *center = this->CurrentRenderer->GetCenter();

	int dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];
  
	if(center[1]==0)center[1]=1;

	double dyf = this->MotionFactor * (double)(dy) / (double)(center[1]);
	double zoomFactor = pow((double)1.1, dyf);

	if (Cam->GetParallelProjection()){
    	Cam->SetParallelScale(Cam->GetParallelScale()/zoomFactor);
	} else{
		Cam->Dolly(zoomFactor);
		if (this->AutoAdjustCameraClippingRange){
			Ren->ResetCameraClippingRange();
		}
	}

    if (CamRight->GetParallelProjection()){
        CamRight->SetParallelScale(CamRight->GetParallelScale()/zoomFactor);
    } else{
        CamRight->Dolly(zoomFactor);
        if (this->AutoAdjustCameraClippingRange){
            RenLeft->ResetCameraClippingRange();
        }
    }

    if (CamLeft->GetParallelProjection()){
        CamLeft->SetParallelScale(CamLeft->GetParallelScale()/zoomFactor);
    } else{
        CamLeft->Dolly(zoomFactor);
        if (this->AutoAdjustCameraClippingRange){
            RenRight->ResetCameraClippingRange();
        }
    }

 	if (rwiMain->GetLightFollowCamera()){
		Ren->UpdateLightsGeometryToFollowCamera();
	}
	if (rwiStereo->GetLightFollowCamera()){
		RenRight->UpdateLightsGeometryToFollowCamera();
        RenLeft->UpdateLightsGeometryToFollowCamera();
	}

	rwiMain->Render();
	rwiStereo->Render();
}
 //----------------------------------------------------------------------------
  void eosInteractorMyStyle::StereoCameraSpin(int x,int y)
  {
    if (rwiMain->GetInteractorStyle()->GetCurrentRenderer() == NULL
        || rwiStereo->GetInteractorStyle()->GetCurrentRenderer() == NULL){
        return;
    }

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

/*
		if(rwi->GetEventPosition()[1]-rwi->GetLastEventPosition()[1]==0 ){
			if(rwi->GetEventPosition()[0]-rwi->GetLastEventPosition()[0]==1){
				rwi->GetEventPosition()[1]=rwi->GetLastEventPosition()[0];
			} else if(rwi->GetEventPosition()[0]-rwi->GetLastEventPosition()[0]==-1){
				rwi->GetEventPosition()[0]=rwi->GetLastEventPosition()[1];
			}
		} else if(rwi->GetEventPosition()[0]-rwi->GetLastEventPosition()[0]==0){
			if(rwi->GetEventPosition()[0]-rwi->GetLastEventPosition()[0]==1){
				rwi->GetEventPosition()[1]=rwi->GetEventPosition()[0];
			} else if(rwi->GetEventPosition()[0]-rwi->GetLastEventPosition()[0]==-1){
				rwi->GetEventPosition()[0]=rwi->GetEventPosition()[1];
			}
		}
  */  

		newAngle =
    		atan2((double)rwi->GetEventPosition()[1] - (double)center[1],
       		(double)rwi->GetEventPosition()[0] - (double)center[0]);
		double oldAngle =
  			atan2((double)rwi->GetLastEventPosition()[1] - (double)center[1],
       		(double)rwi->GetLastEventPosition()[0] - (double)center[0]);
rwiStereo->SetEventInformation(rwi->GetEventPosition()[0],rwi->GetEventPosition()[1],rwi->GetControlKey(),rwi->GetShiftKey(),rwi->GetKeyCode(),rwi->GetRepeatCount(),rwi->GetKeySym()); 
		newAngle *= vtkMath::RadiansToDegrees();
		oldAngle *= vtkMath::RadiansToDegrees();
		newAngle = newAngle-oldAngle;
#ifdef DEBUG
    fprintf(stderr,"In StereoCameraSpin Trackball newAngle = %g curPos=%d,%d lasPos=%d,%d\n",newAngle,rwi->GetEventPosition()[0],rwi->GetEventPosition()[1],rwi->GetLastEventPosition()[0],rwi->GetLastEventPosition()[1]);
#endif
	
  }	
  Cam->Roll(newAngle);
  Cam->OrthogonalizeViewUp();
  CamRight->Roll(newAngle);
  CamRight->OrthogonalizeViewUp();
  CamLeft->Roll(newAngle);
  CamLeft->OrthogonalizeViewUp();
	
  rwiMain->Render();
  rwiStereo->Render();
}
  
//----------------------------------------------------------------------------
void eosInteractorMyStyle::DeleteXwindow(Display* disp, Window win)
{
	XDestroyWindow(disp, win);
	XFlush(disp);
}

//          Create/Delete StereoWindow
//---------------------------------------------------------------------------
// 
void eosInteractorMyStyle::DeleteStereoWindow()
{
	Display* disp = (Display*)rwiStereo->GetRenderWindow()->GetGenericDisplayId();
	Window   win  = (Window)rwiStereo->GetRenderWindow()->GetGenericWindowId();
	
	delete stereoWin;
	this->DeleteXwindow(disp, win);
	this->ResetStereoWindowInformation();
}

void eosInteractorMyStyle::CreateStereoWindow()
{
  stereoWin = eosStereoWindow::New();
  this->SetStereoWindowInformation();

  stereoWin->SetFromMainWindow(rwiMain->GetRenderWindow());
  stereoWin->SetTclWindowInterp(this->TclWindowInterp);
  stereoWin->ShowWindow();
/*
  rwiMain->Render();
  rwiMain->Enable();
  rwiStereo->Render();
  rwiStereo->Enable();
*/
}

//---------------------------------------------------------------------------
void eosInteractorMyStyle::SetRenderWindowData(vtkRenderer* ren,vtkRenderWindowInteractor* iren)
{
  Ren     = ren;
  rwiMain = iren;
  Cam     = ren->GetActiveCamera();

  rwiMain->GetRenderWindow()->SetDesiredUpdateRate(rwiMain->GetDesiredUpdateRate());
}

//----------------------------------------------------------------------------
void eosInteractorMyStyle::ResetStereoWindowInformation()
{
	RenLeft=NULL;
	RenRight=NULL;
	CamLeft=NULL;
	CamRight=NULL;
	rwiStereo=NULL;
}

void eosInteractorMyStyle::SetStereoWindowInformation()
{
	RenLeft  = stereoWin->GetRendererLeft();
	RenRight = stereoWin->GetRendererRight();
	CamLeft  = stereoWin->GetCameraLeft();
	CamRight = stereoWin->GetCameraRight();
	rwiStereo = stereoWin->GetRenderWindowInteractor(); 

#ifdef DEBUG
	fprintf(stderr,"rwiStereo in GetStereoWindowInformation: %p\n", rwiStereo);
#endif
}


//----------------------------------------------------------------------------
void eosInteractorMyStyle::SetTclWindowInterp(Tcl_Interp *interp)
{
  if(interp!=NULL){
     this->TclWindowInterp = interp;
   } else {
   	 fprintf(stderr, "interp is NULL in SetTclWindowInterp");
   }
}
//----------------------------------------------------------------------------
Tcl_Interp* eosInteractorMyStyle::GetTclWindowInterp()
{
 return TclWindowInterp;
}
