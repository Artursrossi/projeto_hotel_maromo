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
    int codigo_quarto_escolhido = 1;
    int codigo_usuario = 1;
    int periodo_dias = 5;
    int numero_ocupantes = 2;

    // Obter informações relacionadas ao quarto escolhido
    t_quarto quarto;
    int statusObterUnicoQuartoPorCodigo = obterUnicoQuartoPorCodigo(&quarto, codigo_quarto_escolhido);

    // Checar possibilidades de retorno da função
    if(statusObterUnicoQuartoPorCodigo == 404){
        printf("Quarto não encontrado \n");
        return 200;
    }
    if(statusObterUnicoQuartoPorCodigo != 200){
        printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
        return 200;
    }

    // Definir quarto como ocupado no banco de dados
    int statusOcuparQuarto = ocuparQuarto(quarto.codigo);

    // Checar possibilidades de retorno da função
    if(statusOcuparQuarto != 200){
        printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
        return 200;
    }

    // Definir valor total do aluguel
    float valor_total = quarto.valor_diaria * periodo_dias;

    // Cadastrar registro aluguel e obter status do retorno
    int statusCadastrarRegistroAluguel = cadastrarRegistroAluguel(codigo_quarto_escolhido, codigo_usuario, periodo_dias, valor_total, numero_ocupantes);

    // Checar possibilidades de retorno da função
    if(statusCadastrarRegistroAluguel != 201){
        printf("Ocorreu um erro inesperado. Tente novamente mais tarde... \n");
        return 200;
    }


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
    while (tipo == '0')
    {
        scanf("%c", &tipo);
        switch (tipo)
        {
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
            if (min_room == 0)
            {
                min_room = i;
                max_room = i;
            }
            else {
                max_room += 1;
            }


            printf("%d ", Hotel[i]->numero);
        }
    }

    /** Obtendo o numero do quarto **/
    printf("-- Qual quarto (%d-%d) voce gostaria de alugar? --\n", min_room, max_room);
    while (numero == 0)
    {
        scanf("%d", &numero);
        if (numero < min_room || numero > max_room)
        {
            numero = 0;
        }
        if (Hotel[numero]->ocupado == true)
        {
            printf("-- o quarto esta ocupado por favor escolha outro--\n");
            numero = 0;
        }
    }

    /** Obtendo o numero de ocupantes **/
    printf("-- Quantos ocupantes? (max 4 pessoas) --\n");
    while (ocupantes == 0)
    {
        scanf("%d", &ocupantes);
        if (ocupantes < 0 || ocupantes > 4)
        {
            printf("-- Por favor informe um numero valido de ocupantes (1 min - 4 max) --\n");
            ocupantes = 0;
        }
    }
    /** obtendo o preco final **/

    quarto_preco = aluguel * ocupantes;

    printf("-- o valor total do aluguel sera de %.2f --\n", quarto_preco);

    printf("-- confirme o agendamento -- (S para continuar, N para sair)\n");
    fflush(stdin);
    resposta = getchar();
    if (resposta == 'N')
    {
        printf("agendamento cancelado\n");
    }
    else if (resposta == 'S')
    {
        printf("agendamento confirmado\n");
        Registro[numero]->valor_total = quarto_preco;
        Registro[numero]->numero_ocupantes = ocupantes;
        Registro[numero]->quarto_escolhido = numero;
        Hotel[numero]->ocupado = true;
    }

    return 200;
}

int desalugarQuarto() {
     int numero = 0;
    int ocupantes = 0;
    float quarto_preco = 0;
    char resposta;

    printf("por favor informe o numero do quarto alugado\n");
    while (numero == 0)
    {
        scanf("%d", &numero);

        if (numero < 1 || numero > 32)
        {
            printf("por favor informe um quarto valido\n");
            numero = 0;
        }
    }
    printf("-- voce realmente deseja desalugar seu quarto?  -- (S para continuar, N para cancelar)\n");
    fflush(stdin);
    resposta = getchar();
    if (resposta == 'S')
    {
        printf("seu quarto foi desalugado com sucesso!\n");
        //resetando as informações do quarto
        Registro[numero]->valor_total = quarto_preco;
        Registro[numero]->numero_ocupantes = ocupantes;
        Hotel[numero]->ocupado = false;
    }

  return 200;
}

