#ifndef CPU_H
#define CPU_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "memoria.h"
#include "instrucao.h"

#define NUM_CORES 4
#define NUM_REGISTRADORES 32

typedef struct {
    int registradores[NUM_REGISTRADORES]; 
} Core;

typedef struct {
    Core cores[NUM_CORES];        
    int pc;                        
    Cache cache;                  
    Instrucoes registradorInstrucao;
} CPU;

void exibirRegistradores(Core *core);

#endif
