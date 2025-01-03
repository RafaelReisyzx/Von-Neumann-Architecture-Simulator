#include "system.h"
#include "cpu.h"
#include "pipeline.h"

int main() {
    SYSTEM system;
    CPU cpu;
    inicializarSistema(&cpu, &system);

    carregarValoresIniciais("dataset/valores_iniciais.txt", &cpu, &system);

    int numInstrucoes = 0;
    carregarInstrucoesDeArquivo("dataset/instruções.txt", &system, &numInstrucoes);

    Pipeline(&cpu, &system, numInstrucoes);
    exibirInformacoes(&cpu, &system);

    return 0;
}

