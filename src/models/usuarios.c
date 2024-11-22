#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
#include "../usuario.h"
#include "../utils/conversoes.h"

int cadastrarUsuario(char nome[65],char email[33],char senha[17],int idade) {
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
    char *s_idade = intToCharVetor(idade);
    strcat(query, s_idade);
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

int obterUnicoUsuario(t_usuario *p_usuario, char email[33]) {
    // Obter conexão com o banco de dados
    PGconn *conn = connection();

    // SQL para ser executado
    char query[192] = "SELECT * FROM usuarios WHERE email = ";
    strcat(query, "'");
    strcat(query, email);
    strcat(query, "'");

    // Obter resposta do SQL executado
    PGresult *res = PQexec(conn, query);

    // Obter código de resposta da chamada ao banco
    ExecStatusType resStatus = PQresultStatus(res);

    // Fazer a captação de possíveis erros
    if (resStatus != PGRES_TUPLES_OK) {
      PQclear(res);
      PQfinish(conn);
      return 500; // Retornar CÓDIGO 500 para erro de execução
    }

    // Obter número de linhas e colunas
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    if(rows == 0) return 404; // Retornar CÓDIGO 404 para usuário não encontrado

    // Percorrer cada linha do banco
    for (int i = 0; i < rows; i++) {
        // Percorrer cada coluna da linha
        for (int j = 0; j < cols; j++) {
            printf("%s\t", PQgetvalue(res, i, j));
            switch(j){
                // Obter coluna ID
                case 0:
                    int codigo = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
                    p_usuario->codigo = codigo;
                    break;
                // Obter coluna NOME
                case 1:
                    strcpy(p_usuario->nome, PQgetvalue(res, i, j));
                    break;
                // Obter coluna EMAIL
                 case 2:
                    strcpy(p_usuario->email, PQgetvalue(res, i, j));
                    break;
                // Obter coluna SENHA
                case 3:
                    strcpy(p_usuario->senha, PQgetvalue(res, i, j));
                    break;
                // Obter coluna IDADE
                case 4:
                    int idade = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &idade); // Transformar string em inteiro
                    p_usuario->idade = idade;
                    break;
                // Obter coluna CARGO
                case 5:
                    strcpy(p_usuario->cargo, PQgetvalue(res, i, j));
                    break;
                // Obter coluna CADASTRADO_EM
                case 6:
                    // Formatar data para aaaa-mm-dd
                    char data[27];
                    strcpy(data, PQgetvalue(res, i, j));
                    char data_formatada[11];
                    for(int i = 0; i < 10; i++){
                      data_formatada[i] = data[i];
                    }
                    data_formatada[10] = '\0';
                    strcpy(p_usuario->cadastrado_em, data_formatada);
                    break;
            }
        }
        // Pular linha para inserir próximo usuário
        printf("\n");
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 200; // Retornar CÓDIGO 200 sucesso
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

    return 200; // Retornar CÓDIGO 200 sucesso
}