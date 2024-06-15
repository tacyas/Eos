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
	MODE="ZONS"; ROT=" 0 0 0 "; NAME=data/test00; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="ZONS"; ROT=" 20 10 0"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YONS"; ROT=" 10 0 70"; NAME=dat/atest1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XONS"; ROT=" 20 0 40"; NAME=dat/atest1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="ZOYS"; ROT=" 0 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YOYS"; ROT=" 20 70 0"; NAME=dat/atest0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XOYS"; ROT=" 0 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	@echo "----- Calc check -----"		
	MODE="ZENS"; ROT=" 20 0 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YENS"; ROT=" 20 30 0"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XENS"; ROT=" 0 0 40"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="ZEYS"; ROT=" 20 0 0"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YEYS"; ROT=" 20 0 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XEYS"; ROT=" 0 30 0"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	@echo "----- Calc check -----"		
	MODE="ZONR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YONR"; ROT=" 20 30 40"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XONR"; ROT=" 20 30 40"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="ZOYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YOYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XOYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	@echo "----- Calc check -----"		
	MODE="ZENR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YENR"; ROT=" 20 30 40"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XENR"; ROT=" 20 30 40"; NAME=data/test1; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="ZEYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="YEYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	MODE="XEYR"; ROT=" 20 30 40"; NAME=data/test0; echo "$${MODE} $${ROT}" > $${NAME}.ea; cat $${NAME}.ea;  \
	matrix3DFromEulerAngle -i $${NAME}.ea -o $${NAME}.mat ; \
	../$(OSTYPE)/$(OBJECTNAME) -i $${NAME}.mat -EM $${MODE} -o $${NAME}.res; \
	diff $${NAME}.ea $${NAME}.res
	#
	@echo "----- Calc check -----"		

clean:
