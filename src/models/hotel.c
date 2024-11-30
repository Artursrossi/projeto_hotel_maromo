#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../external/libpq/libpq-fe.h"
#include "../lib/psql.h"
#include "../hotel.h"
#include "../utils/conversoes.h"

int cadastrarQuarto(int numero, char tipo, float valor_diaria) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "INSERT INTO quartos (numero, tipo, valor_diaria) VALUES ";

  // Concatenar numero
  char *s_numero = intToCharVetor(numero);
  strcat(query, "(");
  strcat(query, s_numero);
  strcat(query, ", ");

  // Concatenar tipo
  char s_tipo[2] = {
    tipo,
    '\0'
  }; // Transformar char para vetor de char
  strcat(query, "'");
  strcat(query, s_tipo);
  strcat(query, "', ");

  // Concatenar valor_diaria
  char *s_valor_diaria = floatToCharVetor(valor_diaria);
  strcat(query, s_valor_diaria);
  strcat(query, ");");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 201; // Retornar CÓDIGO 201 criado com sucesso
}

int cadastrarRegistroAluguel(int codigo_quarto_escolhido, int codigo_usuario, int periodo_dias, float valor_total, int numero_ocupantes) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "INSERT INTO registro_alugueis (quarto_escolhido, usuario_relacionado, periodo_dias, valor_total, numero_ocupantes) VALUES ";

  // Concatenar quarto_escolhido
  char *s_codigo_quarto_escolhido = intToCharVetor(codigo_quarto_escolhido);
  strcat(query, "(");
  strcat(query, s_codigo_quarto_escolhido);
  strcat(query, ", ");

  // Concatenar usuario_relacionado
  char *s_codigo_usuario = intToCharVetor(codigo_usuario);
  strcat(query, s_codigo_usuario);
  strcat(query, ", ");

  // Concatenar periodo_dias
  char *s_periodo_dias = intToCharVetor(periodo_dias);
  strcat(query, s_periodo_dias);
  strcat(query, ", ");

  // Concatenar valor_total
  char *s_valor_total = floatToCharVetor(valor_total);
  strcat(query, s_valor_total);
  strcat(query, ", ");

  // Concatenar valor_total
  char *s_numero_ocupantes = intToCharVetor(numero_ocupantes);
  strcat(query, s_numero_ocupantes);
  strcat(query, ");");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 201; // Retornar CÓDIGO 201 criado com sucesso
}

