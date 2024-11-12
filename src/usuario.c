#include <stdio.h>
#include <string.h>
#include "usuario.h"

int registrarUsuario(Usuario *usuario){
  printf("Usuario \n");
  printf("%d \n", usuario -> idade);

  return 1;
}

int autenticarUsuario(char email[64], char senha[64]){
  return 1;
}

int deslogarUsuario(Usuario *usuario){
  return 1;
}

int deletarUsuario(char id_usuario[64]){
  return 1;
}

int buscarUnicoUsuario(char id_usuario[64]){
  return 1;
}

int listarUsuarios(){
  return 1;
}

int controlarRegistroUsuario(){
  printf("Cadastrar nova conta \n");

  return 1;
}

int controlarLoginUsuario(){
  printf("Entrar com uma conta existente \n");

  return 1;
}