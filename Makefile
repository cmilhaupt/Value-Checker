cc = gcc

options = -g -std=c11 -lm

all: checkNum numGen
checkNum: checkNumber.c
	$(cc) checkNumber.c -o checkNumber $(options)

numGen: numGen.c
	$(cc) numGen.c -o numGen $(options)

clean:
	rm *.txt
