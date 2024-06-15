#
# Makefile for 2D Clustering
#


#
# Preparetion 
#    xxxx.roi
#    Makefile.config
#

include Makefile.config

.SUFFIXES: .roi .preshrink .pad .padlst .log .logIn
.SUFFIXES: .logps 
.SUFFIXES: .padsortlst .clstlst .clstref .fitlst .clstavg .normfitlst .normclstavg .norm .prop .subprop .subproplst .subpropmon .fit .fitCent .clstavgCent .normclstavgpad 

#
Menu::
	@echo "------------ How to use this Makefile -------------------"
	@echo "make Init"
	@echo "make ALLROIS"
	@echo "make Pad"
	@echo "make Log"
	@echo "If make Log stopped in mid-flow, you can recalculate cluster in the middle by make ReLog"
	@echo "make LogPS"
	@echo "Refinement Start"
	@echo "You must create xxxx.clstlst and xxxx.clstref, judging from ClusterTree:logps/padsortmon/avgsortmon."
	@echo "xxxx.clstlst"
	@echo "xxxx.fitlst"
	@echo "xxxx.clstavg"
	@echo "If you want to repeat refinement, "
	@echo "xxxx.clstref"
	@echo "Refinement End"
#

Init::
	mkdir Temp
	touch ALLROIS
	touch NOSUFFIXLST
#
#

-include ALLROIS
-include NOSUFFIXLST

# xxxx.roi list 
ALLROIS::
	echo "ALLROIS=\\" > ALLROIS 
	ls -1 *.roi | sed s/roi/roi\\\\/ >> ALLROIS
	echo "" >> ALLROIS

# xxxx.padlst
Pad: $(ALLROIS:.roi=.pad)
	rm -f $(CLUSTER).padlst
	make $(CLUSTER).padlst	

$(CLUSTER).padlst:
	ls -1 *.pad > $(CLUSTER).padlst

.roi.pad:
	mrcImagePad -i $*.roi -o $*.prelow -W $(PADWIDTH) -H $(PADHEIGHT) -m $(PADMODE) 
	mrcImageLowPassFilter -i $*.prelow -o $*.preshrink -m $(LowPassMode) -hvp $(LowPassResolution) 
	mrcImageShrink -i $*.preshrink -o $*.pad -S $(SHRINK)

CleanPad:
	rm *.pad
	rm $(CLUSTER).padlst

# Clustering 

Log::
	@if [ -f Log ]; then \
		echo "If you really want to classify the images, make CleanLog; make Log"; \
	else \
		mrcImageClusterAnalysis -I $(CLUSTER).padlst -O \
			-AR $(ClusterRotationRangePartitionNumber) -ARange $(ClusterRotationRangeMin) $(ClusterRotationRangeMax) \
			-ARiter $(ClusterRotationIterationNumber) -ARMethod $(ClusterRotationCorrelationMode) \
			-M $(ClusterCorrelationMode) -Log $(CLUSTER).log -m $(ClusterMode) $(RELOG) ; \
		touch Log ; \
	fi

CleanLog::
	rm Log

ReLog::
	mv all.log all.logIn
	make RELOG="-LogIn $(CLUSTER).logIn" Log


LogPS::
	clusterShow -i $(CLUSTER).log -PS $(CLUSTER).logps -Last 1 \
		-S $(TreeScaleX) $(TreeScaleY) -P $(TreeRootPositionX) $(TreeRootPositionY) -Log -Scaling -Offset $(TreeOffset) \
		-I $(CLUSTER).padlst -OL $(CLUSTER).padsortlst -AL $(CLUSTER).avgsortlst 0 avg -OT $(CLUSTER).treeinfo
	mrcImageMontageCreate -i $(CLUSTER).padsortlst -o $(CLUSTER).padsortmon 
	mrcImageMontageCreate -i $(CLUSTER).avgsortlst -o $(CLUSTER).avgsortmon 
	touch LogPS

#
# Refinement
#

.clstlst.fitlst:
	if [ ! -f $*.refinement ] ; \
	then \
		echo "Count: 0" > $*.refinement ; \
	else \
		echo "##################################" >> $*.refinement; \
	fi
	#
	FILES=`awk '{print $$1}' $*.clstlst`; \
	rm -rf $*.fitlst ; \
	for i in $$FILES ; \
	do \
		mrcImageAutoRotationCorrelation -i $$i -r $*.clstref -o $$i.param -O $$i.paramasc -cor $$i.corinfo -fit $$i.fit -range -1 1.5 -n 5 -Method 0 -m 19 -Iter 4; \
		echo "$$i.fit" >> $*.fitlst ; \
		awk '/Cor/ {printf("%15.6f %10.2f %10.2f %10.2f %s\n", $$17,$$10,$$11,$$8,$$15)}' $$i.paramasc >> $*.refinement ; \
	done

.fitlst.clstavg:
	mrcImageSN -i $*.fitlst -A $*.clstavg

.clstavg.clstref:
	COUNT=`awk '/Count:/ {print $$2} ' $*.refinement | tail -n 1`	; \
	mv $*.clstref $*.clstref.$$(printf "%04d" $$COUNT); \
	cp $*.clstavg $*.clstref ; \
	mv $*.clstavg $*.clstavg.$$(printf "%04d" $$COUNT); \
	echo "Count: $$(($$COUNT+1))" >> $*.refinement	
	touch $*.clstlst

