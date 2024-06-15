include ../../../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../Config/Define.inc
include ../../Config/Define.inc

all:compile
	crystalInfoReadAndWrite < test.inNothing > test.Initial
	cat test.Initial	
	crystalInfoReadAndWrite < test.in > test.out	
	diff test.in test.out > test.diff
	cat test.out
	cat test.diff

compile:
	$(CC) crystalInfoReadAndWrite.c -L${TOP}/lib/$(OSTYPE) -lEosObjects -lM -o crystalInfoReadAndWrite  

clean:
	rm test.out test.diff test.Initial crystalInfoReadAndWrite
