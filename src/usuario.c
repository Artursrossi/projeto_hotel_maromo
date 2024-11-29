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
  char compararSenha[17];
  int idade = 0;
  t_usuario temp_usuario;

  limparBufferEntrada();

  // Validar entrada de nome
  printf("Digite seu nome:");
  fgets(nome, sizeof(nome), stdin);

  // Validar entrada de email
  printf("Digite seu email:");
  fgets(email, sizeof(email), stdin);

  // Validar entrada de idade
  do {
    printf("Digite sua idade: ");
    if (scanf("%d", &idade) != 1) {
      // Entrada inválida, limpa o buffer
      printf("Entrada invalida. Digite um numero inteiro.\n");
      while (getchar() != '\n'); // Limpa o buffer de entrada
    } else if (idade < 0) {
      // Idade negativa é inválida
      printf("Idade nao pode ser negativa. Tente novamente.\n");
    } else {
      break; // Entrada válida, sai do loop
    }
  } while (1);

  limparBufferEntrada();

  // Validar entrada de senha
  do {
    printf("Digite sua senha: ");
    fgets(compararSenha, sizeof(compararSenha), stdin);
    compararSenha[strcspn(compararSenha, "\n")] = '\0'; // Remove o '\n'

    printf("Confirme sua senha novamente: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove o '\n'

    if (strcmp(compararSenha, senha) != 0) {
      printf("As senhas nao estao combinando. Tente novamente.\n");
    }
  } while (strcmp(compararSenha, senha) != 0);

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

  // Validar entrada de email
  printf("Digite seu email:");
  limparBufferEntrada();
  fgets(email, sizeof(email), stdin);
  strtok(senha, "\n");

  // Validar entrada de senha
  printf("Digite sua senha:");
  fgets(senha, sizeof(senha), stdin);
  strtok(senha, "\n");

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
  t_usuario * usuarios = malloc(sizeof(t_usuario));
  int numero_usuarios;

  int statusObterMuitosUsuarios = obterMuitosUsuarios( &usuarios, &numero_usuarios);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosUsuarios != 200) {
    printf("Ocorreu um erro ao listar usuários. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_usuarios; i++) {
    printf("Código: %d, Nome: %s, Email: %s, Idade: %d, Cargo: %s, Cadastrado em: %s \n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].cargo, usuarios[i].cadastrado_em);
  }

  return 200;
}

int deslogarUsuario(){
  return 200;
}
