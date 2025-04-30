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

    if (!traduzirCoordenada(coordenada, &linha, &coluna)) {
        printf("\tPoltrona nao encontrada!\n\tUse algo como 'B5'.\n");
        return;
    }

    if (bilheteria->sala[filme.sala][linha - 1][coluna - 1] != 'D') {
        printf("Poltrona (%c%d) ja ocupada!\n", linha + 'A' - 1, coluna);
        return;
    }

    getchar(); // Limpa buffer antes do fgets

    printf("Digite o nome do cliente >");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    while (valida_ingresso) {
        printf("Tipo de ingresso ([1] Integral - [2] Meia-entrada) > ");
        scanf("%d", &ingresso);
        switch (ingresso) {
            case 1:
                strncpy(tipo_ingresso, "Integral", sizeof(tipo_ingresso));
                valida_ingresso = 0;
                break;
            case 2:
                strncpy(tipo_ingresso, "Meia-entrada", sizeof(tipo_ingresso));
                valida_ingresso = 0;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    int num_bilhete = reservarLugar(bilheteria, linha, coluna, nome,
                                    tipo_ingresso, filme);
    if (num_bilhete != -1) {
        printf("Reserva feita com sucesso! Nº do bilhete: %d\n", num_bilhete);
    } else {
        printf("Erro ao reservar a poltrona.\n");
    }
    getchar();
}