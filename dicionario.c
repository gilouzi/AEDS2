#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "saco.h"
#include "jogadas.h"
#include "dicionario.h"

trie_t *cria_trie(){

  trie_node_t *first = cria_node();

  trie_t *trie = (trie_t *) malloc(sizeof(trie_t));
  trie->firstLevel = first;

  return trie;
}

trie_node_t *cria_node(){

  trie_node_t *node =(trie_node_t *) malloc(sizeof(trie_node_t) * ALPHABET_SIZE);
  for (int i = 0; i < ALPHABET_SIZE; i++){
    node[i].letra = '0';
    node[i].fimPalavra = 0;
    node[i].filho = NULL;
  }

  return node;
}

void insere_palavra_rest(char *palavra, trie_t *trie, int i, trie_node_t *node){ //insere o restante da palavra sempre alocando novos espacos

  while(palavra[i+1] != '\0'){

    int pos = palavra[i]-97;

    node[pos].letra = palavra[i];
    trie_node_t *prox = cria_node();
    node[pos].filho = prox;
    node = prox;

    i++;
  }

  int pos = palavra[i]-97; //ultima letra da palavra -> i+1 = '\0'

  node[pos].letra = palavra[i];
  node[pos].filho = NULL;
  node[pos].fimPalavra = 1;

}

void insere_palavra(char *palavra, trie_t *trie){

  int i=0;
  trie_node_t *node = trie->firstLevel;

  while(palavra[i+1] != '\0'){

    int pos = palavra[i]-97;

    if(node[pos].letra == '0'){
      insere_palavra_rest(palavra,trie,i,node);
      return;
    }
    else{
      if(node[pos].filho != NULL){
       //printf("if node[pos].filho != null\n");
        node = node[pos].filho;
      }
      else{
        //printf("else %s\n", palavra);
        insere_palavra_rest(palavra,trie,i++,node);
        return;
      }
    }
    i++;
  }


  int pos = palavra[i]-97; //ultima letra da palavra -> i+1 = '\0'
  node[pos].letra = palavra[i];
  node[pos].fimPalavra = 1;
  node[pos].filho = NULL;

}


void inicia_dicionario(FILE *arq){

  trie_t *trie = cria_trie();
  char palavra[1040];

  while (fscanf(arq, "%s\n", palavra) != EOF){

    //printf("lido: %s\n",palavra);

    insere_palavra(palavra,trie);

  }
}

int busca(trie_t *trie, char *palavra){

  int i=0;
  trie_node_t *node = trie->firstLevel;

  while(palavra[i+1] != '\0'){

    int pos = palavra[i]-97;

    if(node[pos].letra == '0' || node[pos].filho == NULL)
      return 0;

    printf("encontrado %c\n",node[pos].letra);
    node = node[pos].filho;
    i++;
  }

  int pos = palavra[i]-97;
  if(node[pos].fimPalavra == 1){
    return 1;
  }

  return 0;

}

void chamada_busca(trie_t *trie) {

  char palavra[1040];
  int b;

  printf("Digite a palavra que deseja buscar se existe, se quiser sair, digite 0\n");
  scanf("%s",palavra);

  if(strcmp("0",palavra) == 0){
    return;
  }

  else{
    b = busca(trie,palavra);
  }

  if(b == 0){
    printf("Palavra %s nao existe\n",palavra);
  }

  else{
    printf("Palavra %s existe\n",palavra);
  }

  chamada_busca(trie);

}

void destroy_trie(trie_node_t *node){
  for(int i = 0; i<ALPHABET_SIZE; i++){
    if(node[i].filho != NULL){
      node = node[i].filho;
      destroy_trie(node);
    }
  }
  free(node);
}

void destroy_dicionario(trie_t *trie){
  trie_node_t *node = trie->firstLevel;
  destroy_trie(node);
  free(trie);
}