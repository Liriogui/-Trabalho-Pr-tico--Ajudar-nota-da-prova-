#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Nome: Índice Invertido
    Autor: Guilherme Lirioberto da Silva Alves
    Descrição: Este programa lê um arquivo de texto e cria um índice invertido,
               mostrando as palavras e as linhas em que aparecem, junto com a
               quantidade de ocorrências em cada linha.
*/

struct nodo {
    int linha;
    int contador;
    struct nodo* proximo;
};

struct dicionario {
    char palavra[50];
    struct nodo* lista;
};

struct dicionario vetor[1000]; 
int total_palavras = 0; 

int procurar_palavra(char *palavra) {
    for(int i = 0; i < total_palavras; i++) {
        if(strcmp(vetor[i].palavra, palavra) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    char linha[1000];
    int numero_linha = 1;

    while(fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *pedaco = strtok(linha, " ,.!?;:");
        while(pedaco != NULL) {
            for(int i = 0; pedaco[i]; i++) {
                pedaco[i] = tolower(pedaco[i]);
            }

            int pos = procurar_palavra(pedaco);
            if(pos == -1) {
                strcpy(vetor[total_palavras].palavra, pedaco);
                vetor[total_palavras].lista = NULL;
                pos = total_palavras;
                total_palavras++;
            }

          
            struct nodo *atual = vetor[pos].lista;
            struct nodo *anterior = NULL;
            int encontrou = 0;

            while(atual != NULL) {
                if(atual->linha == numero_linha) {
                    atual->contador++;
                    encontrou = 1;
                    break;
                }
                anterior = atual;
                atual = atual->proximo;
            }

            if(!encontrou) {
                struct nodo *novo = malloc(sizeof(struct nodo));
                novo->linha = numero_linha;
                novo->contador = 1;
                novo->proximo = NULL;

                if(vetor[pos].lista == NULL) {
                    vetor[pos].lista = novo;
                } else {
                    anterior->proximo = novo;
                }
            }

            pedaco = strtok(NULL, " ,.!?;:");
        }
        numero_linha++; 
    }

    printf("\nÍndice Invertido:\n");
    for(int i = 0; i < total_palavras; i++) {
        printf("%s : ", vetor[i].palavra);
        struct nodo *atual = vetor[i].lista;
        while(atual != NULL) {
            printf("(%d,%d)", atual->linha, atual->contador);
            if(atual->proximo != NULL) printf(", ");
            atual = atual->proximo;
        }
        printf("\n");
    }

    for(int i = 0; i < total_palavras; i++) {
        struct nodo *atual = vetor[i].lista;
        while(atual != NULL) {
            struct nodo *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    fclose(arquivo);
    return 0;
}



// Fontes: https://www.geeksforgeeks.org/linked-list-set-1-introduction/   https://www.tutorialspoint.com/cprogramming/c_file_io.htm  https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
