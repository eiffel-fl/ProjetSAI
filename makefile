CC = gcc
CFLAGS = -lGLU -lGL -lglut -lm
EXEC = test clean_o

all : $(EXEC)

test : animer interaction labyrinthe
	$(CC) test.c labyrinthe.o animer.o interaction.o $(CFLAGS) -o test

animer : interaction
	$(CC) animer.c -c $(CFLAGS)

interaction : labyrinthe
	$(CC) interaction.c -c $(CFLAGS)

labyrinthe :
	$(CC) labyrinthe.c -c $(CFLAGS)

clean_o :
	rm -rf *.o

clean_exe :
	rm -rf test
