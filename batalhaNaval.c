#include <stdio.h>
#include <stdlib.h>

#define TAM 10  // tamanho do tabuleiro
#define HAB 5   // tamanho das matrizes de habilidade

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");   // água
            else if (tabuleiro[i][j] == 3) printf("N "); // navio
            else if (tabuleiro[i][j] == 5) printf("* "); // área da habilidade
            else printf("? "); // fallback
        }
        printf("\n");
    }
    printf("\n");
}

// Função para construir a habilidade em forma de cone
void construirCone(int cone[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            // O cone expande conforme a linha aumenta
            if (j >= (HAB/2 - i) && j <= (HAB/2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para construir a habilidade em forma de cruz
void construirCruz(int cruz[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            // Linha central ou coluna central
            if (i == HAB/2 || j == HAB/2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para construir a habilidade em forma de octaedro (losango)
void construirOctaedro(int octaedro[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            // Distância de Manhattan até o centro
            if (abs(i - HAB/2) + abs(j - HAB/2) <= HAB/2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função para aplicar a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HAB][HAB], int origemX, int origemY) {
    int offset = HAB / 2; // metade do tamanho da matriz de habilidade

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemX + (i - offset);
                int y = origemY + (j - offset);

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                    tabuleiro[x][y] = 5; // marca área afetada
                }
            }
        }
    }
}

// Função opcional para mostrar a matriz de habilidade isolada
void exibirHabilidade(int habilidade[HAB][HAB], const char *nome) {
    printf("\n=== MATRIZ %s ===\n", nome);
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[HAB][HAB], cruz[HAB][HAB], octaedro[HAB][HAB];

    // Inicializa tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Adiciona alguns navios (exemplo)
    tabuleiro[2][2] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][8] = 3;

    // Constrói habilidades
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // (Opcional) Mostra as matrizes das habilidades
    exibirHabilidade(cone, "CONE");
    exibirHabilidade(cruz, "CRUZ");
    exibirHabilidade(octaedro, "OCTAEDRO");

    // Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 5);       // cone na parte superior
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);   // octaedro embaixo à esquerda

    // Exibe o tabuleiro completo
    exibirTabuleiro(tabuleiro);

    return 0;
}
