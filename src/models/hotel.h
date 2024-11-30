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
  Obter os registros de alugueis do banco de dados, filtrando pelo usuário enviado e aluguel em andamento
 */
int obterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento(t_registro_aluguel **p_registro_aluguel, int *numero_registro_aluguel, int codigo_usuario);

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
int obterUnicoQuartoPorNumero(t_quarto *p_quarto, int numero_quarto);

/*
  Modificar, na tabela de quartos, a coluna "ocupado" para true
 */
int ocuparQuarto(int codigo_quarto);

/*
  Modificar, na tabela de quartos, a coluna "ocupado" para true
 */
int desocuparQuarto(int codigo_quarto);

/*
  Modificar, na tabela de registro_alugueis, a coluna "aluguel_em_andamento" para false
 */
int finalizarReserva(int codigo_registro_aluguel);

#endif
