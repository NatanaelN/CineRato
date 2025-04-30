//
// Created by natan on 4/18/2025.
//

#ifndef BILHETE_H
#define BILHETE_H

#include "model/struct.h"

#include <string.h>



// Protótipos das funções (buscarBilhete, comparadores…)
int buscarBilhete(Bilheteria *bilheteria, int numero_bilhete);
int compararBilhetesPorNumeroCrescente(const void *a, const void *b);
int compararBilhetesPorNumeroDecrescente(const void *a, const void *b);
int compararBilhetesPorTipoIngresso(const void *a, const void *b);


#endif // BILHETE_H
