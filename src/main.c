#include "system.h"

int main() {
    SYSTEM system;
    inicializarSistema(&system);
    int i=0;

        system.memoria.dados[100].inteiro = 20;
        system.cores[0].registradores[2] = 10;  // Core 0, R2 = 10
        system.cores[0].registradores[3] = 5;   // Core 0, R3 = 5
        system.cores[1].registradores[1] = 30;  // Core 1, R1 = 30
        system.memoria.dados[4].inteiro = 3;


     Instrucoes instr1 = {0, 1, 2, 3, 0, 0, 0};
         system.memoria.dados[i].instrucao=instr1;
          i++;
        Instrucoes instr2 = {7, 4, 4, 0, 0, 0, 0};
          system.memoria.dados[i].instrucao=instr2;
            i++;
       Instrucoes instr3 = {3, 5, 1, 4, 1, 1, 0};
         system.memoria.dados[i].instrucao=instr3;
        i++;
        Instrucoes instr4 = {8, 1, 5 , 0, 0, 1, 0};
          system.memoria.dados[i].instrucao=instr4;
            i++;
       Instrucoes instr5 = {2, 6, 5, 4, 1, 1, 0}; 
         system.memoria.dados[i].instrucao=instr5;
           i++;

 

    Pipeline(&system,i);  

    exibirMenu(&system); 
    return 0;
}
