#include "cpu.h"

void exibirRegistradores(Core *core) {
	int i;
    printf("Registradores:\n");
    for (i = 0; i < NUM_REGISTRADORES; i++) {
        printf("R[%d] = %d\n", i, core->registradores[i]);
    }
}
