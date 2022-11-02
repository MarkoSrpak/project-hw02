SRC=$(wildcard src/*.c)
EXESRC=$(wildcard exesrc/*.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
EXEOBJ=$(patsubst %.c, %.o, $(EXESRC))
BIN=$(wildcard bin/*.bin)
INC=inc/
EXE=$(patsubst exesrc/%.c, exe/%.elf, $(EXESRC))

CFLAGS=-I $(INC)

.SECONDARY:

all: $(EXE)

exe/%.elf: exesrc/%.o $(OBJ)
	gcc $(OBJ) $< -o $@ -lm

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

run:
#$(EXE)
	exe/test_dft.elf
	exe/test_idft.elf
	
clean:
	rm -f $(OBJ) $(EXE) $(EXEOBJ) $(BIN)

print:
	echo $(SRC)
	echo $(EXESRC)
	echo $(OBJ)
	echo $(EXEOBJ)
	echo $(BIN)
	echo $(INC)
	echo $(EXE)