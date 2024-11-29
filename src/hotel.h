#ifndef HOTEL_H
#define HOTEL_H

#include <stdbool.h>

//simula um quarto e suas caracteristicas de interesse gerencial
typedef struct Quarto {
  int codigo;
  int numero;
  char tipo;
  float valor_diaria;
  bool preparado;
  bool ocupado;
  char modificado_em[11];
  char cadastrado_em[11];
}
t_quarto;

typedef struct RegistroAluguel {
  int codigo;
  int quarto_escolhido;
  int usuario_relacionado;
  int periodo_dias;
  float valor_total;
  int numero_ocupantes;
  char alugado_em[11];
}
t_registro_aluguel;

/*
  Esta funcao permite que o usuario alugue um quarto
*/
int alugarQuarto();

/*
  Essa função reseta o quarto que o usuario informa, liberando-o para aluguel novamente
*/
int desalugarQuarto();

/*
  Atualiza informações do quarto
*/
int alterarReservaAtual();

/**
  Lidar com Registro de Quartos
 */
int gerarHistoricoReservas();

/**
  Listar todos os quartos
 */
int listarQuartos();

/**
  Lidar com Registro de Quartos
 */
int registrarQuarto();

#endif
