#include "simulador.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

PCB *fila_processos_prontos = NULL;
Nucleo nucleo[NUM_NUCLEOS];
sem_t mutex_fila_prontos;
sem_t mutex_gerenciamento;

void iniciar_simulador() {
    sem_init(&mutex_fila_prontos, 0, 1); 
    sem_init(&mutex_gerenciamento, 0, 1); 

    for (int i = 0; i < NUM_NUCLEOS; i++) {
        nucleo[i].processo_execucao = NULL;
        pthread_create(&nucleo[i].thread_nucleo, NULL, executar_processo, (void *)&nucleo[i]);
    }
}

void criar_processo(int id, int prioridade) {
    PCB *novo_processo = malloc(sizeof(PCB));
    novo_processo->id = id;
    novo_processo->estado = PRONTO;
    novo_processo->prioridade = prioridade;
    novo_processo->tempo_execucao = 0;
    novo_processo->recursos_associados = NULL;  
    novo_processo->proximo = NULL;

    sem_wait(&mutex_fila_prontos);
    if (fila_processos_prontos == NULL) {
        fila_processos_prontos = novo_processo;
    } else {
        PCB *temp = fila_processos_prontos;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo_processo;
    }
    sem_post(&mutex_fila_prontos);
}

void* executar_processo(void* arg) {
    Processo* processo = (Processo*)arg;
    pthread_mutex_t mutex;
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("Processo %d (Prioridade %d) executando por %d segundos\n", processo->id, processo->prioridade, processo->quantum);
        sleep(processo->quantum); 
        pthread_mutex_unlock(&mutex);
        
        printf("Troca de contexto: Processo %d interrompido\n", processo->id);
        break; 
    }
    return NULL;
}


void bloquear_processo(PCB *processo) {
    processo->estado = BLOQUEADO;
    printf("Processo %d está bloqueado\n", processo->id);
}

void desbloquear_processo(PCB *processo) {
    processo->estado = PRONTO;
    printf("Processo %d está pronto\n", processo->id);
}

void gerenciar_recursos() {
    sem_wait(&mutex_gerenciamento);
    PCB *processo_atual = fila_processos_prontos;
    
    while (processo_atual != NULL) {
        if (processo_atual->recursos_associados != NULL) {
            bloquear_processo(processo_atual);
        } else {
            desbloquear_processo(processo_atual);
        }
        processo_atual = processo_atual->proximo;
    }
    sem_post(&mutex_gerenciamento);
}
