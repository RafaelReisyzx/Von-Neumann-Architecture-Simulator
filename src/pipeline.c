#include "pipeline.h"

void fetch(SYSTEM *system,CPU *cpu) {
cpu->registradorInstrucao = system->memoria.dados[cpu->pc].instrucao;
}

void decode(CPU *cpu, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int *r1, int *r2) {
    UC(cpu, operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida, r, r1, r2);
}

int execute(CPU *cpu, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2,int resultado) {
    resultado=ULA(cpu, operador, operando1, operando2, r, r1, r2, coreIDR, coreIDR1, coreIDR2);
    return resultado;
}

void memory_access(CPU *cpu,SYSTEM *system, int operador, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1) {
    if (operador == LOAD) {
        *saida = system->memoria.dados[r].inteiro;
        InstructionsMemory(cpu,system, LOAD, saida, operando1, coreIDR, coreIDR1, r, r1);
    } else if (operador == STORE) {
        *saida = system->memoria.dados[r1].inteiro;
        InstructionsMemory(cpu,system, STORE, saida, operando1, coreIDR, coreIDR1, r, r1);
    }
}

void write_back(CPU *cpu,int operador,int coreIDR,int r,int resultado){
 if (operador != LOAD&&operador != STORE&&operador != IF_EQUAL&&operador != IF_LESS&&operador != IF_LESS) {   
      cpu->cores[coreIDR].registradores[r]=resultado;
    }

}

void Pipeline(CPU *cpu,SYSTEM *system, int i) {
    int j, r, r1, r2, operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida,resultado;
    
    for (j = 0; j < i; j++) {
        fetch(system,cpu);
        decode(cpu, &operando1, &operando2, &operador, &coreIDR, &coreIDR1, &coreIDR2, &saida, &r, &r1, &r2);
        resultado= execute(cpu, operador, operando1, operando2, r, r1, r2, coreIDR, coreIDR1, coreIDR2,resultado);
        memory_access(cpu,system, operador, &saida, &operando1, coreIDR, coreIDR1, r, r1);
        write_back(cpu,operador,coreIDR,r,resultado);
        cpu->pc++; 
    }
}

