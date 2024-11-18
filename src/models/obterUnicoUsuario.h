#ifndef OBTER_UNICO_USUARIO_H
#define OBTER_UNICO_USUARIO_H

#include "obterUnicoUsuario.c"

/*
  Obter um único usuário do banco de dados, utilizando o email do mesmo, que é único
 */
int obterUnicoUsuario(char email_usuario[32]);

#endif