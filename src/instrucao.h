#ifndef INSTRUCAO_H
#define INSTRUCAO_H

typedef struct {
    int Opcode;
    int Register;       
    int Register1;
    int Register2;
    int coreIDR;
    int coreIDR1;
    int coreIDR2;
} Instrucoes;

#endif
