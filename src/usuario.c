#include <stdio.h>
#include <string.h>
#include "usuario.h"
#include "models/obterUsuarios.h"
#include "models/cadastrarUsuario.h"

int registrarUsuario(){
  char nome[64] = "Teste";
  char email[32] = "teste@gmail.com";
  char senha[32] = "123";
  int idade = 30;
  cadastrarUsuario(nome, email, senha, idade);


  return 1;
}

int autenticarUsuario(){
  return 1;
}

int deslogarUsuario(){
  return 1;
}

int deletarUsuario(){
  return 1;
}

int buscarUnicoUsuario(){
  return 1;
}

int listarUsuarios(){
  obterUsuarios();

  return 1;
}

int controlarRegistroUsuario(){
  printf("Cadastrar nova conta \n");
  registrarUsuario();

  return 1;
}

int controlarLoginUsuario(){
  printf("Entrar com uma conta existente \n");

  return 1;
}