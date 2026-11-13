// PSE em Acao - Sistema de Planejamento e Acompanhamento de Acoes de Saude na Escola
#include <stdio.h>
#include <stdlib.h>

#define MAX_ACOES 100
#define TAM_TEXTO 60
#define ARQUIVO_DADOS "acoes.txt"

#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

typedef struct {
	int codigo;
	char escola[TAM_TEXTO];
	char tema[TAM_TEXTO];
	char data[12];
	char publico[TAM_TEXTO];
	char responsavel[TAM_TEXTO];
	int qtdPrevista;
	int qtdEfetiva; // -1 enquanto os participantes ainda nao foram registrados
	int situacao;
} Acao;

// vetor com todas as acoes do programa. e carregado do arquivo ao abrir e salvo a cada alteracao
Acao acoes[MAX_ACOES];
int totalAcoes = 0;

/* ================= FUNCOES DE TEXTO =================
   feitas a mao para o programa usar apenas stdio.h e stdlib.h */

int tamanhoTexto(const char *texto) {
	int i = 0;
	while (texto[i] != '\0') i++;
	return i;
}

int temCaractere(const char *texto, char c) {
	int i;
	for (i = 0; texto[i] != '\0'; i++) {
		if (texto[i] == c) return 1;
	}
	return 0;
}

char minusculo(char c) {
	if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
	return c;
}

int textosIguais(const char *a, const char *b) {
	// compara dois textos sem diferenciar maiusculas de minusculas
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
		if (minusculo(a[i]) != minusculo(b[i])) return 0;
	}
	return a[i] == b[i];
}

int contemTexto(const char *texto, const char *busca) {
	// pesquisa parcial sem diferenciar maiusculas de minusculas ("saude" encontra "Saude Bucal")
	// testa cada posicao do texto como possivel inicio da busca
	int i, j;
	for (i = 0; texto[i] != '\0'; i++) {
		for (j = 0; busca[j] != '\0' && minusculo(texto[i + j]) == minusculo(busca[j]); j++);
		if (busca[j] == '\0') return 1;
	}
	return 0;
}

/* ================= FUNCOES AUXILIARES ================= */

void lerLinha(char *destino, int tamanho) {
	// le a linha inteira (aceita espacos), tira o ENTER e descarta o que passar do tamanho
	int c, i;
	if (fgets(destino, tamanho, stdin) == NULL) {
		printf("\nEntrada encerrada.\n");
		exit(0);
	}
	for (i = 0; destino[i] != '\0' && destino[i] != '\n'; i++);
	if (destino[i] == '\n') {
		destino[i] = '\0';
		if (i > 0 && destino[i - 1] == '\r') destino[i - 1] = '\0';
	} else while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(const char *pergunta, char *destino, int tamanho) {
	// validacao de campo obrigatorio: so sai do loop quando o usuario digitar algo
	int inicio, i;
	do {
		printf("%s", pergunta);
		lerLinha(destino, tamanho);

		// tira espacos do inicio (puxando o texto para a esquerda) e do fim
		for (inicio = 0; destino[inicio] == ' '; inicio++);
		for (i = 0; destino[inicio + i] != '\0'; i++) destino[i] = destino[inicio + i];
		destino[i] = '\0';
		while (i > 0 && destino[i - 1] == ' ') destino[--i] = '\0';

		if (destino[0] == '\0') printf("Campo obrigatorio. Preencha, por favor.\n");
		else if (temCaractere(destino, ';')) {
			// o ; separa os campos no arquivo, entao nao pode aparecer dentro do texto
			printf("O caractere ';' nao e permitido.\n");
			destino[0] = '\0';
		}
	} while (destino[0] == '\0');
}

int lerInteiro(const char *pergunta, int minimo, int maximo) {
	// so aceita numeros inteiros dentro do intervalo. letras ou valores fora do limite pedem de novo
	char linha[32], *fim;
	long valor;
	while (1) {
		printf("%s", pergunta);
		lerLinha(linha, sizeof(linha));
		valor = strtol(linha, &fim, 10);
		while (*fim == ' ') fim++;
		if (linha[0] == '\0' || *fim != '\0') printf("Digite apenas numeros inteiros.\n");
		else if (valor < 0 && minimo >= 0) printf("O valor nao pode ser negativo.\n");
		else if (valor < minimo || valor > maximo) printf("Valor invalido. Digite entre %d e %d.\n", minimo, maximo);
		else return (int) valor;
	}
}

int dataValida(const char *data) {
	// confere o formato dd/mm/aaaa e se o dia existe no mes (inclusive ano bissexto)
	int dia, mes, ano;
	int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (tamanhoTexto(data) != 10 ||data[2] != '/' || data[5] != '/') return 0;
	if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) return 0;
	if (ano < 2000 || ano > 2100 || mes < 1 || mes > 12) return 0;
	if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) diasNoMes[1] = 29;
	return dia >= 1 && dia <= diasNoMes[mes - 1];
}

