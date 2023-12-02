#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 32
#define TAM 30

struct pessoa {
    char nome[TAMSTR];
    int codigo;
    long tel;
    int calorias;
};

typedef struct pessoa Atleta;

struct prato {
    int codigo;
    int dia;
    int mes;
    int ano;
    int cal;
};
typedef struct prato Refeicao;

struct plano {
    int codigo;
    int dia;
    int mes;
    int ano;
    int calMin;
    int calMax;
};
typedef struct plano Planos;

void lerArquivo(char arquivo[5]);

int main() {
    lerArquivo("1.txt");
    return 0;
}

void lerArquivo(char arquivo[5]) {
    FILE *fOne, *fTwo, *fThree;
    char ch;
    int i = 0, j, k, codigo, dia, mes, ano, calMin, calMax, qtdClientes, qtdPratos, qtdPlanos;
    long tel;

    Atleta Cliente[TAM];
    char nome[TAMSTR];

    if ((fOne = fopen(arquivo, "r")) == NULL) {
        printf("Error opening file %s\n", arquivo);
        return;
    }

    qtdClientes = 0;
    do {
        fscanf(fOne, "%d;%[^;];%ld\n", &codigo, nome, &tel);
        if (codigo >= 0 && codigo < TAM) {
            Cliente[i].codigo = codigo;
            strcpy(Cliente[i].nome, nome);
            Cliente[i].tel = tel;
            Cliente[i].calorias = 0;
        } else {
            printf("Invalid Code: %d\n", codigo);
        }
        i++;
    } while ((!feof(fOne) && (i < TAM)));
    qtdClientes = i - 1;
    fclose(fOne);

    if ((fTwo = fopen("2.txt", "r")) == NULL) {
        printf("Error opening file 2.txt\n");
        return;
    }

    Refeicao Pratos[TAM];
    int calorias;
    char refeicao[TAMSTR], prato[TAMSTR];
    i = 0;
    qtdPratos = 0;
    do {
        fscanf(fTwo, "%d;%d-%d-%d;%[^;];%[^;];%d cal", &codigo, &dia, &mes, &ano, refeicao, prato, &calorias);
        if (codigo >= 0 && codigo < TAM) {
            Pratos[i].codigo = codigo;
            Pratos[i].dia = dia;
            Pratos[i].mes = mes;
            Pratos[i].ano = ano;
            Pratos[i].cal = calorias;
        } else {
            printf("Invalid Code: %d\n", codigo);
        }
        i++;
    } while (!feof(fTwo));
    qtdPratos = i - 1;
    fclose(fTwo);

    if ((fThree = fopen("3.txt", "r")) == NULL) {
        printf("Error opening file 3.txt\n");
        return;
    }

    Planos Plano[TAM];
    i = 0;
    qtdPlanos = 0;
    do {
        // Initialize variables before the loop
        codigo = dia = mes = ano = calMin = calMax = 0;
        // Read data and check for successful reading
        if (fscanf(fThree, "%d;%d-%d-%d;%[^;];%d Cal, %d Cal,", &codigo, &dia, &mes, &ano, prato, &calMin, &calMax)!= 7) {
            printf("Erro ao ler do ficheiro\n");
            break;
        }
        if (codigo >= 0 && codigo < TAM) {
            Plano[i].dia = dia;
            Plano[i].mes = mes;
            Plano[i].ano = ano;
            Plano[i].calMin = calMin;
            Plano[i].calMax = calMax;
        } else {
            printf("Invalid Code: %d\n", codigo);
        }
        i++;
    } while (!feof(fThree));
    qtdPlanos = i - 1;

    fclose(fThree);

    int numCal;
    numCal = codigo = 0;
    for (int i = 0; i < qtdPratos; i++){
        codigo = Pratos[i].codigo;
        numCal = Pratos[i].cal;
        for (int j = 0; j < qtdClientes; j++) {
            if (Cliente[j].codigo == codigo) {
                if (Cliente[j].calorias > 0) {
                    Cliente[j].calorias += numCal;
                } else {
                    Cliente[j].calorias = numCal;
                }
                printf("Codigo: %d, Nome: %s, Calorias: %d\n", Cliente[j].codigo, Cliente[j].nome, Cliente[j].calorias);
            }
        }
    }
 }
