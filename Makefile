all:
	gcc main.c fun.c -o sims
clean:
	rm sims.out -rf