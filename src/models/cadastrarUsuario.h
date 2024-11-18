#ifndef CADASTRAR_USUARIO_H
#define CADASTRAR_USUARIO_H

#include "cadastrarUsuario.c"

/*
  Cadastrar Usuário no banco de dados
 */
int cadastrarUsuario(char nome[64],char email[32],char senha[32],int idade);

#endif