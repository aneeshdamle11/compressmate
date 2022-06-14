image: imagehandler.o imagemodifiers.o wavlet.o k2tree.o Tlist.o Llist.o
	cc imagehandler.o imagemodifiers.o wavlet.o k2tree.o Tlist.o Llist.o
imagehandler.o: src/imagehandler.c src/bmp.h
	cc -c src/imagehandler.c
imagemodifiers.o: src/imagemodifiers.c src/imagemodifiers.h src/bmp.h
	cc -c src/imagemodifiers.c
wavlet.o: wavet/wavlet.c wavet/wavlet.h
	cc -c wavet/wavlet.c
k2tree.o: k2t/k2tree.h k2t/k2tree.c 
	cc -c k2t/k2tree.c
Tlist.o: k2t/linked-lists/Tlist.c k2t/linked-lists/Tlist.h
	cc -c k2t/linked-lists/Tlist.c
Llist.o: k2t/linked-lists/Llist.c k2t/linked-lists/Llist.h
	cc -c k2t/linked-lists/Llist.c
clean:
	rm *.o
	rm *.out



