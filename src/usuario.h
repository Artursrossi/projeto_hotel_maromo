#ifndef USUARIO_H
#define USUARIO_H

#include "usuario.c"

typedef enum  {
  USER, ADMIN
} Cargo;

typedef struct {
  int codigo;
  char nome[64];
  char email[64];
  char senha[64];
  int idade;
  char cargo[32];
  char cadastrado_em[64];
} Usuario;

typedef struct {
  char nome[64];
  char email[64];
  char senha[64];
  int idade;
} CadastrarUsuario;

/*
  Registrar usuário
 */
int registrarUsuario(Usuario *usuario);

/*
  Autenticar usuário
 */
int autenticarUsuario(char email[64], char senha[64]);

/*
  Deslogar usuário
 */
int deslogarUsuario(Usuario *usuario);

/*
  Deletar usuário
 */
int deletarUsuario(char id_usuario[64]);

/*
  Buscar um único usuário
 */
int buscarUnicoUsuario(char id_usuario[64]){
  return 1;
}

/*
  Listar usuários
 */
int listarUsuarios();

/*
  Lidar com Registro de Usuários
 */
int controlarRegistroUsuario();

/*
  Lidar com Login do Usuários
 */
int controlarLoginUsuario();

#endif