#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define NUM_CIDADES  500
#define NUM_FORMIGAS 100
#define NUM_ITERACOES 10

#define RHO  0.01
#define Q    10

typedef struct {
    int caminho[NUM_CIDADES];
    double distancia;
} Formiga;

Formiga formigas[NUM_FORMIGAS];
Formiga melhorFormiga;

double distancias[NUM_CIDADES][NUM_CIDADES];
double feromonios[NUM_CIDADES][NUM_CIDADES];

void inicializarDistancias();
void inicializarFeromonios();
void inicializarFormigas();
void gerarCaminhos();
void atualizarFeromonios();

int main() {
    srand(time(NULL));

    inicializarDistancias();
    inicializarFeromonios();
    melhorFormiga.distancia = INFINITY;

    for (int i=0; i<NUM_ITERACOES; i++) {
        inicializarFormigas();
        gerarCaminhos();
        atualizarFeromonios();

        printf("\n");
        printf("\nIteracao: %d", i+1);
        printf("\nMelhor caminho: %.2f\n", melhorFormiga.distancia);
        for (int j=0; j<NUM_CIDADES; j++) {
            printf("%d ", melhorFormiga.caminho[j]);
        }
    }

    return 0;
}

// Okay
void inicializarDistancias() {
    for (int i=0; i < NUM_CIDADES; i++) {
        for (int j=0; j < NUM_CIDADES; j++) {
            if (i == j) {
                distancias[i][j] = 0.0;
            } else {
                distancias[i][j] = rand() % 100 + 1;
                distancias[j][i] = distancias[i][j];
            }
        }
    }
}

// Okay
void inicializarFeromonios() {
    for (int i=0; i < NUM_CIDADES; i++) {
        for (int j=0; j < NUM_CIDADES; j++) {
            feromonios[i][j] = 0.1;
        }
    }
}

// Okay
void inicializarFormigas() {
    for (int i=0; i < NUM_FORMIGAS; i++) {
        for (int j=0; j < NUM_CIDADES; j++) {
            formigas[i].caminho[j] = -1;
        }
        formigas[i].distancia = 0.0;
    }
}

// Okay
void gerarCaminhos() {

    // PASSO 01 - Calula as probabilidades de cada caminho
    double probabilidades[NUM_CIDADES][NUM_CIDADES];
    for (int i=0; i<NUM_CIDADES; i++) {
        double somatorioTxyNxy = 0.0;

        // Calcula Txy * Nxy para todos os caminhos
        for (int j=0; j<NUM_CIDADES; j++) {
            if (i != j) {
                probabilidades[i][j] = 1 / distancias[i][j] * feromonios[i][j];
                somatorioTxyNxy += probabilidades[i][j];
            } else {
                probabilidades[i][j] = 0;
            }
        }

        // Calcula a probabilidade de cada caminho
        for (int j=0; j<NUM_CIDADES; j++) {
            probabilidades[i][j] = (probabilidades[i][j] / somatorioTxyNxy) * 100;
        }
    }

    // PASSO 02 - Vai em cada formiga e gera o seu caminho
    for (int i=0; i<NUM_FORMIGAS; i++) {

        // Escolhe uma cidade inicial
        formigas[i].caminho[0] = rand() % NUM_CIDADES;

        // Gera o percurso da formiga pelo restante das cidades
        for (int j=1; j<NUM_CIDADES; j++) {
            int cidadeAtual = formigas[i].caminho[j-1];

            // Seleciona as probabilidades das cidade ainda não visitadas
            double probAtuais[NUM_CIDADES], somaProb=0.0;
            for (int k=0; k<NUM_CIDADES; k++) {
                if (k == cidadeAtual) {
                    probAtuais[k] = 0;
                    continue;
                }

                // Verifica se a cidade ja foi visitada
                bool cidadeVisitada = false;
                for (int x=0; x<NUM_CIDADES; x++) {
                    if (formigas[i].caminho[x] == k) {
                        cidadeVisitada = true;
                        probAtuais[k] = 0;
                        break;
                    }
                }

                if (!cidadeVisitada) {
                    probAtuais[k] = probabilidades[cidadeAtual][k];
                    somaProb += probAtuais[k];
                }
            }

            // Seleciona a proxima cidade
            double num = (double) rand() / RAND_MAX * somaProb;
            for (int k=0; k<NUM_CIDADES; k++) {
                if (probAtuais[k] > 0)  {
                    num -= probAtuais[k];

                    if (num <= 0) {
                        formigas[i].caminho[j] = k;
                        break;
                    }
                }
            }
        }

        // PASSO 3 - Calcula a distancia percorrida pela formiga
        formigas[i].distancia = 0;
        formigas[i].distancia += distancias[formigas[i].caminho[NUM_CIDADES-1]][formigas[i].caminho[0]];
        for (int j=0; j<NUM_CIDADES-1; j++) {
            formigas[i].distancia += distancias[formigas[i].caminho[j]][formigas[i].caminho[j+1]];
        }

        // Verifica se eh a melhor formiga
        if (formigas[i].distancia < melhorFormiga.distancia) {
            melhorFormiga = formigas[i];
        }
    }
}

// Okay
void atualizarFeromonios() {
    // PASSO 01 - Faz a evaporacao dos feromonios ja existentes
    for (int i=0; i<NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            feromonios[i][j] *= (1.0 - RHO);
        }
    }

    // PASSO 02 - Atualiza os feromonios deixado pelas formigas
    for (int i=0; i<NUM_FORMIGAS; i++) {
        int ultCidade = formigas[i].caminho[NUM_CIDADES-1];
        int priCidade = formigas[i].caminho[0];

        feromonios[ultCidade][priCidade] += Q / formigas[i].distancia;
        feromonios[priCidade][ultCidade] = feromonios[ultCidade][priCidade];

        for (int j=0; j<NUM_CIDADES-1; j++) {
            int cidadeAtual = formigas[i].caminho[j];
            int proxCidade = formigas[i].caminho[j+1];

            feromonios[cidadeAtual][proxCidade] += Q / formigas[i].distancia;
            feromonios[proxCidade][cidadeAtual] = feromonios[cidadeAtual][proxCidade];
        }
    }
}
