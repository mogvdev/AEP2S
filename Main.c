#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(int op) {
	// funcao para apresentar o menu principal. muda se o usuario acabou de abrir o programa ou acabou de voltar para o menu
	system("cls");
	if (op == 0) printf("======= BEM-VINDO =======\n");
	else printf("======= RETORNANDO PARA O MENU =======\n");
	printf("Escolha uma opcao\n\t1 - Cadastro\n\t2 - Pesquisa\n\t3 - Atualizacao de situacao\n\t4 - Geracao de resumo\n\t5 - Sair do programa\nR: ");
}

void cadastro(){

}

void pesquisa(char *resposta){
	// criacao das variaveis da funcao e da variavel responsavel por armazenar o arquivo
	int criterio, i;
	char registro[50], pesquisados[50][50];
	FILE *arquivo;
	
	// escolha do criterio de pesquisa + validacao do criterio escolhido
	system("cls");
    printf("\n============== INICIANDO O PROCESSO DE PESQUISA ==============\nEscolha o criterio da pesquisa\n\t1 - Codigo\n\t2 - Escola\n\t3 - Tema\nR: ");
    scanf("%d", &criterio);

    while (criterio < 1 || criterio > 3) {
        printf("Criterio invalido. Insira outro: ");
        scanf("%d", &criterio);
    }

	// escolha do registro para a pesquisa
    printf("Insira o registro a ser pesquisado: ");
    scanf("%50s", registro);
    
    // repeticao do criterio e do registro escolhidos + abertura do arquivo correspondente ao criterio
    switch (criterio) {
        case 1:
            printf("\nCriterio escolhido = Codigo");
            arquivo = fopen("critCodigo.txt", "r");
        break;
        case 2:
            printf("\nCriterio escolhido = Escola");
            arquivo = fopen("critEscola.txt", "r");
        break;
        case 3:
            printf("\nCriterio escolhido = Tema");
            arquivo = fopen("critTema.txt", "r");
        break;
    }
    printf(" / Registro escolhido = %s\n\n======= PESQUISANDO =======", registro);
    
    // colocando todos os itens do criterio escolhido dentro da variavel
    if (arquivo != NULL) for (i = 0; i < 50, fscanf(arquivo, "%50s", pesquisados[i]) == 1; i++);
    fclose(arquivo);
    
    // exibicao dos resultados
    printf("\nResultados encontrados: ");
    for (i = 0; i < 50; i++) {
    	if (strstr(pesquisados[i], registro) != NULL) printf("\n\t%s", pesquisados[i]);
	}
    
    // opcao de repetir a funcao. finalizada dentro do switch() do int main
    printf("\n\nVoce deseja fazer outra pesquisa? (S ou N): ");
    scanf(" %c", resposta);
}

void atualSituacao(){

}

void geraResumo(){

}

int main() {
	// variaveis usadas por todas as funcoes. a maioria das variaveis esta dentro do escopo de cada funcao separadamente
    int op = 0;
    char resposta;

	// loop de executar cada opcao e voltar para o menu
    while (op != 5) {
    menu(op);
    scanf("%d", &op);
        switch(op) {
            case 1:
                cadastro();
            break;
            case 2:
                pesquisa(&resposta);
                while (resposta == 'S') pesquisa(&resposta); // continuacao da repeticao da funcao
            break;
            case 3:
                atualSituacao();
            break;
            case 4:
                geraResumo();
            break;
            case 5:
    			printf("\nObrigado por utilizar o programa!");
            break;
            default:
                printf("Opcao invalida (%d). Insira outra: ", op);
                scanf("%d", &op);
            break;
        }
    }

    return 0;
}
