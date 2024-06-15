#ifndef FUNCTION_MODE_HH
#define FUNCTION_MODE_HH

enum CG{
  All,
  CAonly
};

enum TextMode{
  ResidueSequenceNumber,
  AtomName,
  ResidueName,
  ChainIdentifier,
  AllSet,
  Homology
};

enum HomologyMode{
  AllView,
  Pacentage,
  EachData,
  Color
};

enum ViewerMode{
  SpaceFill=0,
  BackBone=1
};

#endif /* FUNCTION_MODE */
