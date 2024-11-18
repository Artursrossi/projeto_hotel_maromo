#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"

int cadastrarUsuario(char nome[64],char email[32],char senha[32],int idade) {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char query[192] = "INSERT INTO usuarios (nome, email, senha, idade) VALUES ";
    // Concatenar Nome
    strcat(query, "('");
    strcat(query, nome);
    strcat(query, "', ");

    // Concatenar Email
    strcat(query, "'");
    strcat(query, email);
    strcat(query, "', ");

    // Concatenar Senha
    strcat(query, "'");
    strcat(query, senha);
    strcat(query, "', ");

    // Concatenar Idade
    // char s_idade[3];
    // itoa(idade, s_idade, 10);
    strcat(query, "30");
    strcat(query, ");");

    // Obter resposta do SQL executado
    PGresult *res = PQexec(conn, query);

    // Obter código de resposta da chamada ao banco
    ExecStatusType resStatus = PQresultStatus(res);

    // Fazer a captação de possíveis erros
    if (resStatus != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return 0; // Código de erro
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 1; // Código de sucesso
}