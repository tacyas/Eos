#include<stdio.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>

main()
{
  Display *dsp;
  Window   win;

  dsp=XOpenDisplay(NULL);

  win=XCreateSimpleWindow(dsp,DefaultRootWindow(dsp),
                           0,0,800,400,1,
			  BlackPixel(dsp,0),WhitePixel(dsp,0));

  XMapWindow(dsp,win);
  XFlush(dsp);
  
  getchar();
  XUnmapWindow(dsp,win);
  XFlush(dsp);
  
  getchar();
  XMapWindow(dsp,win);
  XFlush(dsp);
  
  getchar();
  XCloseDisplay(dsp);
}
