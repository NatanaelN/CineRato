//
// Created by natan on 4/18/2025.
//

#include "bilhete.h"
#include "utils.h"

// Busca um bilhete pelo número (BUSCA BINÁRIA - a lista de bilhetes precisará estar ordenada)
int buscarBilhete(Bilheteria *bilheteria, const int numero_bilhete) {
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

// Imprime as informações de um bilhete
void imprimirBilhete(Bilheteria *bilheteria, const int indice_bilhete) {
    setlocale(LC_ALL, "");
    if (indice_bilhete >= 0 && indice_bilhete < bilheteria->num_bilhetes) {
        printf("\n%s%s=************ Bilheteria CineRatao ************=%s\n\n",
               NEGRITO, VERDE_BASICO,
               LIMPAR);
        printf("| Bilhete Nº:\t%d\t|\n",
               bilheteria->bilhetes[indice_bilhete].numero_bilhete);
        printf("| Filme:\t%s\t|\n",
               bilheteria->bilhetes[indice_bilhete].nome_filme);
        printf("| Poltrona:\t%c%d\t|\n",
               65 + (bilheteria->bilhetes[indice_bilhete].fileira - 1),
               bilheteria->bilhetes[indice_bilhete].coluna);
        printf("| Cliente:\t%s\t|\n",
               bilheteria->bilhetes[indice_bilhete].nome_cliente);
        printf("| Ingresso:\t%s\t|\n",
               bilheteria->bilhetes[indice_bilhete].tipo_ingresso);
        printf("%s%s================================================%s\n",
               NEGRITO, VERDE_BASICO,
               LIMPAR);
    } else {
        printf("Bilhete nao encontrado.\n");
        getchar();
    }
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

// Lista todos os bilhetes emitidos (ordenados conforme o critério)
void listarBilhetes(Bilheteria *bilheteria, int criterio_ordenacao) {
    setlocale(LC_ALL, "");
    if (bilheteria->num_bilhetes > 0) {
        Bilhete bilhetes_ordenados[bilheteria->num_bilhetes];
        memcpy(bilhetes_ordenados, bilheteria->bilhetes,
               sizeof(bilheteria->bilhetes[0]) * bilheteria->num_bilhetes);

        printf("\n=************ %sRelatorio de Bilhetes%s ************=\n",
               AZUL_BASICO, LIMPAR);
        switch (criterio_ordenacao) {
            case 1: // Número crescente
                qsort(bilhetes_ordenados, bilheteria->num_bilhetes,
                      sizeof(Bilhete), compararBilhetesPorNumeroCrescente);
                printf("%sOrdenacao crescente%s:\n", AZUL_BASICO, LIMPAR);
                break;
            case 2: // Número decrescente
                qsort(bilhetes_ordenados, bilheteria->num_bilhetes,
                      sizeof(Bilhete), compararBilhetesPorNumeroDecrescente);
            printf("%sOrdenacao decrescente%s:\n", AZUL_BASICO, LIMPAR);
                break;
            case 3: // Tipo de ingresso
                qsort(bilhetes_ordenados, bilheteria->num_bilhetes,
                      sizeof(Bilhete), compararBilhetesPorTipoIngresso);
                printf("%sOrdenado por tipo de ingresso%s:\n", AZUL_BASICO, LIMPAR);
                break;
            default:
                printf(
                    "Criterio de ordenacao invalido. Exibindo na ordem de emissao:\n");
                break;
        }

        printf("| Bilhete\t| Filme\t| Poltrona\t| Cliente\t| Tipo\t|\n");
        for (int i = 0; i < bilheteria->num_bilhetes; i++) {
            printf("| %d\t| %s\t| %c%d\t| %s\t| %s\t|\n",
                   bilhetes_ordenados[i].numero_bilhete,
                   bilhetes_ordenados[i].nome_filme,
                   65 + (bilhetes_ordenados[i].fileira - 1),
                   bilhetes_ordenados[i].coluna,
                   bilhetes_ordenados[i].nome_cliente,
                   bilhetes_ordenados[i].tipo_ingresso);
        }
        printf(
            "%s================================================%s\n",
            AZUL_BASICO, LIMPAR);
    } else {
        printf("Nenhum bilhete emitido.\n");
    }
}