int buscarPorCodigo(int codigo) {
	// devolve a posicao da acao no vetor, ou -1 se o codigo nao existir
	int i;
	for (i = 0; i < totalAcoes; i++) {
		if (acoes[i].codigo == codigo) return i;
	}
	return -1;
}

const char *nomeSituacao(int situacao) {
	switch (situacao) {
		case PLANEJADA: return "Planejada";
		case REALIZADA: return "Realizada";
		case CANCELADA: return "Cancelada";
	}
	return "Desconhecida";
}

void mostrarAcao(Acao a) {
	printf("\n\tCodigo: %d\n\tEscola: %s\n\tTema: %s\n\tData prevista: %s\n", a.codigo, a.escola, a.tema, a.data);
	printf("\tPublico-alvo: %s\n\tResponsavel: %s\n\tSituacao: %s\n", a.publico, a.responsavel, nomeSituacao(a.situacao));
	printf("\tParticipantes previstos: %d\n", a.qtdPrevista);
	if (a.qtdEfetiva >= 0) printf("\tParticipantes efetivos: %d\n", a.qtdEfetiva);
	else printf("\tParticipantes efetivos: nao registrado\n");
}

void pausar() {
	char lixo[8];
	printf("\n\nPressione ENTER para voltar ao menu...");
	lerLinha(lixo, sizeof(lixo));
}

/* ================= ARQUIVO ================= */

void salvarDados() {
	// regrava o arquivo inteiro, uma acao por linha, com os campos separados por ;
	int i;
	FILE *arquivo = fopen(ARQUIVO_DADOS, "w");
	if (arquivo == NULL) {
		printf("\nAVISO: nao foi possivel salvar os dados em %s.\n", ARQUIVO_DADOS);
		return;
	}
	for (i = 0; i < totalAcoes; i++) {
		fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%d;%d;%d\n", acoes[i].codigo, acoes[i].escola, acoes[i].tema,
			acoes[i].data, acoes[i].publico, acoes[i].responsavel, acoes[i].qtdPrevista, acoes[i].qtdEfetiva, acoes[i].situacao);
	}
	fclose(arquivo);
}

void carregarDados() {
	char linha[400];
	Acao a;
	FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
	if (arquivo == NULL) return; // primeira execucao: o arquivo ainda nao existe

	// %59 = TAM_TEXTO - 1, para nunca estourar os campos de texto
	while (totalAcoes < MAX_ACOES && fgets(linha, sizeof(linha), arquivo) != NULL) {
		if (sscanf(linha, "%d;%59[^;];%59[^;];%11[^;];%59[^;];%59[^;];%d;%d;%d", &a.codigo, a.escola, a.tema,
			a.data, a.publico, a.responsavel, &a.qtdPrevista, &a.qtdEfetiva, &a.situacao) == 9) {
			acoes[totalAcoes] = a;
			totalAcoes++;
		}
	}
	fclose(arquivo);
}

/* ================= FUNCIONALIDADES DO MENU ================= */

void menu(int op) {
	// funcao para apresentar o menu principal. muda se o usuario acabou de abrir o programa ou acabou de voltar para o menu
	system("cls");
	if (op == 0) printf("======= BEM-VINDO AO PSE EM ACAO =======\n");
	else printf("======= RETORNANDO PARA O MENU =======\n");
	printf("Acoes cadastradas: %d de %d\n\n", totalAcoes, MAX_ACOES);
	printf("Escolha uma opcao\n\t1 - Cadastro\n\t2 - Lista de acoes\n\t3 - Pesquisa\n\t4 - Atualizacao de situacao\n\t5 - Registro de participantes\n\t6 - Geracao de resumo\n\t7 - Sair do programa\n");
}

