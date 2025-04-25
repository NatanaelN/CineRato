//
// Created by natan on 4/18/2025.
//

#ifndef BILHETE_H
#define BILHETE_H

#include "utils.h"

int buscarBilhete(Bilheteria *bilheteria, int numero_bilhete);

void imprimirBilhete(Bilheteria *bilheteria, int indice_bilhete);

int compararBilhetesPorNumeroCrescente(const void *a, const void *b);

int compararBilhetesPorNumeroDecrescente(const void *a, const void *b);

int compararBilhetesPorTipoIngresso(const void *a, const void *b);

void listarBilhetes(Bilheteria *bilheteria, int criterio_ordenacao);

#endif //BILHETE_H
