#ifndef HOTEL_H
#define HOTEL_H

#include <stdbool.h>

//simula um quarto e suas caracteristicas de interesse gerencial
typedef struct Quarto{
    int codigo;
    int numero;
    char tipo;
    float valor_diaria;
    bool preparado;
    bool ocupado;
    char modificado_em[11];
    char cadastrado_em[11];
} t_quarto;

typedef struct RegistroAluguel{
    int codigo;
    int quarto_escolhido;
    int usuario_relacionado;
    int periodo_dias;
    float valor_total;
    int numero_ocupantes;
    char alugado_em[11];
} t_registro_aluguel;

/*
 esta funcao inicializa a estrutura hotel atribuindo as classes de quarto para cada um dos itens do Hotel[32]
*/
void inicializa_hotel();

/*
  Esta funcao permite que o usuario alugue um quarto
*/ 
void alugar_quarto();

/*
  Essa função reseta o quarto que o usuario informa, liberando-o para aluguel novamente
*/
void desalugar_quarto();

/*
  Atualiza informações do quarto
*/
void alterar_aluguel(); 

/*
  Esta funcao simula um menu para o usuario
*/
void cliente_janela();

/**
  Lidar com Registro de Quartos
 */
void controlarRegistroQuarto();

#endif
