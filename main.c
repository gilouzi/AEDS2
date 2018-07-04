#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "jogadas.h"
#include "dicionario.h"
#include "saco.h"

#define BUFSZ 1024 

int main(int argc, char const *argv[]){

  //definir quantidade de jogadores: 2,3 ou 4



  //implementar a LISTA de letras (saco)
  /*   -> distribuir de forma aleatoria -> criar um vetor representando as letras e suas quantidades,fazer o random acessar o vetor
       -> cada letra com sua pontuacao (node com char e int)
       -> letras brancas (representadas por '0')
  */


  
  //teste se vetor_pecas esta funcionando

  /*int *v = vetor_pecas();

  for (int i = 0; i < 25; i++){
    printf("%d ",v[i]);
  }
  printf("\n"); */ 


  //teste se arruma_saco esta funcionando

  /*
  pacote_t *pacote = arruma_pacote();

  node_t *toVisit = pacote->inicio;
    while (toVisit != NULL) {
      printf("%c %d %d\n", toVisit->letra, toVisit->ponto, toVisit->quantidade);
      toVisit = toVisit->prox;
    } */


  //teste se remove_quant_pacote esta funcionando

  /*
  node_t *node = remove_quant_pacote(pacote,24);
  node = remove_quant_pacote(pacote,23);
  node = remove_quant_pacote(pacote,24);

  toVisit = pacote->inicio;
    while (toVisit != NULL) {
      printf("%c %d %d\n", toVisit->letra, toVisit->ponto, toVisit->quantidade);
      toVisit = toVisit->prox;
    }

    if(node==NULL){
      printf("NULO\n");
    } */


  //teste se inicializar_saco esta funcionando

  //inicializar_saco();

  /*
  pacote_t *pacote = arruma_pacote();
  int d = 0;
  node_t *Visit = pacote->inicio;
    while (Visit != NULL) {
      printf("peca pac %d = %c %d %d\n",d, Visit->letra, Visit->ponto, Visit->quantidade);
      d++;
      Visit = Visit->prox;
    }

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
   // printf("pos = %d, quantidade elementos = %d\n",pos, saco->num_elementos);
  } 

  //node_t *node = remove_quant_pacote(pacote,0);
  //insere_valor(saco,node->ponto,node->letra);

    peca_t *toVisit = saco->inicio;
    int i=1;
    while (toVisit != NULL) {
      printf("peca %d = %c %d \n",i, toVisit->letra, toVisit->ponto);
      i++;
      toVisit = toVisit->prox;
    }

    Visit = pacote->inicio;
    while (Visit != NULL) {
      printf("peca pac %d = %c %d \n",i, Visit->letra, Visit->ponto);
      i++;
      Visit = Visit->prox;
    }

  destroy_pacote(pacote); */

  





  //distribuir 7 peças pra cada jogador retirando da lista
  

  //teste se as 7 pecas estao sendo distribuidas

/*
  jogo_t *jogo = inicio_jogo ();
  printf("jogo iniciado\n");
  jogador_t *jogador = jogo->inicio;

  for(int i = 0; i < jogo->num_jogadores; i++) {
    printf("pecas jogador %d: ",i+1);
    for (int d = 0; d < 7; d++){
      printf("%c ",jogador->suporte[d]->letra);
    }
    printf("\n");
    jogador=jogador->prox;
  }
*/




  //inicio do jogo, parar so quando o saco estiver vazio
  /*    ->JOGADA: escolher entre:
                  1- trocar todas as pedras
                  2- trocar uma pedra
                  3- formar uma palavra
                  4- pular a vez
                caso 1,2 ou 4 sejam escolhidas, vez do proximo jogador;
                na escolha de 4, aumentar de 1 a quantidade de vezes que pularam a vez;
                se todos pularem a vez seguidas apos duas rodadas(num_jog*2) = fim do jogo;
                caso 1,2 ou 3 sejam escolhidas & pular_a_vez != 0, pular_a_vez = 0;
                caso 3 seja escolhido: FORMANDO PALAVRA:
                  jogador vai selecionar as letras que formarao a palavra (suas posicoes no array suporte)
                  jogador escolhe a posicao que vai a primeira letra (coordenadas matriz) e a direcao que sera escrita a palavra (pra cima, pra baixo, esquerda, direita)
                  PONTUANDO: jogador recebe as pontuacoes de acordo
                  CONFERIR SE A PALAVRA ESTA CERTA: trie ou mapa
                  jogador compra mais ate ter 7 de novo ou ate atingir o fim do saco(comprar_pecas);
                  passa a vez pro prox jogador;

        ->FIM DO JOGO: 
                quant_saco==0 && suporte_algum_jogador == 0 || formar palavras == impossivel || pular_a_vez == num_jog*2;
                subtrair da pontuacao a soma das letras no suporte, acrescentar à sub_total;
                se suporte esta vazio, jogador soma à pontuacao o sub_total;
                apresentar a pontuacao de forma ordenada;
  */

  //teste se imprimir tabuleiro esta funcionando

  /*char tabuleiro[15][15];

  inicia_tabuleiro(tabuleiro);

  tabuleiro[0][0] = 'J';
  tabuleiro[2][4] = 'A';
  tabuleiro[3][12] = 'B';
  tabuleiro[14][14] = 'C';

  imprime_tabuleiro(tabuleiro);

  */




    //teste se trocar_peca esta funcionando
/*
  int a = 1;
  while (a==1) {
    printf("Jogador %d sua vez de jogar\n",jogo->atual->jogador_num);

    printf("Suas pedras são:\n");
    int i = 0;

      for (int d = 0; d < 7; d++){
        if(jogo->atual->suporte[d]->letra != '-'){
          printf("%c ",jogo->atual->suporte[d]->letra);
          i++;
        }
      }
      printf("\n");
      for (int d = 0; d < i; d++){
        printf("%d ",d+1);
      }
      printf("\n");

      printf("Saco:\n");

      peca_t *toVisit = jogo->saco->inicio;
      while (toVisit != NULL) {
        printf("%c ",toVisit->letra);
        toVisit = toVisit->prox;
      }
      printf("\n");

      toVisit = jogo->saco->inicio;
      while (toVisit != NULL) {
        printf("%d ",toVisit->ponto);
        toVisit = toVisit->prox;
      } 
      printf("\n");     

      trocar_peca(jogo);

      printf("Para continuar testando digite 1\n");
      scanf("%d", &a);
  }
*/


    //testar se dicionario esta funcionando
  /*

    FILE *arq = fopen("palavras_validas.txt", "r");

    trie_t *trie = cria_trie();
    char palavra[1040];

    while (fscanf(arq, "%s\n", palavra) != EOF){

     // printf("lido: %s\n",palavra);

      insere_palavra(palavra,trie);

    }

    chamada_busca(trie);

    fclose(arq);

*/

  //testar se jogada esta funcionando

  FILE *arq = fopen("palavras_validas_teste.txt", "r");

  jogo_t *jogo = inicio_jogo(arq);
  printf("Jogo iniciado\n");
  int a=0;
  /*while (a==0){
    jogada(jogo);
    a++;
  } */
  destroy_jogo(jogo);

  fclose(arq);
  


	return 0;
}