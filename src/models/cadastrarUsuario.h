#ifndef CADASTRAR_USUARIO_H
#define CADASTRAR_USUARIO_H

#include "cadastrarUsuario.c"

/*
  Cadastrar Usuário no banco de dados
 */
int cadastrarUsuario(char nome[64],char email[64],char senha[64],int idade);

#endif