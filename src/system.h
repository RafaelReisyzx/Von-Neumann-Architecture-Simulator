#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "memoria.h" 
#include "cpu.h"

#define NUM_PERIFERICOS 4

typedef struct {
    char* nome;
    bool disponivel;
} Periferico;

typedef struct {
    MemoriaPrincipal memoria;
    MemoriaSecundaria disco;
    Periferico periferico[NUM_PERIFERICOS];
} SYSTEM;

void inicializarSistema(CPU *cpu, SYSTEM *system);
void exibirInformacoes(CPU *cpu, SYSTEM *system);
void InstructionsMemory(CPU *cpu, SYSTEM *system, int code, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1);

#endif