void cadastro() {
	Acao nova;
	system("cls");
	printf("\n============== CADASTRO DE ACAO ==============\n");

	// limite de armazenamento atingido
	if (totalAcoes >= MAX_ACOES) {
		printf("\nLimite de %d acoes atingido. Nao e possivel cadastrar novas acoes.", MAX_ACOES);
		return;
	}

	// codigo unico (RN01). o 0 permite desistir e voltar ao menu
	nova.codigo = lerInteiro("Codigo da acao (0 para cancelar): ", 0, 999999);
	while (nova.codigo != 0 && buscarPorCodigo(nova.codigo) != -1) {
		printf("O codigo %d ja esta cadastrado. Informe outro.\n", nova.codigo);
		nova.codigo = lerInteiro("Codigo da acao (0 para cancelar): ", 0, 999999);
	}
	if (nova.codigo == 0) {
		printf("\nCadastro cancelado.");
		return;
	}

	lerTexto("Escola: ", nova.escola, TAM_TEXTO);
	lerTexto("Tema: ", nova.tema, TAM_TEXTO);
	lerTexto("Data prevista (dd/mm/aaaa): ", nova.data, sizeof(nova.data));
	while (!dataValida(nova.data)) {
		printf("Data invalida. Use o formato dd/mm/aaaa (ex: 15/03/2026).\n");
		lerTexto("Data prevista (dd/mm/aaaa): ", nova.data, sizeof(nova.data));
	}
	lerTexto("Publico-alvo: ", nova.publico, TAM_TEXTO);
	lerTexto("Responsavel: ", nova.responsavel, TAM_TEXTO);
	nova.qtdPrevista = lerInteiro("Quantidade prevista de participantes: ", 1, 100000);

	// toda acao nova comeca como planejada e sem participantes registrados
	nova.situacao = PLANEJADA;
	nova.qtdEfetiva = -1;

	acoes[totalAcoes] = nova;
	totalAcoes++;
	salvarDados();
	printf("\nAcao %d cadastrada com sucesso! Situacao inicial: Planejada.", nova.codigo);
}

void lista() {
	int i;
	char efetiva[12];
	system("cls");
	printf("\n============== LISTA DE ACOES ==============\n");

	if (totalAcoes == 0) {
		printf("\nNao ha acoes cadastradas.");
		return;
	}

	printf("\n%-6s %-20s %-16s %-10s %-10s %5s %5s\n", "Cod", "Escola", "Tema", "Data", "Situacao", "Prev", "Efet");
	printf("------------------------------------------------------------------------------\n");
	for (i = 0; i < totalAcoes; i++) {
		if (acoes[i].qtdEfetiva >= 0) sprintf(efetiva, "%d", acoes[i].qtdEfetiva);
		else sprintf(efetiva, "-");
		// o .20 e o .16 cortam textos grandes para a tabela nao quebrar
		printf("%-6d %-20.20s %-16.16s %-10s %-10s %5d %5s\n", acoes[i].codigo, acoes[i].escola, acoes[i].tema,
			acoes[i].data, nomeSituacao(acoes[i].situacao), acoes[i].qtdPrevista, efetiva);
	}
	printf("\nTotal: %d acao(oes).", totalAcoes);
}

