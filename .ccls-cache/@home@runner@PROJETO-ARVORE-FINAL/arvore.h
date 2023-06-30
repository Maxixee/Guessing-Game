//arvore.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados para um nó da árvore
typedef struct No {
    char pergunta[100];
    struct No* simNo;
    struct No* naoNo;
} No;

No* criaNo(const char* pergunta, No* simNo, No* naoNo);
void libera_Arvore(No* no_atual);
void jogar(No* no_atual);