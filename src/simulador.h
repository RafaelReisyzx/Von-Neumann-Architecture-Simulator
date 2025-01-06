#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_NUCLEOS 4      
#define QUANTUM_TEMPO 10   

#define NUM_PROCESSOS 5

typedef enum {
    PRONTO,
    EXECUTANDO,
    BLOQUEADO
} EstadoProcesso;

typedef struct {
    int id;
    int prioridade;
    int quantum;
    pthread_t thread;
} Processo;

typedef struct {
    int id_recurso;
    bool recurso_ocupado;
} Recurso;

typedef struct PCB {
    int id;
    EstadoProcesso estado;
    int prioridade;
    int tempo_execucao;
    Recurso *recursos_associados;   
    struct PCB *proximo;       
} PCB;

typedef struct {
    PCB *processo_execucao;
    pthread_t thread_nucleo;
} Nucleo;


extern PCB *fila_processos_prontos;  
extern Nucleo nucleo[NUM_NUCLEOS];  
extern sem_t mutex_fila_prontos;    
extern sem_t mutex_gerenciamento;

void iniciar_simulador();
void criar_processo(int id, int prioridade);
void *executar_processo(void *arg);
void bloquear_processo(PCB *processo);
void desbloquear_processo(PCB *processo);
void gerenciar_recursos();

#endif
