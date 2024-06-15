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
    menubutton $f.mode -text "Mode" -underline 0 -menu $f.mode.m
    menubutton $f.switch -text "TJSwitch" -underline 0 -menu $f.switch.m

    puts "File"
    set m [ menu $f.file.m ]
    $m add command -label "Open" -command {
    }
    $m add command -label "Reset" -command {
       myi OnButtonFromWindow "Reset"
    }
    $m add command -label "Quit" -command {
       vtkCommand DeleteAllObjects
       exit
    }

    puts "Mode"
    set m [ menu $f.mode.m ]
    $m add command -label "Stereo" -command {
      myi OnButtonFromWindow "StereoMode"
    }

    $m add command -label "Rotate" -command {
        #iren SetRenderWindow renWin
        #iren AddObserver UserEvent {wm deiconify .vtkInteract}
        #iren Initialize
        #iren Start
		myi OnButtonFromWindow "RotateMode"
    }

    $m add command -label "Spin" -command {
        #iren Disable
        #iren SetInteractorStyle vtkInteractorStyleTrackball
        #iren Enable
      myi OnButtonFromWindow "SpinMode"
    }

    $m add command -label "Pan" -command {
      myi OnButtonFromWindow "PanMode"
    }

    $m add command -label "Dolly" -command {
      myi OnButtonFromWindow "DollyMode"
    }

    set m [ menu $f.switch.m ]
    $m add command -label "Trackball" -command {
      myi OnButtonFromWindow "Trackball"
      puts "Trackball"
    }
    $m add command -label "JoyStick" -command {
      myi OnButtonFromWindow "JoyStick"
      puts "JoyStick"
    }

    puts "pack"
    pack .mainMenu.file .mainMenu.mode .mainMenu.switch -side left

    set f [ frame .params ]
    button $f.quit -text Quit -command bye
	button $f.reset -text Reset -command {
	  myi OnButtonFromWindow "Reset"
	}
	button $f.rotate -text Rotate -command {
	  myi OnButtonFromWindow "RotateMode" 
	}			  
    pack $f.quit -side left
	pack $f.reset -side left 
	pack $f.rotate -side right
}

    wm title . MainWindow
    wm protocol . WM_DELETE_WINDOW bye

    vtkCylinderSource cylinder
     cylinder SetResolution 8

    vtkPolyDataMapper cylinderMapper
     cylinderMapper SetInput [cylinder GetOutput]
    vtkActor cylinderActor
     cylinderActor SetMapper cylinderMapper

    vtkCamera cam
     #cam SetFocalPoint 165 165 100
     #cam SetPosition 1650 1650 -100
     #cam SetEyeAngle 3.0
     cam SetFocalPoint 0 0 0
     cam SetPosition   0 0 8
     cam ParallelProjectionOn

    vtkLight light
     light SetFocalPoint 0.21406 1.5 0
     light SetPosition 8.3761 4.94858 4.1250
     light SetLightType 1


#    puts "before vtkmrcImageReader"
#    vtkmrcImageReader aVol
#    puts "after vtkmrcImageReader"
#    aVol SetFilename "test.mrc"
#    aVol SetDataType 0
#    aVol SetDataHow  0
#    aVol Update

#    puts "Contour"
#    vtkContourFilter cf
#    cf SetInput [ aVol GetOutput ]
#    cf SetValue 0 50
#    cf ComputeScalarsOff
#    cf ReleaseDataFlagOn

#    vtkPolyDataMapper volMap
#    volMap SetInput [ cf GetOutput ]
#    volMap ImmediateModeRenderingOn

 #   vtkActor volActor
 #   volActor SetMapper volMap
 #   eval [ volActor GetProperty ] SetDiffuseColor 1.0 1.0 1.0
 #   eval [ volActor GetProperty ] SetColor        1.0 1.0 1.0
 #   eval [ volActor GetProperty ] SetSpecular     0.5
 #   eval [ volActor GetProperty ] SetDiffuse      0.4
 #   eval [ volActor GetProperty ] SetInterpolation 1

    vtkRenderer ren
     ren SetActiveCamera cam
     ren AddLight light
     ren AddActor cylinderActor
  #   ren AddActor volActor

    vtkRenderWindow renWin
    renWin AddRenderer ren
    set vtkw [ vtkTkRenderWidget .ren -width 400 -height 400 -rw renWin ]
    ::vtk::bind_tk_render_widget $vtkw

    eosInteractorMyStyle myi
    vtkRenderWindowInteractor iren
    iren SetRenderWindow renWin
    iren SetDesiredUpdateRate .00001
    iren AddObserver UserEvent {wm deiconify .vtkInteract}

    iren SetInteractorStyle myi
    iren Initialize
    puts "Initialized: [ iren GetInitialized ]"
    puts "Enabled: [ iren GetEnabled ]"
    myi SetRenderWindowData ren iren
    myi SetTclWindowInterp

    puts "myi Success"

#---------------------
#vtkCursor3D cursor
#  eval cursor SetModelBounds [[reader GetOutput] GetBounds]
#  eval cursor SetFocalPoint [[reader GetOutput] GetCenter]
#  cursor AllOff
#  cursor AxesOn
#  cursor OutlineOn
#  cursor XShadowsOn
#  cursor YShadowsOn
#  cursor ZShadowsOn
#puts "cursor set success"

#vtkConeSource cone
#  cone SetResolution 16
#  cone SetRadius 0.25
#puts "cursorCone set success"

#vtkPolyDataMapper cursorMapper
#  cursorMapper SetInput [cone GetOutput]
#puts "cursorMapper set success"

#vtkActor cursorActor
#  cursorActor SetMapper cursorMapper
#  [cursorActor GetProperty] SetColor 1 0 0
#puts "cursorActor set success"

#ren AddActor cursorActor

#---------------------
puts "cursor set success"

    eval [cylinderActor GetProperty] SetColor $tomato
     cylinderActor RotateX  30.0
     cylinderActor RotateY -45.0
     cylinderActor SetPosition 0.0 0.0 0.0

    #ren SetBackground 0.1 0.2 0.4

    windowLayoutSet
    pack   .mainMenu $vtkw .params -side top -fill both -expand yes

   #iren Render
   #renWin Start 
   #iren Start
   #myi Start

    [ren GetActiveCamera] Zoom 1
    tkwait window .

