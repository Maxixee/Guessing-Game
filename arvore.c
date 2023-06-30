//arvore.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"


// Função para criar um novo nó
No* criaNo(const char* pergunta, No* simNo, No* naoNo) {
    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->pergunta, pergunta);
    novoNo->simNo = simNo;
    novoNo->naoNo = naoNo;
    return novoNo;
}

// Função para liberar a memória ocupada pela árvore
void libera_Arvore(No* no_atual) {
    if (no_atual == NULL)
        return;

    libera_Arvore(no_atual->simNo);
    libera_Arvore(no_atual->naoNo);
    free(no_atual);
}

// Função para jogar o jogo de adivinhação
void jogar(No* no_atual) {
    if (no_atual->simNo == NULL && no_atual->naoNo == NULL) {
        // Nó folha - adivinhação concluída
        printf("Eu acho que o animal é: %s\n", no_atual->pergunta);

        char resposta;
        printf("Estou certo? (s/n): ");
        scanf(" %c", &resposta);

        if (resposta == 's') {
            system("clear");
            printf("Que bom! Acertei de novo!\n");
        } else if (resposta == 'n') {
            char novo_animal[100];
            system("clear");
            printf("Qual era o animal? ");
            scanf(" %[^\n]", novo_animal);

            char nova_pergunta[100];
            printf("Digite uma pergunta para distinguir %s de %s: ", novo_animal, no_atual->pergunta);
            scanf(" %[^\n]", nova_pergunta);

            char yesOrNo;
            printf("Para o animal %s, qual é a resposta para a pergunta '%s'? (s/n): ", novo_animal, nova_pergunta);
            scanf(" %c", &yesOrNo);

            No* novo_simNo;
            No* novo_naoNo;

            if (yesOrNo == 's') {
                novo_simNo = criaNo(novo_animal, NULL, NULL);
                novo_naoNo = criaNo(no_atual->pergunta, NULL, NULL);
            } else {
                novo_simNo = criaNo(no_atual->pergunta, NULL, NULL);
                novo_naoNo = criaNo(novo_animal, NULL, NULL);
            }

            strcpy(no_atual->pergunta, nova_pergunta);
            no_atual->simNo = novo_simNo;
            no_atual->naoNo = novo_naoNo;

            printf("\nObrigado por me ensinar algo novo!!!!!!\n");
        } else {
            printf("Resposta inválida. Por favor, responda com 's' para sim ou 'n' para não.\n");
        }
    } else {
        // Pergunta atual
        printf("%s (s/n): ", no_atual->pergunta);

        char resposta;
        scanf(" %c", &resposta);

        if (resposta == 's') {
            // Movimenta-se para o nó da resposta "sim"
            jogar(no_atual->simNo);
        } else if (resposta == 'n') {
            // Movimenta-se para o nó da resposta "não"
            jogar(no_atual->naoNo);
        } else {
            // Resposta inválida
            printf("Resposta inválida. Por favor, responda com 's' para sim ou 'n' para não.\n");
            jogar(no_atual);
        }
    }
}