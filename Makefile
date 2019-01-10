
VPATH = _build
objects = nfc.o RC522.o
.PHONY : clear run

top:
	make clear
	make compile

compile: $(objects)
	gcc $(objects) -o debug.run -lwiringPi

clear: 
	rm -f *.run
	rm -f $(objects)

run: clear compile
	./debug.run

./$(VPATH)/nfc.o:RC522.o
	gcc -c nfc.c

./$(VPATH)/RCC522.o:
	gcc -c RC522.c RC522.h