int obterMuitosRegistroAluguel(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char *query = "SELECT * FROM registro_alugueis;";

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
  *numero_registro_aluguel = rows;

  // Percorrer cada linha do banco
  for (int i = 0; i < rows; i++) {
    int novo_tamanho = i + 2; // Próximo tamanho do vetor
    *p_registro_aluguel = realloc(*p_registro_aluguel, novo_tamanho * sizeof(t_registro_aluguel));
    /* Verificar se o realloc foi executado com sucesso*/
    if (*p_registro_aluguel == NULL) {
      printf("Erro ao alocar memória para p_registro_aluguel");
      return 500; // Retornar CÓDIGO 500 erro na execução
    }

    // Percorrer cada coluna da linha
    for (int j = 0; j < cols; j++) {
      switch (j) {
        //Obter coluna CODIGO
      case 0:
        int codigo = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
        (*p_registro_aluguel)[i].codigo = codigo;
        break;
        // Obter coluna QUARTO_ESCOLHIDO
      case 1:
        int quarto_escolhido = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &quarto_escolhido); // Transformar string em inteiro
        (*p_registro_aluguel)[i].quarto_escolhido = quarto_escolhido;
        break;
        // Obter coluna USUARIO_RELACIONADO
      case 2:
        int usuario_relacionado = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &usuario_relacionado); // Transformar string em inteiro
        (*p_registro_aluguel)[i].usuario_relacionado = usuario_relacionado;
        break;
        // Obter coluna PERIODO_DIAS
      case 3:
        int periodo_dias = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &periodo_dias); // Transformar string em inteiro
        (*p_registro_aluguel)[i].periodo_dias = periodo_dias;
        break;
        // Obter coluna VALOR_TOTAL
      case 4:
        float valor_total = 0.0;
        sscanf(PQgetvalue(res, i, j), "%f", &valor_total); // Transformar string em inteiro
        (*p_registro_aluguel)[i].valor_total = valor_total;
        break;
        // Obter coluna NUMERO_OCUPANTES
      case 5:
        int numero_ocupantes = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &numero_ocupantes); // Transformar string em inteiro
        (*p_registro_aluguel)[i].numero_ocupantes = numero_ocupantes;
        break;
        // Obter coluna ALUGUEL_EM_ANDAMENTO
      case 6:
          bool aluguel_em_andamento = PQgetvalue(res, i, j)[0] == 't' ? true : false;
         (*p_registro_aluguel)[i].aluguel_em_andamento = aluguel_em_andamento;
        // Obter coluna CADASTRADO_EM
      case 7:
        // Formatar data para aaaa-mm-dd
        char data_cadastro[27];
        strcpy(data_cadastro, PQgetvalue(res, i, j));
        char data_alugado_em[11];
        for (int i = 0; i < 10; i++) {
          data_alugado_em[i] = data_cadastro[i];
        }
        data_alugado_em[10] = '\0';
        strcpy((*p_registro_aluguel)[i].alugado_em, data_alugado_em);
        break;
      }
    }
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int obterMuitosRegistroAluguelPorCodigoUsuario(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel, int codigo_usuario) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "SELECT * FROM registro_alugueis WHERE usuario_relacionado = ";

  // Concatenar codigo_usuario
  char *s_codigo_usuario = intToCharVetor(codigo_usuario);
  strcat(query, s_codigo_usuario);
  strcat(query, ";");

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
  *numero_registro_aluguel = rows;

  // Percorrer cada linha do banco
  for (int i = 0; i < rows; i++) {
    int novo_tamanho = i + 2; // Próximo tamanho do vetor
    *p_registro_aluguel = realloc(*p_registro_aluguel, novo_tamanho * sizeof(t_registro_aluguel));
    /* Verificar se o realloc foi executado com sucesso*/
    if (*p_registro_aluguel == NULL) {
      printf("Erro ao alocar memória para p_registro_aluguel");
      return 500; // Retornar CÓDIGO 500 erro na execução
    }

    // Percorrer cada coluna da linha
    for (int j = 0; j < cols; j++) {
      switch (j) {
        //Obter coluna CODIGO
      case 0:
        int codigo = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
        (*p_registro_aluguel)[i].codigo = codigo;
        break;
        // Obter coluna QUARTO_ESCOLHIDO
      case 1:
        int quarto_escolhido = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &quarto_escolhido); // Transformar string em inteiro
        (*p_registro_aluguel)[i].quarto_escolhido = quarto_escolhido;
        break;
        // Obter coluna USUARIO_RELACIONADO
      case 2:
        int usuario_relacionado = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &usuario_relacionado); // Transformar string em inteiro
        (*p_registro_aluguel)[i].usuario_relacionado = usuario_relacionado;
        break;
        // Obter coluna PERIODO_DIAS
      case 3:
        int periodo_dias = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &periodo_dias); // Transformar string em inteiro
        (*p_registro_aluguel)[i].periodo_dias = periodo_dias;
        break;
        // Obter coluna VALOR_TOTAL
      case 4:
        float valor_total = 0.0;
        sscanf(PQgetvalue(res, i, j), "%f", &valor_total); // Transformar string em inteiro
        (*p_registro_aluguel)[i].valor_total = valor_total;
        break;
        // Obter coluna NUMERO_OCUPANTES
      case 5:
        int numero_ocupantes = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &numero_ocupantes); // Transformar string em inteiro
        (*p_registro_aluguel)[i].numero_ocupantes = numero_ocupantes;
        break;
        // Obter coluna ALUGUEL_EM_ANDAMENTO
      case 6:
          bool aluguel_em_andamento = PQgetvalue(res, i, j)[0] == 't' ? true : false;
         (*p_registro_aluguel)[i].aluguel_em_andamento = aluguel_em_andamento;
        // Obter coluna CADASTRADO_EM
      case 7:
        // Formatar data para aaaa-mm-dd
        char data_cadastro[27];
        strcpy(data_cadastro, PQgetvalue(res, i, j));
        char data_alugado_em[11];
        for (int i = 0; i < 10; i++) {
          data_alugado_em[i] = data_cadastro[i];
        }
        data_alugado_em[10] = '\0';
        strcpy((*p_registro_aluguel)[i].alugado_em, data_alugado_em);
        break;
      }
    }
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int obterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel, int codigo_usuario) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "SELECT * FROM registro_alugueis WHERE aluguel_em_andamento = true AND usuario_relacionado = ";

  // Concatenar codigo_usuario
  char *s_codigo_usuario = intToCharVetor(codigo_usuario);
  strcat(query, s_codigo_usuario);
  strcat(query, ";");

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
  *numero_registro_aluguel = rows;

  // Percorrer cada linha do banco
  for (int i = 0; i < rows; i++) {
    int novo_tamanho = i + 2; // Próximo tamanho do vetor
    *p_registro_aluguel = realloc(*p_registro_aluguel, novo_tamanho * sizeof(t_registro_aluguel));
    /* Verificar se o realloc foi executado com sucesso*/
    if (*p_registro_aluguel == NULL) {
      printf("Erro ao alocar memória para p_registro_aluguel");
      return 500; // Retornar CÓDIGO 500 erro na execução
    }

    // Percorrer cada coluna da linha
    for (int j = 0; j < cols; j++) {
      switch (j) {
        //Obter coluna CODIGO
      case 0:
        int codigo = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
        (*p_registro_aluguel)[i].codigo = codigo;
        break;
        // Obter coluna QUARTO_ESCOLHIDO
      case 1:
        int quarto_escolhido = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &quarto_escolhido); // Transformar string em inteiro
        (*p_registro_aluguel)[i].quarto_escolhido = quarto_escolhido;
        break;
        // Obter coluna USUARIO_RELACIONADO
      case 2:
        int usuario_relacionado = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &usuario_relacionado); // Transformar string em inteiro
        (*p_registro_aluguel)[i].usuario_relacionado = usuario_relacionado;
        break;
        // Obter coluna PERIODO_DIAS
      case 3:
        int periodo_dias = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &periodo_dias); // Transformar string em inteiro
        (*p_registro_aluguel)[i].periodo_dias = periodo_dias;
        break;
        // Obter coluna VALOR_TOTAL
      case 4:
        float valor_total = 0.0;
        sscanf(PQgetvalue(res, i, j), "%f", &valor_total); // Transformar string em inteiro
        (*p_registro_aluguel)[i].valor_total = valor_total;
        break;
        // Obter coluna NUMERO_OCUPANTES
      case 5:
        int numero_ocupantes = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &numero_ocupantes); // Transformar string em inteiro
        (*p_registro_aluguel)[i].numero_ocupantes = numero_ocupantes;
        break;
        // Obter coluna ALUGUEL_EM_ANDAMENTO
      case 6:
          bool aluguel_em_andamento = PQgetvalue(res, i, j)[0] == 't' ? true : false;
         (*p_registro_aluguel)[i].aluguel_em_andamento = aluguel_em_andamento;
        // Obter coluna CADASTRADO_EM
      case 7:
        // Formatar data para aaaa-mm-dd
        char data_cadastro[27];
        strcpy(data_cadastro, PQgetvalue(res, i, j));
        char data_alugado_em[11];
        for (int i = 0; i < 10; i++) {
          data_alugado_em[i] = data_cadastro[i];
        }
        data_alugado_em[10] = '\0';
        strcpy((*p_registro_aluguel)[i].alugado_em, data_alugado_em);
        break;
      }
    }
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
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
      switch (j) {
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
          bool preparado = PQgetvalue(res, i, j)[0] == 't' ? true : false;
         (*p_quartos)[i].preparado = preparado;
        break;
        // Obter coluna OCUPADO
      case 5:
        bool ocupado = PQgetvalue(res, i, j)[0] == 't' ? true : false;
        (*p_quartos)[i].ocupado = ocupado;
        break;
        // Obter coluna MODIFICADO_EM
      case 6:
        // Formatar data para aaaa-mm-dd
        char data_modificado[27];
        strcpy(data_modificado, PQgetvalue(res, i, j));
        char data_modificado_formatada[11];
        for (int i = 0; i < 10; i++) {
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
        for (int i = 0; i < 10; i++) {
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

int obterMuitosQuartosDesocupados(t_quarto **p_quartos, int *numero_quartos) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char *query = "SELECT * FROM quartos WHERE ocupado = false AND preparado = true";

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
      switch (j) {
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
        bool preparado = PQgetvalue(res, i, j)[0] == 't' ? true : false;
         (*p_quartos)[i].preparado = preparado;
        break;
        // Obter coluna OCUPADO
      case 5:
        bool ocupado = PQgetvalue(res, i, j)[0] == 't' ? true : false;
        (*p_quartos)[i].ocupado = ocupado;
        break;
        // Obter coluna MODIFICADO_EM
      case 6:
        // Formatar data para aaaa-mm-dd
        char data_modificado[27];
        strcpy(data_modificado, PQgetvalue(res, i, j));
        char data_modificado_formatada[11];
        for (int i = 0; i < 10; i++) {
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
        for (int i = 0; i < 10; i++) {
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

int obterUnicoQuartoPorNumero(t_quarto *p_quarto, int numero_quarto) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "SELECT * FROM quartos WHERE numero = ";

  // Concatenar codigo_quarto
  char *s_numero_quarto = intToCharVetor(numero_quarto);
  strcat(query, "'");
  strcat(query, s_numero_quarto);
  strcat(query, "';");

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

  if (rows == 0) return 404; // Retornar CÓDIGO 404 para quarto não encontrado

  // Percorrer cada linha do banco
  for (int i = 0; i < rows; i++) {
    // Percorrer cada coluna da linha
    for (int j = 0; j < cols; j++) {
      switch (j) {
        //Obter coluna CODIGO
      case 0:
        int codigo = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &codigo); // Transformar string em inteiro
        p_quarto -> codigo = codigo;
        break;
        // Obter coluna NUMERO
      case 1:
        int numero = 0;
        sscanf(PQgetvalue(res, i, j), "%d", &numero); // Transformar string em inteiro
        p_quarto -> numero = numero;
        break;
        // Obter coluna TIPO
      case 2:
        p_quarto -> tipo = PQgetvalue(res, i, j)[0];
        break;
        // Obter coluna VALOR_DIARIA
      case 3:
        float valor_diaria = 0.0;
        sscanf(PQgetvalue(res, i, j), "%f", &valor_diaria); // Transformar string em inteiro
        p_quarto -> valor_diaria = valor_diaria;
        break;
        // Obter coluna PREPARADO
      case 4:
        p_quarto -> preparado = PQgetvalue(res, i, j);
        break;
        // Obter coluna OCUPADO
      case 5:
        p_quarto -> ocupado = PQgetvalue(res, i, j);
        break;
        // Obter coluna MODIFICADO_EM
      case 6:
        // Formatar data para aaaa-mm-dd
        char data_modificado[27];
        strcpy(data_modificado, PQgetvalue(res, i, j));
        char data_modificado_formatada[11];
        for (int i = 0; i < 10; i++) {
          data_modificado_formatada[i] = data_modificado[i];
        }
        data_modificado_formatada[10] = '\0';
        strcpy(p_quarto -> modificado_em, data_modificado_formatada);
        break;
        // Obter coluna CADASTRADO_EM
      case 7:
        // Formatar data para aaaa-mm-dd
        char data_cadastro[27];
        strcpy(data_cadastro, PQgetvalue(res, i, j));
        char data_cadastro_formatada[11];
        for (int i = 0; i < 10; i++) {
          data_cadastro_formatada[i] = data_cadastro[i];
        }
        data_cadastro_formatada[10] = '\0';
        strcpy(p_quarto -> cadastrado_em, data_cadastro_formatada);
        break;
      }
    }
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int ocuparQuarto(int codigo_quarto) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "UPDATE quartos SET ocupado = true WHERE codigo = ";

  // Concatenar codigo_quarto
  char *s_codigo_quarto = intToCharVetor(codigo_quarto);
  strcat(query, "'");
  strcat(query, s_codigo_quarto);
  strcat(query, "';");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 para erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int desocuparQuarto(int codigo_quarto) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "UPDATE quartos SET ocupado = false WHERE codigo = ";

  // Concatenar codigo_quarto
  char *s_codigo_quarto = intToCharVetor(codigo_quarto);
  strcat(query, "'");
  strcat(query, s_codigo_quarto);
  strcat(query, "';");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 para erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int finalizarReserva(int codigo_registro_aluguel) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "UPDATE registro_alugueis SET aluguel_em_andamento = false WHERE codigo = ";

  // Concatenar codigo_quarto
  char *s_codigo_registro_aluguel = intToCharVetor(codigo_registro_aluguel);
  strcat(query, "'");
  strcat(query, s_codigo_registro_aluguel);
  strcat(query, "';");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 para erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}

int atualizarReservaNumeroOcupantes(int codigo_registro_aluguel, int novo_numero_ocupantes) {
  // Obter conexão com o banco de dados
  PGconn *conn = connection();

  // SQL para ser executado
  char query[192] = "UPDATE registro_alugueis SET numero_ocupantes = ";

  // Concatenar novo_numero_ocupantes
  char *s_novo_numero_ocupantes = intToCharVetor(novo_numero_ocupantes);
  strcat(query, s_novo_numero_ocupantes);

  strcat(query, " WHERE codigo = ");

  // Concatenar codigo_registro_aluguel
  char *s_codigo_registro_aluguel = intToCharVetor(codigo_registro_aluguel);
  strcat(query, s_codigo_registro_aluguel);
  strcat(query, ";");

  // Obter resposta do SQL executado
  PGresult *res = PQexec(conn, query);

  // Obter código de resposta da chamada ao banco
  ExecStatusType resStatus = PQresultStatus(res);

  // Fazer a captação de possíveis erros
  if (resStatus != PGRES_COMMAND_OK) {
    PQclear(res);
    PQfinish(conn);
    return 500; // Retornar CÓDIGO 500 para erro de execução
  }

  // Finalizar conexão com o banco de dados
  PQclear(res);
  PQfinish(conn);

  return 200; // Retornar CÓDIGO 200 sucesso
}
