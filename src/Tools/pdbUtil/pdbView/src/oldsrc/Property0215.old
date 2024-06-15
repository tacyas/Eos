#include "./FunctionMode.hh"

Property::Property()
{

  //DEFAULT
  displayMode = SpaceFill;
  colorMode = Monochrome;
  atomMode = CA;
  pickMode = Default;
  homologyMode = AllData;

  ResMin = 1;
  ResMax = 10;

}

void Property::SetDisplayMode(DisplayMode m)
{
  displayMode = m;
  if(m==BackBone)
    {atomMode = CA;}
}

DisplayMode Property::GetDisplayMode()
{
  return displayMode;
}

void Property::SetAtomMode(AtomMode m)
{
  atomMode = m;
  if(displayMode == BackBone)
    {atomMode = CA;}
}

AtomMode Property::GetAtomMode()
{
  return atomMode;
}

void Property::SetColorMode(ColorMode m)
{
  colorMode =  m;
}

ColorMode Property::GetColorMode()
{
  return colorMode;
}

void Property::SetPickMode(PickMode m)
{
  pickMode = m;
  if(m == Homology){
    homologyMode = AllData;
  }
}

PickMode Property::GetPickMode()
{
  return pickMode;
}

void Property::SetHomologyMode(HomologyMode m)
{
  homologyMode = m;
}

HomologyMode Property::GetHomologyMode()
{
  return homologyMode;
}

void Property::SetResNumMinAndMax(int min, int max)
{
  ResMin = min;
  ResMax = max;
  printf("min%d  max%d\n",ResMin,ResMax);
}

int Property::GetResNumMin()
{
  return ResMin;
}

int Property::GetResNumMax()
{
  return ResMax;
}
