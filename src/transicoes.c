#include "transicoes.h"
#include <stdlib.h>
#include <stdio.h>

void imprimeArcos (unsigned char * tabelaVerdade, char * operandos, int quantosOperandos){

  unsigned long int peso, i, j, l = 0;
  int k;
  unsigned long int indiceTabela = 0, indiceTabelaArco;
  unsigned long int tamanhoVetor = quantosOperandos - 1ULL;
  
  char *arco = calloc(sizeof(char), quantosOperandos+1ULL);
  
  if (arco == NULL){
    fputs("Nao foi possivel alocar memoria para a tabela verdade", stderr);
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < (unsigned long int)quantosOperandos; i++) {
    for (j = 0; j < (unsigned long int)(1ULL << tamanhoVetor); j++) {
      for (k = quantosOperandos - 1; k >= 0; k--) {
        peso = (quantosOperandos - 1ULL) - k;
        if ((unsigned int)k != i) {
          indiceTabela += ((j & 1ULL << l) >> l) * (1ULL << peso); //faz o (UL)l
          arco[k] = '0' + ((j & 1ULL << l) >> l);
          l++;
          continue;
        }
        arco[k]=operandos[i];
      }
      indiceTabelaArco = indiceTabela + (unsigned long int)(1ULL << (tamanhoVetor - i));
      if(tabelaVerdade[indiceTabela] != tabelaVerdade[indiceTabelaArco]){
        printf("%s\n", arco);
      }
      l = 0;
      indiceTabela = 0;
    }
  }

  free(arco);
}
