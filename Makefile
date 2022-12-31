all: exec

exec:
	gcc -Iinclude -lraylib -Llib/ main.c -o exec