#include "model/bilheteria.h"

#include "model/struct.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Inicializa o sistema de bilheteria
void inicializarBilheteria(Bilheteria *bilheteria) {
    bilheteria->num_filmes = 0;
    bilheteria->num_bilhetes = 0;
    bilheteria->proximo_numero_bilhete = 1;
    bilheteria->isAdmin = false;
    // Inicializa a sala com todos os lugares disponíveis
    for (int f = 0; f < MAX_SALAS; f++) {
        for (int i = 0; i < MAX_LINHAS; i++) {
            for (int j = 0; j < MAX_COLUNAS; j++) {
                bilheteria->sala[f][i][j] = 'D';
            }
        }
    }
}

void alocarFilmes(Bilheteria *bilheteria) {
    bilheteria->filmes = NULL;
    bilheteria->num_filmes = 0;
}

// Adiciona um filme à lista de filmes disponíveis
void adicionarFilme(Bilheteria *bilheteria, const char *nome,
                    const char *data) {
    // Realoca espaço para mais 1 filme
    Filme *novo_filmes = (Filme *) realloc(bilheteria->filmes,
                                           (bilheteria->num_filmes + 1) * sizeof
                                           (Filme));
    if (novo_filmes == NULL) {
        printf("Erro ao alocar memoria para novo filme.\n");
        exit(1);
    }

    bilheteria->filmes = novo_filmes; // Atualiza o ponteiro após realocar
    strncpy(bilheteria->filmes[bilheteria->num_filmes].nome, nome, MAX_NOME - 1);
    bilheteria->filmes[bilheteria->num_filmes].nome[MAX_NOME - 1] = '\0';
    bilheteria->filmes[bilheteria->num_filmes].data_lancamento =
            ExtrairData(data);
    bilheteria->filmes[bilheteria->num_filmes].sala = bilheteria->num_filmes + 1;
    bilheteria->num_filmes++;
}

void liberarFilmes(Bilheteria *bilheteria) {
    free(bilheteria->filmes);
    bilheteria->filmes = NULL;
    bilheteria->num_filmes = 0;
}

void LimparSalas(Bilheteria *bilheteria) {
    for (int f = 1; f <= bilheteria->num_filmes; f++) {
        for (int i = 0; i < MAX_LINHAS; i++) {
            for (int j = 0; j < MAX_COLUNAS; j++) {
                bilheteria->sala[f][i][j] = 'D';
            }
        }
    }
    printf("Salas zeradas!\n");
    system("pause");
}

// Função criada usando por base o selection sort
void filmeSort(const Bilheteria *bilheteria, Filme filmes[]) {
    for (int i = 0; i < bilheteria->num_filmes; i++) {
        filmes[i] = bilheteria->filmes[i];
    }

    for (int i = 0; i < bilheteria->num_filmes; ++i) {
        for (int j = i + 1; j < bilheteria->num_filmes; ++j) {
            // Pega as datas dos dois filmes
            Data d1 = filmes[i].data_lancamento;
            Data d2 = filmes[j].data_lancamento;

            // Compara do mais recente pro mais antigo
            if ((d2.ano > d1.ano) ||
                (d2.ano == d1.ano && d2.mes > d1.mes) ||
                (d2.ano == d1.ano && d2.mes == d1.mes && d2.dia > d1.dia)) {
                Filme temp = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = temp;
                }
        }
    }
}

int traduzirCoordenada(const char *entrada, int *linha, int *coluna) {
    if (strlen(entrada) < 2) return 0; // Tamanho mínimo "A1"

    const char letra = (char) toupper(entrada[0]);
    if (letra < 'A' || letra >= 'A' + MAX_LINHAS) return 0;

    // Pega o resto como número (ex: "10" de "A10")
    const int numero = atoi(&entrada[1]);
    if (numero < 1 || numero > MAX_COLUNAS) return 0;

    *linha = letra - 'A' + 1; // Transforma A = 1, B = 2, etc.
    *coluna = numero;

    return 1; // Sucesso
}

void DeletarBilhete(Bilheteria *bilheteria, int ingresso, int sala) {
    int max = bilheteria->num_bilhetes;
    int min = 0;

    while (min <= max) {
        int metade = min + (max - min) / 2;

        if (ingresso == bilheteria->bilhetes[metade].numero_bilhete) {
            int coluna = bilheteria->bilhetes[0].coluna;
            int fileira = bilheteria->bilhetes[0].fileira;

            bilheteria->sala[sala][coluna][fileira] = 'D';

            for (int f = metade; f <= bilheteria->num_bilhetes; f++) {
                bilheteria->bilhetes[f] = bilheteria->bilhetes[f + 1];
            }

            bilheteria->num_bilhetes--;
            printf("\n✅ Bilhete nº %d cancelado com sucesso!\n", ingresso);
        }
        if (ingresso > metade) {
            min = metade + 1;
        } else {
            max = metade - 1;
        }
    }
}

Data ExtrairData(const char *s) {
    while (*s) {
        int n = 0;

        sscanf(s, "%*2[0-9]-%*2[0-9]-%*4[0-9]%n", &n);
        if (n > 0) {
            int day = 0;
            int month = 0;
            int year = 0;
            sscanf(s, "%d-%d-%d", &day, &month, &year);
            s += n;
            Data date = {day, month, year};
            return date;
        } else {
            s++;
        }
    }
    Data invalid_date = {0, 0, 0};
    return invalid_date;
}