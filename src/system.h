#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define ADD 0
#define SUB 1
#define DIV 2
#define MUL 3
#define IF_GREATER 4
#define IF_LESS 5
#define IF_EQUAL 6
#define LOAD 7
#define STORE 8

#define CACHE_SIZE 128 
#define MEM_SIZE 1024  
#define DISK_SIZE 2048     
#define NUM_PERIFERICOS 4
#define NUM_CORES 4  
#define NUM_REGISTRADORES 32

typedef struct {
    int dados[CACHE_SIZE]; 
    int tags[CACHE_SIZE]; 
    int fifo_index; 
} Cache;

typedef struct {
    int Opcode;
    int Register;       
    int Register1;
    int Register2;
    int coreIDR;
    int coreIDR1;
    int coreIDR2;
} Instrucoes;

typedef struct {
    int inteiro;
    Instrucoes instrucao;  
} Dados;

typedef struct {
    Dados dados[MEM_SIZE];      
} MemoriaPrincipal;

typedef struct {
    Dados dados[DISK_SIZE]; 
} MemoriaSecundaria;

typedef struct {
    char* nome;
    bool disponivel;
} Periferico;

typedef struct {
    int registradores[NUM_REGISTRADORES]; 
} Core;

typedef struct {
    Core cores[NUM_CORES];
    int pc;           
    Cache cache;                  
    MemoriaPrincipal memoria;    
    MemoriaSecundaria disco;   
    Periferico periferico[NUM_PERIFERICOS]; 
    Instrucoes registradorInstrucao;
} SYSTEM;

void fetch(SYSTEM *system);
void decode(SYSTEM *system, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int *r1, int *r2);
int execute(SYSTEM *system, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2,int resultado) ;
void memory_access(SYSTEM *system, int operador, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1) ;
void write_back(SYSTEM *system,int operador,int coreIDR,int r,int resultado);
void Pipeline(SYSTEM *system,int i);
void inicializarSistema(SYSTEM *system);
void exibirMemoriaSecundaria(MemoriaSecundaria *disco);
void exibirMemoriaPrincipal(MemoriaPrincipal *memoria);
void exibirRegistradores(Core *core);
void exibirMenu(SYSTEM *system);
int ULA(SYSTEM *system,int opcode, int reg1, int reg2,int r,int r1,int r2,int coreIDR,int coreIDR1,int coreIDR2);
void UC(SYSTEM *system, int *operando1, int *operando2, int *operador,int *coreIDR,int *coreIDR1,int *coreIDR2,int *saida,int *r,int *r1,int *r2);
void escreverMemoriaPrincipal(MemoriaPrincipal *memoria);
void escreverMemoriaSecundaria(MemoriaSecundaria *disco, int endereco, int valor);
void InstructionsMemory(SYSTEM *system,int code,int *saida, int *operando1,int coreIDR,int coreIDR1,int r,int r1);

#endif
