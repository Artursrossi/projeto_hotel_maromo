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
  Obter todos os registros de alugueis do banco de dados
 */
int obterMuitosRegistroAluguel(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel);

/*
  Obter os registros de alugueis do banco de dados, filtrando pelo usuário enviado
 */
int obterMuitosRegistroAluguelPorCodigoUsuario(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel, int codigo_usuario);

/*
  Obter todos os quartos do banco de dados
 */
int obterMuitosQuartos(t_quarto **p_quartos, int *numero_quartos);

/*
  Obter todos os quartos do banco de dados que estejam com a coluna "ocupado" como false e "preparado" como true
 */
int obterMuitosQuartosDesocupados(t_quarto **p_quartos, int *numero_quartos);

/*
  Obter único quartos por id
 */
int obterUnicoQuartoPorCodigo(t_quarto *p_quarto, int codigo_quarto);

/*
  Modificar, na tabela de quartos, a coluna "ocupado" para true
 */
int ocuparQuarto(int codigo_quarto);

/*
  Modificar, na tabela de quartos, a coluna "ocupado" para true
 */
int desocuparQuarto(int codigo_quarto);

#endif
