#include "usuario.c"

/*
  Registrar usuário
 */
int registrar(Usuario *usuario);

/*
  Autenticar usuário
 */
int entrar(char email[64], char senha[64]);

/*
  Deslogar usuário
 */
int sair(Usuario *usuario);

/*
  Deletar usuário
 */
int deletar(char id_usuario[64]);

/*
  Buscar um único usuário
 */
int buscarUnico(char id_usuario[64]){
  return 1;
}

/*
  Listar usuário
 */
int listar();