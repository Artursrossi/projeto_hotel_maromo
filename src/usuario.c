#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "models/usuarios.h"

t_usuario usuario;

int registrarUsuario(){
  char nome[65] = "Maromo Roberto Moraes";
  char email[33] = "maromo@email.com";
  char senha[17] = "123";
  int idade = 45;

  int res = 0; // flag para salvar código de retorno da função
  res = cadastrarUsuario(nome, email, senha, idade);

  // Checar possibilidades de retorno da função
  if(res != 201){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  return 200;
}

int autenticarUsuario(){
  char email[33] = "maromo@email.com";

  int res = 0; // flag para salvar código de retorno da função
  res = obterUnicoUsuario(&usuario, email);
  
  // Checar possibilidades de retorno da função
  if(res == 404){
    printf("Usuário não encontrado"); 
    return 200;
  }
  if(res != 200){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }


  return 200;
}

int listarUsuarios(){
  t_usuario *usuarios = malloc(sizeof(t_usuario));
  int numero_usuarios;

  int res = 0; // flag para salvar código de retorno da função
  res = obterMuitosUsuarios(&usuarios, &numero_usuarios);

  // Checar possibilidades de retorno da função
  if(res != 200){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_usuarios; i++) {
    printf("Nome: %s, Email: %s, Idade: %d, Cadastrado em: %s \n", usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].cadastrado_em);
  }

  return 200;
}

int deslogarUsuario(){
  return 200;
}