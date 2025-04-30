#include "view/menu_principal.h"

#include "model/bilheteria.h"
#include "model/bilhete.h"
#include "common.h"
#include "view/menu.h"
#include "view/menu_gerencial.h"
#include "view/visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void menu_principal() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    Bilheteria cinema;
    inicializarBilheteria(&cinema);

    alocarFilmes(&cinema);

    adicionarFilme(&cinema, "Thunderbolts*", "01-05-2025");
    adicionarFilme(&cinema, "Especial: Trilogia - Fragmentado", "24-12-2025");


    int opcao;
    system("cls");

    do {
        opcao = -1;
        criacao_caixa(TAMCAIXA);
        centralizar_retornos("=***** Bilheteria CineRatao *****=");
        criacao_caixa(TAMCAIXA);
        char *campos_iniciais[] = {
            "Ver lancamentos", "Reserva de poltrona", "Impressao de bilhete",
            "Tela de administrador", "Sair", NULL
        };

        int maiorTamanhoValorMenu =
                encontrarMaiorTamanhoString(campos_iniciais);

        for (int k = 0; campos_iniciais[k] != NULL; k++) {
            int campo_sair = (strcmp(campos_iniciais[k], "Sair") == 0)
                                 ? 0
                                 : k + 1;
            printf("\t\t\xBA [%s%-*d%s] \xBA %-*s", AZUL_BASICO, 1,
                   campo_sair, LIMPAR, maiorTamanhoValorMenu,
                   campos_iniciais[k]);
            int tamanho_atual = 2 + 6 + 3 + maiorTamanhoValorMenu;
            while (tamanho_atual < TAMCAIXA + 2) {
                printf(" ");
                tamanho_atual++;
            }
            printf("\xBA\n");
        }


        // Rodapé
        criacao_caixa(TAMCAIXA);
        criacao_caixa(TAMCAIXA);

        printf("Escolha uma opcao > ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                exibirLancamentos(&cinema);
                break;
            }
            case 2: {
                system("cls");

                if (cinema.num_filmes > 0) {
                    exibirFilmes(&cinema);
                    int escolha_filme;
                    printf("Selecione o filme (sala) > ");
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
                } else {
                    printf("Nenhum filme cadastrado ainda.\n");
                }
                break;
            }
            case 3: {
                if (&cinema.num_bilhetes > 0) {
                    int numero_buscar;
                    printf("Numero do bilhete > ");
                    scanf("%d", &numero_buscar);
                    getchar();

                    qsort(&cinema.bilhetes, cinema.num_bilhetes,
                          sizeof(Bilhete),
                          compararBilhetesPorNumeroCrescente);
                    int indice_encontrado = buscarBilhete(
                        &cinema, numero_buscar); //&cinema, numero_buscar)
                    imprimirBilhete(&cinema, indice_encontrado);
                } else {
                    printf("Nenhum bilhete emitido ainda.\n");
                }
                break;
            }
            case 4:
                menu_gerencial(&cinema);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
