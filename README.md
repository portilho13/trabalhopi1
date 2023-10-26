# Trabalho Programacao Imperativa

LESI - PI- 2023-2024 1Programação Imperativa
IPCA / EST
1º ano - LESI / LESIPL - 2023-2024
Trabalho Prático
A resolução do trabalho prático é individual ou em grupo de no máximo trẽs elementos.Deverá ser submetida até ao dia 31-12-2023, via a plataforma Moodle (através de endereçoadisponibilizar posteriormente) sob a forma de um ficheiro compactado comonomeLESI_PI_TP_nºaluno1_nºaluno2.zip. Juntamente com todo o código fonte desenvolvido deverá entregar a API correspondente(ex.documentação em Doxygen). Critérios de avaliação
● Cumprimento dos objetivos 30%;
● Qualidade do código produzido 20%;
● Qualidade da documentação elaborada 10%;
● Comportamento da aplicação (estar operacional) 10%;
● Defesa individual do trabalho 30%
Objetivos
Com este trabalho prático pretende-se sedimentar os conhecimentos introduzidos nas aulasda unidade curricular Programação Imperativa, relativos a:
● Métodos rigorosos de análise de problemas e desenvolvimento de software;
● Métodos de programação imperativa e sua implementação na linguagemdeprogramação C. Enunciado
O problema que se pretende explorar está relacionado com o bem-estar das pessoas. Ocontexto atual promove a necessidade de cuidados nutricionais bem como uma dieta saudável.
LESI - PI- 2023-2024 2Existência evidências que indicam que um comportamento alimentar saudável pode modularfavoravelmente a inflamação do corpo e prevenir a forma grave de doenças. Umadietasaudável incluí um alto teor de frutas e vegetais, peixe, etc. Para isso, possuir uma aplicação informática que apoie a gerir este tipo de comportamento,controlando e monitorizando a realização de uma deita alimentar saudável, é fundamental.Pretende-se assim desenvolver uma solução para manipulação dos dados dos pacientes deuma gabinete de nutrição, aplicando o paradigma de programação imperativa (linguagemC),de modo a responder, entre outras, às funcionalidades seguintes:
1. a. Carregamento de um ficheiro de texto contendo os dados dos pacientes. Considereainformação estruturada em várias linhas, identificando em cada linha vária informação,nomeadamente, o número de paciente, nome, telefone. Apresenta-se a seguir umexemplo de conteúdo do ficheiro a ler:
0001;Paulo;123456789
0003;Maria;96543210
0002;João;123321123
b. Carregamento do conteúdo de um segundo ficheiro de texto contendoainformação da dieta realizada por cada paciente, nomeadamente, númerodepaciente, data, refeição, alimento, calorias:
0001; 01-01-2023; pequeno almoço; pão; 60 cal
0003; 14-02-2023; almoço; sopa; 120 cal
0002; 23-05-2023; jantar; prato de carne; 1200 cal
0001; 01-01-2023; pequeno almoço; banana; 120 cal
c. Carregamento do conteúdo de um terceiro ficheiro de texto contendo os dados dosplanos nutricionais, definido pelo gabinete de nutrição para cada paciente, ajustadoao perfil e necessidade de cada paciente. Cada linha deve identificar o paciente, datada refeição, refeição, calorias mínimas admissíveis, calorias máximas permitidas:
0001; 01-01-2023; pequeno almoço; 300 Cal, 400 Cal
0001; 01-01-2023; jantar; 500 Cal, 600 Cal
0003; 21-03-2023; almoço; 500 Cal, 600 Cal
LESI - PI- 2023-2024 32. Apresentação do número de pacientes que ultrapassaram determinada quantidadedecalorias, num determinado período;
3. Listagem dos pacientes, ordenada por ordem decrescente do número de paciente, querealizaram alguma refeição com quantidade de calorias fora do intervalo (de acordocomo plano nutricional) num determinado período;
4. Listar o plano nutricional de um paciente para determinada refeição ao longodeumdeterminado período;
5. Cálculo das médias da calorias consumidas por refeição por cada paciente ao longodeumdeterminado período;
6. Gerar a tabela das refeições planeadas e realizadas para todos os pacientes, ondedevemconstar a seguinte informação: Número de Paciente, Nome, Tipo Refeição, Data deInício,Data de Fim, Calorias Mínimo, Calorias Máximo e Consumo realizado. No ecrã, essatabeladeverá ter um aspeto semelhante ao que a seguir se apresenta:
NP Paciente
Tipo
Refeição
Inicio Fim Mínimo Máximo Consumo0001 Paula
Peq. Almoço
01-01- 2023
20-01- 2023 3000 4000 37500003 Maria Jantar
21-03- 2023
15-04- 2023 5000 6000 57500001 Paula Almoço
21-01- 2023
15-02- 2023 5000 6000 5800- - - - - -
- - - - - -