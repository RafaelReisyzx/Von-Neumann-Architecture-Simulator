# Descrição do Algoritmo
Este algoritmo implementa um simulador da arquitetura de Von Neumann, demonstrando o funcionamento de um sistema de processamento baseado no modelo tradicional de memória unificada para dados e instruções. A simulação detalha como a arquitetura executa comandos através de um ciclo de instruções, que abrange as seguintes etapas:

Busca (Fetch): O simulador recupera a próxima instrução a ser executada da memória principal.

Decodificação (Decode): A instrução é decodificada para identificar a operação e os operandos necessários.

Execução (Execute): A operação decodificada é realizada pela Unidade Lógica Aritmética (ULA) ou outro componente relevante.

Acesso à Memória (Memory Access): Se necessário, a instrução pode acessar a memória principal para leitura ou escrita de dados.

Escrita (Write-Back): O resultado da operação é escrito de volta nos registradores ou na memória.

Este ciclo de instruções permite observar como as instruções são processadas e executadas. Além disso, o simulador incorpora a utilização de memória cache, memória principal e memória secundária.

___

# Estruturas de Dados
- SYSTEM:contém os seguintes componentes:
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
 
___

# Instruções Suportadas

No sistema, você pode usar as seguintes instruções:

- ADD (Opcode 0): Soma dois valores de registradores.
- SUB (Opcode 1): Subtrai um valor de outro.
- DIV (Opcode 2): Divide um valor por outro.
- MUL (Opcode 3): Multiplica dois valores.
- IF_GREATER (Opcode 4): Condição de verificação se o valor é maior que o outro.
- IF_LESS (Opcode 5): Condição de verificação se o valor é menor que o outro.
- IF_EQUAL (Opcode 6): Condição de verificação se os valores são iguais.
- LOAD (Opcode 7): Carrega dados da memória.
- STORE (Opcode 8): Armazena dados na memória.

___

