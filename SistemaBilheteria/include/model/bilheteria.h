#ifndef BILHETERIA_H
#define BILHETERIA_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/struct.h"

void inicializarBilheteria(Bilheteria *bilheteria);
void alocarFilmes(Bilheteria *bilheteria);
void adicionarFilme(Bilheteria *bilheteria, const char *nome, const char *data);
void liberarFilmes(Bilheteria *bilheteria);
void LimparSalas(Bilheteria *bilheteria);
void filmeSort(const Bilheteria *bilheteria, Filme filmes[]);
int traduzirCoordenada(const char *entrada, int *linha, int *coluna);
void DeletarBilhete(Bilheteria *bilheteria, int ingresso, int sala);
Data ExtrairData(const char *s);

#endif // BILHETERIA_H
