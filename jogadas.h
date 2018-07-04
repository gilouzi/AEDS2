#ifndef JOGADAS_H
#define JOGADAS_H


#include "saco.h"
#include "dicionario.h"

//definicao do tipo
/*
typedef struct peca {
  char letra;
  int ponto;
  struct peca *prox;
  struct peca *prev;
} peca_t;

typedef struct {
  int num_elementos;
  peca_t *inicio;
  peca_t *fim;
} saco_t; */

typedef struct jogador {
  peca_t *suporte[7];
  int jogador_pontos;
  int jogador_num;
  struct jogador *prox;
  struct jogador *prev;
} jogador_t;

typedef struct{
  int num_jogadores;
  saco_t *saco;
  jogador_t *inicio;
  jogador_t *fim;
  jogador_t *atual;
  int pula_vez;
  char tabuleiro[15][15];
  trie_t *dicionario;
} jogo_t;


jogo_t *inicio_jogo (FILE *arq);
jogo_t *cria_jogo(saco_t *Saco, FILE *arq);
void inicia_tabuleiro(char tabuleiro[15][15]);
void imprime_tabuleiro(char tabuleiro[15][15]);
void insere_jogador(jogo_t *jogo);
void def_quant_jog (jogo_t *jogo);
void trocar_todas_pecas(jogo_t *jogo);
void trocar_peca(jogo_t *jogo);
void formar_palavra(jogo_t *jogo);
void pular_vez(jogo_t *jogo);
void fim_jogo(jogo_t *jogo);
void jogada(jogo_t *jogo);
void destroy_suporte(jogador_t *jogador);
void destroy_jogo(jogo_t *jogo);

#endif