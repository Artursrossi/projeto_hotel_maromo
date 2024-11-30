#include <stdio.h>
#include <malloc.h>

#include "hotel.h"
#include "usuario.h"
#include "models/hotel.h"
#include "models/usuarios.h"

typedef t_quarto *p_quarto; // variavel que cria um ponteiro apontando para a estrutura quarto_hotel
p_quarto Hotel[32]; //variavel que simula o hotel sendo este tratado como um array contendo 100 quartos

typedef t_registro_aluguel *p_registro; // variavel que cria um ponteiro apontando para a estrutura RegistroAluguel
p_registro Registro[32]; // variavel que registra o aluguel de um quarto contendo 32 possiveis alugueis para 32 quartos

int alugarQuarto() {
  // Declarar variáveis necessárias
  int codigo_usuario = usuario.codigo;
  int numero_quarto_escolhido;
  int periodo_dias = 5;
  int numero_ocupantes = 2;

  /** Obtendo o numero do quarto **/
  printf("-- Qual quarto voce gostaria de alugar? --\n");
  while (numero_quarto_escolhido == 0) {
    scanf("%d", &numero_quarto_escolhido);

    if (numero_quarto_escolhido < 1) {
      printf("-- Por favor informe um quarto válido --\n");
      continue;
    }
  }

  /** Obtendo o numero de ocupantes **/
  printf("-- Quantos ocupantes? (max 4 pessoas) --\n");
  while (1) {
    scanf("%d", &numero_ocupantes);

    if (numero_ocupantes < 1 || numero_ocupantes > 4) {
      printf("-- Por favor informe um numero valido de ocupantes (1 min - 5 max) --\n");
      continue;
    }

    break;
  }

  /** Obtendo o período de dias **/
  printf("-- Deseja reservar o quarto por quantos dias? --\n");
  while (1) {
    scanf("%d", &periodo_dias);

    if (periodo_dias < 0 || periodo_dias > 20) {
      printf("-- Por favor informe um intervalo de dias válido (1 min - 20 max) --\n");
      continue;
    }

    break;
  }

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

  // Definir valor total do aluguel
  float valor_total = quarto.valor_diaria * periodo_dias;


  int min_room = 0;
  int max_room = 0;
  int numero = 0; //se refere ao numero do quarto escolhido só agora que eu vi que esse nome é horrivel
  int ocupantes = 0;
  char tipo = '0';
  int aluguel = 0;
  float quarto_preco = 0;
  char resposta;

  printf("-- Menu de aluguel para quartos --\n");

  /**  Obtendo os dados do usuario **/

  /** Obtendo a classe do quarto **/
  printf("-- Qual tipo de quarto voce gostaria de alugar? (M,A,B,C) --\n");
  while (tipo == '0') {
    scanf("%c", &tipo);
    switch (tipo) {
    case 'C': {
      aluguel = 500;
      break;
    }
    case 'B': {
      aluguel = 600;
      break;
    }
    case 'A': {
      aluguel = 700;
      break;
    }
    case 'M': {
      aluguel = 800;
      break;
    }
    default:
      printf("informe um tipo valido\n");
      tipo = '0';
    }

  }
  for (int i = 1; i < 33; i++) {
    if (Hotel[i]->tipo == tipo) {
      /** procura quais são os indices para o tipo de quarto especificado **/
      if (min_room == 0) {
        min_room = i;
        max_room = i;
      } else {
        max_room += 1;
      }

      printf("%d ", Hotel[i]->numero);
    }
  }

  /** Obtendo o numero do quarto **/
  printf("-- Qual quarto (%d-%d) voce gostaria de alugar? --\n", min_room, max_room);
  while (numero == 0) {
    scanf("%d", &numero);
    if (numero < min_room || numero > max_room) {
      numero = 0;
    }
    if (Hotel[numero]->ocupado == true) {
      printf("-- o quarto esta ocupado por favor escolha outro--\n");
      numero = 0;
    }
  }

  /** Obtendo o numero de ocupantes **/
  printf("-- Quantos ocupantes? (max 4 pessoas) --\n");
  while (ocupantes == 0) {
    scanf("%d", &ocupantes);
    if (ocupantes < 0 || ocupantes > 4) {
      printf("-- Por favor informe um numero valido de ocupantes (1 min - 4 max) --\n");
      ocupantes = 0;
    }
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

  /** obtendo o preco final **/
  quarto_preco = aluguel * ocupantes;

  printf("-- o valor total do aluguel sera de %.2f --\n", quarto_preco);

  printf("-- confirme o agendamento -- (S para continuar, N para sair)\n");
  fflush(stdin);
  resposta = getchar();
  if (resposta != 'S') {
    printf("agendamento cancelado. \n");
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

  return 200;
}

int desalugarQuarto() {
  // Declarar variáveis necessárias
  int codigo_usuario = usuario.codigo;
  int numero_quarto_escolhido = 1;

  // Capturar número do quarto
  printf("Informe o numero do quarto que deseja desalugar \n");
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

  // Definir quarto como ocupado no banco de dados
  int statusDesocuparQuarto = desocuparQuarto(quarto.codigo);

  // Checar possibilidades de retorno da função
  if (statusDesocuparQuarto != 200) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
    return 200;
  }

  return 200;
}

int alterarReservaAtual() {
  char tipo = '0';
  int numero = 0;
  int novo_numero_quarto;
  int option = 0;
  int novo_numero_ocupantes = 0;

  printf("por favor informe o numero do quarto alugado\n");
  while (numero == 0) {
    scanf("%d", &numero);

    if (numero < 1 || numero > 32) {
      printf("por favor informe um quarto valido\n");
      numero = 0;
    }
  }
  printf("por favor informe o que deseja alterar\n");
  printf("1 - quarto alugado\n");
  printf("2 - numero de hospedes\n");
  printf("3 - cancelar\n");

  while (numero == 0) {
    switch (numero) { // altera o quarto alugado
    case 1: {
      // verificao para checar se o novo quarto alugado sera do mesmo tipo e esta disponivel
      tipo = Hotel[numero]->tipo;
      while (novo_numero_quarto == 0) {
        printf("por favor informe qual quarto voce gostaria de alugar!\n");
        scanf("%d", &novo_numero_quarto);

        if (Hotel[novo_numero_quarto]->ocupado == true) {
          printf("o quarto escolhido esta alugado por favor escolha outro!\n");
          novo_numero_quarto = 0;
        }

        if (Hotel[novo_numero_quarto]->tipo != tipo) {
          printf("o quarto escolhido nao e do mesmo tipo que o seu atual por favor escolha outro!\n");
          novo_numero_quarto = 0;
        }
      }

      //migrando as informacoes de um quarto para outro
      // disponibilidade
      Hotel[novo_numero_quarto]->ocupado = true;
      Hotel[numero]->ocupado = false;

      //valor do aluguel
      Registro[novo_numero_quarto]->valor_total = Registro[numero]->valor_total;
      Registro[numero]->valor_total = 0;

      //numero de ocupantes
      Registro[novo_numero_quarto]->numero_ocupantes = Registro[numero]->numero_ocupantes;
      Registro[numero]->numero_ocupantes = 0;

      printf("a alterecao de quartos foi realizada com sucesso!\n");
      break;
    }
    case 2: {
      //alteracao do numero de ocupantes
      while (novo_numero_ocupantes == 0) {
        printf("por favor informe qual quarto voce gostaria de alugar!\n");
        scanf("%d", &novo_numero_ocupantes);

        if (novo_numero_ocupantes > 4 || novo_numero_ocupantes < 1) {
          printf("o valor digitado e invalido por favor digite outro! (min - 1 max - 4)");
          novo_numero_ocupantes = 0;
        }
      }
      Registro[novo_numero_quarto]->numero_ocupantes = novo_numero_ocupantes;
      printf("o numero de hospedes foi alterado com sucesso para %d!\n", novo_numero_ocupantes);
      break;
    }

    case 3: {
      printf("A alteracao de aluguel foi cancelada!\n");
      break;
    }
    default: {
      printf("por favor informe uma opcao valida");
      break;
    }
    }
  }

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

  for (int i = 0; i < numero_registro_aluguel; i++) {
    printf("Quarto escolhido: %d, Usuário relacionado: %d, Período dias: %d, Valor total: %.2f, Número ocupantes: %d, Aluguel em andamento: %s, Alugado em: %s \n", registro_aluguel[i].quarto_escolhido, registro_aluguel[i].usuario_relacionado, registro_aluguel[i].periodo_dias, registro_aluguel[i].valor_total, registro_aluguel[i].numero_ocupantes, registro_aluguel[i].aluguel_em_andamento ? "sim" : "não", registro_aluguel[i].alugado_em);
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
    printf("%d", quartos[i].ocupado);
    printf("Numero: %d, Tipo: %c, Valor diaria: %.2f, Preparado: %s, Ocupado: %s, Modificado em: %s, Cadastrado em: %s \n", quartos[i].numero, quartos[i].tipo, quartos[i].valor_diaria, quartos[i].preparado ? "sim" : "não", quartos[i].ocupado ? "sim" : "não", quartos[i].modificado_em, quartos[i].cadastrado_em);
  }

  // Libera a memória alocada
  free(quartos);

  return 200;
}

int registrarQuarto() {
  // Declaração das variáveis
  int numero;
  char tipo;
  float valor_diaria;

  // Validar entrada de número
  do {
    printf("Digite o número do quarto: ");
    int isNumber = scanf("%d", &numero);

    // Deve ser um número
    if (isNumber != 1) {
      printf("Digite um numero inteiro. \n");
      continue;
    }

    // Número do quarto menor ou igual a zero
    if (numero <= 0) {
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

  int statusCadastrarQuarto = cadastrarQuarto(numero, tipo, valor_diaria);

  // Checar possibilidades de retorno da função
  if (statusCadastrarQuarto != 201) {
    printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
    return 200;
  }

  printf("Quarto cadastrado com sucesso! \n");

  return 200;
}
