#include <stdio.h>
#include <stdlib.h>

void cadastro(){

}
void pesquisa(int criterio, char registro[50]){
    printf("\n======= ABRINDO O PROCESSO DE PESQUISA =======\nEscolha o criterio da pesquisa\n\t1 - Codigo\n\t2 - Escola\n\t3 - Tema\n");
    scanf("%d", &criterio);

    while (criterio < 1 || criterio > 3) {
        printf("\tCriterio invalido. Insira outro: ");
        scanf("%d", &criterio);
    }

    printf("Insira o registro a ser pesquisado: ");
    scanf("%s", &registro);
    
    switch (criterio) {
        case 1:
            printf("Criterio escolhido = Codigo");
        break;
        case 2:
            printf("Criterio escolhido = Escola");
        break;
        case 3:
            printf("Criterio escolhido = Tema");
        break;
    }
    printf("\nRegistro escolhido = %s\n======= PESQUISANDO =======", registro);

    // fazer BUSCA DOS REGISTROS CORRESPONDENTES

}
void atualSituacao(){

}
void geraResumo(){

}

int main() {
    int op, criterioPesquisa;
    char registroPesquisa[50];
    printf("Escolha uma opcao\n\t1 - Cadastro\n\t2 - Pesquisa\n\t3 - Atualizacao de situacao\n\t4 - Geracao de resumo\n\t5 - Sair do programa\n");
    scanf("%d", &op);

    while (op != 5) {
        switch(op) {
            case 1:
                cadastro();
            break;
            case 2:
                pesquisa(criterioPesquisa, registroPesquisa);
            break;
            case 3:
                atualSituacao();
            break;
            case 4:
                geraResumo();
            break;
            default:
                printf("Opcao invalida. Insira outra: ");
                scanf("%d", &op);
            break;
        }
    }
    printf("\nObrigado por utilizar o programa!");

    return 0;
}