void pesquisa(char *resposta) {
	// criacao das variaveis da funcao
	int criterio, codigo, i, encontrados = 0;
	char registro[TAM_TEXTO], linhaResposta[8];

	// escolha do criterio de pesquisa + validacao do criterio escolhido (dentro do lerInteiro)
	system("cls");
	printf("\n============== INICIANDO O PROCESSO DE PESQUISA ==============\nEscolha o criterio da pesquisa\n\t1 - Codigo\n\t2 - Escola\n\t3 - Tema\n");
	criterio = lerInteiro("R: ", 1, 3);

	// codigo e procurado de forma exata. escola e tema aceitam parte do nome
	if (criterio == 1) {
		codigo = lerInteiro("Insira o codigo a ser pesquisado: ", 1, 999999);
		printf("\nCriterio escolhido = Codigo / Registro escolhido = %d\n\n======= PESQUISANDO =======", codigo);
		i = buscarPorCodigo(codigo);
		if (i != -1) {
			mostrarAcao(acoes[i]);
			encontrados = 1;
		}
	} else {
		lerTexto("Insira o registro a ser pesquisado: ", registro, TAM_TEXTO);
		printf("\nCriterio escolhido = %s / Registro escolhido = %s\n\n======= PESQUISANDO =======", criterio == 2 ? "Escola" : "Tema", registro);
		for (i = 0; i < totalAcoes; i++) {
			if ((criterio == 2 && contemTexto(acoes[i].escola, registro)) || (criterio == 3 && contemTexto(acoes[i].tema, registro))) {
				mostrarAcao(acoes[i]);
				encontrados++;
			}
		}
	}

	// exibicao dos resultados
	if (encontrados == 0) printf("\nNenhum registro encontrado.");
	else printf("\n%d resultado(s) encontrado(s).", encontrados);

	// opcao de repetir a funcao. a repeticao em si acontece no switch() do int main
	do {
		printf("\n\nVoce deseja fazer outra pesquisa? (S ou N): ");
		lerLinha(linhaResposta, sizeof(linhaResposta));
		*resposta = linhaResposta[0];
		if (*resposta == 's') *resposta = 'S';
		if (*resposta == 'n') *resposta = 'N';
	} while (*resposta != 'S' && *resposta != 'N');
}

void atualSituacao() {
	int codigo, posicao, novaSituacao;
	system("cls");
	printf("\n============== ATUALIZACAO DE SITUACAO ==============\n");

	codigo = lerInteiro("Codigo da acao: ", 1, 999999);
	posicao = buscarPorCodigo(codigo);
	if (posicao == -1) {
		printf("\nAcao %d nao encontrada.", codigo);
		return;
	}

	printf("\nAcao: %s - %s\nSituacao atual: %s\n", acoes[posicao].escola, acoes[posicao].tema, nomeSituacao(acoes[posicao].situacao));
	printf("\nNova situacao\n\t1 - Planejada\n\t2 - Realizada\n\t3 - Cancelada\n");
	novaSituacao = lerInteiro("R: ", 1, 3);

	if (novaSituacao == acoes[posicao].situacao) {
		printf("\nA acao ja esta como %s. Nada foi alterado.", nomeSituacao(novaSituacao));
		return;
	}

	// participantes so valem para acao realizada (RN01 do registro de participantes)
	if (acoes[posicao].situacao == REALIZADA && acoes[posicao].qtdEfetiva >= 0) {
		printf("\nA acao deixou de ser realizada, entao o registro de %d participante(s) foi removido.", acoes[posicao].qtdEfetiva);
		acoes[posicao].qtdEfetiva = -1;
	}

	acoes[posicao].situacao = novaSituacao;
	salvarDados();
	printf("\nSituacao atualizada para %s!", nomeSituacao(novaSituacao));
}

void regParticip() {
	int codigo, posicao;
	system("cls");
	printf("\n============== REGISTRO DE PARTICIPANTES ==============\n");

	codigo = lerInteiro("Codigo da acao: ", 1, 999999);
	posicao = buscarPorCodigo(codigo);
	if (posicao == -1) {
		printf("\nNao existe acao com o codigo %d.", codigo);
		return;
	}
	if (acoes[posicao].situacao != REALIZADA) {
		printf("\nA acao esta como %s. Ela precisa estar Realizada para receber o registro de participantes.", nomeSituacao(acoes[posicao].situacao));
		return;
	}

	printf("\nAcao: %s - %s\nParticipantes previstos: %d\n", acoes[posicao].escola, acoes[posicao].tema, acoes[posicao].qtdPrevista);
	if (acoes[posicao].qtdEfetiva >= 0) printf("Ja havia %d participante(s) registrado(s). O valor sera substituido.\n", acoes[posicao].qtdEfetiva);

	acoes[posicao].qtdEfetiva = lerInteiro("Quantidade efetiva de participantes: ", 0, 100000);
	salvarDados();
	printf("\nRegistro concluido: %d participante(s) na acao %d.", acoes[posicao].qtdEfetiva, codigo);
}

