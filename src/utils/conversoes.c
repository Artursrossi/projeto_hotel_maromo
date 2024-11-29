#include <stdio.h>

#include <stdlib.h>

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

int validacaoEmail(char *array) {
  // loop que percorre o array inteiro parando quando encontrar o terminador como i ja é zero nao deixamos o inicio vazio
  for (int i = 0; array[i] != '\0'; i++) {
    if (array[i] == '@') return 1;
  }

  return 0;
}

int validacaoSenha(char *senha) {
  int chars[127] = {
    0
  }; // array contendo uma posição que corresponde pra o valor de cada um dos characteres ASCII até 127!
  int loop_counter = 0;
  int integer_counter = 0;
  int char_counter = 0;
  int check_char = 0;

  for (; senha[loop_counter] != '\0'; loop_counter++) {
    chars[senha[loop_counter]]++;
  }

  for (check_char = 0; check_char < 127; check_char++) {
    if (check_char >= 47 && check_char <= 56) {
      chars[check_char] != 0 && integer_counter++;
    }

    if (check_char < 47 || check_char > 56) {
      chars[check_char] != 0 && char_counter++;
    }

  }

  if (integer_counter && char_counter != 0) {
    return 1;
  }

  return 0;
}

void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  return;
}
