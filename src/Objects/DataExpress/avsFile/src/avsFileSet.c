/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% avsFileSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : avsFileSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%avsFileSet ver%I%; Date:%D% %Z%";

#include "Memory.h"
#include "../inc/avsFile.h"

void
avsFileUCDNodeSet(avsFileUCD* avs, 
				  avsFileParaTypeInteger NodeID,
				  avsFileParaTypeReal x, 
				  avsFileParaTypeReal y, 
				  avsFileParaTypeReal z)
{
	avs->Node[NodeID].ID = NodeID;
	avs->Node[NodeID].x = x;
	avs->Node[NodeID].y = y;
	avs->Node[NodeID].z = z;
}

void
avsFileUCDNodeDataSet(avsFileUCD* avs, 
					  avsFileParaTypeInteger NodeID, 
					  avsFileParaTypeInteger indexComponent,
					  avsFileParaTypeInteger indexElement, 
					  double data)
{
	avs->Node[NodeID].Component[indexComponent].data[indexElement] = data;
}

void
avsFileUCDLineTypeCellSet(avsFileUCD* avs, 
				  avsFileParaTypeInteger CellID,
				  avsFileParaTypeInteger MaterialID,
				  avsFileUCDNode* NodeID0,
				  avsFileUCDNode* NodeID1)
{
	avs->Cell[CellID].ID = CellID;
	avs->Cell[CellID].MaterialID =MaterialID;
	avs->Cell[CellID].Type = avsFileUCDCellTypeLine;
	avs->Cell[CellID].Node = (avsFileUCDNode**)memoryAllocate(sizeof(avsFileUCDNode)*2,
				"in avsFileUCDLIneTypeCellSet");
	avs->Cell[CellID].Node[0] = NodeID0;
	avs->Cell[CellID].Node[1] = NodeID1;
}

void
avsFileUCDCellDataSet(avsFileUCD* avs, 
					  avsFileParaTypeInteger CellID, 
					  avsFileParaTypeInteger indexComponent,
					  avsFileParaTypeInteger indexElement, 
					  double data)
{
	avs->Cell[CellID].Component[indexComponent].data[indexElement] = data;
}
