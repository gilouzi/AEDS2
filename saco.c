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
	//printf("saco criado\n");
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

void insere_valor_pac(pacote_t *pacote, int p, char l, int q){ //vai inserir dentro do pacote as letras com suas quantidades disponiveis

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

	//printf("inserido no pacote letra %c\n",l);

}

pacote_t *arruma_pacote() { //criar a lista pecas com suas quantidades disponiveis inicialmente
	pacote_t *pacote = cria_pacote();

	int ponto=0;
	//insere_valor_pac(pacote,ponto,'0',3);

	ponto=1;
	insere_valor_pac(pacote,ponto,'a',17);
	insere_valor_pac(pacote,ponto,'e',11);
	insere_valor_pac(pacote,ponto,'i',10);
	insere_valor_pac(pacote,ponto,'o',10);
	insere_valor_pac(pacote,ponto,'s',8);
	insere_valor_pac(pacote,ponto,'u',7);
	insere_valor_pac(pacote,ponto,'m',6);
	insere_valor_pac(pacote,ponto,'r',6);
	insere_valor_pac(pacote,ponto,'t',5);

	ponto=2;
	insere_valor_pac(pacote,ponto,'d',5);
	insere_valor_pac(pacote,ponto,'l',5);
	insere_valor_pac(pacote,ponto,'c',6);
	insere_valor_pac(pacote,ponto,'p',4);
	
	ponto=3;
	insere_valor_pac(pacote,ponto,'n',4);
	insere_valor_pac(pacote,ponto,'b',3);
	//insere_valor_pac(pacote,ponto,'c',2);
	
	ponto=4;
	insere_valor_pac(pacote,ponto,'f',2);
	insere_valor_pac(pacote,ponto,'g',2);
	insere_valor_pac(pacote,ponto,'h',2);
	insere_valor_pac(pacote,ponto,'v',2);
	
	ponto=5;
	insere_valor_pac(pacote,ponto,'j',2);
	
	ponto=6;
	insere_valor_pac(pacote,ponto,'q',1);
	
	ponto=8;
	insere_valor_pac(pacote,ponto,'x',1);
	insere_valor_pac(pacote,ponto,'z',1);

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
	//printf("pacote arrumado\n");
	saco_t *saco = cria_saco();
	int n = 23; //quantidade de nodes dentro do saco, ou de letras disponiveis
	srand(time(NULL));
	while(saco->num_elementos<120) { //quantidade de pecas existentes
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
	saco->num_elementos--;
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
	printf("saco destruido\n");
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