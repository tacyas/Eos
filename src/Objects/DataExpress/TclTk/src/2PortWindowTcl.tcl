package require vtk
package require vtkinteraction
package require vtktesting

wm title . 2PortWindow(TclTk)

    vtkCylinderSource cylinder
     cylinder SetResolution 8

	vtkPolyDataMapper cylinderMapper
	 cylinderMapper SetInput [cylinder GetOutput]

	vtkActor  cylinderActor
	  cylinderActor SetMapper cylinderMapper
	  #cylinderActor GetProperty SetColor 0.0 0.0 1.0
      cylinderActor RotateZ 0.0
      cylinderActor SetPosition 0.0 0.0 0.0
	  cylinderActor RotateY 0.0

	vtkCamera cam
	 cam SetFocalPoint 0 0 0
	 cam SetPosition 0 0 10
	 cam SetEyeAngle 10.0
	
	vtkLight light
	 light SetFocalPoint 0.21406 1.5 0
	 light SetPosition 8.3761 4.94858 4.1250
	
    vtkRenderer ren
     ren SetActiveCamera cam
	 ren AddLight light
 	 ren AddActor  cylinderActor
     ren SetViewport 0.0 0.0 1.0 1.0
	  
	vtkRenderer ren2
      ren2 SetActiveCamera cam
	  ren2 AddLight light
	  ren2 AddActor  cylinderActor
	  ren2 SetViewport 0.0 0.0 0.0 0.0
    vtkRenderWindow renWin
     renWin AddRenderer ren
	 renWin AddRenderer ren2

	vtkRenderWindowInteractor iren
	 iren SetRenderWindow renWin
 	#eosInteractorMyStyle temp
	# temp New
	#eosInteractorMyStyle myi
	 #set myi temp
	 #myi SetStereoRenderWindows ren iren
     #iren SetInteractorStyle myi


    #eval [cylinderActor GetProperty] SetColor $tomato 
    # cylinder1Actor RotateX  30.0
    # cylinder1Actor RotateY -45.0
    #eval [cylinder2Actor GetProperty] SetColor $red 
    # cylinder2Actor RotateX  30.0
    # cylinder2Actor RotateY -45.0


    #vtkRenderWindowInteractor iren
    #eosInteractorMyStyle ListInstances 
    #eosInteractorMyStyle myi
    #eosInteractorMyStyle ListInstances 
    #iren SetInteractorStyle myi
	#myi ListMethods
    #myi SetStereoRenderWindows ren1 iren 
    #vtkInteractorStyle myi


    set vtkw [vtkTkRenderWidget .ren -width 300 -height 300 -rw renWin]

	set stereoflag 0

    BindTkRenderWidget $vtkw    

    frame .params
    
    [ren GetActiveCamera] Zoom 1 

. configure -menu .m1

menu .m1

.m1 add cascade -label File -underline 0 -menu .m1.file
menu .m1.file -tearoff no

.m1 add cascade -label Menu -underline 0 -menu .m1.menu
menu .m1.menu -tearoff no


.m1.file add command -label Open -command {
    renWin Render
}


.m1.file add command -label Quit -command {
   vtkCommand DeleteAllObjects
   exit
}

.m1.menu add command -label stereo -command {

	if {$stereoflag == 0} {
	  set stereoflag 1
	}else {
	  set stereoflag 0
	}
		
    StereoMode stereoflag 
}

.m1.menu add command -label RotateOn -command {
    iren SetRenderWindow renWin
    iren AddObserver UserEvent {wm deiconify .vtkInteract}
    iren Initialize
    iren Enable
}

.m1.menu add command -label RotateOff -command {
    iren Disable
    #wait 3
    #iren Enable 
    iren SetInteractorStyle vtkInteractorStyleTrackball
	iren Enable
}


button .params.quit -text "Quit" -command bye
pack .params.quit -side top -anchor nw -fill both
pack $vtkw .params -side top -fill both -expand yes

wm protocol . WM_DELETE_WINDOW bye 
proc bye {} {
    vtkCommand DeleteAllObjects
    exit
}

#renWin Render
#iren Start

tkwait window .
