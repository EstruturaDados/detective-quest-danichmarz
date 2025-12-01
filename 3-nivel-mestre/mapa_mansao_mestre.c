/*
 * =====================================================================
 * DETECTIVE QUEST - NIVEL MESTRE
 * Sistema Completo: Arvore + BST + Hash Table
 * =====================================================================
 * Autora: Daniela Chiavenato Marzagao
 * Data: Novembro/2025
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* proximo;
} HashNode;

typedef struct {
    HashNode* tabela[TAM_HASH];
} TabelaHash;

int funcaoHash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_HASH;
}

void inicializarHash(TabelaHash* th) {
    for (int i = 0; i < TAM_HASH; i++) {
        th->tabela[i] = NULL;
    }
}

void inserirHash(TabelaHash* th, char* pista, char* suspeito) {
    int indice = funcaoHash(pista);
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = th->tabela[indice];
    th->tabela[indice] = novo;
}

char* buscarSuspeito(TabelaHash* th, char* pista) {
    int indice = funcaoHash(pista);
    HashNode* atual = th->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

Sala* criarSala(char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
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

void contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* th, char* suspeito, int* contador) {
    if (raiz != NULL) {
        contarPistasPorSuspeito(raiz->esquerda, th, suspeito, contador);
        
        char* susp = buscarSuspeito(th, raiz->pista);
        if (susp != NULL && strcmp(susp, suspeito) == 0) {
            (*contador)++;
        }
        
        contarPistasPorSuspeito(raiz->direita, th, suspeito, contador);
    }
}

char* obterPista(char* nomeSala) {
    if (strcmp(nomeSala, "Sala de Estar") == 0) return "Cinzas na lareira";
    if (strcmp(nomeSala, "Cozinha") == 0) return "Faca suja";
    if (strcmp(nomeSala, "Biblioteca") == 0) return "Livro aberto";
    if (strcmp(nomeSala, "Escritorio") == 0) return "Carta rasgada";
    if (strcmp(nomeSala, "Despensa") == 0) return "Veneno";
    if (strcmp(nomeSala, "Jardim") == 0) return "Pegadas na lama";
    return NULL;
}

PistaNode* explorar(Sala* atual, PistaNode* pistas) {
    char escolha;
    
    while (atual != NULL) {
        printf("\n>>> %s\n", atual->nome);
        
        char* pista = obterPista(atual->nome);
        if (pista != NULL) {
            printf(">>> PISTA: %s\n", pista);
            pistas = inserirPista(pistas, pista);
        }
        
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf(">>> Fim!\n");
            return pistas;
        }
        
        printf("\n(e)Esquerda (d)Direita (s)Sair: ");
        scanf(" %c", &escolha);
        
        if (escolha == 's') return pistas;
        else if (escolha == 'e' && atual->esquerda != NULL) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita != NULL) atual = atual->direita;
    }
    return pistas;
}

int main() {
    printf("=====================================================\n");
    printf("     DETECTIVE QUEST - INVESTIGACAO COMPLETA\n");
    printf("=====================================================\n\n");
    
    Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Escritorio");
    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Jardim");
    
    TabelaHash th;
    inicializarHash(&th);
    
    inserirHash(&th, "Cinzas na lareira", "Sr. Mostarda");
    inserirHash(&th, "Faca suja", "Sra. Peacock");
    inserirHash(&th, "Livro aberto", "Sr. Mostarda");
    inserirHash(&th, "Carta rasgada", "Prof. Plum");
    inserirHash(&th, "Veneno", "Sra. Peacock");
    inserirHash(&th, "Pegadas na lama", "Sr. Mostarda");
    
    PistaNode* pistas = NULL;
    pistas = explorar(hall, pistas);
    
    printf("\n=====================================================\n");
    printf("       HORA DE ACUSAR!\n");
    printf("=====================================================\n");
    printf("Suspeitos: Sr. Mostarda, Sra. Peacock, Prof. Plum\n");
    printf("Quem e o culpado? ");
    
    char acusado[50];
    scanf(" %[^\n]", acusado);
    
    int contador = 0;
    contarPistasPorSuspeito(pistas, &th, acusado, &contador);
    
    printf("\n>>> Pistas contra %s: %d\n", acusado, contador);
    
    if (contador >= 2) {
        printf("\n*** CASO RESOLVIDO! %s e o culpado! ***\n", acusado);
    } else {
        printf("\n*** Evidencias insuficientes! ***\n");
    }
    
    printf("=====================================================\n");
    return 0;
}