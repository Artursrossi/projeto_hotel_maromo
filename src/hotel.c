#include <stdio.h>
#include <malloc.h>

#include "hotel.h"
#include "usuario.h"
#include "models/hotel.h"
#include "models/usuarios.h"

int alugarQuarto() {
  // Declarar variáveis necessárias
  int codigo_usuario = usuario.codigo;
  int numero_quarto_escolhido;
  int periodo_dias;
  int numero_ocupantes;

  /** Obtendo o numero do quarto **/
  do {
    printf("-- Qual quarto voce gostaria de alugar? --\n");
    int isNumber = scanf("%d", &numero_quarto_escolhido);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Número inválido
    if (numero_quarto_escolhido <= 0) {
      printf("Número inválida. \n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  /** Obtendo o numero de ocupantes **/
  do {
    printf("-- Quantos ocupantes? (max 5 pessoas) --\n");
    int isNumber = scanf("%d", &numero_ocupantes);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Número de hospedes inválidos
    if (numero_ocupantes < 1 || numero_ocupantes > 5) {
      printf("Número de hospedes inválido (1 min - 5 max). \n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  /** Obtendo o período de dias **/
  do {
    printf("-- Deseja reservar o quarto por quantos dias? --\n");
    int isNumber = scanf("%d", &periodo_dias);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Número de hospedes inválidos
    if (periodo_dias < 0 || periodo_dias > 20) {
      printf("-- Por favor informe um intervalo de dias válido (1 min - 20 max) --\n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  // Obter informações relacionadas ao quarto escolhido
  t_quarto quarto;
  int statusObterUnicoQuartoPorNumero = obterUnicoQuartoPorNumero(&quarto, numero_quarto_escolhido);

  // Checar possibilidades de retorno da função
  if (statusObterUnicoQuartoPorNumero == 404) {
    printf("Quarto não encontrado \n");
    return 200;
  }
  if (statusObterUnicoQuartoPorNumero != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Verificar se o quarto já está preparado para ser alugado
  if(!quarto.preparado){
    printf("O quarto escolhido não está preparado para ser alugado. \n");
    return 200;
  }

  // Verificar se o quarto já está ocupado
  if(quarto.ocupado){
    printf("O quarto escolhido já está ocupado. \n");
    return 200;
  }

  // Definir valor total do aluguel
  float valor_total = quarto.valor_diaria * periodo_dias;

  printf("-- o valor total do aluguel sera de %.2f --\n", valor_total);

  // Perguntar se o usuário realmente quer confirmar
  char confirmacao;
  printf("-- confirme o agendamento -- (Digite S para continuar, N para sair)\n");
  scanf(" %c", &confirmacao);
  if (!(confirmacao == 'S' || confirmacao == 's')) {
    printf("Agendamento cancelado. \n");
    return 200;
  }

  // Definir quarto como ocupado no banco de dados
  int statusOcuparQuarto = ocuparQuarto(quarto.codigo);

  // Checar possibilidades de retorno da função
  if (statusOcuparQuarto != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Cadastrar registro aluguel e obter status do retorno
  int statusCadastrarRegistroAluguel = cadastrarRegistroAluguel(quarto.codigo, codigo_usuario, periodo_dias, valor_total, numero_ocupantes);

  // Checar possibilidades de retorno da função
  if (statusCadastrarRegistroAluguel != 201) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  printf("O quarto de número %d foi alugado com sucesso!\n", quarto.numero);

  return 200;
}

int desalugarQuarto() {
  // Declarar variáveis necessárias
  int codigo_usuario = usuario.codigo;
  int numero_quarto_escolhido;
  t_registro_aluguel *registro_aluguel = malloc(sizeof(t_registro_aluguel));
  int numero_registro_aluguel;

  // Capturar número do quarto
  printf("Informe o do quarto que deseja desalugar \n");
  scanf("%d", &numero_quarto_escolhido);

  // Obter informações relacionadas ao quarto escolhido
  t_quarto quarto;
  int statusObterUnicoQuartoPorNumero = obterUnicoQuartoPorNumero(&quarto, numero_quarto_escolhido);

  // Checar possibilidades de retorno da função
  if (statusObterUnicoQuartoPorNumero == 404) {
    printf("Quarto não encontrado \n");
    return 200;
  }
  if (statusObterUnicoQuartoPorNumero != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  int statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento = obterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento(&registro_aluguel, &numero_registro_aluguel, codigo_usuario);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Mensagem caso não tenha aluguéis
  if(numero_registro_aluguel == 0){
    printf("Você não tem nenhuma reserva em aberto. \n");
    return 200;
  }

  int codigo_reserva_escolhida = 0;
  for (int i = 0; i < numero_registro_aluguel; i++) {
    if(registro_aluguel[i].quarto_escolhido == quarto.codigo && registro_aluguel[i].usuario_relacionado == usuario.codigo && registro_aluguel[i].aluguel_em_andamento == true) codigo_reserva_escolhida = registro_aluguel[i].codigo;
  }

  // Verificar se a reserva desse quarto está no nome do usuário que está desalugando o quarto
  if(codigo_reserva_escolhida == 0){
    printf("Você não está alugando o quarto de número %d no momento. \n", numero_quarto_escolhido);
    return 200;
  }

  // Verificar se o quarto está ocupado
  if(!quarto.ocupado){
    printf("O quarto escolhido não está ocupado. \n");
    return 200;
  }

  // Definir quarto como ocupado no banco de dados
  int statusDesocuparQuarto = desocuparQuarto(quarto.codigo);

  // Checar possibilidades de retorno da função
  if (statusDesocuparQuarto != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Definir quarto como ocupado no banco de dados
  int statusFinalizarReserva = finalizarReserva(codigo_reserva_escolhida);

  // Checar possibilidades de retorno da função
  if (statusFinalizarReserva != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  printf("O quarto de número %d foi desocupado! \n", quarto.numero);

  // Libera a memória alocada
  free(registro_aluguel);

  return 200;
}

int alterarReservaAtual() {
  // Declarar variáveis necessárias
  int codigo_usuario = usuario.codigo;
  int numero_quarto_escolhido;
  int novo_numero_ocupantes;
  t_registro_aluguel *registro_aluguel = malloc(sizeof(t_registro_aluguel));
  int numero_registro_aluguel;

  printf("Informe o numero do quarto alugado\n");
  scanf("%d", &numero_quarto_escolhido);

  printf("Informe o novo número de hospedes\n");
  scanf("%d", &novo_numero_ocupantes);

  // Obter informações relacionadas ao quarto escolhido
  t_quarto quarto;
  int statusObterUnicoQuartoPorNumero = obterUnicoQuartoPorNumero(&quarto, numero_quarto_escolhido);

  // Checar possibilidades de retorno da função
  if (statusObterUnicoQuartoPorNumero == 404) {
    printf("Quarto não encontrado \n");
    return 200;
  }
  if (statusObterUnicoQuartoPorNumero != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  int statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento = obterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento(&registro_aluguel, &numero_registro_aluguel, codigo_usuario);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Mensagem caso não tenha aluguéis
  if(numero_registro_aluguel == 0){
    printf("Você não tem nenhuma reserva em aberto. \n");
    return 200;
  }

  int codigo_reserva_escolhida = 0;
  for (int i = 0; i < numero_registro_aluguel; i++) {
    if(registro_aluguel[i].quarto_escolhido == numero_quarto_escolhido && registro_aluguel[i].usuario_relacionado == usuario.codigo && registro_aluguel[i].aluguel_em_andamento == true) codigo_reserva_escolhida = registro_aluguel[i].codigo;
  }

  // Verificar se a reserva desse quarto está no nome do usuário que está desalugando o quarto
  if(codigo_reserva_escolhida == 0){
    printf("Você não está alugando o quarto de número %d no momento. \n", numero_quarto_escolhido);
    return 200;
  }

  // Alterar novo número de hospedes
  int statusFinalizarReserva = atualizarReservaNumeroOcupantes(codigo_reserva_escolhida, novo_numero_ocupantes);

  // Checar possibilidades de retorno da função
  if (statusFinalizarReserva != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  printf("o numero de hospedes foi alterado com sucesso para %d!\n", novo_numero_ocupantes);

  return 200;
}

int listarRegistrosAlugueis() {
  t_registro_aluguel *registro_aluguel = malloc(sizeof(t_registro_aluguel));
  int numero_registro_aluguel;

  int statusObterMuitosRegistroAluguel = obterMuitosRegistroAluguel(&registro_aluguel, &numero_registro_aluguel);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosRegistroAluguel != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Mensagem caso não tenha aluguéis
  if(numero_registro_aluguel == 0){
    printf("Não há reservas no sistema. \n");
    return 200;
  }

  for (int i = 0; i < numero_registro_aluguel; i++) {
    printf("Codigo: %d, Quarto escolhido: %d, Usuário relacionado: %d, Período dias: %d, Valor total: %.2f, Número ocupantes: %d, Aluguel em andamento: %s, Alugado em: %s \n", registro_aluguel[i].codigo, registro_aluguel[i].quarto_escolhido, registro_aluguel[i].usuario_relacionado, registro_aluguel[i].periodo_dias, registro_aluguel[i].valor_total, registro_aluguel[i].numero_ocupantes, registro_aluguel[i].aluguel_em_andamento ? "sim" : "não", registro_aluguel[i].alugado_em);
  }

  // Libera a memória alocada
  free(registro_aluguel);

  return 200;
}

int listarReservaAtual() {
  int codigo_usuario = usuario.codigo;
  t_registro_aluguel *registro_aluguel = malloc(sizeof(t_registro_aluguel));
  int numero_registro_aluguel;

  int statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento = obterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento(&registro_aluguel, &numero_registro_aluguel, codigo_usuario);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosRegistroAluguelPorCodigoUsuarioEmAndamento != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Mensagem caso não tenha aluguéis
  if(numero_registro_aluguel == 0){
    printf("Você não tem nenhuma reserva em aberto. \n");
    return 200;
  }

  // Obter informações relacionadas ao quarto escolhido
  t_quarto quarto;

  for (int i = 0; i < numero_registro_aluguel; i++) {
    int statusObterUnicoQuartoPorNumero = obterUnicoQuartoPorCodigo(&quarto, registro_aluguel[i].quarto_escolhido);

    printf("Número do quarto: %d, Período dias: %d, Valor total: %.2f, Número ocupantes: %d, Aluguel em andamento: %s, Alugado em: %s \n", quarto.numero, registro_aluguel[i].periodo_dias, registro_aluguel[i].valor_total, registro_aluguel[i].numero_ocupantes, registro_aluguel[i].aluguel_em_andamento ? "sim" : "não", registro_aluguel[i].alugado_em);
  }

  // Libera a memória alocada
  free(registro_aluguel);

  return 200;
}

int listarHistoricoReservas() {
  int codigo_usuario = usuario.codigo;
  t_registro_aluguel *registro_aluguel = malloc(sizeof(t_registro_aluguel));
  int numero_registro_aluguel;

  int statusObterMuitosRegistroAluguelPorCodigoUsuario = obterMuitosRegistroAluguelPorCodigoUsuario(&registro_aluguel, &numero_registro_aluguel, codigo_usuario);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosRegistroAluguelPorCodigoUsuario != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  // Mensagem caso não tenha aluguéis
  if(numero_registro_aluguel == 0){
    printf("Você ainda não efetuou nenhum aluguel. \n");
    return 200;
  }

  for (int i = 0; i < numero_registro_aluguel; i++) {
    printf("Quarto escolhido: %d, Usuário relacionado: %d, Período dias: %d, Valor total: %.2f, Número ocupantes: %d, Aluguel em andamento: %s, Alugado em: %s \n", registro_aluguel[i].quarto_escolhido, registro_aluguel[i].usuario_relacionado, registro_aluguel[i].periodo_dias, registro_aluguel[i].valor_total, registro_aluguel[i].numero_ocupantes, registro_aluguel[i].aluguel_em_andamento ? "sim" : "não", registro_aluguel[i].alugado_em);
  }

  // Libera a memória alocada
  free(registro_aluguel);

  return 200;
}

int listarQuartos() {
  t_quarto *quartos = malloc(sizeof(t_quarto));
  int numero_quartos;

  int statusObterMuitosQuartos = obterMuitosQuartos(&quartos, &numero_quartos);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosQuartos != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_quartos; i++) {
    printf("Numero: %d, Tipo: %c, Valor diaria: %.2f, Preparado: %s, Ocupado: %s, Modificado em: %s, Cadastrado em: %s \n", quartos[i].numero, quartos[i].tipo, quartos[i].valor_diaria, quartos[i].preparado ? "sim" : "não", quartos[i].ocupado ? "sim" : "não", quartos[i].modificado_em, quartos[i].cadastrado_em);
  }

  // Libera a memória alocada
  free(quartos);

  return 200;
}

int listarQuartosDesocupados() {
  t_quarto *quartos = malloc(sizeof(t_quarto));
  int numero_quartos;

  int statusObterMuitosQuartos = obterMuitosQuartosDesocupados(&quartos, &numero_quartos);

  // Checar possibilidades de retorno da função
  if (statusObterMuitosQuartos != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  for (int i = 0; i < numero_quartos; i++) {
    printf("Numero: %d, Tipo: %c, Valor diaria: %.2f, Preparado: %s, Ocupado: %s, Modificado em: %s, Cadastrado em: %s \n", quartos[i].numero, quartos[i].tipo, quartos[i].valor_diaria, quartos[i].preparado ? "sim" : "não", quartos[i].ocupado ? "sim" : "não", quartos[i].modificado_em, quartos[i].cadastrado_em);
  }

  // Libera a memória alocada
  free(quartos);

  return 200;
}

int registrarQuarto() {
  // Declaração das variáveis
  int numero_quarto;
  char tipo;
  float valor_diaria;

  // Validar entrada de número
  do {
    printf("Digite o número do quarto: ");
    int isNumber = scanf("%d", &numero_quarto);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Número do quarto menor ou igual a zero
    if (numero_quarto <= 0) {
      printf("Número inválido. \n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  // Validar entrada de tipo
  do {
    printf("Digite o tipo do quarto (A, B, C, D, E): ");
    scanf(" %c", &tipo);

    // Tipo válido
    if (tipo == 'A' || tipo == 'B' || tipo == 'C' || tipo == 'D' || tipo == 'E') {
      break; // Entrada válida, sai do loop
    }
  } while (1);

  // Validar entrada de valor_diaria
  do {
    printf("Digite o valor da diária do quarto: ");
    scanf("%f", &valor_diaria);

    // Número do quarto menor ou igual a zero
    if (valor_diaria <= 0) {
      printf("Valor inválido. \n");
      continue;
    }

    break; // Entrada válida, sai do loop
  } while (1);

  // Obter informações relacionadas ao quarto escolhido
  t_quarto quarto;
  int statusObterUnicoQuartoPorNumero = obterUnicoQuartoPorNumero(&quarto, numero_quarto);

  // Checar possibilidades de retorno da função
  if (statusObterUnicoQuartoPorNumero != 404) {
    printf("Já existe um quarto registrado com o número %d \n", numero_quarto);
    return 200;
  }

  int statusCadastrarQuarto = cadastrarQuarto(numero_quarto, tipo, valor_diaria);

  // Checar possibilidades de retorno da função
  if (statusCadastrarQuarto != 201) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  printf("Quarto cadastrado com sucesso! \n");

  return 200;
}
