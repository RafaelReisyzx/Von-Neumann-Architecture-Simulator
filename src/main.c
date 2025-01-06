#include <unistd.h> 
#include <pthread.h>

#include "system.h"
#include "cpu.h"
#include "pipeline.h"
#include "simulador.h"

int main() {

    SYSTEM system;
    CPU cpu;
    Processo processos[NUM_PROCESSOS];
    int numInstrucoes = 0;
    
    inicializarSistema(&cpu, &system);

    carregarValoresIniciais("dataset/valores_iniciais.txt", &cpu, &system);

    carregarInstrucoesDeArquivo("dataset/instruções.txt", &system, &numInstrucoes);

    for (int i = 0; i < NUM_PROCESSOS; i++) {
        processos[i].id = i + 1;
        processos[i].prioridade = i + 1;
        processos[i].quantum = (i + 1) * 2;

        pthread_create(&processos[i].thread, NULL, executar_processo, &processos[i]);
    }
    Pipeline(&cpu, &system, numInstrucoes);
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        pthread_join(processos[i].thread, NULL);
    }

    sleep(5);
    exibirInformacoes(&cpu, &system);

    return 0;
}
