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
int registrarUsuario();

/*
  Autenticar usuário
 */
int autenticarUsuario();

/*
  Deslogar usuário
 */
int deslogarUsuario();

/*
  Deletar usuário
 */
int deletarUsuario();

/*
  Buscar um único usuário
 */
int buscarUnicoUsuario();

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