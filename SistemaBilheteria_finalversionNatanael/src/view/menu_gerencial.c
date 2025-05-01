#include "view/menu_gerencial.h"

#include "view/menu.h"
#include "view/visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu_gerencial(Bilheteria *cinema) {
    if (!Login()) {
        printf("ACESSO NEGADO!\n");
        return;
    }

    int opcao_adm;
    do {
        printf("\n%s MENU DE ADMINISTRADOR %s %s\n\n", NEGRITO, VERDE_BASICO, LIMPAR);
        printf("[1]\tLimpar salas\n");
        printf("[2]\tAdicionar filmes\n");
        printf("[3]\tRelatorio de bilhetes\n");
        printf("[4]\tCancelar bilhete\n");
        printf("[0]\tSair\n");
        scanf("%d", &opcao_adm);
        getchar();

        switch (opcao_adm) {
            case 1:
                LimparSalas(cinema); //LimparSalas(&cinema);
                break;

            case 2:
                char nome[50];
                char data[25];
                printf("Nome do filme: ");
                fgets(nome, sizeof(nome), stdin);
                printf("Data (dd-mm-AAAA): ");
                fgets(data, sizeof(data), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                data[strcspn(data, "\n")] = '\0';
                adicionarFilme(cinema, nome, data);  //adicionarFilme(&cinema, nome, data);
                break;

            case 3:
                if (cinema->num_bilhetes > 0) {
                    int criterio;
                    printf("Criterio de ordenacao:\n");
                    printf("[1]\tNumero do bilhete (crescente)\n");
                    printf("[2]\tNumero do bilhete (decrescente)\n");
                    printf("[3]\tTipo de ingresso\n");
                    printf("Opcao > ");
                    scanf("%d", &criterio);
                    getchar();
                    listarBilhetes(cinema, criterio); //listarBilhetes(&cinema, criterio);
                } else {
                    printf("Nenhum bilhete emitido ainda.\n");
                }
                break;
            case 4:
                int bilhete;
                int sala;
                exibirFilmes(cinema); //exibirFilmes(&cinema);
                printf("Numero da sala: ");
                scanf("%d", &sala);
                printf("Numero do bilhete: ");
                scanf("%d", &bilhete);

                DeletarBilhete(cinema, bilhete, sala); //&
                break;
            case 0:
                printf("Saindo da tela gerencial...\n");
                printf("Digite ENTER para continuar\n");
                getchar();

                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao_adm != 0);
}
