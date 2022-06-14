k2tree: main.o k2tree.o Tlist.o Llist.o
	cc main.o k2tree.o Tlist.o Llist.o
main.o: main.c
	cc -c main.c
k2tree.o: k2tree.h k2tree.c 
	cc -c k2tree.c
Tlist.o: linked-lists/Tlist.c linked-lists/Tlist.h
	cc -c linked-lists/Tlist.c
Llist.o: linked-lists/Llist.c linked-lists/Llist.h
	cc -c linked-lists/Llist.c
clean:
	rm *.o
	rm *.out

