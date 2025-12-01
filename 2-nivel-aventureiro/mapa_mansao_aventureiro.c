/*
 * =====================================================================
 * DETECTIVE QUEST - NIVEL AVENTUREIRO
 * Mapa + BST de Pistas
 * =====================================================================
 * Autora: Daniela Chiavenato Marzagao
 * Data: Novembro/2025
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista != NULL ? pista : "");
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

PistaNode* inserirPista(PistaNode* raiz, char* pista) {
    if (raiz == NULL) {
        PistaNode* nova = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
        return nova;
    }
    
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    
    return raiz;
}

void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("  - %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

PistaNode* explorarComPistas(Sala* atual, PistaNode* pistasColetadas) {
    char escolha;
    
    while (atual != NULL) {
        printf("\n>>> Voce esta em: %s\n", atual->nome);
        
        if (strlen(atual->pista) > 0) {
            printf(">>> PISTA ENCONTRADA: %s\n", atual->pista);
            pistasColetadas = inserirPista(pistasColetadas, atual->pista);
        }
        
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf(">>> Fim do caminho!\n");
            return pistasColetadas;
        }
        
        printf("\nPara onde?\n");
        if (atual->esquerda != NULL) printf("  (e) Esquerda\n");
        if (atual->direita != NULL) printf("  (d) Direita\n");
        printf("  (s) Sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
        
        if (escolha == 's' || escolha == 'S') {
            return pistasColetadas;
        } else if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) atual = atual->direita;
        }
    }
    
    return pistasColetadas;
}

int main() {
    printf("=====================================================\n");
    printf("     DETECTIVE QUEST - COLETA DE PISTAS\n");
    printf("=====================================================\n\n");
    
    Sala* hall = criarSala("Hall de Entrada", NULL);
    hall->esquerda = criarSala("Sala de Estar", "Cinzas na lareira");
    hall->direita = criarSala("Cozinha", "Faca suja");
    
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro aberto");
    hall->esquerda->direita = criarSala("Escritorio", "Carta rasgada");
    
    hall->direita->esquerda = criarSala("Despensa", "Veneno");
    hall->direita->direita = criarSala("Jardim", "Pegadas na lama");
    
    PistaNode* pistas = NULL;
    
    printf(">>> Explore e colete pistas!\n");
    pistas = explorarComPistas(hall, pistas);
    
    printf("\n=====================================================\n");
    printf("       PISTAS COLETADAS (em ordem)\n");
    printf("=====================================================\n");
    exibirPistas(pistas);
    
    printf("=====================================================\n");
    return 0;
}