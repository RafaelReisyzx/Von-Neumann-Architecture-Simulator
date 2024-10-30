# Descrição do Algoritmo
Este projeto implementa um sistema de processamento simples, simulado através de um modelo de arquitetura que utiliza múltiplos núcleos (cores) e uma estrutura de memória organizada. O sistema simula operações básicas de um processador, incluindo busca, decodificação, execução e acesso à memória.

# Estruturas de Dados
- SYSTEM:representa o estado do sistema e contém os seguintes componentes:
  - cores: Um array de núcleos que contém registradores para cada core.
  - pc: O contador de programa, que indica a posição atual na memória de instruções.
  - cache: A estrutura de cache que armazena dados e tags.
  - memoria: A memória principal do sistema.
  - disco: A memória secundária (simulando um disco).
  - periferico: Um array de dispositivos periféricos.
  
- Instruções:A estrutura Instrucoes define uma instrução com os seguintes campos:
  - Opcode: O código da operação a ser executada.
  - Register, Register1, Register2: Registradores envolvidos na operação.
  - coreIDR, coreIDR1, coreIDR2: Identificadores de cores para operações paralelas.

# Definições de Operações
Utilizei as seguintes constantes para representar operações básicas e condições no código:
```
#define ADD 0          // Adição
#define SUB 1          // Subtração
#define DIV 2          // Divisão
#define MUL 3          // Multiplicação
#define IF_GREATER 4   // Se maior
#define IF_LESS 5      // Se menor
#define IF_EQUAL 6     // Se igual
#define LOAD 7         // Carregar valor
#define STORE 8        // Armazenar valor
```
# Funcionamento


# Funções

### `fetch(SYSTEM system)`
Objetivo: Carregar a instrução que está no endereço de memória indicado pelo contador de programa (pc) para o registrador de instrução.

```
void fetch(SYSTEM *system) {
    system->registradorInstrucao = system->memoria.dados[system->pc].instrucao;
}
```
Explicação:

1. system->registradorInstrucao: A instrução atual que será executada é armazenada neste registrador.
2. system->memoria.dados[system->pc].instrucao: A instrução é lida da memória na posição indicada pelo contador de programa (pc). O contador pc aponta para a próxima instrução a ser executada.

### `decode(SYSTEM *system, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int r1, int r2)`
Objetivo: Decodificar a instrução atual e extrair os operandos e outros parâmetros necessários para a execução.

```
void decode(SYSTEM *system, int *operando1, int *operando2, int *operador, int *coreIDR, int *coreIDR1, int *coreIDR2, int *saida, int *r, int *r1, int *r2) {
    UC(system, operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida, r, r1, r2);
}
```
Explicação:

1. A função UC (Unidade de Controle) é chamada para preencher os parâmetros passados por referência (operando1, operando2, etc.) com os valores extraídos da instrução armazenada no registrador de instrução.
2. Os parâmetros são utilizados na fase de execução, permitindo que o sistema saiba quais registros usar e qual operação realizar.
  
### `int execute(SYSTEM system, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2, int resultado)`
Objetivo: Executar a operação especificada pela instrução.

```
int execute(SYSTEM *system, int operador, int operando1, int operando2, int r, int r1, int r2, int coreIDR, int coreIDR1, int coreIDR2,int resultado) {
    resultado=ULA(system, operador, operando1, operando2, r, r1, r2, coreIDR, coreIDR1, coreIDR2);
    return resultado;
}
```

1. resultado = ULA(...): Chama a Unidade Lógica Aritmética (ULA) para realizar a operação aritmética ou lógica correspondente ao operador (como adição, subtração, etc.) usando os operandos fornecidos (operando1, operando2).
2. A função retorna o resultado da operação, que pode ser armazenado em um registrador ou utilizado em um próximo passo.

### `void memory_access(SYSTEM *system, int operador, int saida, int operando1, int coreIDR, int coreIDR1, int r, int r1)`
Objetivo: Acessar a memória com base na operação (LOAD ou STORE) especificada.

