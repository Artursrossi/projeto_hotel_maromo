#include <stdio.h>
#include <string.h>

typedef enum  {
  USER, ADMIN
} Cargo;

typedef struct {
  char id[64];
  char nome[64];
  char email[64];
  char senha[64];
  int idade;
  Cargo cargo;
  char data_cadastro[64];
} Usuario;

int registrar(Usuario *usuario){
  printf("Usuario \n");
  printf("%d \n", usuario -> idade);

  return 1;
}

int entrar(char email[64], char senha[64]){
  return 1;
}

int sair(Usuario *usuario){
  return 1;
}

int deletar(char id_usuario[64]){
  return 1;
}

int buscarUnico(char id_usuario[64]){
  return 1;
}

int listar(){
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