#include "ula.h"

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
