#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
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