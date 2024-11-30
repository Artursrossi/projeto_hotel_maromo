#include <stdio.h>
#include <string.h>

#include "usuario.h"
#include "hotel.h"

// Definições das funções
void exibirMenuAdmin();
void controlarMenuAdmin();
void exibirMenuLogado();
void controlarMenuLogado();
void exibirMenuInicial();
void controlarMenuInicial();

void exibirMenuAdmin() {
  printf("Escolha uma opção \n");
  printf("1 - Listar todos os usuários \n");
  printf("2 - Listar todos os quartos \n");
  printf("3 - Listar todos os registros de alugueis \n");
  printf("4 - Cadastrar novos quartos \n");
  printf("5 - Voltar ao menu anterior \n");

  return;
}

void controlarMenuAdmin() {
  if (strcmp(usuario.cargo, "ADMINISTRADOR") != 0) return;

  // Declarar variáveis
  int opt = 0; // Variável com a opção escolhida
  int status = 0; // Variável com o retorno da função executada
  char buffer[64];

  do {
    exibirMenuAdmin();

    // Captura entrada do usuário
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Entrada inválida.\n");
      continue;
    }

    // Remove o caractere de nova linha
    buffer[strcspn(buffer, "\n")] = '\0';

    // Verificar se é um número válido
    if (sscanf(buffer, "%d", &opt) != 1) {
      printf("Escolha inválida. \n");
      continue;
    }

    // Validar intervalo de opções
    if(opt < 1 || opt > 5){
      printf("Você deve escolher de 1 a 5 \n");
      continue;
    }

    break;
  } while (1);

  switch (opt) {
    case 1:
      status = listarUsuarios();
      if (status == 200) {
        controlarMenuAdmin();
      }
      break;
    case 2:
      status = listarQuartos();
      if (status == 200) {
        controlarMenuAdmin();
      }
      break;
    case 3:
      status = listarRegistrosAlugueis();
      if (status == 200) {
        controlarMenuAdmin();
      }
      break;
    case 4:
      status = registrarQuarto();
      if (status == 200) {
        controlarMenuAdmin();
      }
      break;
    case 5:
      controlarMenuLogado();
      break;
    default:
      printf("Opção inválida. \n");
      break;
  }
}

void exibirMenuLogado() {
  printf("Escolha uma opção \n");
  printf("1 - Exibir quartos disponíveis \n");
  printf("2 - Alugar um quarto \n");
  printf("3 - Listar reservas atuais \n");
  printf("4 - Desalugar quarto \n");
  printf("5 - Alterar informações da reserva atual \n");
  printf("6 - Gerar histórico de reservas \n");
  printf("7 - Sair da conta \n");

  if (strcmp(usuario.cargo, "ADMINISTRADOR") == 0) printf("8 - Acessar área administrativa \n");

  return;
}

void controlarMenuLogado() {
  // Declarar variáveis
  int opt = 0; // Variável com a opção escolhida
  int status = 0; // Variável com o retorno da função executada
  char buffer[64];

  do {
    exibirMenuLogado();

    // Captura entrada do usuário
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Entrada inválida.\n");
      continue;
    }

    // Remove o caractere de nova linha
    buffer[strcspn(buffer, "\n")] = '\0';

    // Verificar se é um número válido
    if (sscanf(buffer, "%d", &opt) != 1) {
      printf("Escolha inválida. \n");
      continue;
    }

    // Validar intervalo de opções
    if(opt < 1 || opt > 8){
      printf("Você deve escolher de 1 a 8 \n");
      continue;
    }

    break;
  } while (1);

  switch (opt) {
    case 1:
      status = listarQuartosDesocupados();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 2:
      status = alugarQuarto();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 3:
      status = listarReservaAtual();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 4:
      status = desalugarQuarto();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 5:
      status = alterarReservaAtual();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 6:
      status = listarHistoricoReservas();
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 7:
      status = deslogarUsuario();
      if (status == 200) {
        controlarMenuInicial();
      }
      break;
    case 8:
      controlarMenuAdmin();
      break;
    default:
      printf("Opção inválida. \n");
      break;
  }
}

void exibirMenuInicial() {
  printf("Escolha uma opção \n");
  printf("1 - Entrar com uma conta existente  \n");
  printf("2 - Cadastrar nova conta \n");

  return;
}

void controlarMenuInicial() {
  // Declarar variáveis
  int opt = 0; // Variável com a opção escolhida
  int status = 0; // Variável com o retorno da função executada
  char buffer[64];

  do {
    exibirMenuInicial();

    // Captura entrada do usuário
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Entrada inválida.\n");
      continue;
    }

    // Remove o caractere de nova linha
    buffer[strcspn(buffer, "\n")] = '\0';

    // Verificar se é um número válido
    if (sscanf(buffer, "%d", &opt) != 1) {
      printf("Escolha inválida. \n");
      continue;
    }

    // Validar intervalo de opções
    if(opt < 1 || opt > 2){
      printf("Você deve escolher de 1 a 2 \n");
      continue;
    }

    break;
  } while (1);

  switch (opt) {
    case 1:
      status = autenticarUsuario();
      // Usuário não autenticado
      if(status == 400){
        controlarMenuInicial();
        break;
      }
      // Assim que o login for efetuado com sucesso, mostrar Menu Logado
      if (status == 200) {
        controlarMenuLogado();
      }
      break;
    case 2:
      status = registrarUsuario();
      // Assim que o usuário cadastrar um usuário, mostrar a opção de logar
      if (status == 200) {
        controlarMenuInicial();
      }
      break;
    default:
      printf("Opção inválida. \n");
      break;
  }
}

int main() {
  controlarMenuInicial();

  return 0;
}
