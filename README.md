# PSE em Ação

## Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

**AEP — Engenharia de Software | 2º semestre**

---

## 1. Objetivo

A IntegraPSE precisava de uma forma simples de registrar e acompanhar as ações coletivas do Programa Saúde na Escola (PSE). Antes, a equipe tinha dificuldade para localizar as ações programadas, saber quais já tinham sido concluídas, identificar os cancelamentos e somar quantos participantes foram atendidos em cada escola.

O **PSE em Ação** é um programa de console desenvolvido em linguagem C. Com ele, é possível:

- Cadastrar ações com validação dos dados;
- Listar e pesquisar ações por código, escola ou tema;
- Atualizar a situação de cada ação (planejada, realizada ou cancelada);
- Registrar quantas pessoas participaram efetivamente;
- Gerar um resumo com totais, percentual de participação e números consolidados por escola.

Os dados ficam salvos no arquivo `acoes.txt`, portanto não são perdidos quando o programa é fechado.

> O sistema é uma ferramenta de apoio à organização. Ele não substitui os profissionais de saúde e educação.

---

## 2. Como compilar e executar

### 2.1 Dev-C++ ou Code::Blocks (Windows)

1. Abra o arquivo `pse.c`.
2. Clique em **Compilar e Executar** (F11 no Dev-C++).

### 2.2 Terminal com GCC (Windows / MinGW)

Compile o programa:

```bash
gcc -Wall -std=c99 -o pse.exe pse.c
```

Execute:

```bash
pse.exe
```

O arquivo `acoes.txt` é criado automaticamente na mesma pasta do executável quando a primeira ação é cadastrada.

> O programa usa `system("cls")` para limpar a tela, um comando do Windows. Para executar no Linux ou no macOS, troque `cls` por `clear`.

---

## 3. Opções do menu

Ao iniciar, o programa apresenta o menu:

```text
======= BEM-VINDO AO PSE EM ACAO =======

Acoes cadastradas: 0 de 100

Escolha uma opcao

    1 - Cadastro
    2 - Lista de acoes
    3 - Pesquisa
    4 - Atualizacao de situacao
    5 - Registro de participantes
    6 - Geracao de resumo
    7 - Sair do programa

R:
```

### 3.1 Descrição das opções

| Opção | O que faz | Validações |
|---|---|---|
| **1 – Cadastro** | Solicita código, escola, tema, data prevista, público-alvo, responsável e quantidade prevista. A ação começa como *Planejada*. | Código único (de 1 a 999999), sem campos vazios, data real no formato `dd/mm/aaaa` e quantidade maior ou igual a 1. Digite `0` no código para cancelar. Não aceita novos cadastros quando o limite de 100 ações é atingido. |
| **2 – Lista de ações** | Mostra uma tabela com todas as ações: código, escola, tema, data, situação, participantes previstos e efetivos. | Avisa quando não há ações cadastradas. |
| **3 – Pesquisa** | Busca por **código** (valor exato), **escola** ou **tema** (basta parte do nome, sem diferenciar maiúsculas de minúsculas). Ao final, pergunta se o usuário deseja fazer outra pesquisa. | O critério precisa ser 1, 2 ou 3. Avisa quando nada é encontrado. A resposta precisa ser S ou N. |
| **4 – Atualização de situação** | Mostra a situação atual da ação e permite alterá-la para Planejada, Realizada ou Cancelada. | Avisa se o código não existe e só aceita as opções de 1 a 3. Se uma ação *Realizada* mudar de situação, o registro de participantes dela é apagado. |
| **5 – Registro de participantes** | Registra a quantidade efetiva de participantes. Se já houver um valor registrado, ele é substituído. | A ação precisa existir e estar como *Realizada*. A quantidade não pode ser negativa. |
| **6 – Geração de resumo** | Mostra quantas ações há em cada situação, o total previsto, o total registrado, o percentual de participação e uma tabela por escola. | Avisa quando não há dados. |
| **7 – Sair** | Encerra o programa. Os dados já foram salvos a cada alteração. | — |

Todas as entradas numéricas rejeitam letras e valores fora do intervalo permitido, solicitando novamente o valor. Nenhuma entrada incorreta trava o programa.

