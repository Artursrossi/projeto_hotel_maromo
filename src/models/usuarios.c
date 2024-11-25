#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
#include "../usuario.h"
#include "../utils/conversoes.h"

int cadastrarUsuario(char nome[65], char email[33], char senha[17], int idade) {
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

    // Concatenar email
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
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 200; // Retornar CÓDIGO 200 sucesso
}

int obterMuitosUsuarios(t_usuario **p_usuarios, int *numero_usuarios) {
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
        return 500; // Retornar CÓDIGO 500 para erro de execução
    }

    // Obter número de linhas e colunas
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    // Escrever número de usuários no banco de dados no ponteiro recebido
    *numero_usuarios = rows;

    // Percorrer cada linha do banco
    for (int i = 0; i < rows; i++) {
        int novo_tamanho = i + 2; // Próximo tamanho do vetor
        *p_usuarios = realloc(*p_usuarios, novo_tamanho * sizeof(t_usuario));
        /* Verificar se o realloc foi executado com sucesso*/
        if (p_usuarios == NULL) {
            printf("Erro ao alocar memória para p_usuarios");
            return 500; // Retornar CÓDIGO 500 erro na execução
        }

        // Percorrer cada coluna da linha
        for (int j = 0; j < cols; j++) {
            switch(j){
                // Obter coluna ID
                case 0:
                    int codigo = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
                    (*p_usuarios)[i].codigo = codigo;
                    break;
                // Obter coluna NOME
                case 1:
                    strcpy((*p_usuarios)[i].nome, PQgetvalue(res, i, j));
                    break;
                // Obter coluna EMAIL
                 case 2:
                    strcpy((*p_usuarios)[i].email, PQgetvalue(res, i, j));
                    break;
                // Obter coluna SENHA
                case 3:
                    strcpy((*p_usuarios)[i].senha, PQgetvalue(res, i, j));
                    break;
                // Obter coluna IDADE
                case 4:
                    int idade = 0;
                    sscanf(PQgetvalue(res, i, j), "%d", &idade); // Transformar string em inteiro   
                    (*p_usuarios)[i].idade = idade;
                    break;
                // Obter coluna CARGO
                case 5:
                    strcpy((*p_usuarios)[i].cargo, PQgetvalue(res, i, j));
                    break;
                // Obter coluna CADASTRADO_EM
                case 6:
                    strcpy((*p_usuarios)[i].cadastrado_em, PQgetvalue(res, i, j));
                    break;
            }
        }
    }

    // Finalizar conexão com o banco de dados
    PQclear(res);
    PQfinish(conn);

    return 200; // Retornar CÓDIGO 200 sucesso
}