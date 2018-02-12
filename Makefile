all: bindcraft.so

bindcraft.so: bindcraft.c
	gcc -Wall -nostartfiles -fpic -shared bindcraft.c -o bindcraft.so -ldl -D_GNU_SOURCE

