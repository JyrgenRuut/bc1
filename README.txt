The project is a small and fun microprocessor design, simulation and a little assembler for 
the instruction set, which is written in C.

The BC1 is a fictional 8-bit RISC architecture microprocessor design sporting 16 different fixed-size 16bit instructions, 
all of which are slightly explained in the "Instruction_Set.txt". 
The processor has 15 General Purpose registers (r1, r2... r9, ra... re, rf) and one "zero register" (r0).
It has 3 input/output ports (all of which are used up within the simulation schematic for simulation i/o, however
one is free to make their own devices to replace the ones provided).



The BC1.circ file is the actual schematic and simulation of the processor and is meant to be opened  and used with the program "Logisim",
which can be found here: http://www.cburch.com/logisim/
Teaching how to use Logisim is a topic of its own, so it is not explained here.



Since it is no fun to directly translate assembly into machinecode, there is a small assembler that can be found 
here: https://www.dropbox.com/s/lktba2hqtmgqrte/BC1assembler.exe?dl=0
The source code for the assembler is also provided as BC1assembler.c
How to use the assembler:
1: Place the assembly code to be assembled into the same directory as BC1assembler.exe in a file called "input.txt".
2: Run the executable, if there are any problems, the line of assembly on which the problem was found is displayed.
3: If everything went correctly, one should have an "output.txt" file with the hex code to be inserted into the 
program memory inside the simulation. 
Restrictions of the current assembler:
1: Case sensitive - everything must be written in lower-case letters currently.
2: Whitespace sensitive - the instruction must be the first written thing at each given line, except if the line is meant to
be a comment and ontop of that, the separation between each operand of an instruction must be exactly one character. 
3: A comment line is started with a '/'
4: No labels! Unfortunately the programmer is required to make sure the jump addresses are correctly hardcoded before handing
the assembly code over to the assembler. 



To say that this whole project is primitive is an understatement. It is just a small, simple, fun project that I made simply 
because I wanted to "play" a little bit. The processor design and the assembler have multiple shortcomings, along with the 
severely lacking documentation... 

Take this project as simply a little one-two evening play project. 