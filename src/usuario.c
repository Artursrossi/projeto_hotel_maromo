#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuario.h"
#include "models/usuarios.h"
#include "utils/conversoes.h"

t_usuario usuario;

int registrarUsuario() {
  // Declaração das variáveis
  char nome[65];
  char email[33];
  char senha[17];
  char repetirSenha[17];
  int idade = 0;
  t_usuario temp_usuario;

  limparBufferEntrada();

  // Validar entrada de nome
  do {
    printf("Digite seu nome:");
    fgets(nome, sizeof(nome), stdin);

    // Mínimo de 4 caracteres
    if (strlen(nome) <= 4) {
      printf("O nome deve conter pelo menos 4 caracteres. \n");
      continue;
    }

    // Máximo de 64 caracteres
    if (strlen(nome) >= 64) {
      printf("O nome deve no máximo 64 caracteres. \n");
      continue;
    }

    break;
  } while (1);
  strtok(nome, "\n"); // Remover \n da string

  // Validar entrada de email
  do {
    printf("Digite seu email:");
    fgets(email, sizeof(email), stdin);

    // Mínimo de 4 caracteres
    if (strlen(email) <= 4) {
      printf("O email deve conter pelo menos 4 caracteres. \n");
      continue;
    }

    // Máximo de 64 caracteres
    if (strlen(email) >= 32) {
      printf("O email deve no máximo 32 caracteres. \n");
      continue;
    }

    // Formato de email
    if (!validarEmail(email)) {
      printf("Email inválido. \n");
      continue;
    }

    break;
  } while (1);
  strtok(email, "\n"); // Remover \n da string

  // Validar entrada de idade
  do {
    printf("Digite sua idade: ");
    int isNumber = scanf("%d", &idade);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Idade menor ou igual a zero, ou maior ou igual á que 120
    if (idade <= 0 || idade >= 120) {
      printf("Idade inválida. \n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  limparBufferEntrada();

  // Validar entrada de senha
  do {
    printf("Digite sua senha: ");
    fgets(senha, sizeof(senha), stdin);

    // Mínimo de 4 caracteres
    if (strlen(senha) <= 6) {
      printf("A senha deve conter pelo menos 6 caracteres. \n");
      continue;
    }

    // Máximo de 64 caracteres
    if (strlen(senha) >= 16) {
      printf("A senha deve no máximo 16 caracteres. \n");
      continue;
    }

    // Formato de email
    if (!validarSenha(senha)) {
      printf("Senha inválida. \n");
      continue;
    }

    printf("Repetir senha: ");
    fgets(repetirSenha, sizeof(repetirSenha), stdin);

    // Comparar senhas
    if (strcmp(repetirSenha, senha) != 0) {
      printf("As senhas não coincidem. Tente novamente. \n");
      continue;
    }

    break;
  } while (1);
  strtok(senha, "\n"); // Remover \n da string

  // Verificar se o email já foi utilizado
  int statusObterUnicoUsuario = obterUnicoUsuario(&temp_usuario, email);
  if(statusObterUnicoUsuario != 404){
    printf("Este email já está sendo utilizado\n");
    return 200;
  }

  // Cadastrar usuário no banco de dados
  int statusCadastrarUsuario = cadastrarUsuario(nome, email, senha, idade);

  // Checar possibilidades de retorno da função
  if (statusCadastrarUsuario != 201) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...\n");
    return 200;
  }

  printf("Conta cadastrada com sucesso!\n");

  return 200;
}

int autenticarUsuario() {
  // Declaração das variáveis
  char email[33];
  char senha[17];
  t_usuario temp_usuario;

  limparBufferEntrada();

  // Validar entrada de email
  do {
    printf("Digite seu email:");
    fgets(email, sizeof(email), stdin);

    // Mínimo de 4 caracteres
    if (strlen(email) <= 4) {
      printf("O email deve conter pelo menos 4 caracteres. \n");
      continue;
    }

    // Máximo de 64 caracteres
    if (strlen(email) >= 32) {
      printf("O email deve no máximo 32 caracteres. \n");
      continue;
    }

    // Formato de email
    if (!validarEmail(email)) {
      printf("Email inválido. \n");
      continue;
    }

    break;
  } while (1);
  strtok(email, "\n"); // Remover \n da string

  // Validar entrada de senha
  do {
    printf("Digite sua senha: ");
    fgets(senha, sizeof(senha), stdin);

    // Mínimo de 4 caracteres
    if (strlen(senha) <= 6) {
      printf("A senha deve conter pelo menos 6 caracteres. \n");
      continue;
    }

    // Máximo de 64 caracteres
    if (strlen(senha) >= 16) {
      printf("A senha deve no máximo 16 caracteres. \n");
      continue;
    }

    // Formato de email
    if (!validarSenha(senha)) {
      printf("Senha inválida. \n");
      continue;
    }

    break;
  } while (1);
  strtok(senha, "\n"); // Remover \n da string

  // Obter usuário
  int statusObterUnicoUsuario = obterUnicoUsuario(&temp_usuario, email);

  // Checar possibilidades de retorno da função
  if (statusObterUnicoUsuario == 404) {
    printf("Credenciais inválidas\n");
    return 400;
  }
  if (statusObterUnicoUsuario != 200) {
    printf("Ocorreu um erro ao buscar usuário. Tente novamente mais tarde...\n");
    return 200;
  }

  // Verificar se as senhas coincidem
  if(strcmp(temp_usuario.senha, senha) != 0){
    printf("Credenciais inválidas\n");
    return 400;
  }

  // Atribuir retorno ao usuário global
  usuario = temp_usuario;
  printf("Autenticado com sucesso!\n");

  return 200;
}

int listarUsuarios() {
  t_usuario *usuarios = malloc(sizeof(t_usuario));
  int numero_usuarios;

  int statusObterMuitosUsuarios = obterMuitosUsuarios(&usuarios, &numero_usuarios);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosUsuarios != 200) {
    printf("Ocorreu um erro ao listar usuários. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_usuarios; i++) {
    printf("Código: %d, Nome: %s, Email: %s, Idade: %d, Cargo: %s, Cadastrado em: %s \n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].cargo, usuarios[i].cadastrado_em);
  }

  // Libera a memória alocada
  free(usuarios);

  return 200;
}

int deslogarUsuario(){
  memset(&usuario, 0, sizeof(t_usuario)); // Resetar variável global do usuário

  return 200;
}
