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

extern t_usuario usuario;

/*
  Lidar com Registro de Usuários
 */
int registrarUsuario();

/*
  Lidar com Login do Usuários
 */
int autenticarUsuario();

/*
  Listar usuários
 */
int listarUsuarios();

/*
  Deslogar usuário
 */
int deslogarUsuario();

// funcao que valida o cadastro do email é valido! assumindo que tudo que possa estar de erado com um email é a falta de um "@"
int validacao_email(char* array);

// funcao que verifica se a senha cadastrada é valida! uma senha valida deve conter letras e numeros

int validacao_senha(char* senha);

#endif