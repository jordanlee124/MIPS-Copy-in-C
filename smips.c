#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define ADD_PATTERN     0b00000100000   // last 11 bits
#define SUB_PATTERN     0b00000100010
#define AND_PATTERN     0b00000100100
#define OR_PATTERN      0b00000100101
#define SLT_PATTERN     0b00000101010
#define SYS_PATTERN     0b00000001100
#define MUL_PATTERN     0b011100
#define BEQ_PATTERN     0b000100
#define BNE_PATTERN     0b000101
#define ADDI_PATTERN    0b001000
#define SLTI_PATTERN    0b001010
#define ANDI_PATTERN    0b001100
#define ORI_PATTERN     0b001101
#define LUI_PATTERN     0b001111


#define REG_V0      2
#define REG_A0      4
#define REG_ZERO    0

#define PRINT_INTEGER   1
#define EXIT            10
#define PRINT_CHAR      11

uint32_t negNum (uint32_t num);

int main (int argc, char *argv[]) {

    FILE * fileRead = fopen(argv[1], "r");

    char operation[100]={""};
    uint32_t hex[100] = {0};
    uint32_t firstSix = 0;
    uint32_t lastEleven = 0;
    char ch[100];
    int reg[32] = {0};
    int i = 0;
    int pc = 0;
    uint32_t s;
    uint32_t d;
    uint32_t t;
    uint32_t im;
    uint32_t neg;

    while (fgets(ch, 100, fileRead) != NULL) {
        sscanf(ch, "%x", &hex[i]);
        i++;
    }

    printf("Program\n");
    

    // A while loop to print out instructions
    while (pc <= i) { 
        firstSix = hex[pc] >> 26;
        s = (hex[pc] >> 21) & 0x1f;
        t = (hex[pc] >> 16) & 0x1f;
        d = (hex[pc] >> 11) & 0x1f;
        im = hex[pc] & 0xffff;
        neg = (hex[pc] >> 15) & 1;
        if (firstSix == 0) { // Check first 6 binary values to determine operation
            lastEleven = hex[pc] & 0x3f;  
            if (lastEleven == ADD_PATTERN) { 
                strcpy(operation, "add");
                printf("%3d: %s  $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (lastEleven == SUB_PATTERN) {
                strcpy(operation, "sub");
                printf("%3d: %s  $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (lastEleven == AND_PATTERN) {
                strcpy(operation, "and");
                printf("%3d: %s  $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (lastEleven == OR_PATTERN) {
                strcpy(operation, "or");
                printf("%3d: %s   $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (lastEleven == SLT_PATTERN) {
                strcpy(operation, "slt");
                printf("%3d: %s  $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (lastEleven == SYS_PATTERN) {
                strcpy(operation, "syscall");
                printf("%3d: %s\n", pc, operation);
            }
        } else { 
            if (firstSix == MUL_PATTERN) { // Check last 11 binary values to determine operation
                strcpy(operation, "mul");
                printf("%3d: %s  $%d, $%d, $%d\n", pc, operation, d, s, t);
            } else if (firstSix == BEQ_PATTERN) {
                strcpy(operation, "beq");
                if (neg == 0) {
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, s, t, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, s, t, ~im);
                }
            } else if (firstSix == BNE_PATTERN) {
                strcpy(operation, "bne");
                if (neg == 0) {
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, s, t, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, s, t, ~im);
                }
            } else if (firstSix == ADDI_PATTERN) {
                strcpy(operation, "addi");
                if (neg == 0) {
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, ~im);
                }
            } else if (firstSix == SLTI_PATTERN) {
                strcpy(operation, "slti");
                if (neg == 0) {
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, ~im);
                }
            } else if (firstSix == ANDI_PATTERN) {
                strcpy(operation, "andi");
                if (neg == 0) {
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s $%d, $%d, %d\n", pc, operation, t, s, ~im);
                }
            } else if (firstSix == ORI_PATTERN) {
                strcpy(operation, "ori");
                if (neg == 0) {
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, t, s, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s  $%d, $%d, %d\n", pc, operation, t, s, ~im);
                }
            } else if (firstSix == LUI_PATTERN) {
                strcpy(operation, "lui");
                if (neg == 0) {
                    printf("%3d: %s  $%d, %d\n", pc, operation, t, im);
                } else {
                    im = negNum(im);
                    printf("%3d: %s  $%d, %d\n", pc, operation, t, ~im);
                }
            } else {
                printf("%s:%d: invalid instruction code: %08X\n", argv[1], pc, hex[pc]);
                break;
            }
        }
        pc++;
    }   
    
    printf("Output\n");

    pc = 0;


    // A while loop to execute instructions and print an output
    while (pc <= i) {
        firstSix = hex[pc] >> 26;
        s = (hex[pc] >> 21) & 0x1f;
        t = (hex[pc] >> 16) & 0x1f;
        d = (hex[pc] >> 11) & 0x1f;
        im = hex[pc] & 0xffff;
        neg = (hex[pc] >> 15) & 1;
        if (firstSix == 0) {
            lastEleven = hex[pc] & 0x3f; 
            if (d != 0) { // Check if fuction is inputting into $0 register
                if (lastEleven == ADD_PATTERN) {
                    reg[d] = reg[s] + reg[t];
                } else if (lastEleven == SUB_PATTERN) {
                    reg[d] = reg[s] - reg[t];
                } else if (lastEleven == AND_PATTERN) {
                    reg[d] = reg[s] & reg[t];
                } else if (lastEleven == OR_PATTERN) {
                    reg[d] = reg[s] | reg[t];
                } else if (lastEleven == SLT_PATTERN) {
                    if (reg[s] < reg[t]) {
                        reg[d] = 1;       
                    } else {
                        reg[d] = 0;
                    }
                }
            } 
            if (lastEleven == SYS_PATTERN) {
                if (reg[REG_V0] == PRINT_INTEGER) { 
                    printf("%d", reg[REG_A0]);
                } else if (reg[REG_V0] == EXIT) { // Check for exit(0) syscall
                    break;
                } else if (reg[REG_V0] == PRINT_CHAR) {
                    printf("%c", reg[REG_A0]);
                } else { // Check for invalid syscall
                    printf("Unknown system call: %d\n", reg[REG_V0]);
                    break;
                }
            }
             
        } else {
            if (firstSix == BEQ_PATTERN) {
                if (reg[s] == reg[t]) {
                    if (neg == 0) {
                        pc += im - 1;
                    } else {
                        im = negNum(im);
                        pc += ~im - 1;
                    }
                }
            } else if (firstSix == BNE_PATTERN) {
                if(reg[s] != reg [t]) {
                    if (neg == 0) {
                        pc += im - 1;
                    } else {
                        im = negNum(im);
                        pc += ~im - 1;
                    }   
                }
            } else if (t != 0) {
                if (firstSix == MUL_PATTERN) {
                    reg[d] = reg[s] * reg[t];
                } else if (firstSix == ADDI_PATTERN) {
                    if (neg == 0) {
                        reg[t] = reg[s] + im;
                    } else {
                        im = negNum(im);
                        reg[t] = reg[s] + ~im;
                    }
                } else if (firstSix == SLTI_PATTERN) {
                    if (neg == 0) {
                        reg[t] = (reg[s] < im);
                    } else {
                        im = negNum(im);
                        reg[t] = (reg[s] < ~im);
                    }
                } else if (firstSix == ANDI_PATTERN) {
                    if (neg == 0) {
                        reg[t] = reg[s] & im;
                    } else {
                        im = negNum(im);
                        reg[t] = reg[s] & ~im;
                    }
                } else if (firstSix == ORI_PATTERN) {
                    if (neg == 0) {
                        reg[t] = reg[s] | im;
                    } else {
                        im = negNum(im);
                        reg[t] = reg[s] | ~im;
                    }
                } else if (firstSix == LUI_PATTERN) {
                    if (neg == 0) {
                        reg[t] = im << 16;
                    } else {
                        im = negNum(im);
                        reg[t] = ~im << 16;
                    }
                }
            }
        }
        pc++;
    }

    printf("Registers After Execution\n");

    pc = 0;


    // A loop to print non-zero holding registers.  
    while (pc < 32) {
        if (reg[pc] != 0 && pc < 10) {
            printf("$%d  = %d\n", pc, reg[pc]);
        } else if (reg[pc] != 0 && pc >= 10) {
            printf("$%d = %d\n", pc, reg[pc]);
        }
        pc++;
    }

    return 0;
}

// If first bit of immediate is 1, make number negative.
uint32_t negNum (uint32_t num) {
    int n = 0;
    while (n < 16){
        num = num ^ (1 << n);
        n++;
    }

    return num;
}