```
void memory_access(SYSTEM *system, int operador, int *saida, int *operando1, int coreIDR, int coreIDR1, int r, int r1) {
    if (operador == LOAD) {
        *saida = system->memoria.dados[r].inteiro;
        InstructionsMemory(system, LOAD, saida, operando1, coreIDR, coreIDR1, r, r1);
    } else if (operador == STORE) {
        *saida = system->memoria.dados[r1].inteiro;
        InstructionsMemory(system, STORE, saida, operando1, coreIDR, coreIDR1, r, r1);
    }
}
```
Explicação:

1. A função verifica se o operador é um LOAD ou STORE.
2. LOAD: Se for um LOAD, o valor do endereço de memória (r) é lido e armazenado em saida.
3. STORE: Se for um STORE, o valor de r1 é lido e armazenado em saida.
4. Ambas as operações chamam InstructionsMemory, que provavelmente gerencia a lógica de execução da instrução na memória.

### `void write_back(SYSTEM system,int operador,int coreIDR,int r,int resultado)`
Objetivo: Escrever o resultado da execução de volta nos registradores apropriados.

```
void write_back(SYSTEM *system,int operador,int coreIDR,int r,int resultado) {
    if (operador != LOAD && operador != STORE && operador != IF_EQUAL && operador != IF_LESS) {   
        system->cores[coreIDR].registradores[r] = resultado;
    }
}
```
Explicação:

1. A função verifica se o operador não é um LOAD, STORE, ou instruções de comparação.
2. Se não for, o resultado da execução é armazenado no registrador r do núcleo identificado por coreIDR.

### `void Pipeline(SYSTEM system, int i)`
Objetivo: Implementar a execução em pipeline, permitindo que várias instruções sejam processadas simultaneamente.

```
void Pipeline(SYSTEM *system, int i) {
    int j, r, r1, r2, operando1, operando2, operador, coreIDR, coreIDR1, coreIDR2, saida, resultado;
    
    for (j = 0; j < i; j++) {
        fetch(system);
        decode(system, &operando1, &operando2, &operador, &coreIDR, &coreIDR1, &coreIDR2, &saida, &r, &r1, &r2);
        resultado = execute(system, operador, operando1, operando2, r, r1, r2, coreIDR, coreIDR1, coreIDR2, resultado);
        memory_access(system, operador, &saida, &operando1, coreIDR, coreIDR1, r, r1);
        write_back(system, operador, coreIDR, r, resultado);
        system->pc++; 
    }
}
```
Explicação:

1. Um loop é executado i vezes, onde cada iteração processa uma instrução.
2. fetch: Carrega a próxima instrução.
3. decode: Decodifica a instrução e obtém os operandos e operadores necessários.
4. execute: Executa a operação e obtém o resultado.
5. memory_access: Acessa a memória se necessário, dependendo da operação.
6. write_back: Armazena o resultado de volta no registrador apropriado.
7. Finalmente, o contador de programa (pc) é incrementado para apontar para a próxima instrução.

### `void inicializarSistema(SYSTEM system)`
Objetivo: Inicializar o sistema, configurando os registradores, memória e periféricos.

```
void inicializarSistema(SYSTEM *system) {
    int i, j;
    for (i = 0; i < NUM_CORES; i++) {
        for (j = 0; j < NUM_REGISTRADORES; j++) {
            system->cores[i].registradores[j] = 0; 
        }
    }
    system->pc = 0;

    system->cache.fifo_index = 0;
    for (i = 0; i < CACHE_SIZE; i++) {
        system->cache.dados[i] = 0;
        system->cache.tags[i] = -1; 
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
}
```
Explicação:

1. Inicializa os registradores de cada núcleo a zero.
2. O contador de programa (pc) é configurado para zero.
3. A cache é inicializada, com índices e dados limpos.
4. A memória e o disco são zerados, garantindo que todas as entradas estejam em um estado inicial.


# Compilação e Execução

A pasta do repositorio possui um arquivo Makefile que contém as instruções para compilar e executar. Para usar essas instruções, você pode usar o terminal do seu sistema
operacional e navegar até o diretório raiz do projeto.

Existem três comandos principais que você pode usar no Makefile:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Em resumo, para executar o programa, você precisa navegar até o diretório raiz do projeto e executar o comando make para compilar o programa e, em seguida, 
executar o comando make run para executá-lo.Se você precisar limpar a compilação anterior, pode usar o comando make clean antes de executar a compilação.
