#Beaglebone makefile

#Probably only 'gcc' can be used if compiling with the board's toolchain.
CC = arm-angstrom-linux-gnueabi-gcc

#For Windows
RM = cmd /C del

#For Linux
#RM = rm -f

SRC = ./src/main.c ./src/util.c ./src/setup.c ./src/inventory.c ./src/readercaps.c
INCLUDE = -I./inc/
LIBDEF = -L./lib/ -lNurApiBeagleBone -lm -lpthread
CFLAGS = -D_PLAT_BBONE -DNUR_EXPOSE_WIN32API

OUTPUT = nurconbb

all:
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC) -o $(OUTPUT) $(LIBDEF)

clean:
	$(RM) $(OUTPUT)
