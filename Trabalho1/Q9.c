#include <stdio.h>

#define TAM 10
#define MAX_NAVIOS 10

typedef struct {
    int tamanho;
    int vida;
} Navio;

typedef struct {
    char mapa[TAM][TAM];
    Navio navios[MAX_NAVIOS];
    int total_navios;
} Jogador;

const int NUM_NAVIOS = 6;
const int NAVIOS_TAMANHOS[MAX_NAVIOS] = {4, 3, 1, 1, 1, 2};

void inicializar_tabuleiro(Jogador *jogador) {
    jogador->total_navios = NUM_NAVIOS;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            jogador->mapa[i][j] = ' ';
    for (int i = 0; i < NUM_NAVIOS; i++) {
        jogador->navios[i].tamanho = NAVIOS_TAMANHOS[i];
        jogador->navios[i].vida = NAVIOS_TAMANHOS[i];
    }
}

void mostrar_tabuleiro(Jogador *jogador, int mostrar_navios) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            char c = jogador->mapa[i][j];
            if (!mostrar_navios && c == 'N') c = ' ';
            printf("[%c]", c);
        }
        printf("\n");
    }
}

int posicionar_navio(Jogador *jogador, int idx, int x, int y, char direcao) {
    int tam = jogador->navios[idx].tamanho;
    for (int i = 0; i < tam; i++) {
        int nx = x + (direcao == 'V' ? i : 0);
        int ny = y + (direcao == 'H' ? i : 0);
        if (nx >= TAM || ny >= TAM || jogador->mapa[nx][ny] != ' ')
            return 0;
    }
    for (int i = 0; i < tam; i++) {
        int nx = x + (direcao == 'V' ? i : 0);
        int ny = y + (direcao == 'H' ? i : 0);
        jogador->mapa[nx][ny] = 'N';
    }
    return 1;
}

int atirar(Jogador *alvo, int x, int y) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return -1;
    char *celula = &alvo->mapa[x][y];
    if (*celula == 'N') {
        *celula = '0';
        for (int i = 0; i < alvo->total_navios; i++) {
            if (alvo->navios[i].vida > 0) {
                alvo->navios[i].vida--;
                break;
            }
        }
        return 1;
    } else if (*celula == ' ') {
        *celula = 'X';
        return 0;
    }
    return -1;
}

int navios_restantes(Jogador *jogador) {
    int vivos = 0;
    for (int i = 0; i < jogador->total_navios; i++)
        if (jogador->navios[i].vida > 0)
            vivos++;
    return vivos;
}

void posicionar_todos_navios(Jogador *jogador, int id) {
    printf("\n======== POSICIONAMENTO: JOGADOR %d ========\n", id);
    for (int i = 0; i < jogador->total_navios; i++) {
        int x, y; char d;
        mostrar_tabuleiro(jogador, 1);
        printf("Navio %d (tamanho %d):\n", i + 1, jogador->navios[i].tamanho);
        do {
            printf("Digite linha coluna e direção (H ou V): ");
            scanf("%d %d %c", &x, &y, &d);
        } while (!posicionar_navio(jogador, i, x, y, d));
    }
}

void jogar_com_menu(Jogador *j1, Jogador *j2) {
    int turno = 0;
    while (navios_restantes(j1) > 0 && navios_restantes(j2) > 0) {
        Jogador *jogador = (turno % 2 == 0) ? j1 : j2;
        Jogador *oponente = (turno % 2 == 0) ? j2 : j1;
        int id = (turno % 2 == 0) ? 1 : 2;
        int opcao, jogou = 0;

        printf("\n===== TURNO DO JOGADOR %d =====\n", id);
        while (!jogou) {
            printf("\nMenu:\n");
            printf("1 - Mostrar meu tabuleiro\n");
            printf("2 - Mostrar tabuleiro do oponente\n");
            printf("3 - Atirar\n");
            printf("4 - Sair do jogo\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            if (opcao == 1) {
                printf("\n--- Seu Tabuleiro ---\n");
                mostrar_tabuleiro(jogador, 1);
            } else if (opcao == 2) {
                printf("\n--- Tabuleiro do Oponente ---\n");
                mostrar_tabuleiro(oponente, 0);
            } else if (opcao == 3) {
                int x, y, res;
                printf("Digite coordenadas para atirar (linha coluna): ");
                scanf("%d %d", &x, &y);
                res = atirar(oponente, x, y);
                if (res == 1) printf(">> 🎯 ACERTOU um navio!\n");
                else if (res == 0) printf(">> 💨 Errou o tiro.\n");
                else printf(">> ⚠️ Tiro inválido ou repetido. Tente novamente.\n");
                if (res != -1) jogou = 1;
            } else if (opcao == 4) {
                printf("Encerrando o jogo.\n");
                return;
            } else {
                printf("Opção inválida!\n");
            }
        }
        turno++;
    }

    if (navios_restantes(j1) == 0)
        printf("\n🎉 JOGADOR 2 venceu a batalha naval!\n");
    else
        printf("\n🎉 JOGADOR 1 venceu a batalha naval!\n");
}

int main() {
    Jogador j1, j2;
    inicializar_tabuleiro(&j1);
    inicializar_tabuleiro(&j2);
    posicionar_todos_navios(&j1, 1);
    posicionar_todos_navios(&j2, 2);
    jogar_com_menu(&j1, &j2);
    return 0;
}
