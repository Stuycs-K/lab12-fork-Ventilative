compile: fork.c
	@gcc -Wall fork.c -o fork
run: fork
	@./fork
clean:
	rm -rf fork
