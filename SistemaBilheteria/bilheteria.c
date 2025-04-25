//
// Created by natan on 4/18/2025.
//

#include "bilheteria.h"
#include "utils.h"



Data ExtrairData(const char *s) {
    while (*s) {
        int n = 0;

        sscanf(s, "%*2[0-9]-%*2[0-9]-%*4[0-9]%n", &n);
        if (n > 0) {
            int day = 0;
            int month = 0;
            int year = 0;
            sscanf(s, "%d-%d-%d", &day, &month, &year);
            s += n;
            Data date = {day, month, year};
            return date;
        } else {
            s++;
        }
    }
}

void filmeSort(Bilheteria *bilheteria, Filme filmes[]) {
    for (int i = 0; i < bilheteria->num_filmes; i++) {
        filmes[i]  = bilheteria->filmes[i];
    }

    for (int i = 0; i < bilheteria->num_filmes; ++i) {
        for (int j = 0; j < bilheteria->num_filmes; ++j) {
            if(filmes[i].data_lancamento.mes > filmes[j].data_lancamento.mes ) {
                Filme temp = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = temp;
            } else if(filmes[i].data_lancamento.dia > filmes[j].data_lancamento.dia && filmes[i].data_lancamento.mes == filmes[j].data_lancamento.mes) {

                Filme temp = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = temp;
            } else if(filmes[i].data_lancamento.ano > filmes[j].data_lancamento.ano ) {
                Filme temp = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = temp;
            }
        }
    }


}

// Inicializa o sistema de bilheteria
void inicializarBilheteria(Bilheteria *bilheteria) {
    bilheteria->num_filmes = 0;
    bilheteria->num_bilhetes = 0;
    bilheteria->proximo_numero_bilhete = 1;

    // Inicializa a sala com todos os lugares disponíveis
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            bilheteria->sala[i][j] = 'D';
        }
    }
}

// Adiciona um filme à lista de filmes disponíveis
void adicionarFilme(Bilheteria *bilheteria, const char *nome,
                    const char *data) {
    if (bilheteria->num_filmes < MAX_FILMES) {
        strcpy(bilheteria->filmes[bilheteria->num_filmes].nome, nome);
        bilheteria->filmes[bilheteria->num_filmes].data_lancamento = ExtrairData(data);
        bilheteria->num_filmes++;
    } else {
        printf("Limite de filmes atingido.\n");
    }
}

// Exibe a lista de filmes disponíveis
void exibirFilmes(Bilheteria *bilheteria) {
    setlocale(LC_ALL, "");
    printf("\n=***** %sFilmes da sessao%s *****=\n\n", AZUL_BASICO, LIMPAR);
    printf("[ID]\t| %s%20s%s\t| Lancamento |\n",NEGRITO, "Filme", LIMPAR);
    for (int i = 0; i < bilheteria->num_filmes; i++) {
        printf("[%d]\t| %s%40s%s\t| %c%d - %c%d - %d |\n", i + 1, VERDE_BASICO,
               bilheteria->filmes[i]
               .nome, LIMPAR, bilheteria->filmes[i].data_lancamento.dia < 10 ? '0' : ' ', bilheteria->filmes[i].data_lancamento.dia,
               bilheteria->filmes[i].data_lancamento.mes < 10 ? '0' : ' ',
               bilheteria->filmes[i].data_lancamento.mes,
               bilheteria->filmes[i].data_lancamento.ano);
    }
    printf("============================================\n");
}

void exibirLançamentos(Bilheteria *bilheteria) {
    setlocale(LC_ALL, "");
    Filme filmes[bilheteria->num_filmes];

    filmeSort(bilheteria, filmes);

    for (int i = 0; i < bilheteria->num_filmes; i++) {
        printf("[%d]\t| %s%40s%s\t| %c%d - %c%d - %d |\n", i + 1, VERDE_BASICO,
               filmes[i]
               .nome, LIMPAR,filmes[i].data_lancamento.dia < 10 ? '0' : ' ',
               filmes[i].data_lancamento.dia,filmes[i].data_lancamento.mes < 10 ? '0' : ' ', filmes[i].data_lancamento.mes,
               filmes[i].data_lancamento.ano );
    }

}





