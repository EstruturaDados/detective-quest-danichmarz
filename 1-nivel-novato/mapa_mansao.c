/*
 * =====================================================================
 * DETECTIVE QUEST - NIVEL NOVATO
 * Exploracao da Mansao com Arvore Binaria
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
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void explorarSalas(Sala* atual) {
    char escolha;
    
    while (atual != NULL) {
        printf("\n>>> Voce esta em: %s\n", atual->nome);
        
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf(">>> Esta sala nao tem mais saidas!\n");
            printf(">>> Fim da exploracao.\n");
            return;
        }
        
        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL) printf("  (e) Esquerda\n");
        if (atual->direita != NULL) printf("  (d) Direita\n");
        printf("  (s) Sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
        
        if (escolha == 's' || escolha == 'S') {
            printf("\n>>> Saindo da exploracao...\n");
            return;
        } else if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf(">>> Nao ha caminho a esquerda!\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf(">>> Nao ha caminho a direita!\n");
            }
        } else {
            printf(">>> Opcao invalida!\n");
        }
    }
}

int main() {
    printf("=====================================================\n");
    printf("       DETECTIVE QUEST - EXPLORACAO DA MANSAO\n");
    printf("=====================================================\n\n");
    
    // Cria o mapa da mansao
    Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");
    
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Escritorio");
    
    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Jardim");
    
    printf(">>> Bem-vindo a mansao!\n");
    printf(">>> Explore os comodos para encontrar pistas.\n");
    
    explorarSalas(hall);
    
    printf("\n=====================================================\n");
    printf("Exploracao encerrada!\n");
    printf("=====================================================\n");
    
    return 0;
}