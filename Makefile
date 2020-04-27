#Archivo Makefile

PROYECTO=brainfuck
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LFLAGS=
CC=gcc

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) $^ -o $@   $(LFLAGS)

.PHONY: clean 

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
		sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO) *.dat
