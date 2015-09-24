CC=gcc
FILES = main.c processfiles.c hashmethods.c
OUT_EXE = main

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
