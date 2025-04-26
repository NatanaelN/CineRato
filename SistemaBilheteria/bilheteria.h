//
// Created by natan on 4/18/2025.
//

#ifndef BILHETERIA_H
#define BILHETERIA_H

#include <stdbool.h>

#include "utils.h"

void DeletarBilhete(Bilheteria *bilheteria, int ingresso, int sala);

void inicializarBilheteria(Bilheteria *bilheteria);

void adicionarFilme(Bilheteria *bilheteria, const char *nome, const char *data);

void exibirFilmes(Bilheteria *bilheteria);

void LimparSalas(Bilheteria *bilheteria);

bool Login();

void exibirLancamentos(Bilheteria *bilheteria);

void filmeSort(Bilheteria *bilheteria, Filme filmes[]);

void exibirSala(Bilheteria *bilheteria, int sala);

int reservarLugar(Bilheteria *bilheteria, int linha, int coluna,
                  const char *nome_cliente, const char *tipo_ingresso,
                  const Filme filme);

int traduzirCoordenada(const char *entrada, int *linha, int *coluna);

void solicitarReserva(Bilheteria *bilheteria, const Filme filme);

Data ExtrairData(const char *s);

#endif //BILHETERIA_H
