#ifndef DICIONARIO_H
#define DICIONARIO_H

#define ALPHABET_SIZE 26

typedef struct trie_node {
  char letra;
  int fimPalavra;
  struct trie_node *filho; // com ALPHABET_SIZE posições
} trie_node_t;

typedef struct trie {
  trie_node_t *firstLevel; // com ALPHABET_SIZE posições
} trie_t;

trie_t *cria_trie();
trie_node_t *cria_node();
void insere_palavra_rest(char *palavra, trie_t *trie, int i, trie_node_t *node);
void insere_palavra(char *palavra, trie_t *trie);
trie_t *inicia_dicionario(FILE *arq);
int busca(trie_t *trie, char *palavra);
void chamada_busca(trie_t *trie);
void destroy_trie(trie_node_t *node);
void destroy_dicionario(trie_t *trie);


#endif