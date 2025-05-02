#include "view/visual.h"

#include "model/bilheteria.h"
#include "model/bilhete.h"
#include "model/struct.h"
#include "common.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void centralizar_retornos(const char *texto) {
    int len = (int) strlen(texto);
    int esp = (TAMCAIXA - 2 - len) / 2;
    printf("\t\t\xBA");
    for (int i = 0; i < esp; i++) printf(" ");
    printf("%s", texto);
    for (int i = 0; i < TAMCAIXA - 2 - len - esp; i++) printf(" ");
    printf("\xBA\n");
}

// Exibe a lista de filmes disponíveis
void exibirFilmes(Bilheteria *bilheteria) {
    system("cls");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    centralizar_retornos(
        "=********** \033[34mFilmes da sessao\033[0m **********=");

    printf("\t\xBA %-5s ", "Sala");
    printf("\xBA %40s ", "Filme");
    printf("\t\xBA %s \xBA\n", "Lancamento");
    for (int i = 0; i < bilheteria->num_filmes; i++) {
        printf("\t\xBA  [%d]  \xBA %s%40s%s\t\xBA %02d/%02d/%04d \xBA\n",
               bilheteria->filmes[i].sala, VERDE_BASICO,
               bilheteria->filmes[i]
               .nome, LIMPAR,
               bilheteria->filmes[i].data_lancamento.dia,
               bilheteria->filmes[i].data_lancamento.mes,
               bilheteria->filmes[i].data_lancamento.ano);
    }
    centralizar_retornos(
        "\033[34m========================================\033[0m");
    fflush(stdout);
}

// Exibe a disposição da sala
void exibirSala(Bilheteria *bilheteria, int sala) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    centralizar_textoind("=*** Selecione sua poltrona ***=", 35);
    printf("\xBA\n");
    criacao_caixa(35);
    printf("\t\t\xBA  ");
    for (int j = 0; j < MAX_COLUNAS; j++) {
        printf("%s%3d%s", AZUL_BASICO, j + 1, LIMPAR);
    }
    printf(" \xBA%s\n", LIMPAR);
    for (int i = 0; i < MAX_LINHAS; i++) {
        printf("\t\t\xBA %s%c%s ", AZUL_BASICO, 'A' + i, LIMPAR);
        for (int j = 0; j < MAX_COLUNAS; j++) {
            const char h4 = bilheteria->sala[sala][i][j];
            if (h4 == 'X') {
                printf(" %s%c%s ", VERM_BASICO, bilheteria->sala[sala][i][j], LIMPAR);
            } else {
                printf(" %s%c%s ", VERDE_BASICO, bilheteria->sala[sala][i][j], LIMPAR);
            }
        }
        printf("\xBA\n");
    }
    criacao_caixa(35);
    printf("\t\tLegenda: %sD - Disponivel%s - %sX - Ocupado%s\n", VERDE_BASICO, LIMPAR, VERM_BASICO, LIMPAR);
}

// Utilitários de desenho
void criacao_caixa(const int tamanho) {
    printf("\t\t");
    for (int i = 0; i < tamanho; i++) {
        printf("\xCD");
    }
    printf("\n");
}

void centralizar_nomepadrao(const char *nome, const int tam, const int op_grafico) {
    int comprimento_texto = (int) strlen(nome);
    int espacos_esquerda = (tam - 2 - comprimento_texto) / 2;
    int espacos_direita = tam - 2 - comprimento_texto - espacos_esquerda;

    const char grafico = (op_grafico == 0) ? '|' : '\xBA';

    printf("%c", grafico);

    int i;
    for (i = 0; i < espacos_esquerda; i++) {
        printf(" ");
    }
    printf("%s", nome);

    for (i = 0; i < espacos_direita; i++) {
        printf(" ");
    }

    printf("%c\n", grafico);
}

void centralizar_numpadrao(const int num, int tam, int borda) {
    char buf[8];
    snprintf(buf, sizeof(buf), "%d", num);
    centralizar_nomepadrao(buf, tam, borda);
}

