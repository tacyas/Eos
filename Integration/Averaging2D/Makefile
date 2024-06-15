ModelData=test/121p.pdb
StaticData=test/121p.mrc
DELTA=2.5
SIZE=80
N=`echo "" | awk -v D=$(DELTA) -v S=$(SIZE) 'BEGIN { print int(S/D/2.0)*2  }' `
Start=`echo "" | awk -v D=$(DELTA) -v S=$(SIZE) 'BEGIN { print -1*int(S/2.0)  }' `
Sigma=2.0


help::


init: init-static

init-static:
	pdbMove -i $(ModelData) -o $(ModelData).move -GCtoOrigin
	pdb2mrc2d -i $(ModelData).move -o $(StaticData) -d $(DELTA) $(DELTA) -n $(N) $(N) -s $(Start) $(Start)  -sig $(Sigma) 
