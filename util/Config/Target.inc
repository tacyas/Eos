#
#
#
help::


check:
	for i in $(UTILS) ; do echo $$i; \
		make $${i}Check; \
	done
 
config:
	for i in $(UTILS) ; do echo $$i; \
		make $${i}Config; \
	done
 
all:
	for i in $(UTILS) ; do echo $$i; \
		make $${i}All; \
	done
 
clean:
	for i in $(UTILS) ; do echo $$i; \
		make $${i}Clean; \
	done
 
cleanAll:
	for i in $(UTILS) ; do echo $$i; \
		make $${i}CleanAll; \
	done

