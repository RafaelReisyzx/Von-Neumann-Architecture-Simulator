#ifndef UC_H
#define UC_H
#include "cpu.h"

#define ADD 0
#define SUB 1
#define DIV 2
#define MUL 3
#define IF_GREATER 4
#define IF_LESS 5
#define IF_EQUAL 6
#define LOAD 7
#define STORE 8

void UC(CPU *cpu, int *operando1, int *operando2, int *operador,int *coreIDR,int *coreIDR1,int *coreIDR2,int *saida,int *r,int *r1,int *r2);

#endif
