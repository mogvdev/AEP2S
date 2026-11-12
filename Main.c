#include <stdio.h>
#include <stdlib.h>

void menu() {
	printf("Escolha uma opcao\n\t1 - Cadastro\n\t2 - Pesquisa\n\t3 - Atualizacao de situacao\n\t4 - Geracao de resumo\n\t5 - Sair do programa\nR: ");
}

void cadastro(){

}

void pesquisa(int criterio, char registro[], char *resposta){
    printf("\n============== INICIANDO O PROCESSO DE PESQUISA ==============\nEscolha o criterio da pesquisa\n\t1 - Codigo\n\t2 - Escola\n\t3 - Tema\nR: ");
    scanf("%d", &criterio);

    while (criterio < 1 || criterio > 3) {
        printf("Criterio invalido. Insira outro: ");
        scanf("%d", &criterio);
    }

    printf("Insira o registro a ser pesquisado: ");
    scanf("%50s", registro);
    
    switch (criterio) {
        case 1:
            printf("\nCriterio escolhido = Codigo");
        break;
        case 2:
            printf("\nCriterio escolhido = Escola");
        break;
        case 3:
            printf("\nCriterio escolhido = Tema");
        break;
    }
    printf(" / Registro escolhido = %s\n\n======= PESQUISANDO =======", registro);

    // fazer BUSCA DOS REGISTROS CORRESPONDENTES
    
    printf("\nVoce deseja fazer outra pesquisa? (S ou N): ");
    scanf(" %c", resposta);
    printf("%c", *resposta);
}

void atualSituacao(){

}

void geraResumo(){

}

int main() {
    int op = 0, criterioPesquisa;
    char registroPesquisa[50], resposta;

    while (op != 5) {
    menu();
    scanf("%d", &op);
    printf("%d", op);
        switch(op) {
            case 1:
                cadastro();
            break;
            case 2:
                pesquisa(criterioPesquisa, registroPesquisa, &resposta);
                if (resposta != 'N') pesquisa(criterioPesquisa, registroPesquisa, &resposta);
                printf("\n======= RETORNANDO PARA O MENU =======\n");
            break;
            case 3:
                atualSituacao();
            break;
            case 4:
                geraResumo();
            break;
            default:
                printf("Opcao invalida (%d). Insira outra: ", op);
                scanf("%d", &op);
            break;
        }
    }
    printf("\nObrigado por utilizar o programa!");

    return 0;
}
