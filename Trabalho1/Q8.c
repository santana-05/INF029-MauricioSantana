#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TAM 3

void exibirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("\n   1   2   3\n");
    for (int i = 0; i < TAM; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("  ---+---+---\n");
    }
    printf("\n");
}

int verificarVencedor(char tabuleiro[TAM][TAM], char jogador) {
    for (int i = 0; i < TAM; i++) {
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1;
        }
    }
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1;
    }
    return 0;
}

int tabuleiroCheio(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == ' ')
                return 0;
    return 1;
}

int validacaoPosicao(char pos[3]) {
    return (toupper(pos[0]) >= 'A' && toupper(pos[0]) <= 'C' && pos[1] >= '1' && pos[1] <= '3');
}

void fazerJogada(char tabuleiro[TAM][TAM], char jogador, char pos[3]) {
    int linha = toupper(pos[0]) - 'A';
    int coluna = pos[1] - '1';
    tabuleiro[linha][coluna] = jogador;
}

void limparTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = ' ';
}

int verificarJogada(char tabuleiro[TAM][TAM], int l, int c) {
    return (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == ' ');
}

int jogadaInteligente(char tabuleiro[TAM][TAM], char jogador, int *linha, int *coluna) {
    char oponente = (jogador == 'O') ? 'X' : 'O';

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = jogador;
                if (verificarVencedor(tabuleiro, jogador)) {
                    *linha = i;
                    *coluna = j;
                    tabuleiro[i][j] = ' ';
                    return 1;
                }
                tabuleiro[i][j] = oponente;
                if (verificarVencedor(tabuleiro, oponente)) {
                    *linha = i;
                    *coluna = j;
                    tabuleiro[i][j] = ' ';
                    return 1;
                }
                tabuleiro[i][j] = ' ';
            }
        }
    }
    return 0;
}

void jogadaComputador(char tabuleiro[TAM][TAM], char jogador, int dificuldade) {
    int linha, coluna;

    if (dificuldade == 2 && jogadaInteligente(tabuleiro, jogador, &linha, &coluna)) {
        tabuleiro[linha][coluna] = jogador;
        return;
    }

    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] != ' ');
    tabuleiro[linha][coluna] = jogador;
}

int main() {
    char tabuleiro[TAM][TAM];
    char pos[3], resposta;
    int modoJogo, dificuldade;
    int pontosJog1 = 0, pontosJog2 = 0;
    int vezJogador;
    char jogadorAtual;
    srand(time(NULL));

    printf("Jogo da Velha\n");
    printf("1 - Jogador vs Jogador\n");
    printf("2 - Jogador vs Computador\n");
    printf("Escolha o modo: ");
    scanf("%d", &modoJogo);

    if (modoJogo == 2) {
        printf("Dificuldade (1 - Fácil, 2 - Difícil): ");
        scanf("%d", &dificuldade);
    }

    do {
        limparTabuleiro(tabuleiro);
        vezJogador = 1;

        while (1) {
            exibirTabuleiro(tabuleiro);
            jogadorAtual = (vezJogador == 1) ? 'X' : 'O';

            if (modoJogo == 2 && vezJogador == 2) {
                printf("Computador jogando...\n");
                jogadaComputador(tabuleiro, jogadorAtual, dificuldade);
            } else {
                printf("Jogador %d (%c), informe sua jogada (exemplo B3): ", vezJogador, jogadorAtual);
                scanf("%2s", pos);

                if (!validacaoPosicao(pos)) {
                    printf("Posição inválida. Use A1 a C3. Tente novamente.\n");
                    continue;
                }

                int linha = toupper(pos[0]) - 'A';
                int coluna = pos[1] - '1';

                if (!verificarJogada(tabuleiro, linha, coluna)) {
                    printf("Esta célula já está ocupada. Tente novamente.\n");
                    continue;
                }

                tabuleiro[linha][coluna] = jogadorAtual;
            }

            if (verificarVencedor(tabuleiro, jogadorAtual)) {
                exibirTabuleiro(tabuleiro);
                if (modoJogo == 2 && vezJogador == 2) {
                    printf("Computador venceu!\n");
                    pontosJog2++;
                } else {
                    printf("Jogador %d (%c) venceu!\n", vezJogador, jogadorAtual);
                    if (vezJogador == 1)
                        pontosJog1++;
                    else
                        pontosJog2++;
                }
                break;
            }

            if (tabuleiroCheio(tabuleiro)) {
                exibirTabuleiro(tabuleiro);
                printf("Empate!\n");
                break;
            }

            vezJogador = (vezJogador == 1) ? 2 : 1;
        }

        printf("Pontuação: Jogador 1 = %d | %s = %d\n",
               pontosJog1,
               (modoJogo == 2) ? "Computador" : "Jogador 2",
               pontosJog2);

        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);

    } while (resposta == 'S');

    printf("Jogo encerrado.\n");
    return 0;
}