// Exibe a disposição da sala
void exibirSala(Bilheteria *bilheteria) {
    setlocale(LC_ALL, "");
    printf("\n=*** Selecione sua poltrona ***=\n");
    printf("  ");
    for (int j = 0; j < MAX_COLUNAS; j++) {
        printf("%s%3d%s", AZUL_BASICO, j + 1, LIMPAR);
    }
    printf("%s\n", LIMPAR);
    for (int i = 0; i < MAX_LINHAS; i++) {
        printf(" %s%c%s ", AZUL_BASICO, 'A' + i, LIMPAR);
        for (int j = 0; j < MAX_COLUNAS; j++) {
            const char h4 = bilheteria->sala[i][j];
            if (h4 == 'X') {
                printf(" %s%c%s ", VERM_BASICO, bilheteria->sala[i][j], LIMPAR);
            } else {
                printf(" %s%c%s ", VERDE_BASICO, bilheteria->sala[i][j],
                       LIMPAR);
            }
        }
        printf("\n");
    }
    printf("============================\n");
    printf("Legenda: %sD - Disponivel%s - %sX - Ocupado%s\n", VERDE_BASICO,
           LIMPAR, VERM_BASICO,
           LIMPAR);
}


int traduzirCoordenada(const char *entrada, int *linha, int *coluna) {
    if (strlen(entrada) < 2) return 0; // Tamanho mínimo "A1"

    const char letra = (char) toupper(entrada[0]);
    if (letra < 'A' || letra >= 'A' + MAX_LINHAS) return 0;

    // Pega o resto como número (ex: "10" de "A10")
    const int numero = atoi(&entrada[1]);
    if (numero < 1 || numero > MAX_COLUNAS) return 0;

    *linha = letra - 'A' + 1; // Transforma A = 1, B = 2, etc.
    *coluna = numero;

    return 1; // Sucesso
}


// Reserva um lugar na sala
int reservarLugar(Bilheteria *bilheteria, const int linha, const int coluna,
                  const char *nome_cliente, const char *tipo_ingresso,
                  const char *nome_filme) {
    setlocale(LC_ALL, "");

    Bilhete novo_bilhete;
    novo_bilhete.numero_bilhete = bilheteria->proximo_numero_bilhete++;
    novo_bilhete.fileira = linha;
    novo_bilhete.coluna = coluna;
    strcpy(novo_bilhete.nome_cliente, nome_cliente);
    strcpy(novo_bilhete.tipo_ingresso, tipo_ingresso);
    strcpy(novo_bilhete.nome_filme, nome_filme);

    // Adiciona o bilhete ao sistema
    if (bilheteria->num_bilhetes < MAX_LINHAS * MAX_COLUNAS) {
        bilheteria->bilhetes[bilheteria->num_bilhetes++] = novo_bilhete;
        bilheteria->sala[linha - 1][coluna - 1] = 'X';
        // Marca a poltrona como ocupada
        return novo_bilhete.numero_bilhete; // Retorna o número do bilhete
    } else {
        printf("Erro: Limite de bilhetes atingido.\n");
        return -1; // Indica falha na reserva
    }
}

void solicitarReserva(Bilheteria *bilheteria, const char *nome_filme) {
    char coordenada[10];
    int linha;
    int coluna;
    char nome[100];
    char tipo_ingresso[20];
    int ingresso;
    int valida_ingresso = 1;

    printf("Digite o assento (ex: B5): ");
    scanf("%9s", coordenada);

    if (!traduzirCoordenada(coordenada, &linha, &coluna)) {
        printf("\tPoltrona nao encontrada!\n\tUse algo como 'B5'.\n");
        return;
    }

    if (bilheteria->sala[linha - 1][coluna - 1] != 'D') {
        printf("Poltrona (%c%d) ja ocupada!\n", linha + 'A' - 1, coluna);
        return;
    }

    getchar(); // Limpa buffer antes do fgets

    printf("Digite o nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    while (valida_ingresso) {
        printf("Tipo de ingresso ([1] Integral - [2] Meia-entrada): ");
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
                                    tipo_ingresso, nome_filme);
    if (num_bilhete != -1) {
        printf("Reserva feita com sucesso! Nº do bilhete: %d\n", num_bilhete);
    } else {
        printf("Erro ao reservar a poltrona.\n");
    }
}
