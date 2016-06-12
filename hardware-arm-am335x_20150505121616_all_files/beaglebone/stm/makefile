export SHELLOPTS := igncr

COPT := --debug --dwarf2 --cpu=Cortex-A8.no_neon --arm --littleend

.PHONY : all
all: demo_stm.elf

%.o: %.s $(MAKEFILE_LIST)
	armasm $(COPT) -o $@ $<

%.o: %.c   $(MAKEFILE_LIST)
	armcc  $(COPT) -O0 -c -o $@ $<

demo_stm.elf: linker.scat crt0.o demo_stm.o
	armlink --bestdebug --elf --diag_suppress=L6329W,L6314W -o $@ --scatter $^

.PHONY : clean
clean:
	rm -fv *.o *.axf

