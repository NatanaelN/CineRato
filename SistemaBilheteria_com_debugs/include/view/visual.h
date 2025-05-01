//
// Created by natan on 29/04/2025.
//

#ifndef VISUAL_H
#define VISUAL_H


#include "model/bilheteria.h"
#include "model/bilhete.h"
#include "model/struct.h"
#include "common.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMCAIXA 58

void exibirFilmes(Bilheteria *bilheteria);

void exibirSala(Bilheteria *bilheteria, int sala);

void criacao_caixa(const int tamanho);

void centralizar_retornos(const char *texto);

void centralizar_nomepadrao(const char *nome, const int tam,
                            const int op_grafico);

void centralizar_numpadrao(const int num, int tam, int borda);

int encontrarMaiorTamanhoString(char *strings[]);

void centralizar_textoind(char *texto, int tamanho_maximo);

void imprimirBilhete(const Bilheteria *B, int idx);

void imprimirLinhaTabela(const int *tamanhos_colunas, const int num_colunas,
                         int eh_inicio);

void listarBilhetes(Bilheteria *B, int criterio);

void exibirLancamentos(const Bilheteria *B);


#endif //VISUAL_H
