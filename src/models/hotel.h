#ifndef MODELS_HOTEL_H
#define MODELS_HOTEL_H

/*
  Cadastrar Quarto no banco de dados
 */
int cadastrarQuarto(int numero,char tipo,float valor_diaria);

/*
  Obter todos os quartos do banco de dados
 */
int obterMuitosQuartos(t_quarto **p_quartos, int *numero_quartos);

#endif