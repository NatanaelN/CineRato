//
// Created by natan on 4/18/2025.
// Update by Wagner on 4/29/2025.
// Update by Trega on 4/30/2025.

#include "view/menu_principal.h"

#include "common.h"
#include "model/bilhete.h"
#include "model/bilheteria.h"
#include "view/menu.h"
#include "view/menu_gerencial.h"
#include "view/visual.h"

#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void menu_principal() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    Bilheteria cinema;
    inicializarBilheteria(&cinema);

    alocarFilmes(&cinema);
    alocarBilhetes(&cinema);

    adicionarFilme(&cinema, "Thunderbolts*", "01-05-2025");
    adicionarFilme(&cinema, "Especial: Trilogia - Fragmentado", "24-12-2025");

    //declara um vetor pra saber a posição do cursor e inicializa ele
    //j é o nosso indice para achar aonde fica a '->' , tambem é usado para selecionar a opção
    int pos[5];
    int j = 0;
    for (int i = 1; i < 6; i++) {
        pos[i] = 0;
    }

    int opcao = -1;
    char input;
    int selecao_feita = 0; //flag para continuar a executar o switch para setar o valor de opcao
    system("cls");

    do {
        system("cls");
        fflush(stdout);


        //zera o vetor antes de posicionar a seta
        for (int i = 0; i < 5; i++) {
            pos[i] = 0;
        }
        //limita e posiciona a seta
        if (j >= 5) j = 0;
        if (j < 0) j = 4;

        pos[j] = 1;

        criacao_caixa(TAMCAIXA);
        centralizar_retornos("=***** Bilheteria CineRatao *****=");
        criacao_caixa(TAMCAIXA);
        char *campos_iniciais[] = {
            "Ver lancamentos", "Reserva de poltrona", "Impressao de bilhete", "Tela de administrador", "Sair", NULL
        };

        int maiorTamanhoValorMenu = encontrarMaiorTamanhoString(campos_iniciais);

        for (int k = 0; campos_iniciais[k] != NULL; k++) {
            printf("\t\t\xBA [%s%s%s] \xBA %-*s", AZUL_BASICO, (pos[k] == 1 ? "->" : "  "), LIMPAR,
                   maiorTamanhoValorMenu - 1, campos_iniciais[k]);
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
        input = getch();
        printf("\n");

        switch (input) {
            case 'w':
            case 'W':
                j--;
                break;
            case 's':
            case 'S':
                j++;
                break;
            case '\r':
            case '\n':
                opcao = j;
                selecao_feita = 1;
                break;
            default:
                break;
        }

        if (selecao_feita) {
            switch (opcao) {
                case 0: {
                    exibirLancamentos(&cinema);
                    break;
                }
                case 1: {
                    system("cls");
                    if (cinema.num_filmes > 0) {
                        exibirFilmes(&cinema);
                        int escolha_filme;
                        printf("Selecione o filme (sala) > ");
                        scanf("%d", &escolha_filme);
                        getchar();

                        if (escolha_filme >= 1 && escolha_filme <= cinema.num_filmes) {
                            int quantidade;
                            printf("Quantos bilhetes deseja emitir? ");
                            scanf("%d", &quantidade);
                            getchar();
                            if (quantidade <= 0 || quantidade > (MAX_LINHAS * MAX_COLUNAS - cinema.num_bilhetes)) {
                                printf("Quantidade invalida ou excede assentos disponiveis.\n");
                                break;
                            }
                            for (int i = 0; i < quantidade; i++) {
                                printf("\n--- Reserva %d de %d ---\n", i + 1, quantidade);
                                exibirSala(&cinema, escolha_filme);
                                solicitarReserva(&cinema, cinema.filmes[escolha_filme - 1]);
                            }
                            /*printf("DEBUG RESERVA: Endereco de cinema = %p\n", &cinema);
                            printf("DEBUG RESERVA: cinema.num_bilhetes apos reserva = %d\n", cinema.num_bilhetes);
                            // Adicione isto
                            system("pause");*/
                        } else {
                            printf("Opcao de filme invalida.\n");
                        }
                    } else {
                        printf("Nenhum filme cadastrado ainda.\n");
                    }
                    break;
                }
                case 2: {
                    /*printf("DEBUG IMPRIMIR: Endereco de cinema = %p\n", &cinema);
                    printf("Executando Impressao de bilhete (case 2)\n");
                    printf("DEBUG IMPRIMIR: cinema.num_bilhetes antes da busca = %d\n", cinema.num_bilhetes);
                    system("pause");*/
                    if (cinema.num_bilhetes > 0) {
                        /*printf("DEBUG IMPRIMIR: cinema.num_bilhetes dentro do if = %d\n", cinema.num_bilhetes);
                        system("pause");*/
                        int numero_buscar;
                        printf("Numero do bilhete > ");
                        scanf("%d", &numero_buscar);
                        getchar();

                        /*printf("DEBUG Numero de busca: %d\n", numero_buscar);
                        system("pause");
                        printf("DEBUG: Bilhetes ordenados ANTES do qsort:\n");
                        for (int i = 0; i < cinema.num_bilhetes; i++) {
                            printf("DEBUG: bilhetes[%d].numero_bilhete = %d\n", i, cinema.bilhetes[i].numero_bilhete);
                        }
                        system("pause");*/
                        qsort(&cinema.bilhetes[0], cinema.num_bilhetes, sizeof(Bilhete),
                              compararBilhetesPorNumeroCrescente);
                        /*printf("DEBUG: Apos o qsort(&cinema.bilhetes[0]...)\n");
                        system("pause");*/
                        int indice_encontrado = buscarBilhete(&cinema, numero_buscar);
                        /*printf("Indice encontrado: %d\n", indice_encontrado);
                        system("pause");*/
                        imprimirBilhete(&cinema, indice_encontrado);
                    } else {
                        printf("Nenhum bilhete emitido ainda.\n");
                    }
                    system("pause");
                    break;
                }
                case 3:
                    system("cls");
                    menu_gerencial(&cinema);
                    break;
                case 4:
                    printf("Saindo do sistema...\n");
                    liberarBilheteria(&cinema);
                    exit(0);

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    system("pause");
            }
            selecao_feita = 0; // Reseta o flag para a próxima seleção
            opcao = -1; // Reseta opcao para evitar reexecução imediata
        }
    } while (opcao != 4);
}
