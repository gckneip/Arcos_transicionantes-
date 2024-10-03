#include "eval.h"
#include "estruturas.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char *geraTabela(Nodo *arvore, int quantasEntradas, char *entradas) {
  unsigned long int tamanhoVetor = 1ULL << quantasEntradas;
  unsigned char *tabelaVerdade = calloc((tamanhoVetor),sizeof(unsigned char)); // inicia o vetor de resultados com 2^n

  if (tabelaVerdade == NULL) {
        puts("Falha na alocação da tabela verdade.");
        exit(-1);
  }

  for (unsigned long int i = 0; i < tamanhoVetor; i++) {
    tabelaVerdade[i] = percorreArvore(arvore, entradas, quantasEntradas, i);
  }

  return tabelaVerdade;
}

unsigned char percorreArvore(Nodo *raiz, char *variaveis, int quantasEntradas, unsigned long int entrada) {
  int i;
  if (raiz->conteudo == '+') {
    for (i = 0; i < raiz->quantosFilhos; i++) {
      if (procuraZero(raiz->filhos[i], variaveis, quantasEntradas, entrada))
        continue;
      return 1;
    }
  }
  return 0;
}

unsigned char procuraZero(Nodo *raiz, char *variaveis, int quantasEntradas, unsigned long int entrada) {
  int i, j;
  unsigned long int bit;
  for (i = 0; i < raiz->quantosFilhos; i++) {
    if ((raiz->filhos[i]->conteudo >= 'a' && raiz->filhos[i]->conteudo <= 'z') || (raiz->filhos[i]->conteudo >= 'A' && raiz->filhos[i]->conteudo <= 'Z')) {
      for (j = 0; j < quantasEntradas; j++) {
        if (variaveis[j] == raiz->filhos[i]->conteudo) {
          bit = quantasEntradas - j - 1;
          if (((entrada & 1 << bit) >> bit) == 0) {
            return 1;
          }
        }
      }
    }
    if (raiz->filhos[i]->conteudo == '!') {
      for (j = 0; j < quantasEntradas; j++) {
        if (variaveis[j] == raiz->filhos[i]->filhos[0]->conteudo) {
          bit = quantasEntradas - j - 1;
          if (((entrada & 1 << bit) >> bit) == 1) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
