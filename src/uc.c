#include "uc.h"

void UC(CPU *cpu, int *operando1, int *operando2, int *operador,int *coreIDR,int *coreIDR1,int *coreIDR2,int *saida,int *r,int *r1,int *r2) {
    if (cpu->registradorInstrucao.Opcode == 0) {
        *operador = ADD;
    } else if (cpu->registradorInstrucao.Opcode == 1) {
        *operador = SUB;
    } else if (cpu->registradorInstrucao.Opcode == 2) {
        *operador = MUL;
    } else if (cpu->registradorInstrucao.Opcode == 3) {
        *operador = DIV;
    } else if (cpu->registradorInstrucao.Opcode == 4) {
        *operador = IF_GREATER;
    } else if (cpu->registradorInstrucao.Opcode == 5) {
        *operador = IF_LESS;
    } else if (cpu->registradorInstrucao.Opcode == 6) {
        *operador = IF_EQUAL; 
    } else if (cpu->registradorInstrucao.Opcode == 7) {
        *operador = LOAD;
    } else if (cpu->registradorInstrucao.Opcode == 8) {
        *operador = STORE;
    }
    *coreIDR = cpu->registradorInstrucao.coreIDR;
    *coreIDR1 = cpu->registradorInstrucao.coreIDR1;
    *coreIDR2 = cpu->registradorInstrucao.coreIDR2;
    *operando1 = cpu->cores[*coreIDR1].registradores[cpu->registradorInstrucao.Register1];
    *operando2 = cpu->cores[*coreIDR2].registradores[cpu->registradorInstrucao.Register2];
    *saida = cpu->cores[*coreIDR].registradores[cpu->registradorInstrucao.Register];
    *r = cpu->registradorInstrucao.Register;
    *r1 = cpu->registradorInstrucao.Register1;
    *r2 =cpu->registradorInstrucao.Register2;
 

}
 
