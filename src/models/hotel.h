#ifndef MODELS_HOTEL_H
#define MODELS_HOTEL_H

/*
  Cadastrar Quarto no banco de dados
 */
int cadastrarQuarto(int numero, char tipo, float valor_diaria);

/*
  Cadastrar Quarto no banco de dados
 */
int cadastrarRegistroAluguel(int codigo_quarto_escolhido, int codigo_usuario, int periodo_dias, float valor_total, int numero_ocupantes);

/*
  Obter todos os quartos do banco de dados
 */
int obterMuitosQuartos(t_quarto **p_quartos, int *numero_quartos);

/*
  Obter único quartos por id
 */
int obterUnicoQuartoPorCodigo(t_quarto *p_quarto, int codigo_quarto);

#endif