//
// Created by natan on 4/18/2025.
//

#include "menu.h"

#include <stdbool.h>

#include "utils.h"
#include "bilhete.h"
#include "bilheteria.h"

void menu() {


    setlocale(LC_ALL, ".UTF8");
    Bilheteria cinema;
    inicializarBilheteria(&cinema);


    adicionarFilme(&cinema, "Thunderbolts*", "01-05-2025");
    adicionarFilme(&cinema, "Especial: Trilogia - Fragmentado", "24-12-2025");



    int opcao;
    int opcao_adm;
    system("cls");




    do {
        opcao = -1;
        opcao_adm = -1;
        printf("\n%s%s=***** Bilheteria CineRatao *****=%s\n\n", NEGRITO,
               VERDE_BASICO,
               LIMPAR);
        printf("[1]\tReserva de poltrona\n");
        printf("[2]\tImpressao de bilhete\n");
        printf("[3]\tRelatorio de bilhetes\n");
        printf("[4]\tVer lançamentos\n");
        printf("[5]\tTela de administrador\n");
        printf("[0]\tSair\n");


        printf("%s%s=********************************=%s\n", NEGRITO,
               VERDE_BASICO,
               LIMPAR);


        printf("%s%s=********************************=%s\n", NEGRITO,
       VERDE_BASICO,
       LIMPAR);
        printf("Escolha uma opcao > ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                exibirFilmes(&cinema);
                if (cinema.num_filmes > 0) {
                    int escolha_filme;
                    printf("Selecione o filme (pelo numero): ");
                    scanf("%d", &escolha_filme);
                    getchar();

                    if (escolha_filme >= 1 && escolha_filme <= cinema.
                        num_filmes) {
                        exibirSala(&cinema, escolha_filme);
                        solicitarReserva(&cinema,
                                         cinema.filmes[escolha_filme - 1]);
                    } else {
                        printf("Opcao de filme invalida.\n");
                    }
                }
                break;
            }
            case 2: {
                if (cinema.num_bilhetes > 0) {
                    int numero_buscar;
                    printf("Numero do bilhete: ");
                    scanf("%d", &numero_buscar);
                    getchar();

                    qsort(cinema.bilhetes, cinema.num_bilhetes, sizeof(Bilhete),
                          compararBilhetesPorNumeroCrescente);
                    int indice_encontrado = buscarBilhete(
                        &cinema, numero_buscar);
                    imprimirBilhete(&cinema, indice_encontrado);
                } else {
                    printf("Nenhum bilhete emitido ainda.\n");
                }
                break;
            }
            case 3: {

                if(!cinema.isAdmin) {
                    if(!Login()) break;
                }

                if (cinema.num_bilhetes > 0) {
                    int criterio;
                    printf("Criterio de ordenacao:\n");
                    printf("[1]\tNumero do bilhete (crescente)\n");
                    printf("[2]\tNumero do bilhete (decrescente)\n");
                    printf("[3]\tTipo de ingresso\n");
                    printf("Opcao > ");
                    scanf("%d", &criterio);
                    getchar();
                    listarBilhetes(&cinema, criterio);
                } else {
                    printf("Nenhum bilhete emitido ainda.\n");
                }
                break;
            }
            case 4:
                exibirLancamentos(&cinema);
                break;
            case 5:

                if(!cinema.isAdmin) {
                    cinema.isAdmin = Login();
                }





                if(cinema.isAdmin) {

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
                            LimparSalas(&cinema);

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
                        adicionarFilme(&cinema,nome, data);
                        break;

                        case 3:
                            if (cinema.num_bilhetes > 0) {
                                int criterio;
                                printf("Criterio de ordenacao:\n");
                                printf("[1]\tNumero do bilhete (crescente)\n");
                                printf("[2]\tNumero do bilhete (decrescente)\n");
                                printf("[3]\tTipo de ingresso\n");
                                printf("Opcao > ");
                                scanf("%d", &criterio);
                                getchar();
                                listarBilhetes(&cinema, criterio);
                            } else {
                                printf("Nenhum bilhete emitido ainda.\n");
                            }
                        break;
                        case 4:
                            int bilhete;
                            int sala;
                            exibirFilmes(&cinema);
                            printf("Numero da sala: ");
                            scanf("%d", &sala);
                            printf("Numero do bilhete: ");
                            scanf("%d", &bilhete);

                            DeletarBilhete(&cinema, bilhete, sala);
                            break;
                        case 0:
                            printf("Saindo da tela de administração...\n");
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }




                } else {
                    printf("ACESSO NEGADO! Verifique suas credenciais e tente novamente!");
                }


                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
