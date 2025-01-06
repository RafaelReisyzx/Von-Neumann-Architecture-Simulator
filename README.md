# Descrição do Algoritmo
Este algoritmo implementa um simulador da arquitetura de Von Neumann, demonstrando o funcionamento de um sistema de processamento baseado no modelo tradicional de memória unificada para dados e instruções. A simulação detalha como a arquitetura executa comandos através de um ciclo de instruções, que abrange as seguintes etapas:

Busca (Fetch): O simulador recupera a próxima instrução a ser executada da memória principal.

Decodificação (Decode): A instrução é decodificada para identificar a operação e os operandos necessários.

Execução (Execute): A operação decodificada é realizada pela Unidade Lógica Aritmética (ULA) ou outro componente relevante.

Acesso à Memória (Memory Access): Se necessário, a instrução pode acessar a memória principal para leitura ou escrita de dados.

Escrita (Write-Back): O resultado da operação é escrito de volta nos registradores ou na memória.

Este ciclo de instruções permite observar como as instruções são processadas e executadas. Além disso, o simulador incorpora a utilização de memória cache, memória principal e memória secundária.
 
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

1. Inicialização do Sistema
A primeira etapa consiste na configuração inicial do sistema, onde as memórias (principal e cache), os registradores de cada núcleo e os periféricos são devidamente configurados. No momento da inicialização, todos os registradores e memórias são zerados para garantir um estado limpo antes da execução do programa.

2. Configuração de Valores Iniciais
Após a inicialização, o sistema configura valores predefinidos em registradores específicos e em certas posições da memória. Por exemplo:

A posição 100 da memória pode ser configurada com o valor 20.
O registrador R2 do núcleo 0 pode ser atribuído o valor 10, entre outros.

3. Carregamento e Execução de Instruções
O programa carrega uma sequência de instruções na memória. Cada instrução contém informações essenciais sobre a operação a ser realizada (como soma, subtração, multiplicação, etc.) e os registradores que participarão da operação. 

4. Pipeline de Execução
O pipeline de execução é um processo dividido em várias etapas, garantindo que as instruções sejam executadas de forma eficiente e sequencial. Cada ciclo de instrução passa por uma série de estágios para sua execução:

 - Busca (Fetch): A instrução é buscada na memória e armazenada no registrador de instrução, para ser processada na sequência.
 - Decodificação (Decode): A instrução é decodificada, determinando qual operação será realizada e quais registradores e núcleos são necessários para isso.
 - Execução (Execute): A operação é efetivamente realizada. Dependendo do tipo de instrução, pode ser uma soma, subtração ou outra operação aritmética.
 - Acesso à Memória (Memory Access): Caso a instrução envolva acessar a memória (para ler ou escrever dados), a operação de leitura ou escrita é realizada neste estágio.
 - Escrita de Resultado (Write Back): O resultado da operação é gravado no registrador de destino, finalizando a execução da instrução.

5. Execução do Programa
Após o processamento das instruções, o contador do programa (PC - Program Counter) é incrementado a cada nova instrução que é buscada e executada, avançando até que todas as instruções tenham sido processadas. Durante essa execução, os dados nos registradores e na memória vão sendo alterados conforme as operações são realizadas.

6. Exibição do Estado do Sistema
Após a execução das instruções, o sistema exibe um menu para permitir que o usuário visualize o estado atual dos registradores e da memória. Esse menu oferece uma forma de verificação dos resultados obtidos após a execução do programa, fornecendo feedback sobre o impacto das instruções no sistema.
___

# Exemplo
Abaixo tem alguns exemplos e uma análise de cada um em detalhes:

![This is an image](https://github.com/RafaelReisyzx/Von-Neumann-Architecture-Simulator/blob/main/img/Screenshot_76.png)

### Valores Iniciais:

No exemplo, alguns valores são definidos previamente para os registradores e a memória:

```
Registradores:
2 10
3 5
33 30
Memória Principal:
100 20
4 3
Memória Secundaria:
200 15
```


### Explicação do exemplo:
 
1. ADD 1 2 3
A instrução ADD soma os valores dos registradores R2 e R3 e armazena o resultado no registrador R1.

 - R2 = 10
 - R3 = 5
 - A operação é: R1 = R2 + R3 = 10 + 5 = 15

Novo estado dos registradores:

 - R1 = 15

2. LOAD 4 4 0
A instrução LOAD carrega um valor da memória para o registrador especificado. Aqui, a memória na posição 4 é carregada no registrador R4.

 - Mem[4] = 3
 - A operação é: R4 = Mem[4] = 3

Novo estado dos registradores:

 - R4 = 3

3. MUL 5 1 4
A instrução MUL multiplica os valores dos registradores R1 e R4 e armazena o resultado no registrador R5.

 - R1 = 15
 - R4 = 3
 - A operação é: R5 = R1 * R4 = 15 * 3 = 45

Novo estado dos registradores:

 - R5 = 45

4. STORE 1 5 0
A instrução STORE armazena o valor do registrador R5 na posição 1 da memória principal.

 - R5 = 45
 - A operação é: Mem[1] = R5 = 45

Novo estado da memória principal:

 - Mem[1] = 45

5. SUB 6 5 4
A instrução SUB subtrai o valor do registrador R4 do valor do registrador R5 e armazena o resultado no registrador R6.

 - R5 = 45
 - R4 = 3
 - A operação é: R6 = R5 - R4 = 45 - 3 = 42

Novo estado dos registradores:

 - R6 = 42


6. IF_EQUAL 0 1 2
A instrução IF_EQUAL verifica se os valores nos registradores R1 e R2 são iguais. Se forem, a execução do programa será condicionada a isso. Como R1 é 15 e R2 é 10, os valores não são iguais, então o salto condicional não ocorre.

 - R1 = 15
 - R2 = 10
Como R1 != R2, a instrução IF_EQUAL não causa mudança no fluxo de execução e o programa continua normalmente.

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
Telegram: [Rafael Reis](https://t.me/yyy6666666yyy).
