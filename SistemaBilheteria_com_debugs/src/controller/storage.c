//
// Created by natan on 29/04/2025.
//

#include "controller/storage.h"

#include <stdio.h>

#include "model/bilhete.h"
#include "model/bilheteria.h"
#include "model/struct.h"


void meusBilhetes(const Bilheteria *bilheteria, const int indice) {
    if (indice < 0 || indice >= bilheteria->num_bilhetes) {
        return;
    }

    Bilhete b = bilheteria->bilhetes[indice];

    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "..//data//bilhete_%03d.txt", b.numero_bilhete);
    // Essa parte aqui e para gerar o nome

    FILE *fp = fopen(nome_arquivo, "w"); // Aqui abre o arquivo
    if (fp == NULL) {
        perror("Erro ao criar arquivo do bilhete");
        return;
    }

    fprintf(fp, "=========== BILHETE ===========\n");
    fprintf(fp, "Número do Bilhete: %d\n", b.numero_bilhete);
    fprintf(fp, "Filme: %s\n", b.nome_filme);
    fprintf(fp, "Assento: %c%d\n", 'A' + b.fileira, b.coluna + 1);
    fprintf(fp, "Cliente: %s\n", b.nome_cliente);
    fprintf(fp, "Tipo de Ingresso: %s\n", b.tipo_ingresso);
    fprintf(fp, "================================\n");

    fclose(fp);
}
