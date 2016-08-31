all: ahencode ahdecode

ahencode:
	gcc -Wall -o ahencode adaptive.c -lm

ahdecode:
	gcc -Wall -o ahdecode decoder.c -lm
