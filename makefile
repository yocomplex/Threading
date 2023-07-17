# CS 218 Summer 2023 Assignment #7
#Makefile to create the object files from both C and x86 and then link them

OBJS		= parallel_sum.o hw7.o
ASM		= yasm -g dwarf2 -f elf64
LD		= gcc -g -pthread -o sum_prog_par
ARGS		= -g -Wall -c -std=c++11

all: sum_prog_par sum_prog_seq

parallel_sum.o: parallel_sum.cpp
	gcc $(ARGS) parallel_sum.cpp
	
seq_sum.o:
	gcc $(ARGS) seq_sum.cpp
	
hw7.o: hw7.asm 
	$(ASM) hw7.asm -l hw7.lst

sum_prog_par: $(OBJS)
	$(LD) -no-pie $(OBJS) -lstdc++

sum_prog_seq: seq_sum.o
	gcc -g -o sum_prog_seq -no-pie seq_sum.o -lstdc++

# -----
# clean by removing object file.

clean:
	@rm	-f $(OBJS)
	@rm	-f seq_sum.o sum_prog_seq
	@rm	-f hw7.lst
