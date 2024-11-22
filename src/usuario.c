#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "models/usuarios.h"

void registrarUsuario(){
  char nome[65] = "Maromo Roberto Moraes";
  char email[33] = "maromo@email.com";
  char senha[17] = "123";
  int idade = 45;
  cadastrarUsuario(nome, email, senha, idade);


  return;
}

t_usuario usuario;

void autenticarUsuario(){
  char email[33] = "maromo@email.com";
  int res = obterUnicoUsuario(&usuario, email);
  
  if(res == 404){
    printf("Usuário não encontrado"); 
    return;
  }
  if(res == 200){
    printf("\n\n\n%d\n", usuario.idade);
    printf("%s", usuario.cadastrado_em);
  }

  return;
}

void deslogarUsuario(){
  return;
}

void deletarUsuario(){
  return;
}

void buscarUnicoUsuario(){
  return;
}

void listarUsuarios(){
  t_usuario *usuarios = malloc(sizeof(t_usuario));
  int numero_usuarios;

  obterMuitosUsuarios(&usuarios, &numero_usuarios);

  for (int i = 0; i < numero_usuarios; i++) {
    printf("Nome: %s, Email: %s, Idade: %d, Cadastrado em: %s \n", usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].cadastrado_em);
  }

  return;
}

void controlarRegistroUsuario(){
  printf("Cadastrar nova conta \n");
  registrarUsuario();

  return;
}

void controlarLoginUsuario(){
  printf("Entrar com uma conta existente \n");
  listarUsuarios();
  // autenticarUsuario();

  return;
}