#include "psql.h"

PGconn* connection(){
  // Definir credenciais do banco de dados
  char *conninfo = "dbname=lingc user=docker password=Teste123!@# host=localhost port=5432";

  // Estabelecer conexão com o banco de dados
  PGconn *conn = PQconnectdb(conninfo);

  // Verificar o status da conexão, e finalizar o programa em caso de erro de conexão
  if (PQstatus(conn) != CONNECTION_OK) {
    printf("Não foi possível se conectar ao banco de dados: %s\n", PQerrorMessage(conn));
    PQfinish(conn);
    exit(1);
  }

  return conn;
}