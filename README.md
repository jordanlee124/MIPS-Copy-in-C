# MIPS Copy in C
## Project description
In this project, I've re-created basic operations used in MIPS, using C. Such operations are:
* add
* addi
* sub
* mul
* and
* andi
* or
* ori
* bne
* beq
* slt
* slti
* lui
* syscall

## How to run the project
To run this project, you will have to download this repository as a zip file.

Then, unzip this file open a terminal in the file location.

You will need to have a text file with MIPS code that is able to be executed by this program. (A MIPS code containing the operations mentioned above)

In the terminal, run 
```bash 
gcc smips.c -o smips
./smips text.txt
```

