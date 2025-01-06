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

void *fetch_stage(void *args) {
    PipelineArgs *pipeline = (PipelineArgs *)args;
    pthread_mutex_lock(pipeline->lock);
    fetch(pipeline->system, pipeline->cpu);
    *(pipeline->stage_flag) = 1;
    pthread_cond_signal(pipeline->cond_var);
    pthread_mutex_unlock(pipeline->lock);
    return NULL;
}

void *decode_stage(void *args) {
    PipelineArgs *pipeline = (PipelineArgs *)args;
    pthread_mutex_lock(pipeline->lock);
    while (*(pipeline->stage_flag) != 1) {
        pthread_cond_wait(pipeline->cond_var, pipeline->lock);
    }
    decode(pipeline->cpu, &pipeline->operando1, &pipeline->operando2, &pipeline->operador,
           &pipeline->coreIDR, &pipeline->coreIDR1, &pipeline->coreIDR2,
           &pipeline->saida, &pipeline->r, &pipeline->r1, &pipeline->r2);
    *(pipeline->stage_flag) = 2;
    pthread_cond_signal(pipeline->cond_var);
    pthread_mutex_unlock(pipeline->lock);
    return NULL;
}

void *execute_stage(void *args) {
    PipelineArgs *pipeline = (PipelineArgs *)args;
    pthread_mutex_lock(pipeline->lock);
    while (*(pipeline->stage_flag) != 2) {
        pthread_cond_wait(pipeline->cond_var, pipeline->lock);
    }
    pipeline->resultado = execute(pipeline->cpu, pipeline->operador, pipeline->operando1, pipeline->operando2,
                                   pipeline->r, pipeline->r1, pipeline->r2,
                                   pipeline->coreIDR, pipeline->coreIDR1, pipeline->coreIDR2, pipeline->resultado);
    *(pipeline->stage_flag) = 3;
    pthread_cond_signal(pipeline->cond_var);
    pthread_mutex_unlock(pipeline->lock);
    return NULL;
}

void *memory_stage(void *args) {
    PipelineArgs *pipeline = (PipelineArgs *)args;
    pthread_mutex_lock(pipeline->lock);
    while (*(pipeline->stage_flag) != 3) {
        pthread_cond_wait(pipeline->cond_var, pipeline->lock);
    }
    memory_access(pipeline->cpu, pipeline->system, pipeline->operador, &pipeline->saida,
                  &pipeline->operando1, pipeline->coreIDR, pipeline->coreIDR1, pipeline->r, pipeline->r1);
    *(pipeline->stage_flag) = 4;
    pthread_cond_signal(pipeline->cond_var);
    pthread_mutex_unlock(pipeline->lock);
    return NULL;
}

void *write_back_stage(void *args) {
    PipelineArgs *pipeline = (PipelineArgs *)args;
    pthread_mutex_lock(pipeline->lock);
    while (*(pipeline->stage_flag) != 4) {
        pthread_cond_wait(pipeline->cond_var, pipeline->lock);
    }
    write_back(pipeline->cpu, pipeline->operador, pipeline->coreIDR, pipeline->r, pipeline->resultado);
    *(pipeline->stage_flag) = 0; 
    pthread_cond_signal(pipeline->cond_var);
    pthread_mutex_unlock(pipeline->lock);
    return NULL;
}

void Pipeline(CPU *cpu, SYSTEM *system, int num_instrucoes) {
    pthread_t threads[5];
    PipelineArgs pipeline_args;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
    int stage_flag = 0;

    pipeline_args.cpu = cpu;
    pipeline_args.system = system;
    pipeline_args.lock = &lock;
    pipeline_args.cond_var = &cond_var;
    pipeline_args.stage_flag = &stage_flag;

    for (int i = 0; i < num_instrucoes; i++) {
        pthread_create(&threads[0], NULL, fetch_stage, &pipeline_args);
        pthread_create(&threads[1], NULL, decode_stage, &pipeline_args);
        pthread_create(&threads[2], NULL, execute_stage, &pipeline_args);
        pthread_create(&threads[3], NULL, memory_stage, &pipeline_args);
        pthread_create(&threads[4], NULL, write_back_stage, &pipeline_args);

        for (int j = 0; j < 5; j++) {
            pthread_join(threads[j], NULL);
        }
        cpu->pc++;
    }
}

