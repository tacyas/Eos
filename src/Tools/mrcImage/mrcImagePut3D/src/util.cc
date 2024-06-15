#include "../inc/config.h"

#include <string.h>
#include <tcl.h>
#include "vtkmrcImageReader.hh"

int vtkCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
int vtkAGraymapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAGraymapNewCommand();
int vtkAPixmapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAPixmapNewCommand();
int vtkActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkActorNewCommand();
int vtkAppendFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAppendFilterNewCommand();
int vtkAppendPolyDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAppendPolyDataNewCommand();
int vtkAssemblyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAssemblyNewCommand();
int vtkAxesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAxesNewCommand();
int vtkBYUReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBYUReaderNewCommand();
int vtkBYUWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBYUWriterNewCommand();
int vtkBitArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBitArrayNewCommand();
int vtkBitScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBitScalarsNewCommand();
int vtkBitmapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBitmapNewCommand();
int vtkBooleanStructuredPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBooleanStructuredPointsNewCommand();
int vtkBooleanTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBooleanTextureNewCommand();
int vtkBrownianPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkBrownianPointsNewCommand();
int vtkByteSwapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkByteSwapNewCommand();
int vtkCameraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCameraNewCommand();
int vtkCastToConcreteCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCastToConcreteNewCommand();
int vtkCellArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCellArrayNewCommand();
int vtkCellListCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCellListNewCommand();
int vtkCellLocatorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCellLocatorNewCommand();
int vtkCellPickerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCellPickerNewCommand();
int vtkCleanPolyDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCleanPolyDataNewCommand();
int vtkCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCollectionNewCommand();
int vtkConeCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkConeNewCommand();
int vtkConeSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkConeSourceNewCommand();
int vtkConnectivityFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkConnectivityFilterNewCommand();
int vtkContourFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkContourFilterNewCommand();
int vtkCubeSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCubeSourceNewCommand();
int vtkCursor3DCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCursor3DNewCommand();
int vtkCutterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCutterNewCommand();
int vtkCyberReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCyberReaderNewCommand();
int vtkCylinderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCylinderNewCommand();
int vtkCylinderSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkCylinderSourceNewCommand();
int vtkDashedStreamLineCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDashedStreamLineNewCommand();
int vtkDataReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataReaderNewCommand();
int vtkDataSetFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetFilterNewCommand();
int vtkDataSetMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetMapperNewCommand();
int vtkDataSetReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetReaderNewCommand();
int vtkDataSetToDataSetFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetToDataSetFilterNewCommand();
int vtkDataSetToPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetToPolyFilterNewCommand();
int vtkDataSetToStructuredGridFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetToStructuredGridFilterNewCommand();
int vtkDataSetToStructuredPointsFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetToStructuredPointsFilterNewCommand();
int vtkDataSetToUnstructuredGridFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetToUnstructuredGridFilterNewCommand();
int vtkDataSetWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetWriterNewCommand();
int vtkDecimateCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDecimateNewCommand();
int vtkDelaunay2DCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDelaunay2DNewCommand();
int vtkDelaunay3DCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDelaunay3DNewCommand();
int vtkDicerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDicerNewCommand();
int vtkDiskSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDiskSourceNewCommand();
int vtkDividingCubesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDividingCubesNewCommand();
int vtkDoubleArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDoubleArrayNewCommand();
int vtkEarthSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkEarthSourceNewCommand();
int vtkEdgeTableCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkEdgeTableNewCommand();
int vtkEdgePointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkEdgePointsNewCommand();
int vtkElevationFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkElevationFilterNewCommand();
int vtkExtractEdgesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkExtractEdgesNewCommand();
int vtkExtractGeometryCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkExtractGeometryNewCommand();
int vtkExtractVectorComponentsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkExtractVectorComponentsNewCommand();
int vtkExtractGridCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkExtractGridNewCommand();
int vtkExtractVOICommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkExtractVOINewCommand();
int vtkFeatureEdgesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFeatureEdgesNewCommand();
int vtkFeatureVerticesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFeatureVerticesNewCommand();
int vtkFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFilterNewCommand();
int vtkFloatArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatArrayNewCommand();
int vtkFloatNormalsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatNormalsNewCommand();
int vtkFloatPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatPointsNewCommand();
int vtkFloatScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatScalarsNewCommand();
int vtkFloatTCoordsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatTCoordsNewCommand();
int vtkFloatTensorsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatTensorsNewCommand();
int vtkFloatVectorsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFloatVectorsNewCommand();
int vtkFollowerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkFollowerNewCommand();
int vtkGaussianSplatterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGaussianSplatterNewCommand();
int vtkGeometryFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGeometryFilterNewCommand();
int vtkGlyph3DCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlyph3DNewCommand();
int vtkGraymapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGraymapNewCommand();
int vtkHedgeHogCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkHedgeHogNewCommand();
int vtkHexahedronCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkHexahedronNewCommand();
int vtkHyperStreamlineCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkHyperStreamlineNewCommand();
int vtkIdListCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkIdListNewCommand();
int vtkImageDifferenceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkImageDifferenceNewCommand();
int vtkImplicitBooleanCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkImplicitBooleanNewCommand();
int vtkImplicitModellerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkImplicitModellerNewCommand();
int vtkImplicitTextureCoordsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkImplicitTextureCoordsNewCommand();
int vtkIndentCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkIndentNewCommand();
int vtkIntArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkIntArrayNewCommand();
int vtkIntPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkIntPointsNewCommand();
int vtkIntScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkIntScalarsNewCommand();
int vtkLODActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLODActorNewCommand();
int vtkLightCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLightNewCommand();
int vtkLineCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLineNewCommand();
int vtkLineSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLineSourceNewCommand();
int vtkLinearExtrusionFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLinearExtrusionFilterNewCommand();
int vtkLinkListCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLinkListNewCommand();
int vtkLogLookupTableCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLogLookupTableNewCommand();
int vtkLookupTableCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLookupTableNewCommand();
int vtkMCubesReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMCubesReaderNewCommand();
int vtkMCubesWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMCubesWriterNewCommand();
int vtkMarchingCubesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMarchingCubesNewCommand();
int vtkMarchingSquaresCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMarchingSquaresNewCommand();
int vtkMaskPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMaskPointsNewCommand();
int vtkMaskPolyDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMaskPolyDataNewCommand();
int vtkMathCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMathNewCommand();
int vtkMatrix4x4Command(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMatrix4x4NewCommand();
int vtkMergeFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMergeFilterNewCommand();
int vtkMergePointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkMergePointsNewCommand();
int vtkNewVolumeRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkNewVolumeRendererNewCommand();
int vtkOBBTreeCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOBBTreeNewCommand();
int vtkObjectCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkObjectNewCommand();
int vtkOBJExporterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOBJExporterNewCommand();
int vtkOutlineFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOutlineFilterNewCommand();
int vtkOutlineSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOutlineSourceNewCommand();
int vtkPLOT3DReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPLOT3DReaderNewCommand();
int vtkPNMReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPNMReaderNewCommand();
int vtkPNMWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPNMWriterNewCommand();
int vtkPickerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPickerNewCommand();
int vtkPixelCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPixelNewCommand();
int vtkPixmapCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPixmapNewCommand();
int vtkPlaneCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPlaneNewCommand();
int vtkPlaneSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPlaneSourceNewCommand();
int vtkPlanesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPlanesNewCommand();
int vtkPointDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointDataNewCommand();
int vtkPointLoadCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointLoadNewCommand();
int vtkPointLocatorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointLocatorNewCommand();
int vtkPointPickerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointPickerNewCommand();
int vtkPointSetFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointSetFilterNewCommand();
int vtkPointSetToPointSetFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointSetToPointSetFilterNewCommand();
int vtkPointSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPointSourceNewCommand();
int vtkPolyDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyDataNewCommand();
int vtkPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyFilterNewCommand();
int vtkPolyLineCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyLineNewCommand();
int vtkPolyMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyMapperNewCommand();
int vtkPolyNormalsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyNormalsNewCommand();
int vtkPolyReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyReaderNewCommand();
int vtkPolySourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolySourceNewCommand();
int vtkPolyToPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyToPolyFilterNewCommand();
int vtkPolyVertexCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyVertexNewCommand();
int vtkPolyWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyWriterNewCommand();
int vtkPolygonCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolygonNewCommand();
int vtkProbeFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkProbeFilterNewCommand();
int vtkPropertyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPropertyNewCommand();
int vtkQuadCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkQuadNewCommand();
int vtkQuadricCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkQuadricNewCommand();
int vtkRecursiveDividingCubesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRecursiveDividingCubesNewCommand();
int vtkRefCountCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRefCountNewCommand();
int vtkRenderMasterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRenderMasterNewCommand();
int vtkRenderWindowInteractorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRenderWindowInteractorNewCommand();
int vtkRendererCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRendererCollectionNewCommand();
int vtkRendererSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRendererSourceNewCommand();
int vtkRibbonFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRibbonFilterNewCommand();
int vtkRotationalExtrusionFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRotationalExtrusionFilterNewCommand();
int vtkSTLReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSTLReaderNewCommand();
int vtkSTLWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSTLWriterNewCommand();
int vtkSampleFunctionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSampleFunctionNewCommand();
int vtkShepardMethodCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkShepardMethodNewCommand();
int vtkShortArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkShortArrayNewCommand();
int vtkUnsignedShortArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnsignedShortArrayNewCommand();
int vtkShortScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkShortScalarsNewCommand();
int vtkUnsignedShortScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnsignedShortScalarsNewCommand();
int vtkShrinkFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkShrinkFilterNewCommand();
int vtkShrinkPolyDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkShrinkPolyDataNewCommand();
int vtkSliceCubesCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSliceCubesNewCommand();
int vtkSmoothPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSmoothPolyFilterNewCommand();
int vtkSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSourceNewCommand();
int vtkSpatialRepFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSpatialRepFilterNewCommand();
int vtkSphereCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSphereNewCommand();
int vtkSphereSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSphereSourceNewCommand();
int vtkStackCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStackNewCommand();
int vtkStreamLineCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStreamLineNewCommand();
int vtkStreamPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStreamPointsNewCommand();
int vtkStreamerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStreamerNewCommand();
int vtkStripperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStripperNewCommand();
int vtkStructuredDataCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredDataNewCommand();
int vtkStructuredGridCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridNewCommand();
int vtkStructuredGridFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridFilterNewCommand();
int vtkStructuredGridGeometryFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridGeometryFilterNewCommand();
int vtkStructuredGridOutlineFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridOutlineFilterNewCommand();
int vtkStructuredGridReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridReaderNewCommand();
int vtkStructuredGridSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridSourceNewCommand();
int vtkStructuredGridToPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridToPolyFilterNewCommand();
int vtkStructuredGridToStructuredGridFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridToStructuredGridFilterNewCommand();
int vtkStructuredGridWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredGridWriterNewCommand();
int vtkStructuredPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsNewCommand();
int vtkStructuredPointsFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsFilterNewCommand();
int vtkStructuredPointsGeometryFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsGeometryFilterNewCommand();
int vtkStructuredPointsReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsReaderNewCommand();
int vtkStructuredPointsSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsSourceNewCommand();
int vtkStructuredPointsToPolyDataFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsToPolyDataFilterNewCommand();
int vtkStructuredPointsToStructuredPointsFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsToStructuredPointsFilterNewCommand();
int vtkStructuredPointsWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsWriterNewCommand();
int vtkSweptSurfaceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSweptSurfaceNewCommand();
int vtkTensorGlyphCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTensorGlyphNewCommand();
int vtkTetraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTetraNewCommand();
int vtkTextSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextSourceNewCommand();
int vtkTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextureNewCommand();
int vtkTextureMapToBoxCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextureMapToBoxNewCommand();
int vtkTextureMapToCylinderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextureMapToCylinderNewCommand();
int vtkTextureMapToPlaneCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextureMapToPlaneNewCommand();
int vtkTextureMapToSphereCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTextureMapToSphereNewCommand();
int vtkTexturedSphereSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTexturedSphereSourceNewCommand();
int vtkThresholdCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkThresholdNewCommand();
int vtkThresholdPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkThresholdPointsNewCommand();
int vtkThresholdTextureCoordsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkThresholdTextureCoordsNewCommand();
int vtkTimeStampCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTimeStampNewCommand();
int vtkTransformCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformNewCommand();
int vtkTransformFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformFilterNewCommand();
int vtkTransformPolyFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformPolyFilterNewCommand();
int vtkTransformStructuredPointsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformStructuredPointsNewCommand();
int vtkTransformTextureCoordsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformTextureCoordsNewCommand();
int vtkTriangleCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTriangleNewCommand();
int vtkTriangleFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTriangleFilterNewCommand();
int vtkTriangleStripCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTriangleStripNewCommand();
int vtkTubeFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTubeFilterNewCommand();
int vtkUGFacetReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUGFacetReaderNewCommand();
int vtkUnsignedCharArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnsignedCharArrayNewCommand();
int vtkUnsignedCharScalarsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnsignedCharScalarsNewCommand();
int vtkUnstructuredGridCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnstructuredGridNewCommand();
int vtkUnstructuredGridFilterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnstructuredGridFilterNewCommand();
int vtkUnstructuredGridReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnstructuredGridReaderNewCommand();
int vtkUnstructuredGridSourceCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnstructuredGridSourceNewCommand();
int vtkUnstructuredGridWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUnstructuredGridWriterNewCommand();
int vtkUserDefinedCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkUserDefinedNewCommand();
int vtkVectorDotCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVectorDotNewCommand();
int vtkVectorNormCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVectorNormNewCommand();
int vtkVectorTextCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVectorTextNewCommand();
int vtkVectorTopologyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVectorTopologyNewCommand();
int vtkVertexCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVertexNewCommand();
int vtkVoidArrayCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVoidArrayNewCommand();
int vtkVolumeCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVolumeNewCommand();
int vtkVolume16ReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVolume16ReaderNewCommand();
int vtkmrcImageReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkmrcImageReaderNewCommand();
ClientData vtkmrcImageReaderNewCommand()
{
	vtkmrcImageReader * tmp = new vtkmrcImageReader;
	return ((ClientData)tmp);
}

int vtkVolumeRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVolumeRendererNewCommand();
int vtkVoxelCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVoxelNewCommand();
int vtkVoxelModellerCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVoxelModellerNewCommand();
int vtkVoxelReaderCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVoxelReaderNewCommand();
int vtkVoxelWriterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVoxelWriterNewCommand();
int vtkVRMLExporterCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVRMLExporterNewCommand();
int vtkWarpScalarCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkWarpScalarNewCommand();
int vtkWarpToCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkWarpToNewCommand();
int vtkWarpVectorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkWarpVectorNewCommand();
int vtkWindowLevelLookupTableCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkWindowLevelLookupTableNewCommand();
int vtkXRenderWindowInteractorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXRenderWindowInteractorNewCommand();
int vtkActorCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkActorCollectionNewCommand();
int vtkAssemblyPathsCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkAssemblyPathsNewCommand();
int vtkRenderWindowCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkRenderWindowCollectionNewCommand();
int vtkVolumeCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkVolumeCollectionNewCommand();
int vtkLightCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkLightCollectionNewCommand();
int vtkTensorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTensorNewCommand();
int vtkTransformCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkTransformCollectionNewCommand();
int vtkPolyDataCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkPolyDataCollectionNewCommand();
int vtkDataSetCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkDataSetCollectionNewCommand();
int vtkImplicitFunctionCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkImplicitFunctionCollectionNewCommand();
int vtkStructuredPointsCollectionCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkStructuredPointsCollectionNewCommand();
#ifdef USE_GLR
int vtkGlrActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrActorNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrCameraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrCameraNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrLightCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrLightNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrPolyMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrPolyMapperNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrPropertyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrPropertyNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrRenderWindowNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrRendererNewCommand();
#endif
#ifdef USE_GLR
int vtkGlrTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkGlrTextureNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrActorNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrCameraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrCameraNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrLightCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrLightNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrPolyMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrPolyMapperNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrPropertyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrPropertyNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrRenderWindowNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrRendererNewCommand();
#endif
#ifdef USE_SBR
int vtkSbrTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkSbrTextureNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrActorNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrCameraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrCameraNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrLightCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrLightNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrPolyMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrPolyMapperNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrPropertyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrPropertyNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrRenderWindowNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrRendererNewCommand();
#endif
#ifdef USE_OGLR
int vtkOglrTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkOglrTextureNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrActorCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrActorNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrCameraCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrCameraNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrLightCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrLightNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrPolyMapperCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrPolyMapperNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrPropertyCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrPropertyNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrRenderWindowNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrRendererNewCommand();
#endif
#ifdef USE_XGLR
int vtkXglrTextureCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[]);
ClientData vtkXglrTextureNewCommand();
#endif

