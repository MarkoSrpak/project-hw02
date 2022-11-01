.SECONDARY:

dft: exe/test1.elf

%.elf: exesrc/test_dft.o src/cmplx.o src/io.o
	gcc exesrc/test_dft.o src/cmplx.o src/io.o -o $@ -lm

%.o: %.c
	gcc -c $< -I inc/ -o $@

clean:
	rm -f src/*.o exesrc/*.o exe/*.elf bin/*.bin