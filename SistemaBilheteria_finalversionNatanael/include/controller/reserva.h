//
// Created by natan on 30/04/2025.
//

#ifndef RESERVA_H
#define RESERVA_H

#include <locale.h>
#include <stdio.h>

#include "controller/storage.h"

// Reserva um lugar na sala
int reservarLugar(Bilheteria *bilheteria, const int linha, const int coluna, const char *nome_cliente,
                  const char *tipo_ingresso, const Filme filme);


#endif //RESERVA_H
