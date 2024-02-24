make:
	gcc -ggdb -o s-talk list.o main.c manager.c receive.c send.c read.c write.c -lpthread
clean:
	rm s-talk