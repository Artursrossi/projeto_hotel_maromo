#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "models/usuarios.h"

t_usuario usuario;

int registrarUsuario(){
  char nome[65] = "Maromo Roberto Moraes";
  char email[33] = "maromo@email.com";
  char senha[17] = "123";
  int idade = 45;

  int res = 0; // flag para salvar código de retorno da função
  res = cadastrarUsuario(nome, email, senha, idade);

  // Checar possibilidades de retorno da função
  if(res != 201){
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

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

int validacao_email(char* array)
{
    int check, i = 0;

    for (; array[i] != '\0'; i++) // loop que percorre o array inteiro parando quando encontrar o terminador como i ja é zero nao deixamos o inicio vazio
    {
        if (array[i] == '@')
        {
            check++; //acrescenta para a flag
        }
    }
    // simples verificao retorna 1 caso pelo menos um @ seje encontrado!
    if (check > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validacao_senha(char* senha)
{
    int chars[127] = { 0 }; // array contendo uma posição que corresponde pra o valor de cada um dos characteres ASCII até 127!
    int loop_counter = 0;
    int integer_counter = 0;
    int char_counter = 0;
    int check_char = 0;


    for (; senha[loop_counter] != '\0'; loop_counter++)
    {
        chars[senha[loop_counter]]++;
    }


    for (check_char = 0; check_char < 127; check_char++)
    {
        if (check_char >= 47 && check_char <= 56)
        {
            chars[check_char] != 0 && integer_counter++;
        }

        if (check_char < 47 || check_char > 56)
        {
            chars[check_char] != 0 && char_counter++;
        }

    }

    if (integer_counter && char_counter != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}