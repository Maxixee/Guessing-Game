#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main() {
    // Criação da árvore de perguntas e respostas
    No* partida_no = criaNo("É um animal domestico?", NULL, NULL);
    partida_no->simNo = criaNo("Ele late?", criaNo("Cachorro", NULL, NULL), criaNo("Gato", NULL, NULL));
    partida_no->naoNo = criaNo("Eh carnivoro?", criaNo("Leao", NULL, NULL), criaNo("Girafa", NULL, NULL));

    // Início do jogo
    printf("Bem-vindo ao jogo de adivinhação!\n");

    char jogar_novamente;
    do {
        jogar(partida_no);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogar_novamente);
        printf("\n");

    } while (jogar_novamente == 's');

    // Libera a memória da árvore
    libera_Arvore(partida_no);

    return 0;
}