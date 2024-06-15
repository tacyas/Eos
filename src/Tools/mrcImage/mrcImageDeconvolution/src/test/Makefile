include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/1vomTrans.conv2d -k data/kernel.nor2d -o data/1vomTrans.deconv2d -O data/1vomTrans.deconv2d.param -m 3 -Floating -r 7  
	../$(OSTYPE)/$(OBJECTNAME) -i data/1vomTrans.conv2d -k data/kernel.nor2d -o data/1vomTrans.deconv2d.iter -O data/1vomTrans.deconv2d.iter.param -maxIter 30 -m 3 -r 7 -Floating
	@echo "----- Calc check -----"		

initial::
	time pdb2mrc2d -i data/1vomTrans.pdb -o data/1vomTrans.mrc2d -d 2.0 2.0 -s -128 -128 -n 128 128 -sig 1 -w 1 
	time pdb2mrc   -i data/1vomTrans.pdb -o data/1vomTrans.mrc3d -dx 2.0 -dy 2.0 -dz 2.0 -Sx -80 -Sy -80 -Sz -80 -nx 80 -ny 80 -nz 80 -sig 1 -w 1 
	time mrcImageGaussSphere -o data/kernel.mrc2d -W 32 -H 32 -S 1  -weight 1 -sigmax 3 -sigmay 6 -sigmaz 10 -size 2
	time mrcImageAsProbability -i data/kernel.mrc2d -o data/kernel.nor2d
	time mrcImageGaussSphere -o data/kernel.mrc3d -W 32 -H 32 -S 32 -weight 1 -sigmax 3 -sigmay 6 -sigmaz 10 -size 2
	time mrcImageAsProbability -i data/kernel.mrc3d -o data/kernel.nor3d
	time mrcImageConvolution -i data/1vomTrans.mrc2d -o data/1vomTrans.conv2d -ikm data/kernel.nor2d 
	time mrcImageConvolution -i data/1vomTrans.mrc3d -o data/1vomTrans.conv3d -ikm data/kernel.nor3d 

clean:
