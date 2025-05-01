//
// Created by natan on 4/18/2025.
//

#ifndef BILHETE_H
#define BILHETE_H

#include <string.h>

#include "model/struct.h"


// Protótipos das funções (buscarBilhete, comparadores…)
void alocarBilhetes(Bilheteria *bilheteria);

void liberarBilheteria(Bilheteria *bilheteria);

int buscarBilhete(Bilheteria *bilheteria, int numero_bilhete);

int compararBilhetesPorNumeroCrescente(const void *a, const void *b);

int compararBilhetesPorNumeroDecrescente(const void *a, const void *b);

int compararBilhetesPorTipoIngresso(const void *a, const void *b);


#endif // BILHETE_H
