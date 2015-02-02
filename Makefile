all: ptag

ptag: ptag.c
	gcc -o ptag ptag.c
