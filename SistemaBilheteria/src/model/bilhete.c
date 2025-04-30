//
// Created by natan on 4/18/2025.
//

#include "model/bilhete.h"

#include "model/struct.h"

#include <string.h>


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