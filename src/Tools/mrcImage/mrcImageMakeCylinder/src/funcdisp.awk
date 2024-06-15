BEGIN{
  sx=0;
  ex=42;
  dx=1;
  for (x=sx;x<=ex;x+=dx){
    d=func1d(x);
    print x,d;
  }
}

function func1d(x,d,t)
{
  d=(x-19.5)*(x-19.5);
  return(d);
}



