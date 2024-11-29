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
  printf("2 - Exibir todos os quartos \n");
  printf("3 - Cadastrar novos quartos \n");
  printf("4 - Voltar ao menu anterior \n");
  printf("\n");

  return;
}

void controlarMenuAdmin() {
  if (strcmp(usuario.cargo, "ADMINISTRADOR") != 0) return;

  short int opt = 0; // Variável com a opção escolhida
  short int status = 0; // Variável com o retorno da função executada

  do {
    exibirMenuAdmin();
    scanf("%hd", & opt);
  } while (opt <= 0 || opt > 4);
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
    status = registrarQuarto();
    if (status == 200) {
      controlarMenuAdmin();
    }
    break;
  case 4:
    controlarMenuLogado();
    break;
  }
}

void exibirMenuLogado() {
  printf("Escolha uma opção \n");
  printf("1 - Exibir quartos disponíveis \n");
  printf("2 - Alugar um quarto \n");
  printf("3 - Fazer CheckOut do quarto \n");
  printf("4 - Alterar informações da reserva atual \n");
  printf("5 - Gerar histórico de reservas \n");
  printf("6 - Sair da conta \n");

  if (strcmp(usuario.cargo, "ADMINISTRADOR") == 0) printf("7 - Acessar área administrativa \n");
  printf("\n");

  return;
}

void controlarMenuLogado() {
  short int opt = 0; // Variável com a opção escolhida
  short int status = 0; // Variável com o retorno da função executada

  do {
    exibirMenuLogado();
    scanf("%hd", & opt);
  } while (opt <= 0 || opt > 7);

  switch (opt) {
  case 1:
    status = listarQuartos();
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
    status = desalugarQuarto();
    if (status == 200) {
      controlarMenuLogado();
    }
    break;
  case 4:
    status = alterarReservaAtual();
    if (status == 200) {
      controlarMenuLogado();
    }
    break;
  case 5:
    status = gerarHistoricoReservas();
    if (status == 200) {
      controlarMenuLogado();
    }
    break;
  case 6:
    status = deslogarUsuario();
    if (status == 200) {
      controlarMenuInicial();
    }
    break;
  case 7:
    controlarMenuAdmin();
    break;
  }
}

void exibirMenuInicial() {
  printf("Escolha uma opção \n");
  printf("1 - Entrar com uma conta existente  \n");
  printf("2 - Cadastrar nova conta \n");
  printf("\n");

  return;
}

void controlarMenuInicial() {
  short int opt = 0; // Variável com a opção escolhida
  short int status = 0; // Variável com o retorno da função executada

  do {
    exibirMenuInicial();
    scanf("%hd", & opt);
  } while (opt <= 0 || opt > 2);

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
  }
}

int main() {
  controlarMenuInicial();

  return 0;
}
