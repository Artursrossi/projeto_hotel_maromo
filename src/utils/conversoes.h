#ifndef CONVERSOES_H
#define CONVERSOES_H

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
int validacaoEmail(char* array);

/*
  Função que verifica se a senha cadastrada é valida! uma senha valida deve conter letras e numeros
*/ 
int validacaoSenha(char* senha);

#endif