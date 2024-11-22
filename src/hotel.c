#include <stdio.h>
#include <malloc.h>
#include "hotel.h"
#include "models/hotel.h"

typedef t_quarto* p_quarto; // variavel que cria um ponteiro apontando para a estrutura quarto_hotel
p_quarto Hotel[32]; //variavel que simula o hotel sendo este tratado como um array contendo 32 quartos

typedef t_registro* p_registro // variavel que cria um ponteiro apontando para a estrutura RegistroAluguel
p_registro Registro[32]; // variavel que registra o aluguel de um quarto contendo 32 possiveis alugueis para 32 quartos

// TODO: Refatorar essa função para suportar as novas estruturas de Quarto e RegistroAluguel
void inicializa_hotel() {
    //realizando o loop para percorrer do indice 1 até o 32
    for (int i = 1; i <= 31; i++) {

        Hotel[i] = (p_quarto)malloc(sizeof(t_quarto_hotel));
        if (i <= 16)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->numero = i;
            Hotel[i]->tipo = 'C';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_valor_aluguel = 0;
            Hotel[i]->numero_ocupantes = 0;

        }


        else if (i > 16 && i <= 24)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->numero = i;
            Hotel[i]->tipo = 'B';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_valor_aluguel = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
        else if (i > 24 && i <= 30)
        {

            Hotel[i]->quarto_preparado = true;
            Hotel[i]->numero = i;
            Hotel[i]->tipo = 'A';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_valor_aluguel = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
        else if (i > 30 && i <= 33)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->numero = i;
            Hotel[i]->tipo = 'M';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_valor_aluguel = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
    }
};


void alugar_quarto() {
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

//     /** Obtendo a classe do quarto **/
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
        if (Hotel[numero]->quarto_ocupado == true)
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
        cliente_janela();

    }
    else if (resposta == 'S')
    {
        printf("agendamento confirmado\n");
        Registro[numero]->valor_total = quarto_preco;
        Registro[numero]->numero_ocupantes = ocupantes;
        Registro[numero]->quarto_escolhido = numero;
        Hotel[numero]->quarto_ocupado = true;

        quarto_escolhido
            cliente_janela();
    }
}

//TODO: Refatorar essa função para suportar as novas estruturas de Quarto e RegistroAluguel
void desalugar_quarto() {
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
    if (resposta == 'N')
    {
        cliente_janela();
    }
    else if (resposta == 'S')
    {
        printf("seu quarto foi desalugado com sucesso!\n");
        //resetando as informações do quarto
        Registro[numero]->valor_total = quarto_preco;
        Registro[numero]->numero_ocupantes = ocupantes;
        Registro[numero]->quarto_ocupado = false;
        cliente_janela();
    }
}

// TODO: Refatorar essa função para suportar as novas estruturas de Quarto e RegistroAluguel
void alterar_aluguel() {
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

                if (Hotel[novo_numero_quarto]->quarto_ocupado == true)
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
            Hotel[novo_numero_quarto]->quarto_ocupado = true;
            Hotel[numero]->quarto_ocupado = false;

            //valor do aluguel
            Hotel[novo_numero_quarto]->quarto_valor_aluguel = Hotel[numero]->quarto_valor_aluguel;
            Hotel[numero]->quarto_valor_aluguel = 0;

            //numero de ocupantes
            Hotel[novo_numero_quarto]->numero_ocupantes = Hotel[numero]->numero_ocupantes;
            Hotel[numero]->numero_ocupantes = 0;

            printf("a alterecao de quartos foi realizada com sucesso!\n");
            cliente_janela();
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
            Hotel[novo_numero_quarto]->numero_ocupantes = novo_numero_ocupantes;
            printf("o numero de hospedes foi alterado com sucesso para %d!\n", novo_numero_ocupantes);
            cliente_janela();
            break;
        }

        case 3:
        {
            printf("A alteracao de aluguel foi cancelada!\n");
            cliente_janela();
            break;
        }
        default:
        {
            printf("por favor informe uma opcao valida");
            break;
        }
        }
    }

}

void cliente_janela() {
    int opcao = 0;
    printf("-- Seja bem vindo --\n");
    printf("-- Escolha um de nossos servicos --\n");
    printf("-- 1 Alugar quarto --\n");
    printf("-- 2 Desalugar quarto --\n");
    printf("-- 3 Editar quarto --\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
    {
        alugar_quarto();
        break;
    }
    case 2:
    {
        desalugar_quarto();
        break;
    }
    case 3:
    {
        alterar_aluguel();
        break;
    }
    default:
    {
        printf("por favor informe uma opcao valida\n");
        break;
    }
    }
}

void controlarRegistroQuarto() {
    int numero = 111;
    char tipo = 'A';
    float valor_diaria = 276.50;
    cadastrarQuarto(numero, tipo, valor_diaria);
    return;
}
