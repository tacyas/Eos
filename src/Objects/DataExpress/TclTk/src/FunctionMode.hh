#ifndef FUNCTION_MODE_HH
#define FUNCTION_MODE_HH


enum DisplayMode{
  SpaceFill,
  Point,
  BackBone
};

enum AtomMode{
  AtomModeAll,
  AtomModeCA
};

enum ColorMode{
  Monochrome,
  CPK,
  Group,
  Amino,
  Temperature,
  HomoColor
};

enum PickMode{
  Default,
  ResNumber,
  AtomName,
  ResName,
  ChainID,
  Memo,
  Homology
};

enum HomologyMode{
  AllData,
  Percentage,
  EachData,
  ChangeColor
};

enum PickStatus{
  Search,
  Delete,
  Create,
};

/*
enum CG{
  CGAll,
  CGCAonly
};
*/
/*
enum TextMode{
  ResidueSequenceNumber,
  AtomName,
  ResidueName,
  ChainIdentifier,
  AllSet,
  Homology
};
*/

/*
enum HomologyMode{
  AllView,
  Percentage,
  EachData,
  Color
};
*/
/*
enum ViewerMode{
  SpaceFill=0,
  BackBone=1
};
*/

#endif /* FUNCTION_MODE */
