include ${EOS_HOME}/src/Config/${EOS_HOST}.inc

DSTDIR=${EOS_HOME}/lib/$(OSTYPE)
LIB=$(DSTDIR)/libEosObjects.a 
TOOLSDIR=${EOS_HOME}/bin/$(OSTYPE)

objects.data:$(LIB) 
	${EOS_HOME}/sbin/makefunctionlistfromlib objects.data $(LIB)

tools.data::
	${EOS_HOME}/sbin/makeListOfObjectFromTool $(TOOLSDIR) tools.data

call.data:$(LIB) objects.data
	${EOS_HOME}/sbin/makecalllistfromlib call.data objects.data $(LIB)
structlist.dat::
	perl ${EOS_HOME}/sbin/makestructlist.pl  ${EOS_HOME}/include > structlist.dat
constantlist.dat::
	perl ${EOS_HOME}/sbin/makeconstantlist.pl  ${EOS_HOME}/include > constantlist.dat
structconstlist.dat:structlist.dat constantlist.dat
	cat structlist.dat constantlist.dat > structconstlist.dat
structconstnamelist.dat:structconstlist.dat
	perl ${EOS_HOME}/sbin/makestructnamelist.pl structconstnamelist.dat  structconstlist.dat  
prototypelist.dat::
	perl ${EOS_HOME}/sbin/makeprototypelist.pl ${EOS_HOME}/include  > prototypelist.dat
callhtml:call.data objects.data tools.data 
	sort objects.data |awk -f ${EOS_HOME}/sbin/makeallhtml.awk > all.html
	makeListOfUsageForEachObject call.data tools.data objects.data
	touch eachObject.html
defhtml:structconstnamelist.dat prototypelist.dat structconstlist.dat
	perl ${EOS_HOME}/sbin/makeprotohtml.pl prototypelist.dat  structconstnamelist.dat 
	perl ${EOS_HOME}/sbin/makestructhtml.pl  structconstlist.dat  structconstnamelist.dat