int encontrarMaiorTamanhoString(char *strings[]) {
    if (strings == NULL) {
        return 0; // Array nulo, retorna 0
    }

    int maiorTamanho = 0;
    int i = 0;

    // Percorre o array de strings até encontrar um ponteiro NULL (fim do array)
    while (strings[i] != NULL) {
        const int tamanhoAtual = (int) strlen(strings[i]);
        if (tamanhoAtual > maiorTamanho) {
            maiorTamanho = tamanhoAtual;
        }
        i++;
    }
    if (maiorTamanho < 16) {
        maiorTamanho = 16;
    }
    return maiorTamanho;
}

void centralizar_textoind(char *texto, int tamanho_maximo) {
    int espacamento;
    if (strlen(texto) % 2 == 0) {
        espacamento = (int) (tamanho_maximo - strlen(texto)) / 2;
    } else {
        espacamento = (int) (tamanho_maximo - strlen(texto) + 1) / 2;
    }
    printf("\t\t\xBA%s%s%s", AZUL_BASICO, texto, LIMPAR);
    for (int k = 0; k < espacamento; k++) {
        printf(" ");
    }
}

// Visualização de um único bilhete
void imprimirBilhete(const Bilheteria *B, int idx) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    if (idx < 0 || idx >= B->num_bilhetes) {
        printf("\tBilhete nao encontrado.\n");
        return;
    }
    char *itens_bilhete[] = {"Bilhete", "Filme", "Sala", "Poltrona", "Cliente", "Ingresso", NULL};
    const int maiorTamanho = encontrarMaiorTamanhoString(itens_bilhete);

    char buffer_sala[12];
    snprintf(buffer_sala, sizeof(buffer_sala), "%d", B->bilhetes[idx].sala);
    char buffer_bilhete[12];
    snprintf(buffer_bilhete, sizeof(buffer_bilhete), "%d", B->bilhetes[idx].numero_bilhete);

    char buffer_cadeira[4];
    snprintf(buffer_cadeira, sizeof(buffer_cadeira), "%c%d", 'A' + (B->bilhetes[idx].fileira - 1),
             B->bilhetes[idx].coluna);

    char *valor_bilhete[] = {
        buffer_bilhete, B->bilhetes[idx].nome_filme, buffer_sala, buffer_cadeira, B->bilhetes[idx].nome_cliente,
        B->bilhetes[idx].tipo_ingresso, NULL
    };
    const int maiorTamanhoValor = encontrarMaiorTamanhoString(valor_bilhete);
    int t_caixa2 = ((maiorTamanho + maiorTamanhoValor + 10) <= 58) ? 58 : (maiorTamanho + maiorTamanhoValor + 10);


    // Cabeçalho
    criacao_caixa(t_caixa2);
    centralizar_retornos("** Bilheteria Grupo 8 **");
    criacao_caixa(t_caixa2);

    for (int i = 0; itens_bilhete[i] != NULL; i++) {
        printf("\t\t\xBA %s%-*s%s | %-*s", AZUL_BASICO, maiorTamanho, itens_bilhete[i], LIMPAR, maiorTamanhoValor,
               valor_bilhete[i]);
        int tamanho_atual = 2 + maiorTamanho + 3 + maiorTamanhoValor;
        while (tamanho_atual < t_caixa2 - 1) {
            printf(" ");
            tamanho_atual++;
        }
        printf("\xBA\n");
    }

    // Rodapé
    criacao_caixa(t_caixa2);
    printf("\n");
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void imprimirLinhaTabela(const int *tamanhos_colunas, const int num_colunas, int eh_inicio) {
    // Define os caracteres com base no tipo da linha (início ou fim)
    // 1 para topo 0 para fundo
    char canto_esquerdo = eh_inicio ? '\xC9' : '\xC8'; // ╔ ou ╚
    char meio = eh_inicio ? '\xCB' : '\xCA'; // ╦ ou ╩
    char canto_direito = eh_inicio ? '\xBB' : '\xBC'; // ╗ ou ╝

    printf("\t\t%c", canto_esquerdo);
    for (int i = 0; i < num_colunas; i++) {
        for (int j = 0; j < tamanhos_colunas[i] + 2; j++) {
            printf("\xCD"); // linha horizontal
        }
        if (i < num_colunas - 1) {
            printf("%c", meio);
        }
    }
    printf("%c\n", canto_direito);
}

