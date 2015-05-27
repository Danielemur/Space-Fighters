CFLAGS = -std=c99 -Wall -Wextra -Wno-unused-function -g3 -fPIC	\
-march=native -Ofast -funroll-loops -fomit-frame-pointer
LDLIBS = -lm -ldl -lpthread


all : spacefighters

objects = asteroid.o common.o enemy.o entity.o entity_living.o	\
image.o player.o projectile.o stage.o starship.o



spacefighters : main.c $(objects)
	$(CC) $(CFLAGS) -L. -o $@ $^ $(LDLIBS)


deps :
	$(CC) -MM *.c > make.deps


run : spacefighters
	./spacefighters

clean :
	$(RM) $(objects) spacefighters

include make.deps
