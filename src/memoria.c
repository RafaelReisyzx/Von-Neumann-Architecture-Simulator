#include "memoria.h"

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


