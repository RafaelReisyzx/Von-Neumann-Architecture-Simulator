#ifndef PIPELINE_H
#define PIPELINE_H
#include <pthread.h>

#include "system.h"
#include "cpu.h"
#include "ula.h"
#include "uc.h"

typedef struct {
    CPU *cpu;
    SYSTEM *system;
    int operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida, r, r1, r2, resultado;
    pthread_mutex_t *lock;
    pthread_cond_t *cond_var;
    int *stage_flag;
} PipelineArgs;

void fetch(SYSTEM *system, CPU *cpu);
void decode(CPU *cpu, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int *r1, int *r2);
int execute(CPU *cpu, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2, int resultado);
void memory_access(CPU *cpu, SYSTEM *system, int operador, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1);
void write_back(CPU *cpu, int operador, int coreIDR, int r, int resultado);
void *fetch_stage(void *args);
void *decode_stage(void *args);
void *execute_stage(void *args);
void *memory_stage(void *args);
void *write_back_stage(void *args);
void Pipeline(CPU *cpu, SYSTEM *system, int num_instrucoes);

#endif