// Listagem de bilhetes com cabeçalho estilizado
void listarBilhetes(Bilheteria *B, int criterio) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    if (B->num_bilhetes == 0) {
        printf("\tNenhum bilhete emitido.\n");
        return;
    }
    // Definição dos tamanhos das colunas
    int tamanhos_colunas[] = {5, 35, 10, 20, 12};
    int num_colunas = sizeof(tamanhos_colunas) / sizeof(tamanhos_colunas[0]);

    // Cabeçalho
    imprimirLinhaTabela(tamanhos_colunas, num_colunas, 1);
    printf("\t\t");
    centralizar_nomepadrao("** Relatorio de Bilhetes **", 98, 1);

    imprimirLinhaTabela(tamanhos_colunas, num_colunas, 0);

    // Ordenação
    switch (criterio) {
        case ORDEM_CRESCENTE:
            qsort(B->bilhetes, B->num_bilhetes, sizeof(Bilhete), compararBilhetesPorNumeroCrescente);
            printf("\t\t");
            centralizar_nomepadrao("Ordenacao: Crescente", 98, 1);
            break;
        case ORDEM_DECRESCENTE:
            qsort(B->bilhetes, B->num_bilhetes, sizeof(Bilhete), compararBilhetesPorNumeroDecrescente);
            printf("\t\t");
            centralizar_nomepadrao("Ordenacao: Decrescente", 98, 1);
            break;
        case ORDEM_TIPO:
            qsort(B->bilhetes, B->num_bilhetes, sizeof(Bilhete), compararBilhetesPorTipoIngresso);
            printf("\t\t");
            centralizar_nomepadrao("Ordenacao: Tipo Ingresso", 98, 1);
            break;
        default:
            printf("\t\t");
            centralizar_nomepadrao("Ordenacao: Emissao", 98, 1);
    }
    // Desenha linha superior
    imprimirLinhaTabela(tamanhos_colunas, num_colunas, 1);

    // Títulos das colunas
    printf("\t\t\xBA %-5s \xBA %-35s \xBA %-10s \xBA %-20s \xBA %-12s \xBA\n",
           "Num", "Filme", "Poltrona", "Cliente", "Tipo");

    // Linha separadora
    imprimirLinhaTabela(tamanhos_colunas, num_colunas, 0);

    // Corpo da tabela
    for (int i = 0; i < B->num_bilhetes; i++) {
        Bilhete *b = &B->bilhetes[i];
        printf(
            "\t\t\xBA %5d \xBA %-35s \xBA %c%2d        \xBA %-20s \xBA %-12s \xBA\n",
            b->numero_bilhete, b->nome_filme,
            'A' + (b->fileira - 1), b->coluna,
            b->nome_cliente, b->tipo_ingresso);
    }

    // Linha inferior
    imprimirLinhaTabela(tamanhos_colunas, num_colunas, 0);

    printf("\n");
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// Exibição de filmes em cartaz por data de lançamento
void exibirLancamentos(const Bilheteria *B) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    if (B->num_filmes == 0) {
        printf("\tNenhum filme cadastrado.\n");
        return;
    }
    // Cria vetor auxiliar e ordena por data
    Filme *aux = malloc(B->num_filmes * sizeof(Filme));
    memcpy(aux, B->filmes, B->num_filmes * sizeof(Filme));
    // Supondo functie filmeSort ordena por data
    filmeSort((Bilheteria *) B, aux);

    // Cabeçalho
    criacao_caixa(TAMCAIXA);
    centralizar_retornos("** Filmes em Cartaz **");
    criacao_caixa(TAMCAIXA);
    // Linhas de filmes
    for (int i = 0; i < B->num_filmes; i++) {
        char linha[51];
        printf("\t\t\xBA [%2d]", i + 1);
        snprintf(linha, sizeof(linha), "%-30s (%02d/%02d/%04d)",
                 aux[i].nome,
                 aux[i].data_lancamento.dia,
                 aux[i].data_lancamento.mes,
                 aux[i].data_lancamento.ano);
        centralizar_nomepadrao(linha, TAMCAIXA - 6, '\xBA');
    }
    // Rodapé
    criacao_caixa(TAMCAIXA);
    free(aux);
    printf("\nPressione ENTER para continuar...");
    getchar();
}
