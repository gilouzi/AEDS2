#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "saco.h"
#include "jogadas.h"

jogo_t *cria_jogo(saco_t *Saco){
	jogo_t *jogo = (jogo_t *) malloc(sizeof(jogo_t));
	if (jogo == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}
	jogo->inicio = NULL;
	jogo->fim = NULL;
	jogo->atual = NULL;
	jogo->num_jogadores=0;
	jogo->saco=Saco;
	jogo->pula_vez=0;
	return jogo;
}

void insere_jogador(jogo_t *jogo){  //inserir jogador em jogo

	peca_t *novo = (peca_t *) malloc(sizeof(peca_t));
	jogador_t *jogador = (jogador_t *) malloc(sizeof(jogador_t));

	if (novo == NULL || jogador == NULL){
		printf("Erro, sem memoria\n");
		exit(1);
	}

	jogador->prox = NULL;
	jogador->jogador_pontos = 0;

	if (jogo->inicio == NULL){
		jogador->prev = NULL;
		jogo->inicio = jogador;
		jogo->atual = jogador;
		jogador->jogador_num = 1;
	}

	if (jogo->inicio != NULL)	{
		jogador->prev=jogo->fim;
		//jogador->jogador_num = jogo->fim->jogador_num+1;
	}

	if (jogo->fim != NULL){
		jogo->fim->prox = jogador; 
	}

	if(jogador->jogador_num == 0) {
		int num = jogador->prev->jogador_num;
		jogador->jogador_num = num + 1;
	} 

	jogo->fim = jogador;
	jogo->num_jogadores++;

	for(int i = 0; i<7; i++) { //adicionar as 7 primeiras pecas do jogador
		novo = remove_saco(jogo->saco);
		jogador->suporte[i] = novo;
	}

}

jogo_t *def_quant_jog (saco_t *saco) { //definir quantas pessoas vao jogar (2 a 4)
	int jog;
	printf("Digite a quantidade de jogadores de 2 a 4\n");
	scanf("%d", &jog);
	jogo_t *jogo = cria_jogo(saco);
	if(jog>=2 && jog<=4) {
		while (jogo->num_jogadores != jog){
			insere_jogador(jogo);
		}
	}
	else{
		printf("Erro, quantidade de jogadores nao disponivel\n");
		exit(1);
	}
	return jogo;
}

jogo_t *inicio_jogo () { //iniciar o jogo
	saco_t *saco = inicializar_saco();
	jogo_t *jogo = def_quant_jog(saco);
	return jogo;
}

void trocar_todas_pecas(jogo_t *jogo){
	jogo->pula_vez=0;
}

void trocar_peca(jogo_t *jogo){
	jogo->pula_vez=0;

}

void formar_palavra(jogo_t *jogo){
	jogo->pula_vez=0;

}

void pular_vez(jogo_t *jogo){
	jogo->pula_vez++;
	if(jogo->pula_vez == (jogo->num_jogadores)*2){
		fim_jogo(jogo);
	}
}

void fim_jogo(jogo_t *jogo) {
	printf("fim do jogo\n");
	destroy_jogo(jogo);
	exit(1);
}

void jogada(jogo_t *jogo) {
	printf("Jogador %d sua vez de jogar\n",jogo->atual->jogador_num);

	printf("Suas pedras são:\n");
    for (int d = 0; d < 7; d++){
      printf("%c ",jogo->atual->suporte[d]->letra);
    }
    printf("\n");
    for (int d = 0; d < 7; d++){
      printf("%d ",d+1);
    }
    printf("\n");

	printf("Para trocar todas as suas pedras digite 1\n");
	printf("Para trocar apenas uma pedra digite 2\n");
	printf("Para formar uma palavra digite 3\n");
	printf("Para pular sua vez digite 4\n");

	int opt;

	scanf("%d",&opt);

	if(opt==1)
		trocar_todas_pecas(jogo);
	else if(opt==2)
		trocar_peca(jogo);
	else if(opt==3)
		formar_palavra(jogo);
	else if(opt==4)
		pular_vez(jogo);
	else{
		printf("ERRO: OPCAO INVALIDA\n");
		exit(1);
	}


	if(jogo->atual != jogo->fim)
		jogo->atual = jogo->atual->prox;
	else
		jogo->atual = jogo->inicio;

}

void destroy_suporte(jogador_t *jogador){ 								//isso da dando free de verdade??????
	for(int i = 0; i<7; i++)
		free(jogador->suporte[i]);
}

void destroy_jogo(jogo_t *jogo){
	destroy_saco (jogo->saco);

	jogador_t *toVisit = jogo -> inicio;
	jogador_t *toFree;

	while (toVisit != NULL) {
		toFree = toVisit;
		toVisit = toVisit->prox;
		destroy_suporte(toFree);
		free(toFree);
	}

	free(jogo);
}

