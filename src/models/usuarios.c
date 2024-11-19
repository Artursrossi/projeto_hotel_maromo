#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
#include "../usuario.h"

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
    // TODO: Transformar INT to String
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

int obterUnicoUsuario(char email_usuario[32]) {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char *query = "SELECT * FROM usuarios WHERE email = 'artur@gmail.com'";

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

    // Obter número de linhas e colunas
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    t_usuario usuario;

    // Percorrer cada linha do banco
    for (int i = 0; i < rows; i++) {
        // Percorrer cada coluna da linha
        for (int j = 0; j < cols; j++) {
            printf("%s\t", PQgetvalue(res, i, j));
            switch(j){
                // Obter coluna ID
                case 0:
                    usuario.codigo = PQgetvalue(res, i, j)[0] - '0';
                    break;
                // Obter coluna NOME
                case 1:
                    strcpy(usuario.nome, PQgetvalue(res, i, j));
                    break;
                // Obter coluna EMAIL
                 case 2:
                    strcpy(usuario.email, PQgetvalue(res, i, j));
                    break;
                // Obter coluna SENHA
                case 3:
                    strcpy(usuario.senha, PQgetvalue(res, i, j));
                    break;
                // Obter coluna IDADE
                case 4:
                    usuario.idade = PQgetvalue(res, i, j)[0] - '0';
                    break;
                // Obter coluna CARGO
                case 5:
                    strcpy(usuario.cargo, PQgetvalue(res, i, j));
                    break;
                // Obter coluna CADASTRADO_EM
                case 6:
                    strcpy(usuario.cadastrado_em, PQgetvalue(res, i, j));
                    break;
            }
        }
        // Pular linha para inserir próximo usuário
        printf("\n");
    }

    printf("---------------------------------\n");
    printf("%d\n", usuario.codigo);
    printf("%s\n", usuario.nome);
    printf("%s\n", usuario.email);
    printf("%s\n", usuario.senha);
    printf("%d\n", usuario.idade);
    printf("%s\n", usuario.cargo);
    printf("%s\n", usuario.cadastrado_em);

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 1;
}


int obterMuitosUsuarios() {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char *query = "SELECT * FROM usuarios";

    // Obter resposta do SQL executado
    PGresult *res = PQexec(conn, query);

    // Obter código de resposta da chamada ao banco
    ExecStatusType resStatus = PQresultStatus(res);

    // Fazer a captação de possíveis erros
    if (resStatus != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    // Obter número de linhas e colunas
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    t_usuario usuario;

    // Percorrer cada linha do banco
    for (int i = 0; i < rows; i++) {
        // Percorrer cada coluna da linha
        for (int j = 0; j < cols; j++) {
            printf("%s\t", PQgetvalue(res, i, j));
            switch(j){
                // Obter coluna ID
                case 0:
                    usuario.codigo = PQgetvalue(res, i, j)[0] - '0';
                    break;
                // Obter coluna NOME
                case 1:
                    strcpy(usuario.nome, PQgetvalue(res, i, j));
                    break;
                // Obter coluna EMAIL
                 case 2:
                    strcpy(usuario.email, PQgetvalue(res, i, j));
                    break;
                // Obter coluna SENHA
                case 3:
                    strcpy(usuario.senha, PQgetvalue(res, i, j));
                    break;
                // Obter coluna IDADE
                case 4:
                    usuario.idade = PQgetvalue(res, i, j)[0] - '0';
                    break;
                // Obter coluna CARGO
                case 5:
                    strcpy(usuario.cargo, PQgetvalue(res, i, j));
                    break;
                // Obter coluna CADASTRADO_EM
                case 6:
                    strcpy(usuario.cadastrado_em, PQgetvalue(res, i, j));
                    break;
            }
        }
        // Pular linha para inserir próximo usuário
        printf("\n");
    }

    printf("---------------------------------\n");
    printf("%d\n", usuario.codigo);
    printf("%s\n", usuario.nome);
    printf("%s\n", usuario.email);
    printf("%s\n", usuario.senha);
    printf("%d\n", usuario.idade);
    printf("%s\n", usuario.cargo);
    printf("%s\n", usuario.cadastrado_em);

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    // TODO: Retornar todos os usuários
    return 0;
}