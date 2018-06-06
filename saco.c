#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "saco.h"

saco_t *cria_saco(){
	saco_t *saco = (saco_t *) malloc(sizeof(saco_t));
	if (saco == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}
	saco->inicio = NULL;
	saco->fim = NULL;
	saco->num_elementos=0;
	return saco;
}

pacote_t *cria_pacote(){
	pacote_t *pacote = (pacote_t *) malloc(sizeof(pacote_t));
	if (pacote == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}
	pacote->inicio = NULL;
	pacote->fim = NULL;
	pacote->num_elementos=0;
	return pacote;
}

void insere_valor_pac(pacote_t *pacote, int p, char l, int q){

	node_t *novo = (node_t *) malloc(sizeof(node_t));

	if (novo == NULL){
		printf("Erro, sem memoria\n");
		exit(1);
	}

	novo->ponto = p;
	novo->letra = l;
	novo->quantidade=q;
	novo->prox = NULL;

	if (pacote->inicio == NULL){
		novo->prev = NULL;
		pacote->inicio = novo;
	}

	if (pacote->inicio != NULL)	{
		novo->prev=pacote->fim;
	}

	if (pacote->fim != NULL){
		pacote->fim->prox = novo; 
	}

	pacote->fim = novo;

	pacote->num_elementos++;

}

pacote_t *arruma_pacote() { //criar a lista pecas com suas quantidades disponiveis inicialmente
	pacote_t *pacote = cria_pacote();

	int ponto=0;
	insere_valor_pac(pacote,ponto,'0',3);

	ponto=1;
	insere_valor_pac(pacote,ponto,'A',14);
	insere_valor_pac(pacote,ponto,'E',11);
	insere_valor_pac(pacote,ponto,'I',10);
	insere_valor_pac(pacote,ponto,'O',10);
	insere_valor_pac(pacote,ponto,'S',8);
	insere_valor_pac(pacote,ponto,'U',7);
	insere_valor_pac(pacote,ponto,'M',6);
	insere_valor_pac(pacote,ponto,'R',6);
	insere_valor_pac(pacote,ponto,'T',5);

	ponto=2;
	insere_valor_pac(pacote,ponto,'D',5);
	insere_valor_pac(pacote,ponto,'L',5);
	insere_valor_pac(pacote,ponto,'C',4);
	insere_valor_pac(pacote,ponto,'P',4);
	
	ponto=3;
	insere_valor_pac(pacote,ponto,'N',4);
	insere_valor_pac(pacote,ponto,'B',3);
	insere_valor_pac(pacote,ponto,'c',2);
	
	ponto=4;
	insere_valor_pac(pacote,ponto,'F',2);
	insere_valor_pac(pacote,ponto,'G',2);
	insere_valor_pac(pacote,ponto,'H',2);
	insere_valor_pac(pacote,ponto,'V',2);
	
	ponto=5;
	insere_valor_pac(pacote,ponto,'J',2);
	
	ponto=6;
	insere_valor_pac(pacote,ponto,'Q',1);
	
	ponto=8;
	insere_valor_pac(pacote,ponto,'X',1);
	insere_valor_pac(pacote,ponto,'Z',1);

	return pacote;

}

void insere_valor(saco_t *saco, int p, char l){

	peca_t *novo = (peca_t *) malloc(sizeof(peca_t));

	if (novo == NULL){
		printf("Erro, sem memoria\n");
		exit(1);
	}

	novo->ponto = p;
	novo->letra = l;
	novo->prox = NULL;

	if (saco->inicio == NULL){
		novo->prev = NULL;
		saco->inicio = novo;
	}

	if (saco->inicio != NULL)	{
		novo->prev=saco->fim;
	}

	if (saco->fim != NULL){
		saco->fim->prox = novo; 
	}

	saco->fim = novo;
	saco->num_elementos++;
}

node_t *remove_quant_pacote(pacote_t *pacote, int n) { //retirar uma quantidade do node na posicao n da lista

	node_t *toVisit = pacote->inicio;
	for(int i=0; i<n; i++) {
		toVisit=toVisit->prox;
	}

	if(toVisit->quantidade>0){
		toVisit->quantidade--;
		return toVisit;
	}

	else{
		if(toVisit->prox!=NULL && toVisit->prev!=NULL){
			node_t *toFree = toVisit;
			node_t *before = toVisit->prev; 
			node_t *next = toVisit->prox;
			before->prox = next; //toVisit->prev->prox = toVisit->prox;
			next->prev = before; //toVisit->prox->prev = toVisit->prev;
			free(toFree); 		 //free(toVisit);
			return NULL;
		}
		else if(toVisit->prox==NULL && toVisit->prev!=NULL){
			node_t *toFree = toVisit;
			node_t *before = toVisit->prev;
			before->prox=NULL;
			pacote->fim = before;
			free(toFree);
			return NULL;
		}
		else if(toVisit->prox!=NULL && toVisit->prev==NULL){
			node_t *toFree = toVisit;
			node_t *after = toVisit->prox;
			after->prev=NULL;
			pacote->inicio = after;
			free(toFree);
			return NULL;
		}
		else if(toVisit->prox==NULL && toVisit->prev==NULL){
			pacote->inicio=NULL;
			pacote->fim=NULL;
			free(toVisit);
			printf("Pacote vazio\n");
			return NULL;
		}

		pacote->num_elementos--;
		
	}

	return NULL; //adicionado para remover erro "reach end of non-void function"
}

saco_t *inicializar_saco(){ //colocar todas as pecas disponiveis de forma aleatoria dentro do saco
	pacote_t *pacote = arruma_pacote();
	saco_t *saco = cria_saco();
	int n = 25;
	srand(time(NULL));
	while(saco->num_elementos<120) {
		int pos = rand() % n;
		node_t *node = remove_quant_pacote(pacote,pos);
		if(node==NULL){
			n--;
		}
		else
			insere_valor(saco,node->ponto,node->letra);
	} 

	//teste se inicializar_saco esta funcionando

  	/*peca_t *toVisit = saco->inicio;
  	int i = 1;
  	while (toVisit != NULL) {
    	printf("peca %d - %c %d\n",i, toVisit->letra, toVisit->ponto);
    	i++;
    	toVisit = toVisit->prox;
  	}*/

	destroy_pacote(pacote);

	return saco;
}

peca_t *remove_saco(saco_t *saco) { //remove primeira peca do saco
	peca_t *toRemove = saco->inicio;
	saco->inicio = toRemove->prox;
	return toRemove;
}

void destroy_saco (saco_t *saco) {
	peca_t *toVisit = saco -> inicio;
	peca_t *toFree;

	while (toVisit != NULL) {
		toFree = toVisit;
		toVisit = toVisit->prox;
		free(toFree);
	}
	free(saco);
}

void destroy_pacote (pacote_t *pacote) {
	node_t *toVisit = pacote -> inicio;
	node_t *toFree;

	while (toVisit != NULL) {
		toFree = toVisit;
		toVisit = toVisit->prox;
		free(toFree);
	}
	free(pacote);
}