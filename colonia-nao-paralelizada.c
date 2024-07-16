#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define CARREGAR_DISTANCIAS 1
#define CARREGAR_FEROMONIOS 0
#define SALVAR_DISTANCIAS   1
#define SALVAR_FEROMONIOS   0

#define NUM_CIDADES   500
#define NUM_FORMIGAS  500
#define NUM_ITERACOES 3

#define FEROMONIO_INICIAL 0.1
#define RHO  0.01
#define Q    10

typedef struct tipo_formiga {
    int rota[NUM_CIDADES];
    float distancia;
} Formiga;

Formiga formigas[NUM_FORMIGAS];
Formiga melhorFormiga;

float distancias[NUM_CIDADES][NUM_CIDADES];
float feromonios[NUM_CIDADES][NUM_CIDADES];

float arredondar(float num);

void prepararDistancias();
void prepararFeromonios();
void salvarDistancias();
void salvarFeromonios();

void gerarRotas();
void atualizarFeromonios();

int main() {
    srand(time(NULL));

    printf("\n===== CONFIGURACOES =====\n");
    printf("- NUM_CIDADES:   %d\n", NUM_CIDADES);
    printf("- NUM_FORMIGAS:  %d\n", NUM_FORMIGAS);
    printf("- NUM_ITERACOES: %d\n\n", NUM_ITERACOES);

    prepararDistancias();
    prepararFeromonios();

    melhorFormiga.distancia = INFINITY;
    printf("- MELHOR FORMIGA RESETADA!\n");

    double tempoInicial = omp_get_wtime();

    printf("\n");
    for (int i=0; i<NUM_ITERACOES; i++) {
        double tempoInicialIteracao = omp_get_wtime();

        printf("ITERACAO: %d\n", i+1);
        gerarRotas();
        atualizarFeromonios();

        double tempoFinalIteracao = omp_get_wtime();
        
        printf("- MELHOR ROTA: %.2f\n", melhorFormiga.distancia);
        printf("- TEMPO DA ITERACAO: %.3f SEGUNDOS\n\n", tempoFinalIteracao - tempoInicialIteracao);
    }

    double tempoFinal = omp_get_wtime();
    printf("MELHOR ROTA ENCONTRADA: %.2f\n", melhorFormiga.distancia);
    printf("TEMPO TOTAL DE EXECUCAO: %.3f SEGUNDOS\n", tempoFinal - tempoInicial);

    salvarDistancias();
    salvarFeromonios();

    printf("\n===== FIM =====\n\n");
    return 0;
}

// (OKAY) Funcao de arredondar numeros
float arredondar(float num) {
    return roundf(num * 1000) / 1000;
}

// Manipuladores de arquivos
void carregarMatriz(char arquivo[], float matriz[NUM_CIDADES][NUM_CIDADES]) {
    FILE *file = fopen(arquivo, "rb");
    if (file == NULL) {
        printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO '%s'\n", arquivo);
        exit(-1);
    }

    for (int i = 0; i < NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            fscanf(file, "%f", &matriz[i][j]);
        }
    }

    fclose(file);
}

