OBJECTS = controller/echecs.o model/primitives.o model/primitives_pieces.o model/primitives_listes.o controller/ai.o view/gui_window.o view/gui_event.o controller/divers.o

all: Programme

CFLAGS = -g -Wall -O2 `pkg-config --cflags gtk+-2.0`
LIBS = `pkg-config --libs gtk+-2.0`

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@	

Programme: $(OBJECTS)
	gcc $(OBJECTS) -o Capablanca -g $(LIBS)

clean:
	@rm -rf controller/*o view/*o model/*o Capablanca

echecs.o: controller/echecs.c model/primitives.h model/primitives_pieces.h model/primitives_listes.h controller/ai.h view/gui_window.h view/gui_event.h controller/divers.h

primitives.o: model/primitives.c

primitives_pieces.o: model/primitives_pieces.c

primitives_listes.o: model/primitives_listes.c

ai.o: controller/ai.c

gui_window.o: view/gui_window.c

gui_event.o: view/gui_event.c

divers.o: controller/divers.c
