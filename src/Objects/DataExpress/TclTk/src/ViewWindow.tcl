package require vtk
package require vtkinteraction
package require vtktesting

proc bye {} {
    vtkCommand DeleteAllObjects
    exit
}

proc windowLayoutSet { } {
	puts "windowLayoutSet"

	puts "mainManu"

	set f [ frame .mainMenu ] 

	puts "menuButton"
	menubutton $f.file -text "File" -underline 0 -menu $f.file.m
    menubutton $f.windowmode -text "WindowMode" -underline 0 -menu $f.windowmode.m
    menubutton $f.cameramode -text "CameraMode" -underline 0 -menu $f.cameramode.m
    menubutton $f.switch -text "TJSwitch" -underline 0 -menu $f.switch.m

	puts "File"
	set m [ menu $f.file.m ]
	$m add command -label "Open" -command {
	    renWin Render
	}
    $m add command -label "Reset" -command {
       istereo OnButtonFromWindow "Reset" 
    }
	$m add command -label "Quit" -command {
	   vtkCommand DeleteAllObjects
	   exit
	}

    puts "WindowMode"
    set m [ menu $f.windowmode.m ]
    $m add command -label "Nomal" -command {
       istereo OnButtonFromWindow "NomalMode"
    }
    $m add command -label "CrossEye" -command {
       istereo OnButtonFromWindow "CrossMode" 
    }
    $m add command -label "ParallelEye" -command {
       istereo OnButtonFromWindow "ParallelMode"
    }

    puts "CameraMode"
    set m [ menu $f.cameramode.m ]
    $m add command -label "Rotate" -command {
        #iren SetRenderWindow renWin
        #iren AddObserver UserEvent {wm deiconify .vtkInteract}
        #iren Initialize
        #iren Start
        istereo OnButtonFromWindow "RotateMode"
    }
    
    $m add command -label "Spin" -command {
        #iren Disable 
        #iren SetInteractorStyle vtkInteractorStyleTrackball
        #iren Enable
      istereo OnButtonFromWindow "SpinMode"
    }

    $m add command -label "Pan" -command {
      istereo OnButtonFromWindow "PanMode"
    }

    $m add command -label "Dolly" -command {
      istereo OnButtonFromWindow "DollyMode"
    }

    set m [ menu $f.switch.m ]
    $m add command -label "Trackball" -command {
      istereo OnButtonFromWindow "Trackball"
      puts "Trackball"
    }
    $m add command -label "JoyStick" -command {
      istereo OnButtonFromWindow "JoyStick"
      puts "JoyStick"
    }

    puts "pack"
    pack .mainMenu.file .mainMenu.windowmode .mainMenu.cameramode .mainMenu.switch -side left

    set f [ frame .params ]
	button $f.quit -text Quit -command bye
    button $f.reset -text Reset -command {
      istereo OnButtonFromWindow "Reset"
    }
    button $f.rotate -text Rotate -command {
      istereo OnButtonFromWindow "RotateMode"
    }

	pack $f.quit -side left 
    pack $f.reset -side left
    pack $f.rotate -side right

}

proc setResolution {resolution} {
	cf SetValue 0 $resolution
}

proc setResolutionScale { } {

    frame .resolutionScale
    scale .resolutionScale.rsca -from 0 -to 80 -length 200 -tickinterval 0 \
              -resolution 1 \
              -sliderlength 10 -width 8 -showvalue yes \
              -orient horizontal -label "Resolution" \
              -command setResolution -variable resolution
    pack .resolutionScale.rsca
}

	wm title . TclWindow
	wm protocol . WM_DELETE_WINDOW bye 

    vtkCylinderSource cylinder
     cylinder SetResolution 8
    
    vtkPolyDataMapper cylinderMapper
     cylinderMapper SetInput [cylinder GetOutput]
    vtkActor cylinderActor
     cylinderActor SetMapper cylinderMapper

    vtkCamera cam
	 cam SetFocalPoint 165 165 100
	 cam SetPosition 1650 1650 100
	 #cam SetEyeAngle 3.0
	 cam ParallelProjectionOn

	vtkLight light
	 light SetFocalPoint 0.21406 1.5 0
	 #light SetPosition 8.3761 4.94858 4.1250
	 light SetLightType 1 


	puts "before vtkmrcImageReader"
	vtkmrcImageReader aVol
	puts "after vtkmrcImageReader"
	aVol SetFilename "test.mrc"
	aVol SetDataType 0
	aVol SetDataHow  0
	aVol Update

	puts "Contour"	
	vtkContourFilter cf
	cf SetInput [ aVol GetOutput ]
	set resolution 50
    cf SetValue 0 $resolution 
	cf ComputeScalarsOff
	cf ReleaseDataFlagOn 

	vtkPolyDataMapper volMap
	volMap SetInput [ cf GetOutput ]
	volMap ImmediateModeRenderingOn

	vtkActor volActor
	volActor SetMapper volMap
	eval [ volActor GetProperty ] SetDiffuseColor 1.0 1.0 1.0
	eval [ volActor GetProperty ] SetColor        1.0 1.0 1.0
	eval [ volActor GetProperty ] SetSpecular     0.5
	eval [ volActor GetProperty ] SetDiffuse      0.4
	eval [ volActor GetProperty ] SetInterpolation 1 

    vtkRenderer ren
     ren SetActiveCamera cam
     ren AddLight light
     #ren AddActor cylinderActor
     ren AddActor volActor 
	 
    vtkRenderWindow renWin
    renWin AddRenderer ren
    set vtkw [ vtkTkRenderWidget .ren -width 400 -height 400 -rw renWin ]
	::vtk::bind_tk_render_widget $vtkw

    #eosInteractorMyStyle myi
	eosInteractorStyleStereo istereo
    vtkRenderWindowInteractor iren 
    iren SetRenderWindow renWin
	iren SetDesiredUpdateRate .00001
	iren AddObserver UserEvent {wm deiconify .vtkInteract}

    #iren SetInteractorStyle myi
	iren SetInteractorStyle istereo
	iren Initialize
	puts "Initialized: [ iren GetInitialized ]"
	puts "Enabled: [ iren GetEnabled ]"
	istereo SetRenderer ren
	istereo SetTclWindowInterp
    #myi SetRenderWindowData ren iren
    #myi SetTclWindowInterp 

	puts "myi Success"

    eval [cylinderActor GetProperty] SetColor $tomato 
     cylinderActor RotateX  30.0
     cylinderActor RotateY -45.0
     cylinderActor SetPosition 0.0 0.0 0.0

    #ren SetBackground 0.1 0.2 0.4

	windowLayoutSet 
	setResolutionScale
	pack   .mainMenu $vtkw .params .resolutionScale -side top -fill both -expand yes
    [ren GetActiveCamera] Zoom 1 
    tkwait window .
