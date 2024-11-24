#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
#include "../hotel.h"
#include "../utils/conversoes.h"

int cadastrarQuarto(int numero,char tipo,float valor_diaria) {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char query[192] = "INSERT INTO quartos (numero, tipo, valor_diaria) VALUES ";
    // Concatenar numero
    char *s_numero = intToCharVetor(numero);
    strcat(query, "(");
    strcat(query, s_numero);
    strcat(query, ", ");

    // Concatenar Tipo
    char s_tipo[2] = {tipo, '\0'}; // Transformar char para vetor de char
    strcat(query, "'");
    strcat(query, s_tipo);
    strcat(query, "', ");

    char *s_valor_diaria = floatToCharVetor(valor_diaria);
    strcat(query, s_valor_diaria);
    strcat(query, ");");

    // Obter resposta do SQL executado
    PGresult *res = PQexec(conn, query);

    // Obter código de resposta da chamada ao banco
    ExecStatusType resStatus = PQresultStatus(res);

    // Fazer a captação de possíveis erros
    if (resStatus != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return 500; // Retornar CÓDIGO 500 erro de execução
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 201; // Retornar CÓDIGO 201 criado com sucesso
}

int obterMuitosQuartos(t_quarto **p_quartos, int *numero_quartos) {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char *query = "SELECT * FROM quartos";

    // Obter resposta do SQL executado
    PGresult *res = PQexec(conn, query);

    // Obter código de resposta da chamada ao banco
    ExecStatusType resStatus = PQresultStatus(res);

    // Fazer a captação de possíveis erros
    if (resStatus != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return 500; // Retornar CÓDIGO 500 erro de execução
    }

    // Obter número de linhas e colunas
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    // Escrever número de quartos no banco de dados no ponteiro recebido
    *numero_quartos = rows;

    // Percorrer cada linha do banco
    for (int i = 0; i < rows; i++) {
        int novo_tamanho = i + 2; // Próximo tamanho do vetor
        *p_quartos = realloc(*p_quartos, novo_tamanho * sizeof(t_quarto));
        /* Verificar se o realloc foi executado com sucesso*/
        if (*p_quartos == NULL) {
            printf("Erro ao alocar memória para p_quartos");
            return 500; // Retornar CÓDIGO 500 erro na execução
        }

        // Percorrer cada coluna da linha
        for (int j = 0; j < cols; j++) {
            switch(j){
                //Obter coluna CODIGO
                case 0:
                    int codigo = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro  
                    (*p_quartos)[i].codigo = codigo;
                    break;
                // Obter coluna NUMERO
                case 1:
                    int numero = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &numero); // Transformar string em inteiro 
                    (*p_quartos)[i].numero = numero;
                    break;
                // Obter coluna TIPO
                 case 2:
                    (*p_quartos)[i].tipo = PQgetvalue(res, i, j)[0];
                    break;
                // Obter coluna VALOR_DIARIA
                case 3:
                    float valor_diaria = 0.0;
                    sscanf(PQgetvalue(res, i, j), "%f", &valor_diaria); // Transformar string em inteiro 
                    (*p_quartos)[i].valor_diaria = valor_diaria;
                    break;
                // Obter coluna PREPARADO
                case 4:
                    (*p_quartos)[i].preparado = PQgetvalue(res, i, j);
                    break;
                // Obter coluna OCUPADO
                case 5:
                    (*p_quartos)[i].ocupado = PQgetvalue(res, i, j);
                    break;
                // Obter coluna MODIFICADO_EM
                case 6:
                    // Formatar data para aaaa-mm-dd
                    char data_modificado[27];
                    strcpy(data_modificado, PQgetvalue(res, i, j));
                    char data_modificado_formatada[11];
                    for(int i = 0; i < 10; i++){
                      data_modificado_formatada[i] = data_modificado[i];
                    }
                    data_modificado_formatada[10] = '\0';
                    strcpy((*p_quartos)[i].modificado_em, data_modificado_formatada);
                    break;
                // Obter coluna CADASTRADO_EM
                case 7:
                    // Formatar data para aaaa-mm-dd
                    char data_cadastro[27];
                    strcpy(data_cadastro, PQgetvalue(res, i, j));
                    char data_cadastro_formatada[11];
                    for(int i = 0; i < 10; i++){
                      data_cadastro_formatada[i] = data_cadastro[i];
                    }
                    data_cadastro_formatada[10] = '\0';
                    strcpy((*p_quartos)[i].cadastrado_em, data_cadastro_formatada);
                    break;
            }
        }
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 200; // Retornar CÓDIGO 200 sucesso
}