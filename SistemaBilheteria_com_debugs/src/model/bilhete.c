//
// Created by natan on 4/18/2025.
//

#include "model/bilhete.h"


#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "controller/storage.h"
#include "model/bilheteria.h"
#include "model/struct.h"


void alocarBilhetes(Bilheteria *bilheteria) {
    bilheteria->bilhetes = (Bilhete *) malloc(MAX_LINHAS * MAX_COLUNAS * sizeof(Bilhete));
    if (bilheteria->bilhetes == NULL) {
        perror("Erro ao alocar memoria para bilhetes");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    bilheteria->num_bilhetes = 0; // Garante que o contador comece em 0
}

// Lembre-se de criar uma função para liberar essa memória ao final do programa
void liberarBilheteria(Bilheteria *bilheteria) {
    liberarFilmes(bilheteria);
    // Mover os arquivos de bilhetes para a pasta de obsoletos
    if (bilheteria->bilhetes != NULL) {
        for (int i = 0; i < bilheteria->num_bilhetes; i++) {
            char nome_arquivo_original[150];
            char nome_arquivo_obsoleto[150];

            // Construir o caminho original do arquivo
            snprintf(nome_arquivo_original, sizeof(nome_arquivo_original), "..//data//bilhete_%03d.txt",
                     bilheteria->bilhetes[i].numero_bilhete);

            // Construir o novo caminho para a pasta de obsoletos
            snprintf(nome_arquivo_obsoleto, sizeof(nome_arquivo_obsoleto), "./obsoletes_bilhetes/bilhete_%03d.txt",
                     bilheteria->bilhetes[i].numero_bilhete);

            // Tentar mover o arquivo
            if (rename(nome_arquivo_original, nome_arquivo_obsoleto) == 0) {
                printf("Bilhete '%s' movido para '%s'.\n", nome_arquivo_original, nome_arquivo_obsoleto);
            } else {
                perror("Erro ao mover bilhete");
            }
        }
        free(bilheteria->bilhetes);
        bilheteria->bilhetes = NULL;
        bilheteria->num_bilhetes = 0;
        // ... outras liberações ...
    }
}


// Busca um bilhete pelo número (BUSCA BINÁRIA - a lista de bilhetes precisará estar ordenada)
int buscarBilhete(Bilheteria *bilheteria, int numero_bilhete) {
    // Assumindo que a lista de bilhetes está ordenada pelo número_bilhete
    int esquerda = 0;
    int direita = bilheteria->num_bilhetes - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (bilheteria->bilhetes[meio].numero_bilhete == numero_bilhete) {
            return meio; // Retorna o índice do bilhete encontrado
        } else if (bilheteria->bilhetes[meio].numero_bilhete < numero_bilhete) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // Bilhete não encontrado
}


// Função de comparação para ordenar bilhetes por número (crescente)
int compararBilhetesPorNumeroCrescente(const void *a, const void *b) {
    const Bilhete *bilheteA = (const Bilhete *) a;
    const Bilhete *bilheteB = (const Bilhete *) b;

    return bilheteA->numero_bilhete - bilheteB->numero_bilhete;
}

// Função de comparação para ordenar bilhetes por número (decrescente)
int compararBilhetesPorNumeroDecrescente(const void *a, const void *b) {
    const Bilhete *bilheteA = (const Bilhete *) a;
    const Bilhete *bilheteB = (const Bilhete *) b;

    return bilheteB->numero_bilhete - bilheteA->numero_bilhete;
}

// Função de comparação para ordenar bilhetes por tipo de ingresso
int compararBilhetesPorTipoIngresso(const void *a, const void *b) {
    const Bilhete *bilheteA = (const Bilhete *) a;
    const Bilhete *bilheteB = (const Bilhete *) b;

    return strcmp(bilheteA->tipo_ingresso, bilheteB->tipo_ingresso);
}
