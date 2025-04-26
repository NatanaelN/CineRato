//
// Created by natan on 4/18/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_FILMES 5 //Quantidade de filmes/salas disponíveis
#define MAX_LINHAS 10 //Quantidade fileiras
#define MAX_COLUNAS 10 //Quantidade de colunas
#define MAX_NOME 65 //Tamanho nome filme/cliente
#define MAX_SALAS 10 // Salas
#define VERM_BASICO "\033[31m"
#define VERDE_BASICO "\033[32m"
#define AZUL_BASICO "\033[34m"
#define NEGRITO "\033[1m"
#define LIMPAR "\033[0m"


#define SENHA_ADM "CINERATAO123"
#define EMAIL_ADM "CINERATAO@admin.com"




// TAD para representar a data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// TAD para representar um filme
typedef struct {
    int sala;
    char nome[MAX_NOME];
    Data data_lancamento;
} Filme;

// TAD para representar um bilhete
typedef struct {
    int sala;
    int numero_bilhete;
    char nome_filme[MAX_NOME];
    int fileira;
    int coluna;
    char nome_cliente[MAX_NOME];
    char tipo_ingresso[15]; // "Inteiro" ou "Meia-entrada"
} Bilhete;

// TAD para o sistema de bilheteria
typedef struct {
    bool isAdmin;
    Filme filmes[MAX_FILMES];
    int num_filmes;
    char sala[MAX_SALAS][MAX_LINHAS][MAX_COLUNAS]; // 'D' para disponível, 'X' para ocupado
    Bilhete bilhetes[MAX_LINHAS * MAX_COLUNAS];
    // Tamanho máximo possível de bilhetes
    int num_bilhetes;
    int proximo_numero_bilhete;
} Bilheteria;


#endif //UTILS_H