# Componentes do Sistema

 ![This is an image](https://github.com/RafaelReisyzx/Von-Neumann-Architecture-Simulator/blob/main/img/1.png)

### Registradores
Essas são pequenas unidades de armazenamento que mantêm dados temporários, como valores intermediários das operações. Modelados geralmente por um vetor ou matriz, cada posição representa um registrador específico. Isso permite fácil acesso e manipulação direta dos dados pela CPU.

### Unidade de Controle (UC)
Este componente é responsável por interpretar e decodificar as instruções do programa. Uma vez decodificadas, a UC gera sinais de controle para os outros componentes, organizando e sequenciando as operações da CPU. A UC é crucial para orquestrar o fluxo de dados e instruções no sistema, garantindo que cada componente atue na ordem correta.

### Unidade Lógica e Aritmética (ULA)
A ULA executa operações aritméticas (como soma e subtração) e lógicas (como AND, OR) necessárias para a execução de instruções. Internamente, pode-se modelá-la com funções matemáticas específicas, aplicadas aos dados carregados dos registradores, realizando as operações conforme determinado pelas instruções da CPU.

### Contador de Programa (PC)
O PC guarda o endereço da próxima instrução a ser executada, garantindo a continuidade das operações do programa. A cada nova instrução lida, o PC é incrementado, movendo-se para o próximo endereço de instrução. Esse contador pode ser implementado como uma variável simples, que é atualizada constantemente ao longo da execução.

### Conjunto de Instruções
O conjunto de instruções define as operações que a CPU pode realizar. Cada instrução possui um opcode (código que indica a operação) e operandos (valores sobre os quais a operação será realizada). Exemplos incluem:

  - LOAD: Carrega um valor da memória para um registrador.
  - STORE: Armazena um valor do registrador na memória.
  - ADD, SUB: Realizam operações aritméticas entre registradores.

### Pipeline
O pipeline permite que múltiplas instruções sejam processadas simultaneamente, aumentando a eficiência. O modelo MIPS de cinco estágios é comumente utilizado:

  - IF (Instruction Fetch): A instrução é buscada da memória e armazenada no registrador de instrução. O PC é atualizado para apontar para a próxima instrução.
  - ID (Instruction Decode): A instrução é decodificada e os operandos são carregados dos registradores.
  - EX (Execute): A ULA executa a operação definida pela instrução.
  - MEM (Memory Access): Ocorre o acesso à memória caso seja necessário (por exemplo, LOAD ou STORE).
  - WB (Write Back): O resultado é escrito no registrador de destino.

### Cache
A cache é uma memória de acesso rápido para armazenar dados frequentemente usados, reduzindo o tempo de acesso à memória principal. No simulador, a cache será:
Tabela Associativa ou Hash: Facilitando a localização de dados.
Mapeamento Direto com Substituição FIFO: A política FIFO remove o dado mais antigo quando o espaço é necessário para um novo dado.
Política de Escrita Write-back: Os dados são escritos na memória principal apenas ao serem removidos da cache.

### Memória Principal
Representada por um vetor, simula a RAM e permite operações de leitura e escrita que conectam a CPU aos dados principais do programa. Ao modelar, o vetor facilita o acesso sequencial e endereçável à memória, permitindo que a CPU obtenha dados rapidamente conforme necessário.

### Memória Secundária (Disco)
A memória secundária, ou disco, é um armazenamento não volátil, implementado como uma matriz para simular um sistema de arquivos onde dados persistem mesmo após o desligamento do sistema. Funções de leitura e escrita permitem o armazenamento a longo prazo, simulando o acesso a um disco rígido real.

### Periféricos
São representados por variáveis booleanas que indicam se um periférico está disponível ou não. Quando um processo da CPU requisita o uso de um periférico, isso gera eventos de entrada e saída (E/S). Esses eventos controlam as interações com dispositivos externos, como impressoras ou discos externos, garantindo que o simulador também modele operações além do processamento central.

___

# Funcionamento

1. Inicialização do Sistema (inicializarSistema):
Primeiramente, o sistema é configurado, inicializando as memórias (principal e cache), os registradores de cada núcleo e os periféricos. Todos os registradores e memórias começam em zero.

2. Configuração de Valores Iniciais:
O programa coloca valores em certos registradores e posições da memória para ter dados prontos para a execução. Por exemplo:a posição 100 da memória conterá o valor 20, o registrador R2 do núcleo 0 terá valor 10, e assim por diante.

3. Instruções na Memória:
Diversas instruções são configuradas na memória. Cada instrução contém informações como qual operação será realizada (adição, subtração, multiplicação, etc.), e quais registradores e núcleos serão usados.

4. Pipeline (Pipeline):
Como foi dito antes, o pipeline é o ciclo ou sequência de etapas que cada instrução segue até ser completamente executada. Esse processo ocorre para cada instrução na memória e segue os passos:

  - Busca (Fetch): A instrução é buscada na memória e colocada no registrador de instrução para ser processada.
  - Decodificação (Decode): A instrução é interpretada para identificar quais operações serão realizadas e quais registradores estão envolvidos.
  - Execução (Execute): A operação indicada é realizada (por exemplo, soma, subtração, multiplicação, etc.).
  - Acesso à Memória (Memory Access): Caso a operação envolva carregar ou salvar valores na memória, é feita uma operação de leitura ou escrita.
  - Escrita (Write Back): O resultado da operação é armazenado no registrador apropriado do núcleo.
  - Execução do Programa (Pipeline):
Cada instrução, ao ser processada pelo pipeline, incrementa o contador do programa (pc), passando para a próxima instrução até que todas sejam executadas.

5. Exibição do Menu (exibirMenu):
Por fim, o sistema exibe um menu para mostrar o conteúdo de memórias e registradores, permitindo ao usuário verificar o que aconteceu após as instruções serem processadas.

___

# Exemplo
Abaixo tem alguns exemplos e uma análise de cada um em detalhes:

![This is an image](https://github.com/RafaelReisyzx/Von-Neumann-Architecture-Simulator/blob/main/img/Screenshot_76.png)

### Valores Iniciais:

No exemplo, alguns valores são definidos previamente para os registros e a memória:

```
system.memoria.dados[100].inteiro = 20;  // Memória 100 recebe o valor 20
cpu.cores[0].registradores[2] = 10;  // Registro R2 do Core 0 recebe o valor 10
cpu.cores[0].registradores[3] = 5;   // Registro R3 do Core 0 recebe o valor 5
cpu.cores[1].registradores[1] = 30;  // Registro R1 do Core 1 recebe o valor 30
system.memoria.dados[4].inteiro = 3;  // Memória 4 recebe o valor 3
```

### Explicação das Instruções:

As instruções possuem 7 campos (inteiros), e cada campo tem um papel específico na execução das instruções no sistema.

> - Opcode (Código da Operação)
> O campo Opcode especifica o tipo de operação que será realizada. Cada valor de Opcode corresponde a uma operação específica.
    
> - Register (Registrador de Destino)
> Este campo define o registrador de destino onde o resultado da operação será armazenado. Em operações como ADD, SUB, MUL, DIV, o resultado final da operação vai para este registrador. Por exemplo, se estivermos fazendo uma operação ADD, o resultado será armazenado no registrador especificado aqui.

> - Register1 (Primeiro Operando)
>  Este campo define o primeiro operando da operação. Pode ser um registrador, valor imediato ou um valor da memória, dependendo da operação. Por exemplo, em uma instrução ADD REG1 = REG2 + REG3, Register1 pode conter o número do registrador que será somado (REG2).
   
> - Register2 (Segundo Operando)
> Este campo define o segundo operando da operação. Similar ao Register1, é outro valor que será usado na operação. Pode ser um registrador, valor imediato ou valor de memória.
Em uma instrução como MUL REG5 = REG1 * REG2, Register2 seria o registrador que armazena o segundo valor a ser multiplicado.

> - coreIDR (ID do Núcleo de Execução 1)
> Este campo define qual núcleo de processamento (core) irá executar a operação. O valor pode ser o ID de um núcleo específico (por exemplo, 0 para o primeiro núcleo, 1 para o segundo, etc.).

> - coreIDR1 (ID do Núcleo de Execução 2)
> Similar ao coreIDR, mas é um segundo valor que pode indicar outro núcleo de execução que será usado para a operação.

> - coreIDR2 (ID do Núcleo de Execução 3)
> Similar ao coreIDR e coreIDR1, mas para um terceiro núcleo, caso o sistema tenha múltiplos núcleos. Pode ser usado em instruções que exigem mais de dois núcleos ou para operações ainda mais paralelizadas.

Em muitas instruções, nem todos os campos são necessários. Quando um campo não é relevante para a operação específica, ele pode ser definido como 0. Isso acontece porque o sistema foi projetado para usar a mesma estrutura para diferentes tipos de instruções, e não todas as instruções precisam de todos os campos.

### Explicação do exemplo:
 
##### Instr1:{0, 1, 2, 3, 0, 0, 0};
 - Op = 0: A operação é ADD (adição).
 - Regs: O valor de REG 2 (Core 0) e REG 3 (Core 0) serão somados, e o resultado será armazenado em REG 1 (Core 0).
 - Operação: REG 2 (10) + REG 3 (5) → 15.
 - Resultado: REG 1 (Core 0) agora terá o valor 15.

##### Instr2:{7, 4, 4, 0, 0, 0, 0};
 - Op = 7: A operação é LOAD (carregar valor de memória para o registrador).
 - Regs: O valor da posição de memória 4 (que é 3) será carregado para REG 4 (Core 0).
 - Resultado: REG 4 (Core 0) agora terá o valor 3.
   
##### Instr3:{3, 5, 1, 4, 1, 1, 0};
 - Op = 3: A operação é MUL (multiplicação).
 - Regs: O valor de REG 1 (Core 1) será multiplicado pelo valor de REG 4 (Core 0), e o resultado será armazenado em REG 5 (Core 1).
 - Operação: REG 1 (30) * REG 4 (3) → 90.
 - Resultado: REG 5 (Core 1) agora terá o valor 90.
   
##### Instr4:{8, 1, 5, 0, 0, 1, 0};
 - Op = 8: A operação é STORE (armazenar valor de um registrador na memória).
 - Regs: O valor de REG 5 (Core 1) será armazenado na posição de memória 1.
 -Resultado: MEM 1 agora terá o valor 90.

##### Instr5:{2, 6, 5, 4, 1, 1, 0};
 - Op = 2: A operação é DIV (divisão).
 - Regs: O valor de REG 5 (Core 1) será dividido pelo valor de REG 4 (Core 0), e o resultado será armazenado em REG 6 (Core 1).
 - Operação: REG 5 (90) / REG 4 (3) → 30.
 - Resultado: REG 6 (Core 1) agora terá o valor 30.

### Resultados Finais:
Após a execução das instruções, os valores nos registradores e na memória serão os seguintes:

##### Registradores:

 - REG 1 (Core 0): 15 (resultado da soma entre REG 2 e REG 3)
 - REG 2 (Core 0): 10 (valor original)
 - REG 3 (Core 0): 5 (valor original)
 - REG 4 (Core 0): 3 (valor carregado da memória 4)
 - REG 5 (Core 1): 90 (resultado da multiplicação de REG 1 e REG 4)
 - REG 6 (Core 1): 30 (resultado da divisão de REG 5 por REG 4)
   
##### Memória:

 - MEM 1: 90 (valor armazenado de REG 5)
 - MEM 4: 3 (valor original)
 - MEM 100: 20 (valor original)

___

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

___

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

___

## Contato
Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato comigo pelo e-mail: [rafaelreismrg@gmail.com](mailto:rafaelreismrg@gmail.com).
