#ifndef CONVERSOES_H
#define CONVERSOES_H

#include <stdbool.h>

#include "../../external/libpq/libpq-fe.h"

/*
  Função para transformar um inteiro em vetor de char
*/
char* intToCharVetor(int numero);

/*
  Função para transformar um float em vetor de char
*/
char* floatToCharVetor(double numero);

/*
  Função que valida o cadastro do email é valido! assumindo que tudo que possa estar de erado com um email é a falta de um "@"
*/
bool validarEmail(char *str);

/*
  Função que verifica se a senha cadastrada é valida! uma senha valida deve conter letras e numeros
*/
bool validarSenha(char *str);

/*
  Função que limpa o buffer do teclado
*/
void limparBufferEntrada();

#endif
