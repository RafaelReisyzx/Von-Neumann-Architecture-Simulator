#ifndef MEMORIA_H
#define MEMORIA_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "instrucao.h"

#define CACHE_SIZE 128
#define MEM_SIZE 1024
#define DISK_SIZE 2048


typedef struct {
    int dados[CACHE_SIZE]; 
    int tags[CACHE_SIZE]; 
    int fifo_index; 
} Cache;

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

void exibirMemoriaSecundaria(MemoriaSecundaria *disco);
void exibirMemoriaPrincipal(MemoriaPrincipal *memoria);

#endif