---

## 4. Exemplos de uso

### 4.1 Cadastro com erros corrigidos na hora

```text
============== CADASTRO DE ACAO ==============

Codigo da acao (0 para cancelar): 10

Escola: EM Joao Paulo

Tema: Saude Bucal

Data prevista (dd/mm/aaaa): 31/02/2026

Data invalida. Use o formato dd/mm/aaaa (ex: 15/03/2026).

Data prevista (dd/mm/aaaa): 15/03/2026

Publico-alvo: Alunos do 5 ano

Responsavel: Enf. Maria

Quantidade prevista de participantes: -5

O valor nao pode ser negativo.

Quantidade prevista de participantes: 40

Acao 10 cadastrada com sucesso! Situacao inicial: Planejada.
```

### 4.2 Código duplicado

```text
Codigo da acao (0 para cancelar): 10

O codigo 10 ja esta cadastrado. Informe outro.
```

### 4.3 Lista de ações

```text
Cod    Escola               Tema             Data       Situacao    Prev  Efet
------------------------------------------------------------------------------
10     EM Joao Paulo        Saude Bucal      15/03/2026 Realizada     40    35
11     em joao paulo        Vacinacao        20/04/2026 Planejada     30     -
12     EE Centro            Alimentacao saud 10/05/2026 Cancelada     50     -
```

### 4.4 Pesquisa por escola (parte do nome)

```text
Criterio escolhido = Escola / Registro escolhido = joao

...

2 resultado(s) encontrado(s).
```

### 4.5 Registro de participantes em ação que ainda não aconteceu

```text
A acao esta como Planejada. Ela precisa estar Realizada para receber o registro de participantes.
```

### 4.6 Resumo

```text
Acoes por situacao

    Planejadas: 1
    Realizadas: 1
    Canceladas: 1
    Total: 3

Participantes

    Previstos (planejadas + realizadas): 70
    Previstos nas acoes realizadas com registro: 40
    Registrados: 35
    Percentual de participacao: 87.5%

Por escola

Escola                          Acoes Previstos Registrados
EM Joao Paulo                       2        70          35
EE Centro                           1         0           0
```

---

## 5. Organização do código

O programa utiliza apenas as bibliotecas `stdio.h` e `stdlib.h`.

| Parte | Funções / elementos | Papel |
|---|---|---|
| **Estrutura de dados** | `struct Acao`, vetor `acoes[MAX_ACOES]`, `totalAcoes` | Guarda as ações na memória. |
| **Entrada e validação** | `lerLinha`, `lerTexto`, `lerInteiro`, `dataValida` | Leem e validam tudo o que o usuário digita. Aplicam as regras RN01 a RN04. |
| **Funções de texto** | `tamanhoTexto`, `temCaractere`, `minusculo`, `textosIguais`, `contemTexto` | Foram feitas manualmente para substituir `string.h` e `ctype.h`. |
| **Apoio** | `buscarPorCodigo`, `nomeSituacao`, `mostrarAcao`, `pausar` | Funções reaproveitadas por várias opções do menu. |
| **Arquivo** | `carregarDados`, `salvarDados` | Leem e gravam o arquivo `acoes.txt`. |
| **Funcionalidades** | `menu`, `cadastro`, `lista`, `pesquisa`, `atualSituacao`, `regParticip`, `geraResumo` | Há uma função para cada caso de uso do diagrama. |

### 5.1 Formato do arquivo `acoes.txt`

Cada linha do arquivo segue esta estrutura:

```text
codigo;escola;tema;data;publico;responsavel;qtdPrevista;qtdEfetiva;situacao
```

Exemplo:

```text
10;EM Joao Paulo;Saude Bucal;15/03/2026;Alunos do 5 ano;Enf. Maria;40;35;2
```

Na situação:

- `1` significa **Planejada**;
- `2` significa **Realizada**;
- `3` significa **Cancelada**.

Uma `qtdEfetiva` igual a `-1` indica que os participantes ainda não foram registrados.

---

## 6. Testes realizados

Todos os testes foram executados com GCC 16 usando `-Wall -Wextra -std=c99 -pedantic`. A compilação terminou sem erros e sem avisos.