void geraResumo() {
	int i, j, planejadas = 0, realizadas = 0, canceladas = 0, semRegistro = 0;
	int previstoTotal = 0, previstoRealizadas = 0, registrados = 0;
	int qtdEscola, prevEscola, regEscola, jaContada;
	system("cls");
	printf("\n============== RESUMO GERAL ==============\n");

	if (totalAcoes == 0) {
		printf("\nNao ha dados disponiveis para gerar o resumo.");
		return;
	}

	for (i = 0; i < totalAcoes; i++) {
		if (acoes[i].situacao == PLANEJADA) planejadas++;
		else if (acoes[i].situacao == CANCELADA) canceladas++;
		else realizadas++;

		// acao cancelada nao entra no total previsto
		if (acoes[i].situacao != CANCELADA) previstoTotal += acoes[i].qtdPrevista;

		// o percentual compara so as acoes realizadas que ja tem participantes registrados
		if (acoes[i].situacao == REALIZADA) {
			if (acoes[i].qtdEfetiva >= 0) {
				registrados += acoes[i].qtdEfetiva;
				previstoRealizadas += acoes[i].qtdPrevista;
			} else semRegistro++;
		}
	}

	printf("\nAcoes por situacao\n\tPlanejadas: %d\n\tRealizadas: %d\n\tCanceladas: %d\n\tTotal: %d\n", planejadas, realizadas, canceladas, totalAcoes);
	printf("\nParticipantes\n\tPrevistos (planejadas + realizadas): %d\n", previstoTotal);
	printf("\tPrevistos nas acoes realizadas com registro: %d\n\tRegistrados: %d\n", previstoRealizadas, registrados);
	if (previstoRealizadas > 0) printf("\tPercentual de participacao: %.1f%%\n", registrados * 100.0 / previstoRealizadas);
	else printf("\tPercentual de participacao: sem acoes realizadas com registro\n");
	if (semRegistro > 0) printf("\tAtencao: %d acao(oes) realizada(s) ainda sem participantes registrados.\n", semRegistro);

	// consolidado por escola: soma cada escola uma unica vez (nome comparado sem maiusculas/minusculas)
	printf("\nPor escola\n%-30s %6s %9s %11s\n", "Escola", "Acoes", "Previstos", "Registrados");
	for (i = 0; i < totalAcoes; i++) {
		jaContada = 0;
		for (j = 0; j < i && !jaContada; j++) {
			if (textosIguais(acoes[i].escola, acoes[j].escola)) jaContada = 1;
		}
		if (jaContada) continue;

		qtdEscola = prevEscola = regEscola = 0;
		for (j = i; j < totalAcoes; j++) {
			if (!textosIguais(acoes[i].escola, acoes[j].escola)) continue;
			qtdEscola++;
			if (acoes[j].situacao != CANCELADA) prevEscola += acoes[j].qtdPrevista;
			if (acoes[j].qtdEfetiva >= 0) regEscola += acoes[j].qtdEfetiva;
		}
		printf("%-30.30s %6d %9d %11d\n", acoes[i].escola, qtdEscola, prevEscola, regEscola);
	}
}

int main() {
	// variaveis usadas pelo menu. a maioria das variaveis esta dentro do escopo de cada funcao separadamente
	int op = 0;
	char resposta;

	carregarDados();

	// loop de executar cada opcao e voltar para o menu
	while (op != 7) {
		menu(op);
		op = lerInteiro("R: ", 1, 7);
		switch (op) {
			case 1:
				cadastro();
				pausar();
			break;
			case 2:
				lista();
				pausar();
			break;
			case 3:
				pesquisa(&resposta);
				while (resposta == 'S') pesquisa(&resposta); // continuacao da repeticao da funcao
			break;
			case 4:
				atualSituacao();
				pausar();
			break;
			case 5:
				regParticip();
				pausar();
			break;
			case 6:
				geraResumo();
				pausar();
			break;
			case 7:
				printf("\nObrigado por utilizar o programa!\n");
			break;
		}
	}

	return 0;
}