int alterarReservaAtual(){
   char tipo = '0';
    int numero = 0;
    int novo_numero_quarto;
    int option = 0;
    int novo_numero_ocupantes = 0;

    printf("por favor informe o numero do quarto alugado\n");
    while (numero == 0)
    {
        scanf("%d", &numero);

        if (numero < 1 || numero > 32)
        {
            printf("por favor informe um quarto valido\n");
            numero = 0;
        }
    }
    printf("por favor informe o que deseja alterar\n");
    printf("1 - quarto alugado\n");
    printf("2 - numero de hospedes\n");
    printf("3 - cancelar\n");




    while (numero == 0)
    {
        switch (numero)
        {       // altera o quarto alugado
        case 1:
        {
            // verificao para checar se o novo quarto alugado sera do mesmo tipo e esta disponivel
            tipo = Hotel[numero]->tipo;
            while (novo_numero_quarto == 0)
            {
                printf("por favor informe qual quarto voce gostaria de alugar!\n");
                scanf("%d", &novo_numero_quarto);

                if (Hotel[novo_numero_quarto]->ocupado == true)
                {
                    printf("o quarto escolhido esta alugado por favor escolha outro!\n");
                    novo_numero_quarto = 0;
                }

                if (Hotel[novo_numero_quarto]->tipo != tipo)
                {
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
        case 2:
        {
            //alteracao do numero de ocupantes
            while (novo_numero_ocupantes == 0)
            {
                printf("por favor informe qual quarto voce gostaria de alugar!\n");
                scanf("%d", &novo_numero_ocupantes);

                if (novo_numero_ocupantes > 4 || novo_numero_ocupantes < 1)
                {
                    printf("o valor digitado e invalido por favor digite outro! (min - 1 max - 4)");
                    novo_numero_ocupantes = 0;
                }
            }
            Registro[novo_numero_quarto]->numero_ocupantes = novo_numero_ocupantes;
            printf("o numero de hospedes foi alterado com sucesso para %d!\n", novo_numero_ocupantes);
            break;
        }

        case 3:
        {
            printf("A alteracao de aluguel foi cancelada!\n");
            break;
        }
        default:
        {
            printf("por favor informe uma opcao valida");
            break;
        }
        }
    }

    return 200;
}

int gerarHistoricoReservas(){
    int quarto_numero;
    printf("digite o numero do quarto");
    scanf("%d", &quarto_numero);

    int numero_quarto = Hotel[quarto_numero]->numero;
    int preco = Registro[quarto_numero]->valor_total;
    int ocupantes = Registro[quarto_numero]->numero_ocupantes;

    printf("-- Recibo para quarto alugado--");
    printf("-- Numero do quarto -> %d --", numero_quarto);
    printf("-- Preco para o aluguel %d --", preco);
    printf("-- numero de ocupantes %d", ocupantes);

  return 200;
}

int listarQuartos(){
    printf("1, %s", usuario.nome);
    t_quarto *quartos = malloc(sizeof(t_quarto));
    int numero_quartos;

    int res = 0; // flag para salvar código de retorno da função
    res = obterMuitosQuartos(&quartos, &numero_quartos);

    // Checar possibilidades de retorno da função
    if(res != 200){
        printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
        return 200;
    }

    for (int i = 0; i < numero_quartos; i++) {
        printf("Codigo: %d, Numero: %d, Tipo: %c, Valor diaria: %.2f, Modificado em: %s, Cadastrado em: %s \n", quartos[i].codigo, quartos[i].numero, quartos[i].tipo, quartos[i].valor_diaria, quartos[i].modificado_em, quartos[i].cadastrado_em);
    }

    return 200;
}

int registrarQuarto(){
    int numero = 111;
    char tipo = 'A';
    float valor_diaria = 276.50;

    int res = 0; // flag para salvar código de retorno da função
    res = cadastrarQuarto(numero, tipo, valor_diaria);

    // Checar possibilidades de retorno da função
    if(res != 201){
        printf("Ocorreu um erro inesperado. Tente novamente mais tarde...");
        return 200;
    }

    printf("Quarto cadastrado com sucesso!");

    return 200;
}