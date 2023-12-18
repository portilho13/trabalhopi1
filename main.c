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

int Menu();
int CompararDatas(int dia, int mes, int ano, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
int CompararData(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int ContarExcesso(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
int OrdenarClientes(Atleta Cliente[TAM], int quantidadeClientes);
int ListarExcesso(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
int CriarPlano(Atleta Cliente[TAM], Refeicao Pratos[TAM], int quantidadeClientes, int quantidadePratos, int codigo, int opcaoRefeicao, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
float CalcularMediaRefeicoes(Refeicao Pratos[TAM], int quantidadePratos, int codigo, const char *refeicao, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
int GerarTabela(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos);

int main() {
    Atleta Cliente[TAM];
    Refeicao Pratos[TAM];
    Planos Plano[TAM];
    FILE *ficheiroUm, *ficheiroDois, *ficheiroTres;
    char ch;
    int i = 0, j, k, codigo, dia, mes, ano, calMin, calMax, quantidadeClientes, quantidadePratos, quantidadePlanos;
    long tel;
    char nome[TAMSTR];

    if ((ficheiroUm = fopen("1.txt", "r")) == NULL) {
        printf("Erro ao abrir ficheiro 1.txt\n");
        return 0;
    }

    quantidadeClientes = 0;
    do {
        fscanf(ficheiroUm, "%d;%[^;];%ld\n", &codigo, nome, &tel);
        Cliente[i].codigo = codigo;
        strcpy(Cliente[i].nome, nome);
        Cliente[i].tel = tel;
        Cliente[i].calorias = 0;
        i++;
    } while ((!feof(ficheiroUm) && (i < TAM)));
    quantidadeClientes = i;

    fclose(ficheiroUm);

    if ((ficheiroDois = fopen("2.txt", "r")) == NULL) {
        printf("Erro ao abrir ficheiro 2.txt\n");
        return 0;
    }

    int calorias;
    char refeicao[TAMSTR], prato[TAMSTR];
    i = 0;
    quantidadePratos = 0;
    do {
        fscanf(ficheiroDois, "%d;%d-%d-%d;%[^;];%[^;];%d cal\n", &codigo, &dia, &mes, &ano, refeicao, prato, &calorias);
        Pratos[i].codigo = codigo;
        strcpy(Pratos[i].refeicao, refeicao);
        Pratos[i].dia = dia;
        Pratos[i].mes = mes;
        Pratos[i].ano = ano;
        Pratos[i].cal = calorias;
        i++;
    } while (!feof(ficheiroDois));
    quantidadePratos = i;

    fclose(ficheiroDois);

    if ((ficheiroTres = fopen("3.txt", "r")) == NULL) {
        printf("Erro ao abrir ficheiro 3.txt\n");
        return 0;
    }

    i = 0;
    quantidadePlanos = 0;
    do {
        codigo = dia = mes = ano = calMin = calMax = 0;
        if (fscanf(ficheiroTres, "%d;%d-%d-%d;%[^;];%d Cal, %d Cal\n", &codigo, &dia, &mes, &ano, prato, &calMin, &calMax)!= 7) {
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
    } while (!feof(ficheiroTres));
    quantidadePlanos = i;

    fclose(ficheiroTres);

    int opcao, opcaoRefeicao, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim;
    do {
        opcao = Menu();
        switch (opcao) {
            case 1:
                printf("Escolha uma data inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaInicio, &mesInicio, &anoInicio);
                printf("Escolha uma data final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaFim, &mesFim, &anoFim);
                printf("Numero que ultrapassam: %d\n", ContarExcesso(Cliente, Pratos, Plano, quantidadeClientes, quantidadePratos, quantidadePlanos, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim));
                break;
            case 2:
                printf("Escolha uma data inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaInicio, &mesInicio, &anoInicio);
                printf("Escolha uma data final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaFim, &mesFim, &anoFim);
                ListarExcesso(Cliente, Pratos, Plano, quantidadeClientes, quantidadePratos, quantidadePlanos, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);
                break;
            case 3:
                printf("Escolha o codigo de um cliente: ");
                scanf("%d", &codigo);
                printf("Escolha uma refeicao:\n");
                printf("1 - pequeno almoço\n2 - almoço\n3 - jantar\n");
                scanf("%d", &opcaoRefeicao);
                printf("Escolha uma data inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaInicio, &mesInicio, &anoInicio);
                printf("Escolha uma data final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaFim, &mesFim, &anoFim);
                CriarPlano(Cliente, Pratos, quantidadeClientes, quantidadePratos, codigo, opcaoRefeicao, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);
                break;
            case 4:
                printf("Escolha uma data inicial no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaInicio, &mesInicio, &anoInicio);
                printf("Escolha uma data final no formato dd-mm-aa: ");
                scanf("%d-%d-%d", &diaFim, &mesFim, &anoFim);

                Refeicao CopiaPratos[TAM];
                for (int i = 0; i < quantidadePratos; i++) {
                    CopiaPratos[i] = Pratos[i];
                }
                printf("----------------------------------------------------------------\n");
                for (int i = 0; i < quantidadePratos; i++) {
                    float media = CalcularMediaRefeicoes(CopiaPratos, quantidadePratos, CopiaPratos[i].codigo, CopiaPratos[i].refeicao, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);
                    if (media > 0 ) {
                        printf("| Codigo: %d | Refeicao %s | Media de calorias: %.2f |\n", Pratos[i].codigo, Pratos[i].refeicao, media);
                        printf("----------------------------------------------------------------\n");
                    }

                }
                break;
            case 5:
                GerarTabela(Cliente, Pratos, Plano, quantidadeClientes, quantidadePratos, quantidadePlanos);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}


 int Menu() {
    int opcao;
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                    Menu                                                             |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|        1 - Numero de pacientes que ultrapassaram determinada quantidade de calorias, num determinado periodo         |\n");
    printf("|        2 - Listagem dos pacientes, ordenada por ordem decrescente do numero de paciente,                 ||        que realizaram alguma refeicao com quantidade de calorias fora do intervalo                    |\n");
    printf("|        3 - Listar o plano nutricional de um paciente para determinada refeicao ao longo de um determinado periodo    |\n");
    printf("|        4 - Calculo das medias das calorias consumidas por refeicao por cada paciente ao longo                        |\n|            de um determinado periodo                                                                                 |\n");
    printf("|        5 - Gerar a tabela das refeicoes                                                                              |\n");
    printf("|        0 - Sair                                                                                                      |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Selecione uma opcao: ");
    scanf("%i", &opcao); getchar();
    return opcao;
}

int CompararDatas(int dia, int mes, int ano, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim) {
    int data = ano * 10000 + mes * 100 + dia;
    int  dataIncio = anoInicio * 10000 + mesInicio * 100 + diaInicio;
    int dataFim = anoFim * 10000 + mesFim * 100 + diaFim;

    if ((data >= dataIncio) && (data < dataFim)) {
        return 1;
    } else if((data == dataIncio) && (data == dataFim)) {
        return 0;
    } else {
        return -1;
    }

    return 0;
}

int CompararData(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    int data1 = ano1 * 10000 + mes1 * 100 + dia1;
    int data2 = ano2 * 10000 + mes2 * 100 + dia2;

    if (data1 > data2) {
        return 1;
    } else if (data2 > data1) {
        return -1;
    } else {
        return 0;
    }
    return 0;
}

int ContarExcesso(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim) {
    int calorias, numero, caloriasMaximas; 
    calorias = numero = 0;

    for (int i = 0; i < quantidadePlanos; i++) {
        if (CompararDatas(Plano[i].dia, Plano[i].mes, Plano[i].ano, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim) == 1) {
            for (int j = 0; j < quantidadePratos; j++) {
                if (CompararDatas(Pratos[j].dia, Pratos[j].mes, Pratos[j].ano, Plano[i].dia, Plano[i].mes, Plano[i].ano, diaFim, mesFim, anoFim) == 1) {              
                    if ((Plano[i].codigo == Pratos[j].codigo) && (strcmp(Plano[i].refeicao, Pratos[j].refeicao) == 0)) {
                        if ((calorias + Pratos[j].cal) > Plano[i].calMax) {
                            numero++;
                        } else {
                            calorias += Pratos[j].cal;
                        }
                    }
                }
            }
            calorias = 0;
        }
    }
    return numero;
}

int OrdenarClientes(Atleta Cliente[TAM], int quantidadeClientes) {
    int codigo, calorias;
    char nome[TAMSTR];
    long tel;

    for (int i = 0; i < quantidadeClientes; ++i) {
        for (int j = i + 1 ; j < quantidadeClientes; ++j) {
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

int ListarExcesso(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim) {
    OrdenarClientes(Cliente, quantidadeClientes);
    int calorias, numero, caloriasMaximas; 
    calorias = numero = 0;

    for (int i = 0; i < quantidadePlanos; i++) {
        if (CompararDatas(Plano[i].dia, Plano[i].mes, Plano[i].ano, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim) == 1) {

            for (int j = 0; j < quantidadePratos; j++) {
                if (CompararDatas(Pratos[j].dia, Pratos[j].mes, Pratos[j].ano, Plano[i].dia, Plano[i].mes, Plano[i].ano, diaFim, mesFim, anoFim) == 1) {                    
                    if ((Plano[i].codigo == Pratos[j].codigo) && (strcmp(Plano[i].refeicao, Pratos[j].refeicao) == 0)) {
                        for (int k = 0; k < quantidadeClientes; k++) {
                            if (Cliente[k].codigo == Pratos[j].codigo) {
                                if ((calorias + Pratos[j].cal) > Plano[i].calMax) {
                                    printf("Codigo: %d, Nome: %s, Refeicao: %s, Calorias %d, Calorias Maximas: %d\n", Plano[i].codigo, Cliente[k].nome, Plano[i].refeicao, calorias + Pratos[j].cal, Plano[i].calMax);
                                } else {
                                    calorias += Pratos[j].cal;
                                }                                
                            }
                            
                        }
                    }
                }
            }
            calorias = 0;
        }
    }
    return 0;
}

int CriarPlano(Atleta Cliente[TAM], Refeicao Pratos[TAM], int quantidadeClientes, int quantidadePratos, int codigo, int opcaoRefeicao, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim) {
    char refeicao[TAMSTR];
    switch (opcaoRefeicao)
    {
    case 1:
        strcpy(refeicao, "pequeno almoço");
        break;
    case 2:
        strcpy(refeicao, "almoço");
        break;
    case 3:
        strcpy(refeicao, "jantar");
        break;
    default:
        break;
    }
    for (int i = 0; i < quantidadePratos; i++) {
        if ((CompararDatas(Pratos[i].dia, Pratos[i].mes, Pratos[i].ano, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim) == 1) && (strcmp(Pratos[i].refeicao, refeicao) == 0)) {
            for (int j = 0; j < quantidadeClientes; j++) {
                if((Cliente[j].codigo == codigo) && (Pratos[i].codigo == codigo)) {
                    printf("Codigo: %d | Refeicao %s | Data: %d-%d-%d |\n", codigo, refeicao, Pratos[i].dia, Pratos[i].mes, Pratos[i].ano);
                }
            }
        }
    }
    return 0;
}

float CalcularMediaRefeicoes(Refeicao Pratos[TAM], int quantidadePratos, int codigo, const char *refeicao, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim) {
    int totalCalorias = 0;
    int numEntradas = 0;

    for (int i = 0; i < quantidadePratos; i++) {
        if (CompararDatas(Pratos[i].dia, Pratos[i].mes, Pratos[i].ano, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim) >= 0) {
            if (Pratos[i].codigo == codigo && strcmp(Pratos[i].refeicao, refeicao) == 0) {
                totalCalorias += Pratos[i].cal;
                numEntradas++;
                Pratos[i].cal = 0;
            }
        }
    }
    if (numEntradas > 0) {
        return (float)totalCalorias / numEntradas;
    } else {
        return 0;
    }
}


int GerarTabela(Atleta Cliente[TAM], Refeicao Pratos[TAM], Planos Plano[TAM], int quantidadeClientes, int quantidadePratos, int quantidadePlanos) {
    Tabela Tabela[TAM];
    int quantidadeTabela = 0;
    for (int i = 0; i < quantidadePlanos; i++) {
        int repeated = 0;

        for (int j = 0; j < quantidadeTabela; j++) {
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
            Tabela[quantidadeTabela].codigo = Plano[i].codigo;
            strcpy(Tabela[quantidadeTabela].refeicao, Plano[i].refeicao);
            for (int j = 0; j < quantidadeClientes; j++) {
                if (Cliente[j].codigo == Plano[i].codigo) {
                    strcpy(Tabela[quantidadeTabela].nome, Cliente[j].nome);
                }
            }
            Tabela[quantidadeTabela].diainicio = Plano[i].dia;
            Tabela[quantidadeTabela].mesinicio = Plano[i].mes;
            Tabela[quantidadeTabela].anoinicio = Plano[i].ano;
            Tabela[quantidadeTabela].diafim = Plano[i].dia;
            Tabela[quantidadeTabela].mesfim = Plano[i].mes;
            Tabela[quantidadeTabela].anofim = Plano[i].ano;
            Tabela[quantidadeTabela].calMin = Plano[i].calMin;
            Tabela[quantidadeTabela].calMax = Plano[i].calMax;
            Tabela[quantidadeTabela].calorias = 0;
            quantidadeTabela++;
        }
    }

    for (int i = 0; i < quantidadeTabela; i++) {
        for (int j = 0; j < quantidadePratos; j++) {
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
    for (int i = 0; i < quantidadeTabela; i++) {
        printf("| %d | %s | %s | %d-%d-%d | %d-%d-%d | %d | %d | %d |\n", Tabela[i].codigo, Tabela[i].nome, Tabela[i].refeicao, Tabela[i].diainicio, Tabela[i].mesinicio, Tabela[i].anoinicio, Tabela[i].diafim, Tabela[i].mesfim, Tabela[i].anofim, Tabela[i].calMin, Tabela[i].calMax, Tabela[i].calorias);
        printf("---------------------------------------------------------------------------\n");
    }
    return 0;
}