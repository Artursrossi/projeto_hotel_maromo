#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "models/usuarios.h"
#include "utils/conversoes.h"

t_usuario usuario;

int registrarUsuario(){
    char nome[65];
    char email[33];
    char senha[17];
    char compararSenha[17];
    int idade = 0;

    limparBufferEntrada();

    printf("Qual o seu nome:");
    fgets(nome, sizeof(nome), stdin);

    do {
        printf("Qual a sua idade: ");
        if (scanf("%d", &idade) != 1) {
            // Entrada inválida, limpa o buffer
            printf("Entrada invalida. Digite um numero inteiro.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        } else if (idade < 0) {
            // Idade negativa é inválida
            printf("Idade nao pode ser negativa. Tente novamente.\n");
        } else {
            break;  // Entrada válida, sai do loop
        }
    } while (1);

    limparBufferEntrada();

    printf("Qual o seu email:");
    fgets(email, sizeof(email), stdin);

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

    int statusCadastrarUsuario = cadastrarUsuario(nome, email, senha, idade);

    printf("%d", statusCadastrarUsuario);
    // Checar possibilidades de retorno da função
    if(statusCadastrarUsuario != 201){
      printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
      return 200;
    }

    printf("Conta cadastrada com sucesso!\n");

    return 200;
}

int autenticarUsuario(){
  char email[33] = "maromo@email.com";

  int res = 0; // flag para salvar código de retorno da função
  res = obterUnicoUsuario(&usuario, email);
  
  // Checar possibilidades de retorno da função
  if(res == 404){
    printf("Usuário não encontrado"); 
    return 200;
  }
  if(res != 200){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }


  return 200;
}

int listarUsuarios(){
  t_usuario *usuarios = malloc(sizeof(t_usuario));
  int numero_usuarios;

  int res = 0; // flag para salvar código de retorno da função
  res = obterMuitosUsuarios(&usuarios, &numero_usuarios);

  // Checar possibilidades de retorno da função
  if(res != 200){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_usuarios; i++) {
    printf("Nome: %s, Email: %s, Idade: %d, Cadastrado em: %s \n", usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].cadastrado_em);
  }

  return 200;
}

int deslogarUsuario(){
  return 200;
}