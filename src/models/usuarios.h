#ifndef MODELS_USUARIOS_H
#define MODELS_USUARIOS_H

/*
  Cadastrar Usuário no banco de dados
 */
int cadastrarUsuario(char nome[64],char email[32],char senha[32],int idade);

/*
  Obter um único usuário do banco de dados, utilizando o email do mesmo, que é único
 */
int obterUnicoUsuario(char email_usuario[32]);

/*
  Obter todos os usuários do banco de dados
 */
int obterMuitosUsuarios();

#endif