#include "hotel.c"
#include <stdbool.h>

typedef struct //simula um quarto e suas caracteristicas de interesse gerencial
{
    bool quarto_preparado;

    int quarto_numero;

    char numero_ocupantes;

    bool quarto_ocupado; //flag para checar se o quarto está ocupado ou não 0 para falso e 1 para verdadeiro

    float quarto_preco;

    char quarto_classe;

} quarto_hotel;
typedef quarto_hotel *p_hotel; // variavel que cria um ponteiro apontando para a estrutura quarto_hotel


extern p_hotel Hotel[32]; //variavel que simula o hotel sendo este tratado como um array contendo 100 quartos

void inicializa_hotel();

void alugar_quarto();

void gerenciar_quarto(); // atualiza informações do quarto

void desalugar_quarto();


