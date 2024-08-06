#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define CARREGAR_DISTANCIAS  1
#define CARREGAR_FEROMONIOS  1
#define CARREGAR_MELHOR_ROTA 1

#define SALVAR_DISTANCIAS    1
#define SALVAR_FEROMONIOS    1
#define SALVAR_MELHOR_ROTA   1

#define NUM_CIDADES   500
#define NUM_FORMIGAS  400
#define NUM_ITERACOES 10
#define NUM_THREADS   16

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
void prepararMelhorFormiga();

void salvarDistancias();
void salvarFeromonios();
void salvarMelhorFormiga();

void gerarRotas();
void atualizarFeromonios();

int main() {
    srand(time(NULL));

    omp_set_num_threads(NUM_THREADS);

    printf("\n===== CONFIGURACOES =====\n");
    printf("- NUM_CIDADES:   %d\n", NUM_CIDADES);
    printf("- NUM_FORMIGAS:  %d\n", NUM_FORMIGAS);
    printf("- NUM_ITERACOES: %d\n", NUM_ITERACOES);
    printf("- NUM_THREADS:   %d\n\n", NUM_THREADS);

    prepararDistancias();
    prepararFeromonios();
    prepararMelhorFormiga();

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
    salvarMelhorFormiga();

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
    // #pragma omp parallel for
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

void prepararMelhorFormiga() {
    if (CARREGAR_MELHOR_ROTA) {
        FILE *file = fopen("melhor-rota.txt", "rb");
        if (file == NULL) {
            printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO '%s'\n", "melhor-rota.txt");
            exit(-1);
        }

        fscanf(file, "%f", &melhorFormiga.distancia);
        for (int i=0; i<NUM_CIDADES; i++) {
            fscanf(file, "%d", &melhorFormiga.rota[i]);
        }

        fclose(file);
    } else {
        melhorFormiga.distancia = INFINITY;
        printf("- MELHOR FORMIGA RESETADA!\n");
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

void salvarMelhorFormiga() {
    if (SALVAR_MELHOR_ROTA) {
        FILE *file = fopen("melhor-rota.txt", "wb");
        if (file == NULL) {
            printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO '%s'\n", "melhor-rota.txt");
            exit(-1);
        }

        fprintf(file, "%.2f\n", melhorFormiga.distancia);
        for (int i=0; i<NUM_CIDADES; i++) {
            fprintf(file, "%d ", melhorFormiga.rota[i]);
        }

        fclose(file);
    }
}

// (OKAY) Gerador de rotas
void gerarRotas() {

    // Reseta todas as formigas
    resetarFormigas();

    // PASSO 01 - Calula as probabilidades de cada caminho
    float probabilidades[NUM_CIDADES][NUM_CIDADES];
    // #pragma omp parallel for
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
    // #pragma omp parallel for
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

            // if (i == 5 && j == 467) {
            //     printf("Go ahead");
            // }

            // Seleciona a proxima cidade
            double num = (double) rand() / RAND_MAX * somaProb;
            for (int k=0; k<NUM_CIDADES; k++) {
                if (probAtuais[k] > 0)  {
                    num = arredondar(num - probAtuais[k]);

                    if (num <= 0.0) {
                        formigas[i].rota[j] = k;
                        break;
                    }
                }
            }

            if (formigas[i].rota[j] == -1) {
                printf("* FORMIGA PERDIDA!\n");
                exit(-1);
            }
        }

        // PASSO 3 - Calcula a distancia percorrida pela formiga
        formigas[i].distancia = 0;
        formigas[i].distancia += distancias[formigas[i].rota[NUM_CIDADES-1]][formigas[i].rota[0]];
        for (int j=0; j<NUM_CIDADES-1; j++) {
            formigas[i].distancia += distancias[formigas[i].rota[j]][formigas[i].rota[j+1]];
        }

        // Verifica se eh a melhor formiga
        // #pragma omp critical
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
    // #pragma omp parallel for collapse(2)
    for (int i=0; i<NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            feromonios[i][j] *= (1.0 - RHO);
        }
    }

    // PASSO 02 - Atualiza os feromonios deixado pelas formigas
    // #pragma omp parallel for
    for (int i=0; i<NUM_FORMIGAS; i++) {
        int ultCidade = formigas[i].rota[NUM_CIDADES-1];
        int priCidade = formigas[i].rota[0];

        // #pragma omp critical
        feromonios[ultCidade][priCidade] += Q / formigas[i].distancia;

        // #pragma omp critical
        feromonios[priCidade][ultCidade] = feromonios[ultCidade][priCidade];

        for (int j=0; j<NUM_CIDADES-1; j++) {
            int cidadeAtual = formigas[i].rota[j];
            int proxCidade = formigas[i].rota[j+1];

            // #pragma omp critical
            feromonios[cidadeAtual][proxCidade] += Q / formigas[i].distancia;
            
            // #pragma omp critical
            feromonios[proxCidade][cidadeAtual] = feromonios[cidadeAtual][proxCidade];
        }
    }
    printf("- FEROMONIOS ATUALIZADOS!\n");
}