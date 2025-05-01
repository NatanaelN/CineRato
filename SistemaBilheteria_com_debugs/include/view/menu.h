//
// Created by natan on 29/04/2025.
//

#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "controller/reserva.h"
#include "model/bilheteria.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool Login();
void solicitarReserva(Bilheteria *bilheteria, const Filme filme);

#endif //MENU_H
