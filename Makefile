image: imagehandler.o imagemodifiers.o wavlet.o
	cc imagehandler.o imagemodifiers.o wavlet.o
imagehandler.o: src/imagehandler.c src/bmp.h
	cc -c src/imagehandler.c
imagemodifiers.o: src/imagemodifiers.c src/imagemodifiers.h src/bmp.h
	cc -c src/imagemodifiers.c
wavlet.o: wavet/wavlet.c wavet/wavlet.h
	cc -c wavet/wavlet.c
clean:
	rm *.o
	rm *.out



