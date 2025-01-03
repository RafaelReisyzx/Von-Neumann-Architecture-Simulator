#include "system.h"

void inicializarSistema(CPU *cpu,SYSTEM *system) {
	int i,j;
    for (i = 0; i < NUM_CORES; i++) {
        for (j = 0; j < NUM_REGISTRADORES; j++) {
            cpu->cores[i].registradores[j] = 0; 
        }
    }
    cpu->pc = 0;

    cpu->cache.fifo_index = 0;
    for (i = 0; i < CACHE_SIZE; i++) {
        cpu->cache.dados[i] = 0;
        cpu->cache.tags[i] = -1; 
    }

    for (i = 0; i < MEM_SIZE; i++) {
        system->memoria.dados[i].inteiro = 0;
        system->memoria.dados[i].instrucao.Register1 = 0;
        system->memoria.dados[i].instrucao.Register2 = 0;
        system->memoria.dados[i].instrucao.Register = 0;
        system->memoria.dados[i].instrucao.Opcode = 0;
        system->memoria.dados[i].instrucao.coreIDR = 0;
        system->memoria.dados[i].instrucao.coreIDR1 = 0;
        system->memoria.dados[i].instrucao.coreIDR2 = 0;
       

    }

    for (i = 0; i < DISK_SIZE; i++) {
        system->disco.dados[i].inteiro = 0;
        system->disco.dados[i].instrucao.Register1 = 0;
        system->disco.dados[i].instrucao.Register2 = 0;
        system->disco.dados[i].instrucao.Register = 0;
        system->disco.dados[i].instrucao.Opcode = 0;
        system->disco.dados[i].instrucao.coreIDR = 0;
        system->disco.dados[i].instrucao.coreIDR1 = 0;
        system->disco.dados[i].instrucao.coreIDR2 = 0;

    }
    system->periferico[0].nome = "Teclado";
    system->periferico[0].disponivel = true;

    system->periferico[1].nome = "Impressora";
    system->periferico[1].disponivel = true;

    system->periferico[2].nome = "Monitor";
    system->periferico[2].disponivel = true;

    system->periferico[3].nome = "Mouse";
    system->periferico[3].disponivel = true;
}

void exibirInformacoes(CPU *cpu,SYSTEM *system) {
    int i;
 
                for (i = 0; i < NUM_CORES; i++) {
                    printf("\nCore %d:\n", i);
                    exibirRegistradores(&cpu->cores[i]);
                }
               
                exibirMemoriaPrincipal(&system->memoria);
    
                exibirMemoriaSecundaria(&system->disco);
   
}

void InstructionsMemory(CPU *cpu,SYSTEM *system,int code,int *saida, int *operando1,int coreIDR,int coreIDR1,int r,int r1){
int STORE=8;
int LOAD=7;
 if (code == LOAD) {
     
        cpu->cores[coreIDR].registradores[r] = *saida;   
        printf("LOAD REG %d (Core:%d) [%d] = MEM %d [%d] \n",r,coreIDR1, *operando1,r1, *saida);
     *operando1=*saida;
    } else if (code == STORE) {

        system->memoria.dados[r].inteiro = *operando1;   
        printf("STORE MEM %d [%d] = REG %d (Core:%d) [%d] \n",r, *saida,r1,coreIDR, *operando1);
       *saida=*operando1;
    }
}
