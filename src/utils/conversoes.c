#include <stdio.h>
#include <stdlib.h>

char* intToCharVetor(int numero) {
    // Determina o tamanho necessário para armazenar o número como string, incluindo espaço para o sinal e o caractere nulo ('\0')
    int size = snprintf(NULL, 0, "%d", numero) + 1;

    // Aloca memória para o vetor de char
    char* str = (char*)malloc(size * sizeof(char));
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
    char* str = (char*)malloc(size * sizeof(char));
    if (str == NULL) {
      printf("Erro ao alocar memória");
      return NULL;
    }

    // Converte o número para string e armazena no vetor
    sprintf(str, "%.6f", numero);

    return str;
}