Tcl_HashTable vtkInstanceLookup;
Tcl_HashTable vtkPointerLookup;
Tcl_HashTable vtkCommandLookup;


extern "C" {int VTK_Init(Tcl_Interp *interp);}



extern void vtkTclGenericDeleteObject(ClientData cd);

int vtkNewInstanceCommand(ClientData cd, Tcl_Interp *interp,
                         int argc, char *argv[])
{
  Tcl_HashEntry *entry;
  int is_new;
  char temps[80];
  cd = 0; /* just prevents compiler warnings */

  if (argc != 2)
    {
    interp->result = "vtk object creation requires one argument, a name.";
    return TCL_ERROR;
    }


  if (argc != 2)
    {
    interp->result = "vtk object creation requires one argument, a name.";
    return TCL_ERROR;
    }

  if ((argv[1][0] >= '0')&&(argv[1][0] <= '9'))
    {
    interp->result = "vtk object names must start with a letter.";
    return TCL_ERROR;
    }

  if (Tcl_FindHashEntry(&vtkInstanceLookup,argv[1]))
    {
    interp->result = "a vtk object with that name already exists.";
    return TCL_ERROR;
    }

  if (!strcmp("vtkAGraymap",argv[0]))
    {
    ClientData temp = vtkAGraymapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAGraymapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAGraymapCommand));
    }

  if (!strcmp("vtkAPixmap",argv[0]))
    {
    ClientData temp = vtkAPixmapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAPixmapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAPixmapCommand));
    }

  if (!strcmp("vtkActor",argv[0]))
    {
    ClientData temp = vtkActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkActorCommand));
    }

  if (!strcmp("vtkAppendFilter",argv[0]))
    {
    ClientData temp = vtkAppendFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAppendFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAppendFilterCommand));
    }

  if (!strcmp("vtkAppendPolyData",argv[0]))
    {
    ClientData temp = vtkAppendPolyDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAppendPolyDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAppendPolyDataCommand));
    }

  if (!strcmp("vtkAssembly",argv[0]))
    {
    ClientData temp = vtkAssemblyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAssemblyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAssemblyCommand));
    }

  if (!strcmp("vtkAxes",argv[0]))
    {
    ClientData temp = vtkAxesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAxesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAxesCommand));
    }

  if (!strcmp("vtkBYUReader",argv[0]))
    {
    ClientData temp = vtkBYUReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBYUReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBYUReaderCommand));
    }

  if (!strcmp("vtkBYUWriter",argv[0]))
    {
    ClientData temp = vtkBYUWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBYUWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBYUWriterCommand));
    }

  if (!strcmp("vtkBitArray",argv[0]))
    {
    ClientData temp = vtkBitArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBitArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBitArrayCommand));
    }

  if (!strcmp("vtkBitScalars",argv[0]))
    {
    ClientData temp = vtkBitScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBitScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBitScalarsCommand));
    }

  if (!strcmp("vtkBitmap",argv[0]))
    {
    ClientData temp = vtkBitmapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBitmapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBitmapCommand));
    }

  if (!strcmp("vtkBooleanStructuredPoints",argv[0]))
    {
    ClientData temp = vtkBooleanStructuredPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBooleanStructuredPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBooleanStructuredPointsCommand));
    }

  if (!strcmp("vtkBooleanTexture",argv[0]))
    {
    ClientData temp = vtkBooleanTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBooleanTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBooleanTextureCommand));
    }

  if (!strcmp("vtkBrownianPoints",argv[0]))
    {
    ClientData temp = vtkBrownianPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkBrownianPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkBrownianPointsCommand));
    }

  if (!strcmp("vtkByteSwap",argv[0]))
    {
    ClientData temp = vtkByteSwapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkByteSwapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkByteSwapCommand));
    }

  if (!strcmp("vtkCamera",argv[0]))
    {
    ClientData temp = vtkCameraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCameraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCameraCommand));
    }

  if (!strcmp("vtkCastToConcrete",argv[0]))
    {
    ClientData temp = vtkCastToConcreteNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCastToConcreteCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCastToConcreteCommand));
    }

  if (!strcmp("vtkCellArray",argv[0]))
    {
    ClientData temp = vtkCellArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCellArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCellArrayCommand));
    }

  if (!strcmp("vtkCellList",argv[0]))
    {
    ClientData temp = vtkCellListNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCellListCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCellListCommand));
    }

  if (!strcmp("vtkCellLocator",argv[0]))
    {
    ClientData temp = vtkCellLocatorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCellLocatorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCellLocatorCommand));
    }

  if (!strcmp("vtkCellPicker",argv[0]))
    {
    ClientData temp = vtkCellPickerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCellPickerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCellPickerCommand));
    }

  if (!strcmp("vtkCleanPolyData",argv[0]))
    {
    ClientData temp = vtkCleanPolyDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCleanPolyDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCleanPolyDataCommand));
    }

  if (!strcmp("vtkCollection",argv[0]))
    {
    ClientData temp = vtkCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCollectionCommand));
    }

  if (!strcmp("vtkCone",argv[0]))
    {
    ClientData temp = vtkConeNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkConeCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkConeCommand));
    }

  if (!strcmp("vtkConeSource",argv[0]))
    {
    ClientData temp = vtkConeSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkConeSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkConeSourceCommand));
    }

  if (!strcmp("vtkConnectivityFilter",argv[0]))
    {
    ClientData temp = vtkConnectivityFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkConnectivityFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkConnectivityFilterCommand));
    }

  if (!strcmp("vtkContourFilter",argv[0]))
    {
    ClientData temp = vtkContourFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkContourFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkContourFilterCommand));
    }

  if (!strcmp("vtkCubeSource",argv[0]))
    {
    ClientData temp = vtkCubeSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCubeSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCubeSourceCommand));
    }

  if (!strcmp("vtkCursor3D",argv[0]))
    {
    ClientData temp = vtkCursor3DNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCursor3DCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCursor3DCommand));
    }

  if (!strcmp("vtkCutter",argv[0]))
    {
    ClientData temp = vtkCutterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCutterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCutterCommand));
    }

  if (!strcmp("vtkCyberReader",argv[0]))
    {
    ClientData temp = vtkCyberReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCyberReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCyberReaderCommand));
    }

  if (!strcmp("vtkCylinder",argv[0]))
    {
    ClientData temp = vtkCylinderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCylinderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCylinderCommand));
    }

  if (!strcmp("vtkCylinderSource",argv[0]))
    {
    ClientData temp = vtkCylinderSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkCylinderSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkCylinderSourceCommand));
    }

  if (!strcmp("vtkDashedStreamLine",argv[0]))
    {
    ClientData temp = vtkDashedStreamLineNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDashedStreamLineCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDashedStreamLineCommand));
    }

  if (!strcmp("vtkDataReader",argv[0]))
    {
    ClientData temp = vtkDataReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataReaderCommand));
    }

  if (!strcmp("vtkDataSetFilter",argv[0]))
    {
    ClientData temp = vtkDataSetFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetFilterCommand));
    }

  if (!strcmp("vtkDataSetMapper",argv[0]))
    {
    ClientData temp = vtkDataSetMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetMapperCommand));
    }

  if (!strcmp("vtkDataSetReader",argv[0]))
    {
    ClientData temp = vtkDataSetReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetReaderCommand));
    }

  if (!strcmp("vtkDataSetToDataSetFilter",argv[0]))
    {
    ClientData temp = vtkDataSetToDataSetFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetToDataSetFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetToDataSetFilterCommand));
    }

  if (!strcmp("vtkDataSetToPolyFilter",argv[0]))
    {
    ClientData temp = vtkDataSetToPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetToPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetToPolyFilterCommand));
    }

  if (!strcmp("vtkDataSetToStructuredGridFilter",argv[0]))
    {
    ClientData temp = vtkDataSetToStructuredGridFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetToStructuredGridFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetToStructuredGridFilterCommand));
    }

  if (!strcmp("vtkDataSetToStructuredPointsFilter",argv[0]))
    {
    ClientData temp = vtkDataSetToStructuredPointsFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetToStructuredPointsFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetToStructuredPointsFilterCommand));
    }

  if (!strcmp("vtkDataSetToUnstructuredGridFilter",argv[0]))
    {
    ClientData temp = vtkDataSetToUnstructuredGridFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetToUnstructuredGridFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetToUnstructuredGridFilterCommand));
    }

  if (!strcmp("vtkDataSetWriter",argv[0]))
    {
    ClientData temp = vtkDataSetWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetWriterCommand));
    }

  if (!strcmp("vtkDecimate",argv[0]))
    {
    ClientData temp = vtkDecimateNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDecimateCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDecimateCommand));
    }

  if (!strcmp("vtkDelaunay2D",argv[0]))
    {
    ClientData temp = vtkDelaunay2DNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDelaunay2DCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDelaunay2DCommand));
    }

  if (!strcmp("vtkDelaunay3D",argv[0]))
    {
    ClientData temp = vtkDelaunay3DNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDelaunay3DCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDelaunay3DCommand));
    }

  if (!strcmp("vtkDicer",argv[0]))
    {
    ClientData temp = vtkDicerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDicerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDicerCommand));
    }

  if (!strcmp("vtkDiskSource",argv[0]))
    {
    ClientData temp = vtkDiskSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDiskSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDiskSourceCommand));
    }

  if (!strcmp("vtkDividingCubes",argv[0]))
    {
    ClientData temp = vtkDividingCubesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDividingCubesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDividingCubesCommand));
    }

  if (!strcmp("vtkDoubleArray",argv[0]))
    {
    ClientData temp = vtkDoubleArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDoubleArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDoubleArrayCommand));
    }

  if (!strcmp("vtkEarthSource",argv[0]))
    {
    ClientData temp = vtkEarthSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkEarthSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkEarthSourceCommand));
    }

  if (!strcmp("vtkEdgeTable",argv[0]))
    {
    ClientData temp = vtkEdgeTableNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkEdgeTableCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkEdgeTableCommand));
    }

  if (!strcmp("vtkEdgePoints",argv[0]))
    {
    ClientData temp = vtkEdgePointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkEdgePointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkEdgePointsCommand));
    }

  if (!strcmp("vtkElevationFilter",argv[0]))
    {
    ClientData temp = vtkElevationFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkElevationFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkElevationFilterCommand));
    }

  if (!strcmp("vtkExtractEdges",argv[0]))
    {
    ClientData temp = vtkExtractEdgesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkExtractEdgesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkExtractEdgesCommand));
    }

  if (!strcmp("vtkExtractGeometry",argv[0]))
    {
    ClientData temp = vtkExtractGeometryNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkExtractGeometryCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkExtractGeometryCommand));
    }

  if (!strcmp("vtkExtractVectorComponents",argv[0]))
    {
    ClientData temp = vtkExtractVectorComponentsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkExtractVectorComponentsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkExtractVectorComponentsCommand));
    }

  if (!strcmp("vtkExtractGrid",argv[0]))
    {
    ClientData temp = vtkExtractGridNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkExtractGridCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkExtractGridCommand));
    }

  if (!strcmp("vtkExtractVOI",argv[0]))
    {
    ClientData temp = vtkExtractVOINewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkExtractVOICommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkExtractVOICommand));
    }

  if (!strcmp("vtkFeatureEdges",argv[0]))
    {
    ClientData temp = vtkFeatureEdgesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFeatureEdgesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFeatureEdgesCommand));
    }

  if (!strcmp("vtkFeatureVertices",argv[0]))
    {
    ClientData temp = vtkFeatureVerticesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFeatureVerticesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFeatureVerticesCommand));
    }

  if (!strcmp("vtkFilter",argv[0]))
    {
    ClientData temp = vtkFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFilterCommand));
    }

  if (!strcmp("vtkFloatArray",argv[0]))
    {
    ClientData temp = vtkFloatArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatArrayCommand));
    }

  if (!strcmp("vtkFloatNormals",argv[0]))
    {
    ClientData temp = vtkFloatNormalsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatNormalsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatNormalsCommand));
    }

  if (!strcmp("vtkFloatPoints",argv[0]))
    {
    ClientData temp = vtkFloatPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatPointsCommand));
    }

  if (!strcmp("vtkFloatScalars",argv[0]))
    {
    ClientData temp = vtkFloatScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatScalarsCommand));
    }

  if (!strcmp("vtkFloatTCoords",argv[0]))
    {
    ClientData temp = vtkFloatTCoordsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatTCoordsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatTCoordsCommand));
    }

  if (!strcmp("vtkFloatTensors",argv[0]))
    {
    ClientData temp = vtkFloatTensorsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatTensorsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatTensorsCommand));
    }

  if (!strcmp("vtkFloatVectors",argv[0]))
    {
    ClientData temp = vtkFloatVectorsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFloatVectorsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFloatVectorsCommand));
    }

  if (!strcmp("vtkFollower",argv[0]))
    {
    ClientData temp = vtkFollowerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkFollowerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkFollowerCommand));
    }

  if (!strcmp("vtkGaussianSplatter",argv[0]))
    {
    ClientData temp = vtkGaussianSplatterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGaussianSplatterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGaussianSplatterCommand));
    }

  if (!strcmp("vtkGeometryFilter",argv[0]))
    {
    ClientData temp = vtkGeometryFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGeometryFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGeometryFilterCommand));
    }

  if (!strcmp("vtkGlyph3D",argv[0]))
    {
    ClientData temp = vtkGlyph3DNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlyph3DCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlyph3DCommand));
    }

  if (!strcmp("vtkGraymap",argv[0]))
    {
    ClientData temp = vtkGraymapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGraymapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGraymapCommand));
    }

  if (!strcmp("vtkHedgeHog",argv[0]))
    {
    ClientData temp = vtkHedgeHogNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkHedgeHogCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkHedgeHogCommand));
    }

  if (!strcmp("vtkHexahedron",argv[0]))
    {
    ClientData temp = vtkHexahedronNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkHexahedronCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkHexahedronCommand));
    }

  if (!strcmp("vtkHyperStreamline",argv[0]))
    {
    ClientData temp = vtkHyperStreamlineNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkHyperStreamlineCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkHyperStreamlineCommand));
    }

  if (!strcmp("vtkIdList",argv[0]))
    {
    ClientData temp = vtkIdListNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkIdListCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkIdListCommand));
    }

  if (!strcmp("vtkImageDifference",argv[0]))
    {
    ClientData temp = vtkImageDifferenceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkImageDifferenceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkImageDifferenceCommand));
    }

  if (!strcmp("vtkImplicitBoolean",argv[0]))
    {
    ClientData temp = vtkImplicitBooleanNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkImplicitBooleanCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkImplicitBooleanCommand));
    }

  if (!strcmp("vtkImplicitModeller",argv[0]))
    {
    ClientData temp = vtkImplicitModellerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkImplicitModellerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkImplicitModellerCommand));
    }

  if (!strcmp("vtkImplicitTextureCoords",argv[0]))
    {
    ClientData temp = vtkImplicitTextureCoordsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkImplicitTextureCoordsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkImplicitTextureCoordsCommand));
    }

  if (!strcmp("vtkIndent",argv[0]))
    {
    ClientData temp = vtkIndentNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkIndentCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkIndentCommand));
    }

  if (!strcmp("vtkIntArray",argv[0]))
    {
    ClientData temp = vtkIntArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkIntArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkIntArrayCommand));
    }

  if (!strcmp("vtkIntPoints",argv[0]))
    {
    ClientData temp = vtkIntPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkIntPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkIntPointsCommand));
    }

  if (!strcmp("vtkIntScalars",argv[0]))
    {
    ClientData temp = vtkIntScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkIntScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkIntScalarsCommand));
    }

  if (!strcmp("vtkLODActor",argv[0]))
    {
    ClientData temp = vtkLODActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLODActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLODActorCommand));
    }

  if (!strcmp("vtkLight",argv[0]))
    {
    ClientData temp = vtkLightNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLightCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLightCommand));
    }

  if (!strcmp("vtkLine",argv[0]))
    {
    ClientData temp = vtkLineNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLineCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLineCommand));
    }

  if (!strcmp("vtkLineSource",argv[0]))
    {
    ClientData temp = vtkLineSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLineSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLineSourceCommand));
    }

  if (!strcmp("vtkLinearExtrusionFilter",argv[0]))
    {
    ClientData temp = vtkLinearExtrusionFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLinearExtrusionFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLinearExtrusionFilterCommand));
    }

  if (!strcmp("vtkLinkList",argv[0]))
    {
    ClientData temp = vtkLinkListNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLinkListCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLinkListCommand));
    }

  if (!strcmp("vtkLogLookupTable",argv[0]))
    {
    ClientData temp = vtkLogLookupTableNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLogLookupTableCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLogLookupTableCommand));
    }

  if (!strcmp("vtkLookupTable",argv[0]))
    {
    ClientData temp = vtkLookupTableNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLookupTableCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLookupTableCommand));
    }

  if (!strcmp("vtkMCubesReader",argv[0]))
    {
    ClientData temp = vtkMCubesReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMCubesReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMCubesReaderCommand));
    }

  if (!strcmp("vtkMCubesWriter",argv[0]))
    {
    ClientData temp = vtkMCubesWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMCubesWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMCubesWriterCommand));
    }

  if (!strcmp("vtkMarchingCubes",argv[0]))
    {
    ClientData temp = vtkMarchingCubesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMarchingCubesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMarchingCubesCommand));
    }

  if (!strcmp("vtkMarchingSquares",argv[0]))
    {
    ClientData temp = vtkMarchingSquaresNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMarchingSquaresCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMarchingSquaresCommand));
    }

  if (!strcmp("vtkMaskPoints",argv[0]))
    {
    ClientData temp = vtkMaskPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMaskPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMaskPointsCommand));
    }

  if (!strcmp("vtkMaskPolyData",argv[0]))
    {
    ClientData temp = vtkMaskPolyDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMaskPolyDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMaskPolyDataCommand));
    }

  if (!strcmp("vtkMath",argv[0]))
    {
    ClientData temp = vtkMathNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMathCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMathCommand));
    }

  if (!strcmp("vtkMatrix4x4",argv[0]))
    {
    ClientData temp = vtkMatrix4x4NewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMatrix4x4Command,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMatrix4x4Command));
    }

  if (!strcmp("vtkMergeFilter",argv[0]))
    {
    ClientData temp = vtkMergeFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMergeFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMergeFilterCommand));
    }

  if (!strcmp("vtkMergePoints",argv[0]))
    {
    ClientData temp = vtkMergePointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkMergePointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkMergePointsCommand));
    }

  if (!strcmp("vtkNewVolumeRenderer",argv[0]))
    {
    ClientData temp = vtkNewVolumeRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkNewVolumeRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkNewVolumeRendererCommand));
    }

  if (!strcmp("vtkOBBTree",argv[0]))
    {
    ClientData temp = vtkOBBTreeNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOBBTreeCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOBBTreeCommand));
    }

  if (!strcmp("vtkObject",argv[0]))
    {
    ClientData temp = vtkObjectNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkObjectCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkObjectCommand));
    }

  if (!strcmp("vtkOBJExporter",argv[0]))
    {
    ClientData temp = vtkOBJExporterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOBJExporterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOBJExporterCommand));
    }

  if (!strcmp("vtkOutlineFilter",argv[0]))
    {
    ClientData temp = vtkOutlineFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOutlineFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOutlineFilterCommand));
    }

  if (!strcmp("vtkOutlineSource",argv[0]))
    {
    ClientData temp = vtkOutlineSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOutlineSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOutlineSourceCommand));
    }

  if (!strcmp("vtkPLOT3DReader",argv[0]))
    {
    ClientData temp = vtkPLOT3DReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPLOT3DReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPLOT3DReaderCommand));
    }

  if (!strcmp("vtkPNMReader",argv[0]))
    {
    ClientData temp = vtkPNMReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPNMReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPNMReaderCommand));
    }

  if (!strcmp("vtkPNMWriter",argv[0]))
    {
    ClientData temp = vtkPNMWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPNMWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPNMWriterCommand));
    }

  if (!strcmp("vtkPicker",argv[0]))
    {
    ClientData temp = vtkPickerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPickerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPickerCommand));
    }

  if (!strcmp("vtkPixel",argv[0]))
    {
    ClientData temp = vtkPixelNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPixelCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPixelCommand));
    }

  if (!strcmp("vtkPixmap",argv[0]))
    {
    ClientData temp = vtkPixmapNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPixmapCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPixmapCommand));
    }

  if (!strcmp("vtkPlane",argv[0]))
    {
    ClientData temp = vtkPlaneNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPlaneCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPlaneCommand));
    }

  if (!strcmp("vtkPlaneSource",argv[0]))
    {
    ClientData temp = vtkPlaneSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPlaneSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPlaneSourceCommand));
    }

  if (!strcmp("vtkPlanes",argv[0]))
    {
    ClientData temp = vtkPlanesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPlanesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPlanesCommand));
    }

  if (!strcmp("vtkPointData",argv[0]))
    {
    ClientData temp = vtkPointDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointDataCommand));
    }

  if (!strcmp("vtkPointLoad",argv[0]))
    {
    ClientData temp = vtkPointLoadNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointLoadCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointLoadCommand));
    }

  if (!strcmp("vtkPointLocator",argv[0]))
    {
    ClientData temp = vtkPointLocatorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointLocatorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointLocatorCommand));
    }

  if (!strcmp("vtkPointPicker",argv[0]))
    {
    ClientData temp = vtkPointPickerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointPickerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointPickerCommand));
    }

  if (!strcmp("vtkPointSetFilter",argv[0]))
    {
    ClientData temp = vtkPointSetFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointSetFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointSetFilterCommand));
    }

  if (!strcmp("vtkPointSetToPointSetFilter",argv[0]))
    {
    ClientData temp = vtkPointSetToPointSetFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointSetToPointSetFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointSetToPointSetFilterCommand));
    }

  if (!strcmp("vtkPointSource",argv[0]))
    {
    ClientData temp = vtkPointSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPointSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPointSourceCommand));
    }

  if (!strcmp("vtkPolyData",argv[0]))
    {
    ClientData temp = vtkPolyDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyDataCommand));
    }

  if (!strcmp("vtkPolyFilter",argv[0]))
    {
    ClientData temp = vtkPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyFilterCommand));
    }

  if (!strcmp("vtkPolyLine",argv[0]))
    {
    ClientData temp = vtkPolyLineNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyLineCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyLineCommand));
    }

  if (!strcmp("vtkPolyMapper",argv[0]))
    {
    ClientData temp = vtkPolyMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyMapperCommand));
    }

  if (!strcmp("vtkPolyNormals",argv[0]))
    {
    ClientData temp = vtkPolyNormalsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyNormalsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyNormalsCommand));
    }

  if (!strcmp("vtkPolyReader",argv[0]))
    {
    ClientData temp = vtkPolyReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyReaderCommand));
    }

  if (!strcmp("vtkPolySource",argv[0]))
    {
    ClientData temp = vtkPolySourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolySourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolySourceCommand));
    }

  if (!strcmp("vtkPolyToPolyFilter",argv[0]))
    {
    ClientData temp = vtkPolyToPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyToPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyToPolyFilterCommand));
    }

  if (!strcmp("vtkPolyVertex",argv[0]))
    {
    ClientData temp = vtkPolyVertexNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyVertexCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyVertexCommand));
    }

  if (!strcmp("vtkPolyWriter",argv[0]))
    {
    ClientData temp = vtkPolyWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyWriterCommand));
    }

  if (!strcmp("vtkPolygon",argv[0]))
    {
    ClientData temp = vtkPolygonNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolygonCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolygonCommand));
    }

  if (!strcmp("vtkProbeFilter",argv[0]))
    {
    ClientData temp = vtkProbeFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkProbeFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkProbeFilterCommand));
    }

  if (!strcmp("vtkProperty",argv[0]))
    {
    ClientData temp = vtkPropertyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPropertyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPropertyCommand));
    }

  if (!strcmp("vtkQuad",argv[0]))
    {
    ClientData temp = vtkQuadNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkQuadCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkQuadCommand));
    }

  if (!strcmp("vtkQuadric",argv[0]))
    {
    ClientData temp = vtkQuadricNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkQuadricCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkQuadricCommand));
    }

  if (!strcmp("vtkRecursiveDividingCubes",argv[0]))
    {
    ClientData temp = vtkRecursiveDividingCubesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRecursiveDividingCubesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRecursiveDividingCubesCommand));
    }

  if (!strcmp("vtkRefCount",argv[0]))
    {
    ClientData temp = vtkRefCountNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRefCountCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRefCountCommand));
    }

  if (!strcmp("vtkRenderMaster",argv[0])) {
    ClientData temp = vtkRenderMasterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRenderMasterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRenderMasterCommand));
  }

  if (!strcmp("vtkRenderWindowInteractor",argv[0])) {
    ClientData temp = vtkRenderWindowInteractorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRenderWindowInteractorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRenderWindowInteractorCommand));
  }

  if (!strcmp("vtkRendererCollection",argv[0]))
    {
    ClientData temp = vtkRendererCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRendererCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRendererCollectionCommand));
    }

  if (!strcmp("vtkRendererSource",argv[0]))
    {
    ClientData temp = vtkRendererSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRendererSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRendererSourceCommand));
    }

  if (!strcmp("vtkRibbonFilter",argv[0]))
    {
    ClientData temp = vtkRibbonFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRibbonFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRibbonFilterCommand));
    }

  if (!strcmp("vtkRotationalExtrusionFilter",argv[0]))
    {
    ClientData temp = vtkRotationalExtrusionFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRotationalExtrusionFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRotationalExtrusionFilterCommand));
    }

  if (!strcmp("vtkSTLReader",argv[0]))
    {
    ClientData temp = vtkSTLReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSTLReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSTLReaderCommand));
    }

  if (!strcmp("vtkSTLWriter",argv[0]))
    {
    ClientData temp = vtkSTLWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSTLWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSTLWriterCommand));
    }

  if (!strcmp("vtkSampleFunction",argv[0]))
    {
    ClientData temp = vtkSampleFunctionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSampleFunctionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSampleFunctionCommand));
    }

  if (!strcmp("vtkShepardMethod",argv[0]))
    {
    ClientData temp = vtkShepardMethodNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkShepardMethodCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkShepardMethodCommand));
    }

  if (!strcmp("vtkShortArray",argv[0]))
    {
    ClientData temp = vtkShortArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkShortArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkShortArrayCommand));
    }

  if (!strcmp("vtkUnsignedShortArray",argv[0]))
    {
    ClientData temp = vtkUnsignedShortArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnsignedShortArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnsignedShortArrayCommand));
    }

  if (!strcmp("vtkShortScalars",argv[0]))
    {
    ClientData temp = vtkShortScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkShortScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkShortScalarsCommand));
    }

  if (!strcmp("vtkUnsignedShortScalars",argv[0]))
    {
    ClientData temp = vtkUnsignedShortScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnsignedShortScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnsignedShortScalarsCommand));
    }

  if (!strcmp("vtkShrinkFilter",argv[0]))
    {
    ClientData temp = vtkShrinkFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkShrinkFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkShrinkFilterCommand));
    }

  if (!strcmp("vtkShrinkPolyData",argv[0]))
    {
    ClientData temp = vtkShrinkPolyDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkShrinkPolyDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkShrinkPolyDataCommand));
    }

  if (!strcmp("vtkSliceCubes",argv[0]))
    {
    ClientData temp = vtkSliceCubesNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSliceCubesCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSliceCubesCommand));
    }

  if (!strcmp("vtkSmoothPolyFilter",argv[0]))
    {
    ClientData temp = vtkSmoothPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSmoothPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSmoothPolyFilterCommand));
    }

  if (!strcmp("vtkSource",argv[0]))
    {
    ClientData temp = vtkSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSourceCommand));
    }

  if (!strcmp("vtkSpatialRepFilter",argv[0]))
    {
    ClientData temp = vtkSpatialRepFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSpatialRepFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSpatialRepFilterCommand));
    }

  if (!strcmp("vtkSphere",argv[0]))
    {
    ClientData temp = vtkSphereNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSphereCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSphereCommand));
    }

  if (!strcmp("vtkSphereSource",argv[0]))
    {
    ClientData temp = vtkSphereSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSphereSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSphereSourceCommand));
    }

  if (!strcmp("vtkStack",argv[0]))
    {
    ClientData temp = vtkStackNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStackCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStackCommand));
    }

  if (!strcmp("vtkStreamLine",argv[0]))
    {
    ClientData temp = vtkStreamLineNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStreamLineCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStreamLineCommand));
    }

  if (!strcmp("vtkStreamPoints",argv[0]))
    {
    ClientData temp = vtkStreamPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStreamPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStreamPointsCommand));
    }

  if (!strcmp("vtkStreamer",argv[0]))
    {
    ClientData temp = vtkStreamerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStreamerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStreamerCommand));
    }

  if (!strcmp("vtkStripper",argv[0]))
    {
    ClientData temp = vtkStripperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStripperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStripperCommand));
    }

  if (!strcmp("vtkStructuredData",argv[0]))
    {
    ClientData temp = vtkStructuredDataNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredDataCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredDataCommand));
    }

  if (!strcmp("vtkStructuredGrid",argv[0]))
    {
    ClientData temp = vtkStructuredGridNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridCommand));
    }

  if (!strcmp("vtkStructuredGridFilter",argv[0]))
    {
    ClientData temp = vtkStructuredGridFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridFilterCommand));
    }

  if (!strcmp("vtkStructuredGridGeometryFilter",argv[0]))
    {
    ClientData temp = vtkStructuredGridGeometryFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridGeometryFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridGeometryFilterCommand));
    }

  if (!strcmp("vtkStructuredGridOutlineFilter",argv[0]))
    {
    ClientData temp = vtkStructuredGridOutlineFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridOutlineFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridOutlineFilterCommand));
    }

  if (!strcmp("vtkStructuredGridReader",argv[0]))
    {
    ClientData temp = vtkStructuredGridReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridReaderCommand));
    }

  if (!strcmp("vtkStructuredGridSource",argv[0]))
    {
    ClientData temp = vtkStructuredGridSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridSourceCommand));
    }

  if (!strcmp("vtkStructuredGridToPolyFilter",argv[0]))
    {
    ClientData temp = vtkStructuredGridToPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridToPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridToPolyFilterCommand));
    }

  if (!strcmp("vtkStructuredGridToStructuredGridFilter",argv[0]))
    {
    ClientData temp = vtkStructuredGridToStructuredGridFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridToStructuredGridFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridToStructuredGridFilterCommand));
    }

  if (!strcmp("vtkStructuredGridWriter",argv[0]))
    {
    ClientData temp = vtkStructuredGridWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredGridWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredGridWriterCommand));
    }

  if (!strcmp("vtkStructuredPoints",argv[0]))
    {
    ClientData temp = vtkStructuredPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsCommand));
    }

  if (!strcmp("vtkStructuredPointsFilter",argv[0]))
    {
    ClientData temp = vtkStructuredPointsFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsFilterCommand));
    }

  if (!strcmp("vtkStructuredPointsGeometryFilter",argv[0]))
    {
    ClientData temp = vtkStructuredPointsGeometryFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsGeometryFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsGeometryFilterCommand));
    }

  if (!strcmp("vtkStructuredPointsReader",argv[0]))
    {
    ClientData temp = vtkStructuredPointsReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsReaderCommand));
    }

  if (!strcmp("vtkStructuredPointsSource",argv[0]))
    {
    ClientData temp = vtkStructuredPointsSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsSourceCommand));
    }

  if (!strcmp("vtkStructuredPointsToPolyDataFilter",argv[0]))
    {
    ClientData temp = vtkStructuredPointsToPolyDataFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsToPolyDataFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsToPolyDataFilterCommand));
    }

  if (!strcmp("vtkStructuredPointsToStructuredPointsFilter",argv[0]))
    {
    ClientData temp = vtkStructuredPointsToStructuredPointsFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsToStructuredPointsFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsToStructuredPointsFilterCommand));
    }

  if (!strcmp("vtkStructuredPointsWriter",argv[0]))
    {
    ClientData temp = vtkStructuredPointsWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsWriterCommand));
    }

  if (!strcmp("vtkSweptSurface",argv[0]))
    {
    ClientData temp = vtkSweptSurfaceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSweptSurfaceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSweptSurfaceCommand));
    }

  if (!strcmp("vtkTensorGlyph",argv[0]))
    {
    ClientData temp = vtkTensorGlyphNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTensorGlyphCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTensorGlyphCommand));
    }

  if (!strcmp("vtkTetra",argv[0]))
    {
    ClientData temp = vtkTetraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTetraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTetraCommand));
    }

  if (!strcmp("vtkTextSource",argv[0]))
    {
    ClientData temp = vtkTextSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextSourceCommand));
    }

  if (!strcmp("vtkTexture",argv[0]))
    {
    ClientData temp = vtkTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextureCommand));
    }

  if (!strcmp("vtkTextureMapToBox",argv[0]))
    {
    ClientData temp = vtkTextureMapToBoxNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextureMapToBoxCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextureMapToBoxCommand));
    }

  if (!strcmp("vtkTextureMapToCylinder",argv[0]))
    {
    ClientData temp = vtkTextureMapToCylinderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextureMapToCylinderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextureMapToCylinderCommand));
    }

  if (!strcmp("vtkTextureMapToPlane",argv[0]))
    {
    ClientData temp = vtkTextureMapToPlaneNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextureMapToPlaneCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextureMapToPlaneCommand));
    }

  if (!strcmp("vtkTextureMapToSphere",argv[0]))
    {
    ClientData temp = vtkTextureMapToSphereNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTextureMapToSphereCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTextureMapToSphereCommand));
    }

  if (!strcmp("vtkTexturedSphereSource",argv[0]))
    {
    ClientData temp = vtkTexturedSphereSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTexturedSphereSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTexturedSphereSourceCommand));
    }

  if (!strcmp("vtkThreshold",argv[0]))
    {
    ClientData temp = vtkThresholdNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkThresholdCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkThresholdCommand));
    }

  if (!strcmp("vtkThresholdPoints",argv[0]))
    {
    ClientData temp = vtkThresholdPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkThresholdPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkThresholdPointsCommand));
    }

  if (!strcmp("vtkThresholdTextureCoords",argv[0]))
    {
    ClientData temp = vtkThresholdTextureCoordsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkThresholdTextureCoordsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkThresholdTextureCoordsCommand));
    }

  if (!strcmp("vtkTimeStamp",argv[0]))
    {
    ClientData temp = vtkTimeStampNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTimeStampCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTimeStampCommand));
    }

  if (!strcmp("vtkTransform",argv[0]))
    {
    ClientData temp = vtkTransformNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformCommand));
    }

  if (!strcmp("vtkTransformFilter",argv[0]))
    {
    ClientData temp = vtkTransformFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformFilterCommand));
    }

  if (!strcmp("vtkTransformPolyFilter",argv[0]))
    {
    ClientData temp = vtkTransformPolyFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformPolyFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformPolyFilterCommand));
    }

  if (!strcmp("vtkTransformStructuredPoints",argv[0]))
    {
    ClientData temp = vtkTransformStructuredPointsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformStructuredPointsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformStructuredPointsCommand));
    }

  if (!strcmp("vtkTransformTextureCoords",argv[0]))
    {
    ClientData temp = vtkTransformTextureCoordsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformTextureCoordsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformTextureCoordsCommand));
    }

  if (!strcmp("vtkTriangle",argv[0]))
    {
    ClientData temp = vtkTriangleNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTriangleCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTriangleCommand));
    }

  if (!strcmp("vtkTriangleFilter",argv[0]))
    {
    ClientData temp = vtkTriangleFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTriangleFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTriangleFilterCommand));
    }

  if (!strcmp("vtkTriangleStrip",argv[0]))
    {
    ClientData temp = vtkTriangleStripNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTriangleStripCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTriangleStripCommand));
    }

  if (!strcmp("vtkTubeFilter",argv[0]))
    {
    ClientData temp = vtkTubeFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTubeFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTubeFilterCommand));
    }

  if (!strcmp("vtkUGFacetReader",argv[0]))
    {
    ClientData temp = vtkUGFacetReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUGFacetReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUGFacetReaderCommand));
    }

  if (!strcmp("vtkUnsignedCharArray",argv[0]))
    {
    ClientData temp = vtkUnsignedCharArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnsignedCharArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnsignedCharArrayCommand));
    }

  if (!strcmp("vtkUnsignedCharScalars",argv[0]))
    {
    ClientData temp = vtkUnsignedCharScalarsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnsignedCharScalarsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnsignedCharScalarsCommand));
    }

  if (!strcmp("vtkUnstructuredGrid",argv[0]))
    {
    ClientData temp = vtkUnstructuredGridNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnstructuredGridCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnstructuredGridCommand));
    }

  if (!strcmp("vtkUnstructuredGridFilter",argv[0]))
    {
    ClientData temp = vtkUnstructuredGridFilterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnstructuredGridFilterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnstructuredGridFilterCommand));
    }

  if (!strcmp("vtkUnstructuredGridReader",argv[0]))
    {
    ClientData temp = vtkUnstructuredGridReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnstructuredGridReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnstructuredGridReaderCommand));
    }

  if (!strcmp("vtkUnstructuredGridSource",argv[0]))
    {
    ClientData temp = vtkUnstructuredGridSourceNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnstructuredGridSourceCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnstructuredGridSourceCommand));
    }

  if (!strcmp("vtkUnstructuredGridWriter",argv[0]))
    {
    ClientData temp = vtkUnstructuredGridWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUnstructuredGridWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUnstructuredGridWriterCommand));
    }

  if (!strcmp("vtkUserDefined",argv[0]))
    {
    ClientData temp = vtkUserDefinedNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkUserDefinedCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkUserDefinedCommand));
    }

  if (!strcmp("vtkVectorDot",argv[0]))
    {
    ClientData temp = vtkVectorDotNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVectorDotCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVectorDotCommand));
    }

  if (!strcmp("vtkVectorNorm",argv[0]))
    {
    ClientData temp = vtkVectorNormNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVectorNormCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVectorNormCommand));
    }

  if (!strcmp("vtkVectorText",argv[0]))
    {
    ClientData temp = vtkVectorTextNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVectorTextCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVectorTextCommand));
    }

  if (!strcmp("vtkVectorTopology",argv[0]))
    {
    ClientData temp = vtkVectorTopologyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVectorTopologyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVectorTopologyCommand));
    }

  if (!strcmp("vtkVertex",argv[0]))
    {
    ClientData temp = vtkVertexNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVertexCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVertexCommand));
    }

  if (!strcmp("vtkVoidArray",argv[0]))
    {
    ClientData temp = vtkVoidArrayNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVoidArrayCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVoidArrayCommand));
    }

  if (!strcmp("vtkVolume",argv[0]))
    {
    ClientData temp = vtkVolumeNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVolumeCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVolumeCommand));
    }

  if (!strcmp("vtkVolume16Reader",argv[0]))
    {
    ClientData temp = vtkVolume16ReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVolume16ReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVolume16ReaderCommand));
    }

  if (!strcmp("vtkmrcImageReader",argv[0]))
    {
	fprintf(stderr, "in vtkmrcImageReader");	
    ClientData temp = vtkmrcImageReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkmrcImageReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkmrcImageReaderCommand));
    }

  if (!strcmp("vtkVolumeRenderer",argv[0]))
    {
    ClientData temp = vtkVolumeRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVolumeRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVolumeRendererCommand));
    }

  if (!strcmp("vtkVoxel",argv[0]))
    {
    ClientData temp = vtkVoxelNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVoxelCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVoxelCommand));
    }

  if (!strcmp("vtkVoxelModeller",argv[0]))
    {
    ClientData temp = vtkVoxelModellerNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVoxelModellerCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVoxelModellerCommand));
    }

  if (!strcmp("vtkVoxelReader",argv[0]))
    {
    ClientData temp = vtkVoxelReaderNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVoxelReaderCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVoxelReaderCommand));
    }

  if (!strcmp("vtkVoxelWriter",argv[0]))
    {
    ClientData temp = vtkVoxelWriterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVoxelWriterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVoxelWriterCommand));
    }

  if (!strcmp("vtkVRMLExporter",argv[0]))
    {
    ClientData temp = vtkVRMLExporterNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVRMLExporterCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVRMLExporterCommand));
    }

  if (!strcmp("vtkWarpScalar",argv[0]))
    {
    ClientData temp = vtkWarpScalarNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkWarpScalarCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkWarpScalarCommand));
    }

  if (!strcmp("vtkWarpTo",argv[0]))
    {
    ClientData temp = vtkWarpToNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkWarpToCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkWarpToCommand));
    }

  if (!strcmp("vtkWarpVector",argv[0]))
    {
    ClientData temp = vtkWarpVectorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkWarpVectorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkWarpVectorCommand));
    }

  if (!strcmp("vtkWindowLevelLookupTable",argv[0]))
    {
    ClientData temp = vtkWindowLevelLookupTableNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkWindowLevelLookupTableCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkWindowLevelLookupTableCommand));
    }

  if (!strcmp("vtkXRenderWindowInteractor",argv[0]))
    {
    ClientData temp = vtkXRenderWindowInteractorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXRenderWindowInteractorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXRenderWindowInteractorCommand));
    }

  if (!strcmp("vtkActorCollection",argv[0]))
    {
    ClientData temp = vtkActorCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkActorCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkActorCollectionCommand));
    }

  if (!strcmp("vtkAssemblyPaths",argv[0]))
    {
    ClientData temp = vtkAssemblyPathsNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkAssemblyPathsCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkAssemblyPathsCommand));
    }

  if (!strcmp("vtkRenderWindowCollection",argv[0]))
    {
    ClientData temp = vtkRenderWindowCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkRenderWindowCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkRenderWindowCollectionCommand));
    }

  if (!strcmp("vtkVolumeCollection",argv[0]))
    {
    ClientData temp = vtkVolumeCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkVolumeCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkVolumeCollectionCommand));
    }

  if (!strcmp("vtkLightCollection",argv[0]))
    {
    ClientData temp = vtkLightCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkLightCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkLightCollectionCommand));
    }

  if (!strcmp("vtkTensor",argv[0]))
    {
    ClientData temp = vtkTensorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTensorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTensorCommand));
    }

  if (!strcmp("vtkTransformCollection",argv[0]))
    {
    ClientData temp = vtkTransformCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkTransformCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkTransformCollectionCommand));
    }

  if (!strcmp("vtkPolyDataCollection",argv[0]))
    {
    ClientData temp = vtkPolyDataCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkPolyDataCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkPolyDataCollectionCommand));
    }

  if (!strcmp("vtkDataSetCollection",argv[0]))
    {
    ClientData temp = vtkDataSetCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkDataSetCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkDataSetCollectionCommand));
    }

  if (!strcmp("vtkImplicitFunctionCollection",argv[0]))
    {
    ClientData temp = vtkImplicitFunctionCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkImplicitFunctionCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkImplicitFunctionCollectionCommand));
    }

  if (!strcmp("vtkStructuredPointsCollection",argv[0]))
    {
    ClientData temp = vtkStructuredPointsCollectionNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkStructuredPointsCollectionCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkStructuredPointsCollectionCommand));
    }

