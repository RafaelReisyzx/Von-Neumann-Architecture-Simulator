#include "system.h"

void inicializarSistema(CPU *cpu, SYSTEM *system) {
    int i, j;
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

void exibirInformacoes(CPU *cpu, SYSTEM *system) {
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

int opcodeFromString(const char* instrucao) {
    if (strcmp(instrucao, "ADD") == 0) return 0;
    if (strcmp(instrucao, "SUB") == 0) return 1;
    if (strcmp(instrucao, "DIV") == 0) return 2;
    if (strcmp(instrucao, "MUL") == 0) return 3;
    if (strcmp(instrucao, "IF_GREATER") == 0) return 4;
    if (strcmp(instrucao, "IF_LESS") == 0) return 5;
    if (strcmp(instrucao, "IF_EQUAL") == 0) return 6;
    if (strcmp(instrucao, "LOAD") == 0) return 7;
    if (strcmp(instrucao, "STORE") == 0) return 8;
    return -1; 
}

void carregarInstrucoesDeArquivo(const char* caminho, SYSTEM* system, int* contador) {
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de instruções");
        exit(EXIT_FAILURE);
    }

    char linha[MAX_LINHA];
    int i = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char instrucao[20];
        int reg, reg1, reg2;
        if (sscanf(linha, "%s %d %d %d", instrucao, &reg, &reg1, &reg2) != 4) {
            fprintf(stderr, "Formato inválido na linha: %s", linha);
            continue;
        }

        int opcode = opcodeFromString(instrucao);
        if (opcode == -1) {
            fprintf(stderr, "Instrução desconhecida: %s\n", instrucao);
            continue;
        }

        Instrucoes novaInstrucao = {opcode, reg, reg1, reg2, 0, 0, 0};
        system->memoria.dados[i].instrucao = novaInstrucao;
        i++;
    }

    fclose(arquivo);
    *contador = i; 
}



void carregarValoresIniciais(const char* caminho, CPU* cpu, SYSTEM* system) {
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[MAX_LINHA];
    int modo = 0; // 0: nenhum, 1: Registradores, 2: Memória Principal, 3: Memória Secundária

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Registradores:")) {
            modo = 1;
        } else if (strstr(linha, "Memória Principal:")) {
            modo = 2;
        } else if (strstr(linha, "Memória Secundária:")) {
            modo = 3;
        } else if (isdigit(linha[0])) {
            int posicao, valor;
            sscanf(linha, "%d %d", &posicao, &valor);

            if (modo == 1) { 
                int regID = posicao % NUM_REGISTRADORES;
                int coreID = posicao / NUM_REGISTRADORES;
                if (coreID < NUM_CORES) {
                    cpu->cores[coreID].registradores[regID] = valor;
                }
            } else if (modo == 2) { 
                if (posicao < MEM_SIZE) {
                    system->memoria.dados[posicao].inteiro = valor;
                }
            } else if (modo == 3) { 
                if (posicao < DISK_SIZE) {
                    system->disco.dados[posicao].inteiro = valor;
                }
            }
        }
    }

    fclose(arquivo);
}

