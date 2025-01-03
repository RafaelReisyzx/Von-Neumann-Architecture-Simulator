#ifndef PIPELINE_H
#define PIPELINE_H
#include "system.h"
#include "cpu.h"
#include "ula.h"
#include "uc.h"

void fetch(SYSTEM *system,CPU *cpu);
void decode(CPU *cpu, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int *r1, int *r2);
int execute(CPU *cpu, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2,int resultado) ;
void memory_access(CPU *cpu,SYSTEM *system, int operador, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1) ;
void write_back(CPU *cpu,int operador,int coreIDR,int r,int resultado);
void Pipeline(CPU *cpu,SYSTEM *system,int i);

#endif
