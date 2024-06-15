package require vtk
package require vtkinteraction
package require vtktesting

    vtkCylinderSource cylinder
     cylinder SetResolution 8
    
    vtkPolyDataMapper cylinderMapper
     cylinderMapper SetInput [cylinder GetOutput]

    vtkActor cylinderActor
    cylinderActor SetMapper cylinderMapper
    eval [cylinderActor GetProperty] SetColor $tomato 
     cylinderActor RotateX  30.0
     cylinderActor RotateY -45.0

    vtkRenderer ren1
    vtkRenderWindow renWin
    renWin AddRenderer ren1
    vtkRenderWindowInteractor iren


    ren1 AddActor cylinderActor
    ren1 SetBackground 0.1 0.2 0.4

    set vtkw [vtkTkRenderWidget .ren -width 300 -height 300 -rw renWin]

	set stereoflag 0

    BindTkRenderWidget $vtkw    

    frame .params
    
    [ren1 GetActiveCamera] Zoom 1.5

#set color [tk_chooseColor -title color]
. configure -menu .m1

menu .m1

.m1 add cascade -label File -underline 0 -menu .m1.file
menu .m1.file -tearoff no

.m1 add cascade -label Menu -underline 0 -menu .m1.menu
menu .m1.menu -tearoff no


.m1.file add command -label Open -command {
    renWin Render
}


.m1.file add command -label Quit -command exit

.m1.menu add command -label stereo -command {

	if {$stereoflag == 0} {
	  set stereoflag 1
	}else {
	  set stereoflag 0
	}
		
    StereoMode stereoflag 
}

.m1.menu add command -label lotateOn -command {
    iren SetRenderWindow renWin
    iren AddObserver UserEvent {wm deiconify .vtkInteract}
    iren Initialize
    iren Enable
}

.m1.menu add command -label lotateOff -command {
    iren Disable
    #wait 3
    #iren Enable 
}


button .params.quit -text "Quit" -command bye
pack .params.quit -side top -anchor nw -fill both
pack $vtkw .params -side top -fill both -expand yes

wm protocol . WM_DELETE_WINDOW bye 
proc bye {} {
    vtkCommand DeleteAllObjects
    exit
}

tkwait window .
