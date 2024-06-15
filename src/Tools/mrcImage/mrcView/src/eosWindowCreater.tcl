package require vtk
package require vtkinteraction
package require vtktesting

    vtkRenderWindow renWin
    vtkRenderWindowInteractor iren

    #ren1 SetBackground 0.1 0.1 0.1

    set vtkw [vtkTkRenderWidget .ren -width 300 -height 300 -rw renWin]

	set stereoflag 0

    BindTkRenderWidget $vtkw    

    frame .params

. configure -menu .m1

menu .m1

.m1 add cascade -label File -underline 0 -menu .m1.file
menu .m1.file -tearoff no

.m1 add cascade -label Menu -underline 0 -menu .m1.menu
menu .m1.menu -tearoff no


.m1.file add command -label Start -command {
    SetSomeobj renWin
    renWin Render
}


.m1.file add command -label Quit -command bye

.m1.menu add command -label stereo -command {
    if{$stereoflag==0}{
	set stereoflag 1
    }else{
	set stereoflag 0
    }

    SetStereoWindow stereoflag
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
