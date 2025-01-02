#include "system.h"

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

void Pipeline(CPU *cpu,SYSTEM *system, int i) {
    int j, r, r1, r2, operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida,resultado;
    
    for (j = 0; j < i; j++) {
        fetch(system,cpu);
        decode(cpu, &operando1, &operando2, &operador, &coreIDR, &coreIDR1, &coreIDR2, &saida, &r, &r1, &r2);
       resultado= execute(cpu, operador, operando1, operando2, r, r1, r2, coreIDR, coreIDR1, coreIDR2,resultado);
        memory_access(cpu,system, operador, &saida, &operando1, coreIDR, coreIDR1, r, r1);
        write_back(cpu,operador,coreIDR,r,resultado);
        cpu->pc++; 
    }
}


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

void exibirRegistradores(Core *core) {
	int i;
    printf("Registradores:\n");
    for (i = 0; i < NUM_REGISTRADORES; i++) {
        printf("R[%d] = %d\n", i, core->registradores[i]);
    }
}

void exibirMemoriaPrincipal(MemoriaPrincipal *memoria) {
		int i;
    printf("Memória Principal:\n");
    for (i = 0; i < MEM_SIZE; i++) {
        printf("Mem[%d] = %d\n", i, memoria->dados[i].inteiro);
    }
}

void exibirMemoriaSecundaria(MemoriaSecundaria *disco) {
		int i;
    printf("Memória Secundária:\n");
    for (i = 0; i < DISK_SIZE; i++) {
        printf("Disk[%d] = %d\n", i, disco->dados[i].inteiro);
    }
}

void escreverMemoriaPrincipal(MemoriaPrincipal *memoria) {
    int endereco, valor;
    printf("Digite o endereço de memória (0 a %d): ", MEM_SIZE - 1);
    scanf("%d", &endereco);
    if (endereco < 0 || endereco >= MEM_SIZE) {
        printf("Endereço inválido. Deve estar entre 0 e %d.\n", MEM_SIZE - 1);
        return;
    }
    printf("Digite o valor a ser escrito: ");
    scanf("%d", &valor);
    memoria->dados[endereco].inteiro = valor;
    printf("Valor %d escrito na Mem[%d].\n", valor, endereco);
}

void escreverMemoriaSecundaria(MemoriaSecundaria *disco, int endereco, int valor) {
    if (endereco >= 0 && endereco < DISK_SIZE) {
        disco->dados[endereco].inteiro = valor;
        printf("Escrevendo %d na Memória Secundária na posição %d\n", valor, endereco);
    } else {
        printf("Erro: Endereço %d fora dos limites da Memória Secundária\n", endereco);
    }
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

int ULA(CPU *cpu,int opcode, int reg1, int reg2,int r,int r1,int r2,int coreIDR,int coreIDR1,int coreIDR2) {
    int resultado;
    switch (opcode) {
        case 0: // ADD
            resultado = reg1 + reg2;
            printf("ADD REG %d (Core:%d) [%d] = REG %d (Core:%d) [%d] + REG %d (Core:%d) [%d] \n",r,coreIDR, resultado, r1,coreIDR1, reg1,r2,coreIDR2, reg2);         
           cpu->cores[coreIDR].registradores[r]=resultado;
        
            break;
        case 1: // SUB
            resultado = reg1 - reg2;
                     printf("SUB REG %d (Core:%d) [%d] = REG %d (Core:%d) [%d] - REG %d (Core:%d) [%d] \n",r,coreIDR, resultado, r1,coreIDR1, reg1,r2,coreIDR2, reg2);
            cpu->cores[coreIDR].registradores[r]=resultado;
          
            break;
        case 2: // MUL
            resultado = reg1 * reg2;
            printf("MUL REG %d (Core:%d) [%d] = REG %d (Core:%d) [%d] * REG %d (Core:%d) [%d] \n",r,coreIDR, resultado, r1,coreIDR1, reg1,r2,coreIDR2, reg2);
           cpu->cores[coreIDR].registradores[r]=resultado;
           
            break;
        case 3: // DIV
            if (reg2 != 0) {
                resultado = reg1 / reg2;
            printf("DIV REG %d (Core:%d) [%d] = REG %d (Core:%d) [%d] / REG %d (Core:%d) [%d] \n",r,coreIDR, resultado, r1,coreIDR1, reg1,r2,coreIDR2, reg2);
           cpu->cores[coreIDR].registradores[r]=resultado;
       
            } else {
                printf("Erro de divisão por zero\n");
            }
            break;
        case 4: // IF_GREATER
            if (reg1 > reg2) {
                printf("IF_GREATER -REG %d (Core:%d) [%d] é maior que REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);
               
            }else{
              printf("IF_GREATER - REG %d (Core:%d) [%d] não é maior que REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);  
            }
            break;
        case 5: // IF_LESS
            if (reg1 < reg2) {
                printf("IF_LESS - REG %d (Core:%d) [%d] é menor que REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);
              
            }else{
                  printf("IF_LESS - REG %d (Core:%d) [%d] não é menor que REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);
            }
            break;
        case 6: // IF_EQUAL
            if (reg1 == reg2) {
                printf("IF_EQUAL - REG %d (Core:%d) [%d] é igual a REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);
              
            }else{
                 printf("IF_EQUAL - REG %d (Core:%d) [%d] não é igual a REG %d (Core:%d) [%d]\n",r1,coreIDR1, reg1,r2,coreIDR2, reg2);
            }
            break;
        default:
       if (opcode != 7 && opcode != 8) {
    printf("Opcode desconhecido: %d\n", opcode);
}

            break;
    }
      return resultado;
}

void UC(CPU *cpu, int *operando1, int *operando2, int *operador,int *coreIDR,int *coreIDR1,int *coreIDR2,int *saida,int *r,int *r1,int *r2) {
    if (cpu->registradorInstrucao.Opcode == 0) {
        *operador = ADD;
    } else if (cpu->registradorInstrucao.Opcode == 1) {
        *operador = SUB;
    } else if (cpu->registradorInstrucao.Opcode == 2) {
        *operador = MUL;
    } else if (cpu->registradorInstrucao.Opcode == 3) {
        *operador = DIV;
    } else if (cpu->registradorInstrucao.Opcode == 4) {
        *operador = IF_GREATER;
    } else if (cpu->registradorInstrucao.Opcode == 5) {
        *operador = IF_LESS;
    } else if (cpu->registradorInstrucao.Opcode == 6) {
        *operador = IF_EQUAL; 
    } else if (cpu->registradorInstrucao.Opcode == 7) {
        *operador = LOAD;
    } else if (cpu->registradorInstrucao.Opcode == 8) {
        *operador = STORE;
    }
    *coreIDR = cpu->registradorInstrucao.coreIDR;
    *coreIDR1 = cpu->registradorInstrucao.coreIDR1;
    *coreIDR2 = cpu->registradorInstrucao.coreIDR2;
    *operando1 = cpu->cores[*coreIDR1].registradores[cpu->registradorInstrucao.Register1];
    *operando2 = cpu->cores[*coreIDR2].registradores[cpu->registradorInstrucao.Register2];
    *saida = cpu->cores[*coreIDR].registradores[cpu->registradorInstrucao.Register];
    *r = cpu->registradorInstrucao.Register;
    *r1 = cpu->registradorInstrucao.Register1;
    *r2 =cpu->registradorInstrucao.Register2;
 

}
 
void InstructionsMemory(CPU *cpu,SYSTEM *system,int code,int *saida, int *operando1,int coreIDR,int coreIDR1,int r,int r1){

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

