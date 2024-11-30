#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

char* intToCharVetor(int numero) {
  // Determina o tamanho necessário para armazenar o número como string, incluindo espaço para o sinal e o caractere nulo ('\0')
  int size = snprintf(NULL, 0, "%d", numero) + 1;

  // Aloca memória para o vetor de char
  char *str = (char*)malloc(size * sizeof(char));
  if (str == NULL) {
    printf("Erro ao alocar memória");
    return NULL;
  }

  // Converte o número para string e armazena no vetor
  sprintf(str, "%d", numero);

  return str;
}

char* floatToCharVetor(double numero) {
  // Determina o tamanho necessário para armazenar o número como string, incluindo espaço para o sinal e o caractere nulo ('\0')
  int size = snprintf(NULL, 0, "%.6f", numero) + 1; // "%.6f" é usado para 6 casas decimais por padrão

  // Aloca memória para o vetor de char
  char *str = (char*)malloc(size * sizeof(char));
  if (str == NULL) {
    printf("Erro ao alocar memória");
    return NULL;
  }

  // Converte o número para string e armazena no vetor
  sprintf(str, "%.6f", numero);

  return str;
}

bool validarEmail(char *str) {
  // loop que percorre o str inteiro parando quando encontrar o terminador como i ja é zero nao deixamos o inicio vazio
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '@') return true;
  }

  return false;
}

bool validarSenha(char *str) {
  bool temNumero = false;
  bool temLetra = false;

  // Itera pela string até o final
  for (int i = 0; str[i] != '\0'; i++) {
    // Verifica se é um número
    if (isdigit(str[i])) {
      temNumero = true;
    }

    // Verifica se é uma letra
    if (isalpha(str[i])) {
      temLetra = true;
    }

    // Se já tiver ambos, pode encerrar o loop
    if (temNumero && temLetra) {
      return true;
    }
  }

  // Retorna true apenas se tiver pelo menos um número e uma letra
  return false;
}

void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  return;
}
