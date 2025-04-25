//
// Created by natan on 4/18/2025.
//

#include "menu.h"

#include "utils.h"
#include "bilhete.h"
#include "bilheteria.h"

void menu() {
    setlocale(LC_ALL, ".UTF8");
    Bilheteria cinema;
    inicializarBilheteria(&cinema);

    adicionarFilme(&cinema, "Especial: Trilogia - Fragmentado", "24-04-2025");
    adicionarFilme(&cinema, "Thunderbolts*", "01-05-2025");
    adicionarFilme(&cinema, "Until Dawn: Noite de Terror", "24-04-2025");
    adicionarFilme(&cinema, "Avatar 3: O Caminho das Estrelas", "18-12-2025");
    adicionarFilme(&cinema, "Missao Impossovel: Codigo Final", "30-07-2025");


    int opcao;
    system("cls");
    do {
        printf("\n%s%s=***** Bilheteria CineRatao *****=%s\n\n", NEGRITO,
               VERDE_BASICO,
               LIMPAR);
        printf("[1]\tReserva de poltrona\n");
        printf("[2]\tImpressao de bilhete\n");
        printf("[3]\tRelatorio de bilhetes\n");
        printf("[4]\tVer lançamentos\n");
        printf("[0]\tSair\n");
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
                        exibirSala(&cinema);
                        solicitarReserva(&cinema,
                                         cinema.filmes[escolha_filme - 1].nome);
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
                exibirLançamentos(&cinema);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
