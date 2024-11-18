#ifndef HOTEL_H
#define HOTEL_H

#include <stdbool.h>

#include <stdbool.h>

// extern struct QuartoHotel{
//     bool quarto_preparado;
//     int quarto_numero;
//     char numero_ocupantes;
//     bool quarto_ocupado; //flag para checar se o quarto está ocupado ou não 0 para falso e 1 para verdadeiro

//     float quarto_valor_aluguel;

//     char quarto_classe;
// } t_quarto_hotel;

//simula um quarto e suas caracteristicas de interesse gerencial
typedef struct QuartoHotel{
    bool quarto_preparado;
    int quarto_numero;
    char numero_ocupantes;
    bool quarto_ocupado; //flag para checar se o quarto está ocupado ou não 0 para falso e 1 para verdadeiro

    float quarto_valor_aluguel;

    char quarto_classe;
} t_quarto_hotel;

void inicializa_hotel();

void cliente_janela();

void alugar_quarto();

void alterar_aluguel(); // atualiza informações do quarto

void desalugar_quarto();

#endif
