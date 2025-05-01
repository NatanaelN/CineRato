#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

#define MAX_SALAS 10
#define MAX_LINHAS 10
#define MAX_COLUNAS 10
#define MAX_NOME 65

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int sala;
    char nome[MAX_NOME];
    Data data_lancamento;
} Filme;

typedef struct {
    int sala;
    int numero_bilhete;
    char nome_filme[MAX_NOME];
    int fileira;
    int coluna;
    char nome_cliente[MAX_NOME];
    char tipo_ingresso[15];
} Bilhete;


typedef struct {
    bool isAdmin;
    Filme *filmes;
    int num_filmes;
    char sala[MAX_SALAS][MAX_LINHAS][MAX_COLUNAS];
    Bilhete *bilhetes; // recomenda-se dinamizar
    int num_bilhetes;
    int proximo_numero_bilhete;
} Bilheteria;

typedef enum {
    ORDEM_EMISSAO = 0, // Ordem de emissão original
    ORDEM_CRESCENTE, // Ordenar por número crescente
    ORDEM_DECRESCENTE, // Ordenar por número decrescente
    ORDEM_TIPO // Ordenar por tipo de ingresso
} OrdemBilhetes;

typedef enum {
    ORDEM_ALFA = 0, /* Ordem alfabética */
    ORDEM_LANCAMENTO /* Ordenar por data de lançamento */
} OrdemFilmes;


#endif // STRUCT_H
