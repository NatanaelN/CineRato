#include "controller/reserva.h"

#include "controller/storage.h"

#include <locale.h>
#include <stdio.h>


// Reserva um lugar na sala
int reservarLugar(Bilheteria *bilheteria, const int linha, const int coluna, const char *nome_cliente,
                  const char *tipo_ingresso, const Filme filme) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Bilhete novo_bilhete;

    novo_bilhete.numero_bilhete = bilheteria->proximo_numero_bilhete++;
    novo_bilhete.fileira = linha;
    novo_bilhete.coluna = coluna;
    novo_bilhete.sala = filme.sala;
    strcpy(novo_bilhete.nome_cliente, nome_cliente);
    strcpy(novo_bilhete.tipo_ingresso, tipo_ingresso);
    strcpy(novo_bilhete.nome_filme, filme.nome);

    // Adiciona o bilhete ao sistema
    if (bilheteria->num_bilhetes < MAX_LINHAS * MAX_COLUNAS) {
        bilheteria->bilhetes[bilheteria->num_bilhetes++] = novo_bilhete;
        bilheteria->sala[filme.sala][linha - 1][coluna - 1] = 'X';

        //Chamada função Wagner nova
        meusBilhetes(bilheteria, bilheteria->num_bilhetes - 1);
        // Marca a poltrona como ocupada
        return novo_bilhete.numero_bilhete; // Retorna o número do bilhete
    } else {
        printf("Erro: Limite de bilhetes atingido.\n");
        return -1; // Indica falha na reserva
    }
}
