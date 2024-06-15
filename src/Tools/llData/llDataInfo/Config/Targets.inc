depend :
	$(CC) $(CCOPT) $(INCLUDEDIR) -E -M *.c  > .Depend

include .Depend
