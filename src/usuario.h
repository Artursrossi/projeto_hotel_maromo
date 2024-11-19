#ifndef USUARIO_H
#define USUARIO_H

typedef struct Usuario {
    int codigo;
    char nome[65];
    char email[33];
    char senha[17];
    int idade;
    char cargo[14];
    char cadastrado_em[11];
} t_usuario;

/*
  Registrar usuário
 */
void registrarUsuario();

/*
  Autenticar usuário
 */
void autenticarUsuario();

/*
  Deslogar usuário
 */
void deslogarUsuario();

/*
  Deletar usuário
 */
void deletarUsuario();

/*
  Buscar um único usuário
 */
void buscarUnicoUsuario();

/*
  Listar usuários
 */
void listarUsuarios();

/*
  Lidar com Registro de Usuários
 */
void controlarRegistroUsuario();

/*
  Lidar com Login do Usuários
 */
void controlarLoginUsuario();

#endif