// TODO:

// Input para periodos de tempo;
// Criar Tabelas
// Adicionar caso para quando datas sao iguais


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
    char refeicao[TAMSTR];
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
    char refeicao[TAMSTR];
    int calMin;
    int calMax;
};
typedef struct plano Planos;

struct tabela {
    int codigo;
    char nome[TAMSTR];
    char refeicao[TAMSTR];
    int diainicio;
    int mesinicio;
    int anoinicio;
    int diafim;
    int mesfim;
    int anofim;
    int calMin;
    int calMax;
    int calorias;
};
typedef struct tabela Tabela;

void lerArquivo(char arquivo[5]);
int CompararDatas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int dia3, int mes3, int ano3);
int MaxCal(int dia, int mes, int ano, int codigo, int qtdPlanos, Planos Plano[TAM]);
int Ordenar(Atleta Cliente[TAM], int qtdClientes);
int CalcularCalorias(Refeicao Pratos[TAM], int qtdPratos, int codigo, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int VerificarCalorias(int qtdClientes, int qtdPlanos, Atleta Cliente[TAM], Planos Plano[TAM]);
int CriarPlano(Planos Plano[TAM], int qtdPlanos, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int CalcularPratos(Refeicao Pratos[TAM], int codigo, int qtdPratos);
int CalcularCalMedias(Atleta Cliente[TAM], Refeicao Pratos[TAM], int qtdClientes, int qtdPratos);
int GerarTabela(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int qtdClientes, int qtdPratos, int qtdPlanos);
int CompararData(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int Menu();

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
    qtdClientes = i;

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
        fscanf(fTwo, "%d;%d-%d-%d;%[^;];%[^;];%d cal\n", &codigo, &dia, &mes, &ano, refeicao, prato, &calorias);
        if (codigo >= 0 && codigo < TAM) {
            Pratos[i].codigo = codigo;
            strcpy(Pratos[i].refeicao, refeicao);
            Pratos[i].dia = dia;
            Pratos[i].mes = mes;
            Pratos[i].ano = ano;
            Pratos[i].cal = calorias;
        } else {
            printf("Invalid Code: %d\n", codigo);
        }
        i++;
    } while (!feof(fTwo));
    qtdPratos = i;

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
        if (fscanf(fThree, "%d;%d-%d-%d;%[^;];%d Cal, %d Cal\n", &codigo, &dia, &mes, &ano, prato, &calMin, &calMax)!= 7) {
            printf("Erro ao ler do ficheiro\n");
            break;
        }
        if (codigo >= 0 && codigo < TAM) {
            Plano[i].codigo = codigo;
            Plano[i].dia = dia;
            Plano[i].mes = mes;
            Plano[i].ano = ano;
            strcpy(Plano[i].refeicao, prato);
            Plano[i].calMin = calMin;
            Plano[i].calMax = calMax;
        } else {
            printf("Invalid Code: %d\n", codigo);
        }
        i++;
    } while (!feof(fThree));
    qtdPlanos = i;

    fclose(fThree);


    int opcao, dia1, mes1, ano1, dia2, mes2, ano2;
    do {
        opcao = Menu();
        switch(opcao) {
            case 1:
                printf("Eslha um intervalo de tempo inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia1, &mes1, &ano1);
                printf("Eslha um intervalo de tempo final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia2, &mes2, &ano2);
                for (int i = 0; i < qtdClientes; i++) {
                    Cliente[i].calorias = CalcularCalorias(Pratos, qtdPratos, Cliente[i].codigo, dia2, mes2, ano2, dia1, mes1, ano1);
                }
                VerificarCalorias(qtdClientes, qtdPratos, Cliente, Plano);
                break;
            case 2:
                printf("Eslha um intervalo de tempo inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia1, &mes1, &ano1);
                printf("Eslha um intervalo de tempo final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia2, &mes2, &ano2);
                for (int i = 0; i < qtdClientes; i++) {
                    Cliente[i].calorias = CalcularCalorias(Pratos, qtdPratos, Cliente[i].codigo, dia2, mes2, ano2, dia1, mes1, ano1);
                }
                Ordenar(Cliente, qtdClientes);
                VerificarCalorias(qtdClientes, qtdPratos, Cliente, Plano);
                break;
            case 3:
                printf("Eslha um intervalo de tempo inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia1, &mes1, &ano1);
                printf("Eslha um intervalo de tempo final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia2, &mes2, &ano2);
                CriarPlano(Plano, qtdPlanos, dia2, mes2, ano2, dia1, mes1, ano1);
                break;
            case 4:
                printf("Eslha um intervalo de tempo inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia1, &mes1, &ano1);
                printf("Eslha um intervalo de tempo final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &dia2, &mes2, &ano2);
                for (int i = 0; i < qtdClientes; i++) {
                    Cliente[i].calorias = CalcularCalorias(Pratos, qtdPratos, Cliente[i].codigo, dia2, mes2, ano2, dia1, mes1, ano1);
                }
                CalcularCalMedias(Cliente, Pratos, qtdClientes, qtdPratos);
                break;
            case 5:
                GerarTabela(Cliente, Pratos, Plano, qtdClientes, qtdPratos, qtdPlanos);
            case 0:
                printf("A sair...\n");
        }
    } while(opcao != 0);

 }

int CompararDatas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int dia3, int mes3, int ano3) {
    if ((ano1 > ano3) || (ano1 == ano3 && ((mes1 > mes3) || (mes1 == mes3 && dia1 >= dia3))))
        return -1;
    else if ((ano1 < ano2) || (ano1 == ano2 && ((mes1 < mes2) || (mes1 == mes2 && dia1 < dia2))))
        return 1;

    return 0;  // Date1 is within the interval (exclusive of both date3 and date2)
}






int MaxCal(int dia, int mes, int ano, int codigo, int qtdPlanos, Planos Plano[TAM]) {
    int i = 0;
    int index = i;
    int cal = Plano[0].calMax;
    while (i != qtdPlanos) {
        if ((Plano[i].codigo == codigo) && (CompararDatas(Plano[i].dia, Plano[i].mes, Plano[i].ano, dia, mes, ano, 31, 12, 2022) == -1) && (Plano[i].calMax >= cal)) {
            index = i;
        }
        i++;
    }
    return Plano[index].calMax;
}

int Ordenar(Atleta Cliente[TAM], int qtdClientes) {
    int codigo, calorias;
    char nome[TAMSTR];
    long tel;

    for (int i = 0; i < qtdClientes; ++i) {
        for (int j = i + 1 ; j < qtdClientes; ++j) {
            if (Cliente[i].codigo < Cliente[j].codigo) {

                codigo = Cliente[i].codigo;
                strcpy(nome, Cliente[i].nome);
                tel = Cliente[i].tel;
                calorias = Cliente[i].calorias;

                Cliente[i].codigo = Cliente[j].codigo;
                strcpy(Cliente[i].nome, Cliente[j].nome);
                Cliente[i].tel = Cliente[j].tel;
                Cliente[i].calorias = Cliente[j].calorias;


                Cliente[j].codigo = codigo;
                strcpy(Cliente[j].nome, nome);
                Cliente[j].tel = tel;
                Cliente[j].calorias = calorias;


            }
        }
    }
    return 0;
}

int CalcularCalorias(Refeicao Pratos[TAM], int qtdPratos, int codigo, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    int numCal = 0;
    for (int i = 0; i < qtdPratos; i++){
        if ((CompararDatas(Pratos[i].dia, Pratos[i].mes, Pratos[i].ano, dia1, mes1, ano1, dia2, mes2, ano2) == -1) && (Pratos[i].codigo == codigo)) {
            numCal += Pratos[i].cal;
        } else if ((CompararDatas(Pratos[i].dia, Pratos[i].mes, Pratos[i].ano, dia1, mes1, ano1, dia2, mes2, ano2) == -1) && (Pratos[i].codigo == codigo)) {
            numCal = Pratos[i].cal;
        }
    }
    return numCal;
}

int VerificarCalorias(int qtdClientes, int qtdPlanos, Atleta Cliente[TAM], Planos Plano[TAM]) {
    int numCal, codigo, calMax;
    numCal = codigo = 0;
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < qtdClientes; i++) {
        codigo = Cliente[i].codigo;
        calMax = MaxCal(25, 1, 2023, codigo, qtdPlanos, Plano);
        if (calMax < Cliente[i].calorias) {
            printf("| Codigo: %d | Nome: %s | Calorias: %d | Calorias Max: %d |\n", Cliente[i].codigo, Cliente[i].nome, Cliente[i].calorias, calMax);
        }
       
    }
    printf("----------------------------------------------------------------\n");
    return 0;
}

int CriarPlano(Planos Plano[TAM], int qtdPlanos, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < qtdPlanos; i++) {
        if (CompararDatas(Plano[i].dia, Plano[i].mes, Plano[i].ano, dia1, mes1, ano1, dia2, mes2, ano2) == -1) {
            printf("| Codigo %d | Data: %d-%d-%d | Refeicao: %s | Cal Min: %d | Cal Max: %d |\n", Plano[i].codigo, Plano[i].dia, Plano[i].mes, Plano[i].ano, Plano[i].refeicao, Plano[i].calMin, Plano[i].calMax);
            printf("---------------------------------------------------------------------------\n");
        }
    }
    return 0;

}

int CalcularPratos(Refeicao Pratos[TAM], int codigo, int qtdPratos) {
    int n = 0;
    for (int i = 0; i < qtdPratos; i++) {
        if (Pratos[i].codigo == codigo){
            n++;
        }
    }
    return n;
}

int CalcularCalMedias(Atleta Cliente[TAM], Refeicao Pratos[TAM], int qtdClientes, int qtdPratos) {
    int n;
    printf("---------------------------------------\n");
    for (int i = 0; i < qtdClientes; i++) {
        n = CalcularPratos(Pratos, Cliente[i].codigo, qtdPratos);
        //printf("%d\n", Cliente[i].calorias);
        float divisao = (float)Cliente[i].calorias / (float)n;
        printf("| Codigo: %d | Nome: %s | Media Calorias: %.2f |\n", Cliente[i].codigo, Cliente[i].nome, divisao);
        printf("---------------------------------------\n");

    }
    printf("---------------------------------------\n");
    return 0;
}



int CompararData(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    if (ano1 < ano2 || (ano1 == ano2 && (mes1 < mes2 || (mes1 == mes2 && dia1 < dia2)))) {
        return -1; // date1 is earlier than date2
    } else if (ano1 > ano2 || (ano1 == ano2 && (mes1 > mes2 || (mes1 == mes2 && dia1 > dia2)))) {
        return 1;  // date1 is later than date2
    } else {
        return 0;  // dates are equal
    }
}

int GerarTabela(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int qtdClientes, int qtdPratos, int qtdPlanos) {
    Tabela Tabela[TAM];
    int qtdTabela = 0;
    for (int i = 0; i < qtdPlanos; i++) {
        int repeated = 0;

        for (int j = 0; j < qtdTabela; j++) {
            int numCal = 0;
            if ((strcmp(Tabela[j].refeicao, Plano[i].refeicao) == 0) && (Tabela[j].codigo == Plano[i].codigo)) {
                if (CompararData(Tabela[j].diainicio, Tabela[j].mesinicio, Tabela[j].anoinicio, Plano[i].dia, Plano[i].mes, Plano[i].ano) == 1) {
                    Tabela[j].diainicio = Plano[i].dia;
                    Tabela[j].mesinicio = Plano[i].mes;
                    Tabela[j].anoinicio = Plano[i].ano;
                    Tabela[j].calMax += Plano[i].calMax;
                    Tabela[j].calMin += Plano[i].calMin;
                } else if (CompararData(Tabela[j].diainicio, Tabela[j].mesinicio, Tabela[j].anoinicio, Plano[i].dia, Plano[i].mes, Plano[i].ano) == -1) {
                    Tabela[j].diafim = Plano[i].dia;
                    Tabela[j].mesfim = Plano[i].mes;
                    Tabela[j].anofim = Plano[i].ano;
                    Tabela[j].calMax += Plano[i].calMax;
                    Tabela[j].calMin += Plano[i].calMin;                  
                }
                repeated = 1;
                break;
            }
        }

        if (!repeated) {
            Tabela[qtdTabela].codigo = Plano[i].codigo;
            strcpy(Tabela[qtdTabela].refeicao, Plano[i].refeicao);
            for (int j = 0; j < qtdClientes; j++) {
                if (Cliente[j].codigo == Plano[i].codigo) {
                    strcpy(Tabela[qtdTabela].nome, Cliente[j].nome);
                }
            }
            Tabela[qtdTabela].diainicio = Plano[i].dia;
            Tabela[qtdTabela].mesinicio = Plano[i].mes;
            Tabela[qtdTabela].anoinicio = Plano[i].ano;
            Tabela[qtdTabela].diafim = Plano[i].dia;
            Tabela[qtdTabela].mesfim = Plano[i].mes;
            Tabela[qtdTabela].anofim = Plano[i].ano;
            Tabela[qtdTabela].calMin = Plano[i].calMin;
            Tabela[qtdTabela].calMax = Plano[i].calMax;
            Tabela[qtdTabela].calorias = 0;
            qtdTabela++;
        }
    }

    for (int i = 0; i < qtdTabela; i++) {
        for (int j = 0; j < qtdPratos; j++) {
            if ((CompararDatas(Pratos[j].dia, Pratos[j].mes, Pratos[j].ano, Tabela[i].diafim, Tabela[i].mesfim, Tabela[i].anofim, Tabela[i].diainicio, Tabela[i].mesinicio, Tabela[i].anoinicio) == -1) && (Tabela[i].codigo == Pratos[j].codigo) && strcmp(Tabela[i].refeicao, Pratos[j].refeicao) == 0) {
                Tabela[i].calorias += Pratos[j].cal;
                //printf("Codigo: %d, Prato: %s, Cal: %d\n", Pratos[j].codigo, Pratos[j].refeicao, Pratos[j].cal);
            } else if (((CompararDatas(Pratos[j].dia, Pratos[j].mes, Pratos[j].ano, Tabela[i].diafim, Tabela[i].mesfim, Tabela[i].anofim, Tabela[i].diainicio, Tabela[i].mesinicio, Tabela[i].anoinicio) == 0) && (Tabela[i].codigo == Pratos[j].codigo) && strcmp(Tabela[i].refeicao, Pratos[j].refeicao) == 0)) {
                Tabela[i].calorias += Pratos[j].cal;
                printf("Codigo: %d, Prato: %s, Cal: %d\n", Pratos[j].codigo, Pratos[j].refeicao, Pratos[j].cal);

            }
        }
    }
    printf("---------------------------------------------------------------------------\n");
    printf("| NP | Paciente | Refeicao | Inicio | Fim | Minimo | Maximo | Consumo |\n");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < qtdTabela; i++) {
        printf("| %d | %s | %s | %d-%d-%d | %d-%d-%d | %d | %d | %d |\n", Tabela[i].codigo, Tabela[i].nome, Tabela[i].refeicao, Tabela[i].diainicio, Tabela[i].mesinicio, Tabela[i].anoinicio, Tabela[i].diafim, Tabela[i].mesfim, Tabela[i].anofim, Tabela[i].calMin, Tabela[i].calMax, Tabela[i].calorias);
        printf("---------------------------------------------------------------------------\n");
    }
    return 0;
}

int Menu() //Menu Principal
{
    int opc;
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                             		Menu                                           					 \n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|        1 - Numero de pacientes que ultrapassaram determinada quantidade de calorias, num determinado periodo         |\n");
    printf("|        2 - Listagem dos pacientes, ordenada por ordem decrescente do numero de paciente,			       ||	     que realizaram alguma refeicao com quantidade de calorias fora do intervalo     				|\n");
    printf("|        3 - Listar o plano nutricional de um paciente para determinada refeicao ao longo de um determinado periodo    |\n");
    printf("|        4 - Calculo das medias das calorias consumidas por refeicao por cada paciente ao longo                        |\n|            de um determinado periodo                                                                                 |\n");
    printf("|        5 - Gerar a tabela das refeicoes                                                                              |\n");
    printf("|        0 - Sair                                                                                                      |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Selecione uma opcao: ");
    scanf("%i", &opc); getchar();
    return opc;
}
