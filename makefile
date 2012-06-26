# makfile configuration
NAME            = main
OBJECTS         = main.o spi.o can.o init.o global.o lcd.o
CPU             = msp430x2272

ASFLAGS         = -mmcu=${CPU} -x assembler-with-cpp -D_GNU_ASSEMBLER_ -c
CFLAGS          = -mmcu=${CPU} -O2 -Wall -g

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-gcc

.PHONY: all FORCE clean download download-jtag download-bsl dist

#all should be the first target. it's built when make is run without args
all: ${NAME}.elf ${NAME}.a43 ${NAME}.lst

#additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} -mmcu=${CPU} -o $@ ${OBJECTS}

${NAME}.a43: ${NAME}.elf
	msp430-objcopy -O ihex $^ $@

${NAME}.lst: ${NAME}.elf
	msp430-objdump -dSt $^ >$@

clean:
	rm -f ${NAME}.elf ${NAME}.a43 ${NAME}.lst ${OBJECTS}

#automatic collection of dependencies in the source files.
#it's only updated the first time, after that it must be done maually
#with "make depend"
#the dependecies are included from a separate file:
-include dependencies.in
#target to update the file, it's removed first
depend: rmdepend dependencies.in
#remove the file
rmdepend:
	rm -f dependencies.in
#build the file that contains the dependencies. no deps in this rule.
#if there were deps it would be rebuilt every chnage, which is unneded:
dependencies.in:
	$(CC) -MM ${CFLAGS} $(patsubst %.o,%.c,$(OBJECTS)) >$@



