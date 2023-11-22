#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 32
#define TAM 30

struct pessoa {
    char nome[TAMSTR];
    int codigo;
    long tel;
    int caloriasMin;

};

typedef struct pessoa Atleta;


struct prato {
    int codigo;
    char refeicao[TAMSTR];
    char prato[TAMSTR];
    int cal;
};
typedef struct prato Refeicao;


void lerArquivo(char arquivo[5]);

int main() {
    lerArquivo("1.txt");
    return 0;
}


void lerArquivo(char arquivo[5]) { // Funcao ler arquivo
    FILE *fOne, *fTwo;
    char ch;
    int i = 0, codigo;
    long tel;

    Atleta Cliente[TAM];
    char nome[TAMSTR];
    
    if ((fOne = fopen(arquivo, "r")) == NULL) // Se ha erro ao aceder ao ficheiro return 1
    {
        fclose(fOne);
        return;
    }
    
    do {
        fscanf(fOne, "%d;%[^;];%ld\n", &codigo, nome, &tel);
        if (codigo >= 0 && codigo < TAM) {
            Cliente[codigo].codigo = codigo;
            strcpy(Cliente[codigo].nome, nome);
            Cliente[codigo].tel = tel;
            i++;
        } else {
            printf("Codigo Invalido: %d\n", codigo);
        }
    } while ((!feof(fOne) && (i < TAM)));

    fclose(fOne);

    if ((fTwo = fopen("2.txt", "r")) == NULL) // Se ha erro ao aceder ao ficheiro return 1
    {
        fclose(fTwo);
        return;
    }

    Refeicao Pratos[TAM];
    int dia, mes, ano, calorias;
    char refeicao[50];
    char prato[50];

    do {
        fscanf(fTwo, "%d;%d-%d-%d;%[^;];%[^;];%d cal", &codigo, &dia, &mes, &ano, refeicao, prato, &calorias);
        if (codigo >= 0 && codigo < TAM) {
            //printf("Codigo: %d e refeicao: %s e calorias: %d\n", codigo, prato, calorias);
            if (Pratos[codigo].cal > 0) {
                Pratos[codigo].cal += calorias;
            } else {
                Pratos[codigo].cal = calorias;
            }
        } else {
            printf("Codigo Invalido: %d\n", codigo);
        }
        printf("Total %d\n", Pratos[codigo].cal);
    } while (!feof(fTwo));
    //printf("Total: %d\n", Pratos[1].cal);

    fclose(fTwo);
}
