.SECONDARY:

all: exe/test.elf

%.elf: exesrc/main2.o src/cmplx.o src/io.o
	gcc exesrc/main2.o src/cmplx.o src/io.o -o $@ -lm

%.o: %.c
	gcc -c $< -I inc/ -o $@

clean:
	rm -f src/*.o exesrc/*.o exe/*.elf