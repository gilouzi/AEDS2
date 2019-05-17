#ifndef SACO_H
#define SACO_H

//definicao do tipo
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
} saco_t;

typedef struct node {
  char letra;
  int ponto;
  int quantidade;
  struct node *prox;
  struct node *prev;
} node_t;

typedef struct {
  int num_elementos;
  node_t *inicio;
  node_t *fim;
} pacote_t;


//cabecalho das funcoes
saco_t *cria_saco();
pacote_t *cria_pacote();
void insere_valor_pac(pacote_t *pacote, int p, char l, int q);
pacote_t *arruma_pacote();
void insere_valor(saco_t *saco, int p, char l);
node_t *remove_quant_pacote(pacote_t *pacote, int n);
saco_t *inicializar_saco();
peca_t *remove_saco(saco_t *saco);
void destroy_saco (saco_t *saco);
void destroy_pacote (pacote_t *pacote);

#endif