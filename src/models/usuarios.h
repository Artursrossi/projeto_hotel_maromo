#ifndef MODELS_USUARIOS_H
#define MODELS_USUARIOS_H

/*
  Cadastrar Usuário no banco de dados
 */
int cadastrarUsuario(char nome[65],char email[33],char senha[17],int idade);

/*
  Obter um único usuário do banco de dados, utilizando o email do mesmo, que é único
 */
int obterUnicoUsuario(t_usuario *p_usuario,char email[33]);

/*
  Obter todos os usuários do banco de dados
 */
int obterMuitosUsuarios();

#endif