| Nº | Caso de teste | Entrada | Resultado esperado | Resultado |
|---:|---|---|---|:---:|
| 1 | Opção de menu inválida | `9` | Valor inválido | OK |
| 2 | Letra no lugar de número | `abc` | Solicita números inteiros | OK |
| 3 | Cadastro válido | Ação 10 completa | Cadastro realizado | OK |
| 4 | Código duplicado | Código `10` novamente | Informa duplicidade | OK |
| 5 | Data inexistente | `31/02/2026` | Informa data inválida | OK |
| 6 | Quantidade negativa | `-5` | Recusa valor negativo | OK |
| 7 | Lista vazia | Opção 2 sem dados | Informa ausência de ações | OK |
| 8 | Pesquisa por tema | `saude` | Encontra Saúde Bucal | OK |
| 9 | Pesquisa sem resultado | Código `99` | Informa que não encontrou | OK |
| 10 | Critério inválido | `5` | Solicita opção entre 1 e 3 | OK |
| 11 | Atualizar código inexistente | `99` | Informa ação não encontrada | OK |
| 12 | Participantes em ação planejada | Ação 11 | Recusa o registro | OK |
| 13 | Participantes em ação realizada | Ação 10, valor `35` | Registra participantes | OK |
| 14 | Resumo sem dados | Opção 6 sem dados | Informa ausência de dados | OK |
| 15 | Resumo com dados | 3 ações | Contagens corretas e 87,5% | OK |
| 16 | Limite de armazenamento | 100 ações | Informa limite atingido | OK |
| 17 | Persistência | Fechar e abrir programa | Recupera ações do arquivo | OK |

---

## 7. Ajustes nos requisitos durante a implementação

Durante a implementação, foram realizados os seguintes ajustes:

- **Busca por código exata, busca por escola e tema parcial:** código é um identificador, então só faz sentido buscar o valor exato. Já em escola e tema o usuário nem sempre lembra o nome completo.
- **Percentual de participação:** o cálculo usa os participantes registrados divididos pelos previstos das ações *realizadas que já têm registro*. Ações planejadas ainda não aconteceram e entrariam na conta como 0%. Ações canceladas não entram no total previsto.
- **Consolidado por escola no resumo:** foi incluído porque a questão norteadora cita a necessidade de consolidar a quantidade de participantes atendidos em cada escola.
- **Saída de uma ação da situação Realizada:** quando isso acontece, o registro de participantes é apagado, para manter a regra de negócio do caso de uso *Registrar participantes*.
- **Um único arquivo de dados:** a versão inicial lia três arquivos separados (`critCodigo.txt`, `critEscola.txt` e `critTema.txt`). Esses arquivos não tinham ligação com o cadastro, então a pesquisa nunca encontraria uma ação recém-cadastrada.

---

## 8. Considerações finais

### 8.1 Resultados

As seis funcionalidades mínimas e a validação de dados do diagrama de casos de uso foram implementadas e testadas. O programa trata registro inexistente, código duplicado, limite de armazenamento e entradas inválidas sem travar.

### 8.2 Limitações

- Máximo de 100 ações, definido em `MAX_ACOES`.
- Interface apenas em modo texto, sem acentuação, para evitar problemas de codificação no console do Windows.
- Não é possível editar outros campos de uma ação nem excluir ações.
- Não há controle de usuários nem de acesso.
- Escolas com grafias diferentes, como "EM Joao Paulo" e "E.M. João Paulo", são tratadas como escolas distintas.

### 8.3 Aprendizados

Os principais aprendizados foram:

- Separar o código em funções, uma por caso de uso;
- Implementar manualmente as funções de texto sem depender de `string.h`;
- Usar `struct` e vetores para organizar os dados;
- Ler a entrada com `fgets` em vez de `scanf`;
- Gravar e ler arquivos;
- Transformar regras de negócio em validações no código.

### 8.4 Possíveis melhorias

- Editar e excluir ações;
- Pesquisar por período de datas;
- Usar alocação dinâmica (`malloc` e `realloc`) para remover o limite fixo;
- Exportar o resumo para CSV;
- Ter um cadastro de escolas, para evitar grafias diferentes;
- Oferecer uma interface gráfica ou web.

---
