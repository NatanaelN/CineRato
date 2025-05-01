#include "view/menu.h"

#include "common.h"
#include "controller/reserva.h"
#include "model/bilheteria.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool Login() {
    char email[50];
    char password[50];

    printf("Email de administrador: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Senha de administrador: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(email, EMAIL_ADM) == 0 && strcmp(password, SENHA_ADM) == 0) {
        return true;
    }

    return false;
}


void solicitarReserva(Bilheteria *bilheteria, const Filme filme) {
    char coordenada[10];
    int linha;
    int coluna;
    char nome[100];
    char tipo_ingresso[20];
    int ingresso;
    int valida_ingresso = 1;

    printf("Digite o assento (ex: B5) >");
    scanf("%9s", coordenada);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (!traduzirCoordenada(coordenada, &linha, &coluna)) {
        printf("\tPoltrona nao encontrada!\n\tUse algo como 'B5'.\n");
        return;
    }

    if (bilheteria->sala[filme.sala][linha - 1][coluna - 1] != 'D') {
        printf("Poltrona (%c%d) ja ocupada!\n", linha + 'A' - 1, coluna);
        return;
    }

    printf("Digite o nome do cliente >");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    while (valida_ingresso) {
        printf("Tipo de ingresso ([1] Integral - [2] Meia-entrada) > ");
        if (scanf("%d", &ingresso) == 1){
            switch (ingresso) {
                case 1:
                    strncpy(tipo_ingresso, "Integral", sizeof(tipo_ingresso) - 1); // Protege contra buffer overflow
                    tipo_ingresso[sizeof(tipo_ingresso) - 1] = '\0'; // Garante terminação nula
                    valida_ingresso = 0;
                    break;
                case 2:
                    strncpy(tipo_ingresso, "Meia-entrada", sizeof(tipo_ingresso) - 1); // Protege contra buffer overflow
                    tipo_ingresso[sizeof(tipo_ingresso) - 1] = '\0'; // Garante terminação nula
                    valida_ingresso = 0;
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    // Limpar o buffer de entrada para remover a entrada inválida
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
            }
        } else {
            printf("Entrada invalida. Digite um numero (1 ou 2).\n");
            // Limpar o buffer de entrada em caso de falha na leitura do inteiro

            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    int num_bilhete = reservarLugar(bilheteria, linha, coluna, nome,
                                    tipo_ingresso, filme);

    if (num_bilhete != -1) {
        printf("Reserva feita com sucesso! Nº do bilhete: %d\n", num_bilhete);
        system("pause");
    } else {
        printf("Erro ao reservar a poltrona.\n");
    }
    getchar();
}