#ifdef USE_GLR
  if (!strcmp("vtkGlrActor",argv[0]))
    {
    ClientData temp = vtkGlrActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrActorCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrCamera",argv[0]))
    {
    ClientData temp = vtkGlrCameraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrCameraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrCameraCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrLight",argv[0]))
    {
    ClientData temp = vtkGlrLightNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrLightCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrLightCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrPolyMapper",argv[0]))
    {
    ClientData temp = vtkGlrPolyMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrPolyMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrPolyMapperCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrProperty",argv[0]))
    {
    ClientData temp = vtkGlrPropertyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrPropertyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrPropertyCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrRenderWindow",argv[0]))
    {
    ClientData temp = vtkGlrRenderWindowNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrRenderWindowCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrRenderWindowCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrRenderer",argv[0]))
    {
    ClientData temp = vtkGlrRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrRendererCommand));
    }

#endif
#ifdef USE_GLR
  if (!strcmp("vtkGlrTexture",argv[0]))
    {
    ClientData temp = vtkGlrTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkGlrTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkGlrTextureCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrActor",argv[0]))
    {
    ClientData temp = vtkSbrActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrActorCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrCamera",argv[0]))
    {
    ClientData temp = vtkSbrCameraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrCameraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrCameraCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrLight",argv[0]))
    {
    ClientData temp = vtkSbrLightNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrLightCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrLightCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrPolyMapper",argv[0]))
    {
    ClientData temp = vtkSbrPolyMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrPolyMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrPolyMapperCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrProperty",argv[0]))
    {
    ClientData temp = vtkSbrPropertyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrPropertyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrPropertyCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrRenderWindow",argv[0]))
    {
    ClientData temp = vtkSbrRenderWindowNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrRenderWindowCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrRenderWindowCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrRenderer",argv[0]))
    {
    ClientData temp = vtkSbrRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrRendererCommand));
    }

#endif
#ifdef USE_SBR
  if (!strcmp("vtkSbrTexture",argv[0]))
    {
    ClientData temp = vtkSbrTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkSbrTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkSbrTextureCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrActor",argv[0]))
    {
    ClientData temp = vtkOglrActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrActorCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrCamera",argv[0]))
    {
    ClientData temp = vtkOglrCameraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrCameraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrCameraCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrLight",argv[0]))
    {
    ClientData temp = vtkOglrLightNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrLightCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrLightCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrPolyMapper",argv[0]))
    {
    ClientData temp = vtkOglrPolyMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrPolyMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrPolyMapperCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrProperty",argv[0]))
    {
    ClientData temp = vtkOglrPropertyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrPropertyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrPropertyCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrRenderWindow",argv[0]))
    {
    ClientData temp = vtkOglrRenderWindowNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrRenderWindowCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrRenderWindowCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrRenderer",argv[0]))
    {
    ClientData temp = vtkOglrRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrRendererCommand));
    }

#endif
#ifdef USE_OGLR
  if (!strcmp("vtkOglrTexture",argv[0]))
    {
    ClientData temp = vtkOglrTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkOglrTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkOglrTextureCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrActor",argv[0]))
    {
    ClientData temp = vtkXglrActorNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrActorCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrActorCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrCamera",argv[0]))
    {
    ClientData temp = vtkXglrCameraNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrCameraCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrCameraCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrLight",argv[0]))
    {
    ClientData temp = vtkXglrLightNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrLightCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrLightCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrPolyMapper",argv[0]))
    {
    ClientData temp = vtkXglrPolyMapperNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrPolyMapperCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrPolyMapperCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrProperty",argv[0]))
    {
    ClientData temp = vtkXglrPropertyNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrPropertyCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrPropertyCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrRenderWindow",argv[0]))
    {
    ClientData temp = vtkXglrRenderWindowNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrRenderWindowCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrRenderWindowCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrRenderer",argv[0]))
    {
    ClientData temp = vtkXglrRendererNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrRendererCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrRendererCommand));
    }

#endif
#ifdef USE_XGLR
  if (!strcmp("vtkXglrTexture",argv[0]))
    {
    ClientData temp = vtkXglrTextureNewCommand();

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,temp);
    sprintf(temps,"%p",(void *)temp);
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(argv[1])));
    Tcl_CreateCommand(interp,argv[1],vtkXglrTextureCommand,
                      temp,(Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,argv[1],&is_new);
    Tcl_SetHashValue(entry,(ClientData)(vtkXglrTextureCommand));
    }

#endif
  sprintf(interp->result,"%s",argv[1]);
  return TCL_OK;
}

int VTK_Init(Tcl_Interp *interp)
{
  Tcl_InitHashTable(&vtkInstanceLookup, TCL_STRING_KEYS);
  Tcl_InitHashTable(&vtkPointerLookup, TCL_STRING_KEYS);
  Tcl_InitHashTable(&vtkCommandLookup, TCL_STRING_KEYS);
  Tcl_CreateCommand(interp,"vtkCommand",vtkCommand,
		    (ClientData *)NULL, NULL);

  Tcl_CreateCommand(interp,"vtkAGraymap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAPixmap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAppendFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAppendPolyData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAssembly",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAxes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBYUReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBYUWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBitArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBitScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBitmap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBooleanStructuredPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBooleanTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkBrownianPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkByteSwap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCamera",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCastToConcrete",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCellArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCellList",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCellLocator",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCellPicker",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCleanPolyData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCone",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkConeSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkConnectivityFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkContourFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCubeSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCursor3D",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCutter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCyberReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCylinder",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkCylinderSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDashedStreamLine",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetToDataSetFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetToPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetToStructuredGridFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetToStructuredPointsFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetToUnstructuredGridFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDecimate",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDelaunay2D",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDelaunay3D",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDicer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDiskSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDividingCubes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDoubleArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkEarthSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkEdgeTable",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkEdgePoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkElevationFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkExtractEdges",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkExtractGeometry",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkExtractVectorComponents",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkExtractGrid",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkExtractVOI",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFeatureEdges",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFeatureVertices",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatNormals",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatTCoords",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatTensors",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFloatVectors",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkFollower",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkGaussianSplatter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkGeometryFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkGlyph3D",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkGraymap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkHedgeHog",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkHexahedron",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkHyperStreamline",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkIdList",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkImageDifference",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkImplicitBoolean",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkImplicitModeller",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkImplicitTextureCoords",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkIndent",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkIntArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkIntPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkIntScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLODActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLight",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLine",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLineSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLinearExtrusionFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLinkList",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLogLookupTable",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLookupTable",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMCubesReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMCubesWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMarchingCubes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMarchingSquares",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMaskPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMaskPolyData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMath",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMatrix4x4",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMergeFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkMergePoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkNewVolumeRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkOBBTree",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkObject",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkOBJExporter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkOutlineFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkOutlineSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPLOT3DReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPNMReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPNMWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPicker",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPixel",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPixmap",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPlane",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPlaneSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPlanes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointLoad",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointLocator",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointPicker",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointSetFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointSetToPointSetFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPointSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyLine",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyNormals",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolySource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyToPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyVertex",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolygon",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkProbeFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkProperty",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkQuad",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkQuadric",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRecursiveDividingCubes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRefCount",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRenderMaster",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRenderWindowInteractor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRendererCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRendererSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRibbonFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRotationalExtrusionFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSTLReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSTLWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSampleFunction",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkShepardMethod",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkShortArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnsignedShortArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkShortScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnsignedShortScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkShrinkFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkShrinkPolyData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSliceCubes",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSmoothPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSpatialRepFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSphere",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSphereSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStack",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStreamLine",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStreamPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStreamer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStripper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredData",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGrid",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridGeometryFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridOutlineFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridToPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridToStructuredGridFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredGridWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsGeometryFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsToPolyDataFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsToStructuredPointsFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkSweptSurface",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTensorGlyph",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTetra",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTextSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTextureMapToBox",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTextureMapToCylinder",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTextureMapToPlane",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTextureMapToSphere",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTexturedSphereSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkThreshold",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkThresholdPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkThresholdTextureCoords",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTimeStamp",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransform",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransformFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransformPolyFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransformStructuredPoints",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransformTextureCoords",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTriangle",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTriangleFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTriangleStrip",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTubeFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUGFacetReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnsignedCharArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnsignedCharScalars",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnstructuredGrid",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnstructuredGridFilter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnstructuredGridReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnstructuredGridSource",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUnstructuredGridWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkUserDefined",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVectorDot",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVectorNorm",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVectorText",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVectorTopology",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVertex",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVoidArray",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVolume",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVolume16Reader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkmrcImageReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVolumeRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVoxel",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVoxelModeller",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVoxelReader",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVoxelWriter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVRMLExporter",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkWarpScalar",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkWarpTo",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkWarpVector",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkWindowLevelLookupTable",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkXRenderWindowInteractor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkActorCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkAssemblyPaths",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkRenderWindowCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkVolumeCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkLightCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTensor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkTransformCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkPolyDataCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkDataSetCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkImplicitFunctionCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

  Tcl_CreateCommand(interp,"vtkStructuredPointsCollection",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrCamera",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrLight",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrPolyMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrProperty",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrRenderWindow",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_GLR
  Tcl_CreateCommand(interp,"vtkGlrTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrCamera",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrLight",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrPolyMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrProperty",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrRenderWindow",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_SBR
  Tcl_CreateCommand(interp,"vtkSbrTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrCamera",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrLight",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrPolyMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrProperty",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrRenderWindow",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_OGLR
  Tcl_CreateCommand(interp,"vtkOglrTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrActor",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrCamera",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrLight",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrPolyMapper",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrProperty",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrRenderWindow",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrRenderer",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
#ifdef USE_XGLR
  Tcl_CreateCommand(interp,"vtkXglrTexture",vtkNewInstanceCommand,
		    (ClientData *)NULL,
		    (Tcl_CmdDeleteProc *)NULL);

#endif
  return TCL_OK;
}
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: util.cc,v $
  Language:  C++
  Date:      $Date: 2002/02/01 05:31:06 $
  Version:   $Revision: 1.1.1.1 $

This file is part of the Visualization Toolkit. No part of this file or its
contents may be copied, reproduced or altered in any way without the express
written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994

=========================================================================*/

#include <iostream.h>
#include <stdlib.h>
#include "vtkTclUtil.hh"

int vtkRendererCommand(ClientData cd, Tcl_Interp *interp,
		       int argc, char *argv[]);
int vtkRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
			      int argc, char *argv[]);

extern Tcl_HashTable vtkInstanceLookup;
extern Tcl_HashTable vtkPointerLookup;
extern Tcl_HashTable vtkCommandLookup;

static int num = 0;
static int vtkTclDebugOn = 0;

// we do no error checking in this.  We assume that if we were called
// then tcl must have been able to find the command function and object
int vtkTclDeleteObjectFromHash(ClientData cd)
{
  char temps[80];
  Tcl_HashEntry *entry;
  char *temp;
  int (*command)(ClientData, Tcl_Interp *,int, char *[]);

  // lookup the objects name
  sprintf(temps,"%p",(void *)cd);
  entry = Tcl_FindHashEntry(&vtkPointerLookup,temps); 
  temp = (char *)(Tcl_GetHashValue(entry));

  // now delete the three hash entries
  entry = Tcl_FindHashEntry(&vtkCommandLookup,temp);
  command = 
    (int (*)(ClientData,Tcl_Interp *,int,char *[]))Tcl_GetHashValue(entry);
  Tcl_DeleteHashEntry(entry);
  entry = Tcl_FindHashEntry(&vtkPointerLookup,temps); 
  Tcl_DeleteHashEntry(entry);
  entry = Tcl_FindHashEntry(&vtkInstanceLookup,temp);
  Tcl_DeleteHashEntry(entry);

  if (vtkTclDebugOn)
    {
    cerr << "vtkTcl Attempting to free object named " << temp << "\n";
    }
  // if it isn't a temp object (i.e. we created it) then delete it 
  if (strncmp(temp,"vtkTemp",7))
    {
    // finally free the name we got from the hash table
    // it was created using strdup
    free (temp);
    return 1;
    }
  // finally free the name we got from the hash table
  // it was created using strdup
  free (temp);
  return 0;
}

// we do no error checking in this.  We assume that if we were called
// then tcl must have been able to find the command function and object
void vtkTclGenericDeleteObject(ClientData cd)
{
  char temps[80];
  Tcl_HashEntry *entry;
  int (*command)(ClientData, Tcl_Interp *,int, char *[]);
  char *args[2];
  char *temp;
  Tcl_Interp *i;
  
  /* set up the args */
  args[1] = "Delete";

  // lookup the objects name
  sprintf(temps,"%p",(void *)cd);
  entry = Tcl_FindHashEntry(&vtkPointerLookup,temps); 
  temp = (char *)(Tcl_GetHashValue(entry));
  args[0] = temp;
  
  // get the command function and invoke the delete operation
  entry = Tcl_FindHashEntry(&vtkCommandLookup,temp);
  command = (int (*)(ClientData,Tcl_Interp *,int,char *[]))Tcl_GetHashValue(entry);

  i = Tcl_CreateInterp();
  command(cd,i,2,args);
  Tcl_DeleteInterp(i);
}

int vtkCommand(ClientData cd, Tcl_Interp *interp, int argc, char *argv[])
{
  Tcl_HashEntry *entry;
  Tcl_HashSearch search;
  
  cd = 0; // shut up the compiler

  if (argc < 2) return TCL_OK;
  
  if (!strcmp(argv[1],"DeleteAllObjects"))
    {
    for (entry = Tcl_FirstHashEntry(&vtkPointerLookup,&search); 
	 entry != NULL;
	 entry = Tcl_NextHashEntry(&search))
      {
      Tcl_DeleteCommand(interp,(char *)Tcl_GetHashValue(entry));
      }
    return TCL_OK;
    }
  if (!strcmp(argv[1],"DebugOn"))
    {
    vtkTclDebugOn = 1;
    return TCL_OK;
    }
  if (!strcmp(argv[1],"DebugOff"))
    {
    vtkTclDebugOn = 0;
    return TCL_OK;
    }

  return TCL_OK;
}

void vtkTclGetObjectFromPointer(Tcl_Interp *interp,void *temp,
			  int command(ClientData, Tcl_Interp *,int, char *[]))
{
  int is_new;
  char temps[80];
  char name[80];
  Tcl_HashEntry *entry;

  /* return a pointer to a vtk Object */
  /* first we must look up the pointer to see if it already exists */
  sprintf(temps,"%p",temp);
  if ((entry = Tcl_FindHashEntry(&vtkPointerLookup,temps))) 
    {
    sprintf(interp->result,"%s",(char *)(Tcl_GetHashValue(entry)));
    }
  /* we must create a new name */
  else
    {
    sprintf(name,"vtkTemp%i",num);
    num++;

    entry = Tcl_CreateHashEntry(&vtkInstanceLookup,name,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(temp));
    entry = Tcl_CreateHashEntry(&vtkPointerLookup,temps,&is_new);
    Tcl_SetHashValue(entry,(ClientData)(strdup(name)));
    Tcl_CreateCommand(interp,name,command,
                      (ClientData)(temp),
                      (Tcl_CmdDeleteProc *)vtkTclGenericDeleteObject);
    entry = Tcl_CreateHashEntry(&vtkCommandLookup,name,&is_new);
    Tcl_SetHashValue(entry,(ClientData)command);
    sprintf(interp->result,"%s",name); 
    }
}
      
void *vtkTclGetPointerFromObject(char *name,char *result_type)
{
  Tcl_HashEntry *entry;
  ClientData temp;
  int (*command)(ClientData, Tcl_Interp *,int, char *[]);
  char *args[3];


  /* set up the args */
  args[0] = "DoTypecasting";
  args[1] = result_type;
  args[2] = NULL;
  
  // object names cannot start with a number
  if ((name[0] >= '0')&&(name[0] <= '9'))
    {
    return NULL;
    }
  if ((entry = Tcl_FindHashEntry(&vtkInstanceLookup,name)))
    {
    temp = (ClientData)Tcl_GetHashValue(entry);
    }
  else
    {
    fprintf(stderr,"vtk bad argument, could not find object named %s\n", name);
    return NULL;
    }
  
  /* now handle the typecasting, get the command proc */
  if ((entry = Tcl_FindHashEntry(&vtkCommandLookup,name)))
    {
    command = (int (*)(ClientData,Tcl_Interp *,int,char *[]))Tcl_GetHashValue(entry);
    }
  else
    {
    fprintf(stderr,"vtk bad argument, could not find command process for %s.\n", name);
    return NULL;
    }

  if (command(temp,(Tcl_Interp *)NULL,3,args) == TCL_OK)
    {
    return (void *)(args[2]);
    }
  else
    {
    fprintf(stderr,"vtk bad argument, type conversion failed for %s.\n", name);
    return NULL;
    }

}

void vtkTclVoidFunc(void *arg)
{
  vtkTclVoidFuncArg *arg2;

  arg2 = (vtkTclVoidFuncArg *)arg;

  Tcl_GlobalEval(arg2->interp, arg2->command);
}

void vtkTclVoidFuncArgDelete(void *arg)
{
  vtkTclVoidFuncArg *arg2;

  arg2 = (vtkTclVoidFuncArg *)arg;
  
  // free the string and then structure
  delete [] arg2->command;
  delete arg2;
}
/*=========================================================================

  Program:   Visualization Library
  Module:    XInter.cc
  Language:  C++
  Date:      02/20/95
  Version:   1.10

This file is part of the Visualization Library. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "vtkXRenderWindowInteractor.hh"
#include "vtkXRenderWindow.hh"
#include "vtkActor.hh"
#include <X11/Shell.h>
#include <math.h>
#include "tk.h"

// steal the first two elements of the TkMainInfo stuct
// we don't care about the rest of the elements.
typedef struct TkMainInfo {
  int refCount;
  struct TkWindow *winPtr;
};

extern TkMainInfo *tkMainWindowList;

// returns 1 if done
static int vtkTclEventProc(XtPointer clientData,XEvent *event)
{
  Boolean ctd;
  vtkXRenderWindow *rw;
      
  rw = (vtkXRenderWindow *)
    (((vtkXRenderWindowInteractor *)clientData)->GetRenderWindow());
  
  if (rw->GetWindowId() == ((XAnyEvent *)event)->window)
    {
    vtkXRenderWindowInteractorCallback((Widget)NULL,clientData, event, &ctd);
    ctd = 0;
    }
  else
    {
    ctd = 1;
    }

  return !ctd;
}

static void vtkXTclTimerProc(ClientData clientData)
{
  XtIntervalId id;
  vtkXRenderWindowInteractorTimer((XtPointer)clientData,&id);
}

// states
#define VTKXI_START  0
#define VTKXI_ROTATE 1
#define VTKXI_ZOOM   2
#define VTKXI_PAN    3

// Description:
// Construct object so that light follows camera motion.
vtkXRenderWindowInteractor::vtkXRenderWindowInteractor()
{
  this->State = VTKXI_START;
  this->App = 0;
  this->top = 0;
  this->WaitingForMarker = 0;
}

vtkXRenderWindowInteractor::~vtkXRenderWindowInteractor()
{
  if (this->Initialized)
    {
    Tk_DeleteGenericHandler((Tk_GenericProc *)vtkTclEventProc,
			    (ClientData)this);
    }
}

void  vtkXRenderWindowInteractor::SetWidget(Widget foo)
{
  this->top = foo;
} 

void  vtkXRenderWindowInteractor::Start()
{
  Tk_MainLoop();
}

// Description:
// Initializes the event handlers
void vtkXRenderWindowInteractor::Initialize(XtAppContext app)
{
  this->App = app;

  this->Initialize();
}

// Description:
// Begin processing keyboard strokes.
void vtkXRenderWindowInteractor::Initialize()
{
  vtkXRenderWindow *ren;
  int depth;
  Colormap cmap;
  Visual  *vis;
  int *size;
  int *position;

  // make sure we have a RenderWindow and camera
  if ( ! this->RenderWindow)
    {
    vtkErrorMacro(<<"No renderer defined!");
    return;
    }

  this->Initialized = 1;
  ren = (vtkXRenderWindow *)(this->RenderWindow);

  // use the same display as tcl/tk
  ren->SetDisplayId(Tk_Display(tkMainWindowList->winPtr));
  this->DisplayId = ren->GetDisplayId();
  
  // get the info we need from the RenderingWindow
  depth   = ren->GetDesiredDepth();
  cmap    = ren->GetDesiredColormap();
  vis     = ren->GetDesiredVisual();
  size    = ren->GetSize();
  position= ren->GetPosition();
  
  size = ren->GetSize();
  ren->Render();
  this->WindowId = ren->GetWindowId();
  size = ren->GetSize();

  this->Size[0] = size[0];
  this->Size[1] = size[1];

  fprintf(stderr, "%d %d\n", this->DisplayId, this->WindowId);
  XSelectInput(this->DisplayId,this->WindowId,
	       KeyPressMask | ButtonPressMask | ExposureMask |
		    StructureNotifyMask | ButtonReleaseMask);

  // add in tcl init stuff
  Tk_CreateGenericHandler((Tk_GenericProc *)vtkTclEventProc,(ClientData)this);
}

void vtkXRenderWindowInteractor::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkRenderWindowInteractor::PrintSelf(os,indent);
}


void  vtkXRenderWindowInteractor::UpdateSize(int x,int y)
{
  // if the size changed send this on to the RenderWindow
  if ((x != this->Size[0])||(y != this->Size[1]))
    {
    this->Size[0] = x;
    this->Size[1] = y;
    this->RenderWindow->SetSize(x,y);
    }

}
 
void  vtkXRenderWindowInteractor::StartRotate()
{
  if (this->State != VTKXI_START) return;
  this->State = VTKXI_ROTATE;

  this->RenderWindow->SetDesiredUpdateRate(this->DesiredUpdateRate);
  Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)this);
}
void  vtkXRenderWindowInteractor::EndRotate()
{
  if (this->State != VTKXI_ROTATE) return;
  this->State = VTKXI_START;
  this->RenderWindow->SetDesiredUpdateRate(this->StillUpdateRate);
  this->RenderWindow->Render();
}

void  vtkXRenderWindowInteractor::StartZoom()
{
  if (this->State != VTKXI_START) return;
  this->State = VTKXI_ZOOM;
  this->RenderWindow->SetDesiredUpdateRate(this->DesiredUpdateRate);
  Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)this);
}
void  vtkXRenderWindowInteractor::EndZoom()
{
  if (this->State != VTKXI_ZOOM) return;
  this->State = VTKXI_START;
  this->RenderWindow->SetDesiredUpdateRate(this->StillUpdateRate);
  this->RenderWindow->Render();
}

void  vtkXRenderWindowInteractor::StartPan()
{
  float *FocalPoint;
  float *Result;

  if (this->State != VTKXI_START) return;

  this->State = VTKXI_PAN;

  // calculate the focal depth since we'll be using it a lot
  FocalPoint = this->CurrentCamera->GetFocalPoint();
      
  this->CurrentRenderer->SetWorldPoint(FocalPoint[0],FocalPoint[1],
				       FocalPoint[2],1.0);
  this->CurrentRenderer->WorldToDisplay();
  Result = this->CurrentRenderer->GetDisplayPoint();
  this->FocalDepth = Result[2];

  this->RenderWindow->SetDesiredUpdateRate(this->DesiredUpdateRate);
  Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)this);
}
void  vtkXRenderWindowInteractor::EndPan()
{
  if (this->State != VTKXI_PAN) return;
  this->State = VTKXI_START;
  this->RenderWindow->SetDesiredUpdateRate(this->StillUpdateRate);
  this->RenderWindow->Render();
}

void vtkXRenderWindowInteractorCallback(Widget vtkNotUsed(w),
					XtPointer client_data, 
					XEvent *event, 
					Boolean *vtkNotUsed(ctd))
{
  vtkXRenderWindowInteractor *me;
  XEvent marker;
  
  me = (vtkXRenderWindowInteractor *)client_data;

  switch (event->type) 
    {
    case ClientMessage :
      me->WaitingForMarker = 0;
      break;
  
    case Expose : 
      if (!me->WaitingForMarker)
	{
	// put in a marker
	marker.type = ClientMessage;
	marker.xclient.display = me->DisplayId;
	marker.xclient.window = me->WindowId;
	marker.xclient.format = 32;
	XSendEvent(me->DisplayId, me->WindowId,
		   (Bool) 0, (long) 0, &marker);
	XSync(me->DisplayId,False);
	me->WaitingForMarker = 1;
	me->GetRenderWindow()->Render();
	}
      break;
      
    case ConfigureNotify : 
      {
      XEvent result;
      while (XCheckTypedWindowEvent(me->DisplayId, me->WindowId,
				    ConfigureNotify, &result))
	{
	// just getting the last configure event
	event = &result;
	}
      if ((((XConfigureEvent *)event)->width != me->Size[0]) ||
	  (((XConfigureEvent *)event)->height != me->Size[1]))
	{
	me->UpdateSize(((XConfigureEvent *)event)->width,
		       ((XConfigureEvent *)event)->height); 
	// while we are at it clear out any expose events
	// put in a marker
	marker.type = ClientMessage;
	marker.xclient.display = me->DisplayId;
	marker.xclient.window = me->WindowId;
	marker.xclient.format = 32;
	XSendEvent(me->DisplayId, me->WindowId,
		   (Bool) 0, (long) 0, &marker);
	XSync(me->DisplayId,False);
	me->WaitingForMarker = 1;
	me->GetRenderWindow()->Render(); 
	}
      }
      break;

    case ButtonPress : 
      {
      switch (((XButtonEvent *)event)->button)
	{
	case Button1 : 
          me->FindPokedCamera(((XButtonEvent*)event)->x,
			      me->Size[1] - ((XButtonEvent*)event)->y);
	  me->StartRotate(); 
	  break;
	case Button2 : 
          me->FindPokedCamera(((XButtonEvent*)event)->x,
			      me->Size[1] - ((XButtonEvent*)event)->y);
	  me->StartPan(); 
	  break;
	case Button3 : 
          me->FindPokedCamera(((XButtonEvent*)event)->x,
			      me->Size[1] - ((XButtonEvent*)event)->y);
	  me->StartZoom(); 
	  break;
	}
      }
      break;

    case ButtonRelease : 
      {
      switch (((XButtonEvent *)event)->button)
	{
	case Button1 : me->EndRotate(); break;
	case Button2 : me->EndPan(); break;
	case Button3 : me->EndZoom(); break;
	}
      }
      break;

    case KeyPress :
      {
      KeySym ks;
      static char buffer[20];

      XLookupString((XKeyEvent *)event,buffer,20,&ks,NULL);
      switch (ks)
	{
	case XK_e : exit(1); break;
	case XK_u :
	  if (me->UserMethod) (*me->UserMethod)(me->UserMethodArg);
	  break;
	case XK_r : //reset
	  {
          me->FindPokedRenderer(((XKeyEvent*)event)->x,
			        me->Size[1] - ((XKeyEvent*)event)->y);
	  me->CurrentRenderer->ResetCamera();
	  me->RenderWindow->Render();
          }
	  break;

	case XK_w : //change all actors to wireframe
	  {
	  vtkActorCollection *ac;
	  vtkActor *anActor, *aPart;
	  
          me->FindPokedRenderer(((XKeyEvent*)event)->x,
				me->Size[1] - ((XKeyEvent*)event)->y);
	  ac = me->CurrentRenderer->GetActors();
	  for (ac->InitTraversal(); (anActor = ac->GetNextItem()); )
	    {
            for (anActor->InitPartTraversal();(aPart=anActor->GetNextPart());)
              {
              aPart->GetProperty()->SetWireframe();
              }
	    }
	  
	  me->RenderWindow->Render();
	  }
	  break;

	case XK_s : //change all actors to "surface" or solid
	  {
	  vtkActorCollection *ac;
	  vtkActor *anActor, *aPart;
	  
          me->FindPokedRenderer(((XKeyEvent*)event)->x,
			        me->Size[1] - ((XKeyEvent*)event)->y);
	  ac = me->CurrentRenderer->GetActors();
	  for (ac->InitTraversal(); (anActor = ac->GetNextItem()); )
	    {
            for (anActor->InitPartTraversal();(aPart=anActor->GetNextPart()); )
              {
              aPart->GetProperty()->SetSurface();
              }
	    }
	  
	  me->RenderWindow->Render();
          }
	  break;

	case XK_3 : //3d stereo
	  {
	  // prepare the new window
	  if (me->RenderWindow->GetStereoRender())
	    {
	    if (me->RenderWindow->GetRemapWindow())
	      {
	      me->SetupNewWindow(1);
	      }
	    me->RenderWindow->StereoRenderOff();
	    }
	  else
	    {
	    memcpy(me->PositionBeforeStereo,me->RenderWindow->GetPosition(),
		   sizeof(int)*2);
	    if (me->RenderWindow->GetRemapWindow())
	      {
	      me->SetupNewWindow(1);
	      }
	    me->RenderWindow->StereoRenderOn();
	    }
	  me->RenderWindow->Render();
	  if (me->RenderWindow->GetRemapWindow())
	    {
	    me->FinishSettingUpNewWindow();
	    }
          }
	  break;

	case XK_p : //pick actors
	  {
          me->FindPokedRenderer(((XKeyEvent*)event)->x,
			        me->Size[1] - ((XKeyEvent*)event)->y);
          // Execute start method, if any

          if ( me->StartPickMethod ) 
            (*me->StartPickMethod)(me->StartPickMethodArg);
          me->Picker->Pick(((XButtonEvent*)event)->x,
                             me->Size[1] - ((XButtonEvent*)event)->y, 0.0,
                             me->CurrentRenderer);
          me->HighlightActor(me->Picker->GetAssembly());
          if ( me->EndPickMethod ) 
            (*me->EndPickMethod)(me->EndPickMethodArg);
          }
	  break;
        }
      }
      break;
    }
}

void vtkXRenderWindowInteractorTimer(XtPointer client_data,
				     XtIntervalId *vtkNotUsed(id))
{
  vtkXRenderWindowInteractor *me;
  Window root,child;
  int root_x,root_y;
  int x,y;
  float xf,yf;
  unsigned int keys;

  me = (vtkXRenderWindowInteractor *)client_data;

  switch (me->State)
    {
    case VTKXI_ROTATE :
      // get the pointer position
      XQueryPointer(me->DisplayId,me->WindowId,
		    &root,&child,&root_x,&root_y,&x,&y,&keys);
      xf = (x - me->Center[0]) * me->DeltaAzimuth;
      yf = ((me->Size[1] - y) - me->Center[1]) * me->DeltaElevation;
      me->CurrentCamera->Azimuth(xf);
      me->CurrentCamera->Elevation(yf);
      me->CurrentCamera->OrthogonalizeViewUp();
      if (me->LightFollowCamera)
	{
	/* get the first light */
	me->CurrentLight->SetPosition(me->CurrentCamera->GetPosition());
	me->CurrentLight->SetFocalPoint(me->CurrentCamera->GetFocalPoint());
	}
      me->RenderWindow->Render();
      Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)client_data);
      break;
    case VTKXI_PAN :
      {
      float  FPoint[3];
      float *PPoint;
      float  APoint[3];
      float  RPoint[4];

      // get the current focal point and position
      memcpy(FPoint,me->CurrentCamera->GetFocalPoint(),sizeof(float)*3);
      PPoint = me->CurrentCamera->GetPosition();

      // get the pointer position
      XQueryPointer(me->DisplayId,me->WindowId,
		    &root,&child,&root_x,&root_y,&x,&y,&keys);

      APoint[0] = x;
      APoint[1] = me->Size[1] - y;
      APoint[2] = me->FocalDepth;
      me->CurrentRenderer->SetDisplayPoint(APoint);
      me->CurrentRenderer->DisplayToWorld();
      memcpy(RPoint,me->CurrentRenderer->GetWorldPoint(),sizeof(float)*4);
      if (RPoint[3])
	{
	RPoint[0] = RPoint[0]/RPoint[3];
	RPoint[1] = RPoint[1]/RPoint[3];
	RPoint[2] = RPoint[2]/RPoint[3];
	}

      /*
       * Compute a translation vector, moving everything 1/10 
       * the distance to the cursor. (Arbitrary scale factor)
       */
      me->CurrentCamera->SetFocalPoint(
	(FPoint[0]-RPoint[0])/10.0 + FPoint[0],
	(FPoint[1]-RPoint[1])/10.0 + FPoint[1],
	(FPoint[2]-RPoint[2])/10.0 + FPoint[2]);
      me->CurrentCamera->SetPosition(
	(FPoint[0]-RPoint[0])/10.0 + PPoint[0],
	(FPoint[1]-RPoint[1])/10.0 + PPoint[1],
	(FPoint[2]-RPoint[2])/10.0 + PPoint[2]);
      
      me->RenderWindow->Render();
      Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)client_data);
      }
      break;
    case VTKXI_ZOOM :
      {
      float zoomFactor;
      float *clippingRange;

      // get the pointer position
      XQueryPointer(me->DisplayId,me->WindowId,
		    &root,&child,&root_x,&root_y,&x,&y,&keys);
      yf = ((me->Size[1] - y) - me->Center[1])/(float)me->Center[1];
      zoomFactor = pow(1.1,yf);
      if (me->CurrentCamera->GetParallelProjection())
	{
	me->CurrentCamera->
	  SetParallelScale(me->CurrentCamera->GetParallelScale()/zoomFactor);
	}
      else
	{
	clippingRange = me->CurrentCamera->GetClippingRange();
	me->CurrentCamera->SetClippingRange(clippingRange[0]/zoomFactor,
					    clippingRange[1]/zoomFactor);
	me->CurrentCamera->Dolly(zoomFactor);
	}
      me->RenderWindow->Render();
      Tk_CreateTimerHandler(10,vtkXTclTimerProc,(ClientData)client_data);
      }
      break;
    }
}  


// Description:
// Setup a new window before a WindowRemap
void vtkXRenderWindowInteractor::SetupNewWindow(int Stereo)
{
  vtkXRenderWindow *ren;
  int depth;
  Colormap cmap;
  Visual  *vis;
  int *size;
  int *position;
  int zero_pos[2];
  
  // get the info we need from the RenderingWindow
  ren = (vtkXRenderWindow *)(this->RenderWindow);
  this->DisplayId = ren->GetDisplayId();
  depth   = ren->GetDesiredDepth();
  cmap    = ren->GetDesiredColormap();
  vis     = ren->GetDesiredVisual();
  size    = ren->GetSize();
  position= ren->GetPosition();

  if (Stereo)
    {
    if (this->RenderWindow->GetStereoRender())
      {
      position = this->PositionBeforeStereo;
      }
    else
      {
      zero_pos[0] = 0;
      zero_pos[1] = 0;
      position = zero_pos;
      }
    }
}

// Description:
// Finish setting up a new window after the WindowRemap.
void vtkXRenderWindowInteractor::FinishSettingUpNewWindow()
{
  int *size;

  // free the previous widget
  XSync(this->DisplayId,False);
  this->WindowId = ((vtkXRenderWindow *)(this->RenderWindow))->GetWindowId();
  XSync(this->DisplayId,False);

  XSelectInput(this->DisplayId,this->WindowId,
		    KeyPressMask | ButtonPressMask | ExposureMask |
		    StructureNotifyMask | ButtonReleaseMask);

  size = this->RenderWindow->GetSize();
  this->Size[0] = size[0];
  this->Size[1] = size[1];
}