void salvarMatriz(char arquivo[], float matriz[NUM_CIDADES][NUM_CIDADES]) {
    FILE *file = fopen(arquivo, "wb");
    if (file == NULL) {
        printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO '%s'\n", arquivo);
        exit(-1);
    }

    for (int i = 0; i < NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            fprintf(file, "%.2f ", matriz[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// (OKAY) Inicializadores
void gerarDistancias() {
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
    printf("- DISTANCIAS GERADAS!\n");
}

void inicializarFeromonios() {
    for (int i=0; i < NUM_CIDADES; i++) {
        for (int j=0; j < NUM_CIDADES; j++) {
            if (i == j) {
                feromonios[i][j] = 0.0;
            } else {
                feromonios[i][j] = 0.1;
            }
        }
    }
    printf("- FEROMONIOS INICIALIZADOS!\n");
}

void resetarFormigas() {
    for (int i=0; i < NUM_FORMIGAS; i++) {
        for (int j=0; j < NUM_CIDADES; j++) {
            formigas[i].rota[j] = -1;
        }
        formigas[i].distancia = 0.0;
    }
    printf("- FORMIGAS RESETADAS!\n");
}

// Manipuladores de dados
void prepararDistancias() {
    if (CARREGAR_DISTANCIAS) {
        carregarMatriz("distancias.txt", distancias);
    } else {
        gerarDistancias();
    }
}

void prepararFeromonios() {
    if (CARREGAR_FEROMONIOS) {
        carregarMatriz("feromonios.txt", feromonios);
    } else {
        inicializarFeromonios();
    }
}

void salvarDistancias() {
    if (SALVAR_DISTANCIAS) {
        salvarMatriz("distancias.txt", distancias);
    }
}

void salvarFeromonios() {
    if (SALVAR_FEROMONIOS) {
        salvarMatriz("feromonios.txt", feromonios);
    }
}

// (OKAY) Gerador de rotas
void gerarRotas() {

    // Reseta todas as formigas
    resetarFormigas();

    // PASSO 01 - Calula as probabilidades de cada caminho
    float probabilidades[NUM_CIDADES][NUM_CIDADES];
    for (int i=0; i<NUM_CIDADES; i++) {
        float somatorioTxyNxy = 0.0;

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
            probabilidades[i][j] = arredondar((probabilidades[i][j] / somatorioTxyNxy) * 100);
        }
    }
    printf("- PROBABILIDADES CALCULADAS!\n");

    printf("- GERANDO ROTAS...\n");
    // PASSO 02 - Vai em cada formiga e gera sua rota
    for (int i=0; i<NUM_FORMIGAS; i++) {

        // Escolhe uma cidade inicial
        formigas[i].rota[0] = rand() % NUM_CIDADES;

        // Gera o percurso da formiga pelo restante das cidades
        for (int j=1; j<NUM_CIDADES; j++) {
            int cidadeAtual = formigas[i].rota[j-1];

            // Seleciona as probabilidades das cidade ainda não visitadas
            float probAtuais[NUM_CIDADES], somaProb=0.0;
            for (int k=0; k<NUM_CIDADES; k++) {
                if (k == cidadeAtual) {
                    probAtuais[k] = 0;
                    continue;
                }

                // Verifica se a cidade ja foi visitada
                bool cidadeVisitada = false;
                for (int x=0; x<NUM_CIDADES; x++) {
                    if (formigas[i].rota[x] == k) {
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
            float num = (float) rand() / RAND_MAX * somaProb;
            for (int k=0; k<NUM_CIDADES; k++) {
                if (probAtuais[k] > 0)  {
                    num = arredondar(num - probAtuais[k]);

                    if (num <= 0) {
                        formigas[i].rota[j] = k;
                        break;
                    }
                }
            }
        }

        // PASSO 3 - Calcula a distancia percorrida pela formiga
        formigas[i].distancia = 0;
        formigas[i].distancia += distancias[formigas[i].rota[NUM_CIDADES-1]][formigas[i].rota[0]];
        for (int j=0; j<NUM_CIDADES-1; j++) {
            formigas[i].distancia += distancias[formigas[i].rota[j]][formigas[i].rota[j+1]];
        }

        // Verifica se eh a melhor formiga
        if (formigas[i].distancia < melhorFormiga.distancia) {
            melhorFormiga = formigas[i];
            printf("- NOVA ROTA ENCONTRADA: %.2f\n", melhorFormiga.distancia);
        }
    }

    printf("- ROTAS GERADAS!\n");
}

// (OKAY) Atualizador de feromonios
void atualizarFeromonios() {
    // PASSO 01 - Faz a evaporacao dos feromonios ja existentes
    for (int i=0; i<NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            feromonios[i][j] *= (1.0 - RHO);
        }
    }

    // PASSO 02 - Atualiza os feromonios deixado pelas formigas
    for (int i=0; i<NUM_FORMIGAS; i++) {
        int ultCidade = formigas[i].rota[NUM_CIDADES-1];
        int priCidade = formigas[i].rota[0];

        feromonios[ultCidade][priCidade] += Q / formigas[i].distancia;
        feromonios[priCidade][ultCidade] = feromonios[ultCidade][priCidade];

        for (int j=0; j<NUM_CIDADES-1; j++) {
            int cidadeAtual = formigas[i].rota[j];
            int proxCidade = formigas[i].rota[j+1];

            feromonios[cidadeAtual][proxCidade] += Q / formigas[i].distancia;
            feromonios[proxCidade][cidadeAtual] = feromonios[cidadeAtual][proxCidade];
        }
    }
    printf("- FEROMONIOS ATUALIZADOS!\n");
}