# Requisitos do Sistema

## Requisitos Funcionais

### RF01 – Cadastrar ação
O sistema deverá permitir o cadastro de uma ação do Programa Saúde na Escola, informando código, escola, tema, data prevista, público-alvo, responsável, quantidade prevista de participantes e situação inicial.

### RF02 – Listar ações
O sistema deverá permitir a visualização de todas as ações cadastradas, apresentando suas principais informações de forma organizada.

### RF03 – Pesquisar ações
O sistema deverá permitir a pesquisa de ações cadastradas por código, escola ou tema.

### RF04 – Atualizar situação da ação
O sistema deverá permitir alterar a situação de uma ação para planejada, realizada ou cancelada.

### RF05 – Registrar participantes
O sistema deverá permitir registrar a quantidade efetiva de participantes quando uma ação for marcada como realizada.

### RF06 – Gerar resumo das ações
O sistema deverá permitir gerar um resumo contendo a quantidade de ações planejadas, realizadas e canceladas, além do total de participantes e do percentual de participação em relação à quantidade prevista.

### RF07 – Validar informações inseridas
O sistema deverá verificar informações importantes durante o cadastro e as operações, impedindo códigos duplicados, quantidades negativas, campos obrigatórios vazios e opções inválidas.


## Requisitos Não Funcionais

### RNF01 – Linguagem e ambiente
O sistema deverá ser desenvolvido em linguagem C e executado em ambiente de terminal.

### RNF02 – Usabilidade
O sistema deverá apresentar menus, mensagens de erro e confirmações de forma clara e compreensível para o usuário.

### RNF03 – Privacidade e segurança dos dados
O sistema deverá utilizar somente dados fictícios e informações coletivas, não permitindo o armazenamento de dados sensíveis individuais dos estudantes.

### RNF04 – Armazenamento
As informações deverão permanecer armazenadas em memória durante a execução do programa, sendo opcional o uso de arquivos como melhoria adicional.

### RNF05 – Organização do código
O sistema deverá ser dividido em funções com responsabilidades claras, evitando concentrar toda a lógica na função.

