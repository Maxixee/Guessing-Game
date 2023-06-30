#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados para um nó da árvore
typedef struct Node {
    char question[100];
    struct Node* yesNode;
    struct Node* noNode;
} Node;

// Função para criar um novo nó
Node* createNode(const char* question, Node* yesNode, Node* noNode) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->question, question);
    newNode->yesNode = yesNode;
    newNode->noNode = noNode;
    return newNode;
}

// Função para liberar a memória ocupada pela árvore
void freeTree(Node* currentNode) {
    if (currentNode == NULL)
        return;

    freeTree(currentNode->yesNode);
    freeTree(currentNode->noNode);
    free(currentNode);
}

// Função para jogar o jogo de adivinhação
void playGame(Node* currentNode) {
    if (currentNode->yesNode == NULL && currentNode->noNode == NULL) {
        // Nó folha - adivinhação concluída
        printf("Eu acho que o objeto é: %s\n", currentNode->question);

        char answer;
        printf("Estou certo? (s/n): ");
        scanf(" %c", &answer);

        if (answer == 's') {
            printf("Que bom! Acertei de novo!\n");
        } else if (answer == 'n') {
            char newObject[100];
            printf("Qual era o objeto? ");
            scanf(" %[^\n]", newObject);

            char newQuestion[100];
            printf("Digite uma pergunta para distinguir %s de %s: ", newObject, currentNode->question);
            scanf(" %[^\n]", newQuestion);

            char yesOrNo;
            printf("Para o objeto %s, qual é a resposta para a pergunta '%s'? (s/n): ", newObject, newQuestion);
            scanf(" %c", &yesOrNo);

            Node* newYesNode;
            Node* newNoNode;

            if (yesOrNo == 's') {
                newYesNode = createNode(newObject, NULL, NULL);
                newNoNode = createNode(currentNode->question, NULL, NULL);
            } else {
                newYesNode = createNode(currentNode->question, NULL, NULL);
                newNoNode = createNode(newObject, NULL, NULL);
            }

            strcpy(currentNode->question, newQuestion);
            currentNode->yesNode = newYesNode;
            currentNode->noNode = newNoNode;

            printf("Obrigado por me ensinar algo novo!\n");
        } else {
            // Resposta inválida
            printf("Resposta inválida. Por favor, responda com 's' para sim ou 'n' para não.\n");
        }
    } else {
        // Pergunta atual
        printf("%s (s/n): ", currentNode->question);

        char answer;
        scanf(" %c", &answer);

        if (answer == 's') {
            // Movimenta-se para o nó da resposta "sim"
            playGame(currentNode->yesNode);
        } else if (answer == 'n') {
            // Movimenta-se para o nó da resposta "não"
            playGame(currentNode->noNode);
        } else {
            // Resposta inválida
            printf("Resposta inválida. Por favor, responda com 's' para sim ou 'n' para não.\n");
            playGame(currentNode);
        }
    }
}

int main() {
    // Criação da árvore de perguntas e respostas
    Node* rootNode = createNode("É um animal?", NULL, NULL);
    rootNode->yesNode = createNode("Ele late?", createNode("Cachorro", NULL, NULL), createNode("Gato", NULL, NULL));
    rootNode->noNode = createNode("É um objeto?", createNode("Carro", NULL, NULL), createNode("Casa", NULL, NULL));

    // Início do jogo
    printf("Bem-vindo ao jogo de adivinhação!\n");

    char playAgain;
    do {
        playGame(rootNode);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &playAgain);
        printf("\n");

    } while (playAgain == 's');

    // Libera a memória da árvore
    freeTree(rootNode);

    return 0;
}