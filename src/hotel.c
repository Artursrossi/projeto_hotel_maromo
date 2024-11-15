#include <stdio.h>
#include <malloc.h>
#include "Hotel.h"


void inicializa_hotel()
{
    for(int i = 0; i < 32; i++) {

        Hotel[i] = (p_hotel)malloc(sizeof(quarto_hotel));
        if(i <= 16)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->quarto_numero = i;
            Hotel[i]->quarto_classe = 'C';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_preco = 0;
            Hotel[i]->numero_ocupantes = 0;

        }


        else if(i > 16 && i <= 24)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->quarto_numero = i;
            Hotel[i]->quarto_classe = 'B';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_preco = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
        else if(i > 24 && i <= 30)
        {

            Hotel[i]->quarto_preparado = true;
            Hotel[i]->quarto_numero = i;
            Hotel[i]->quarto_classe = 'A';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_preco = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
        else if(i > 30 && i <= 32)
        {
            Hotel[i]->quarto_preparado = true;
            Hotel[i]->quarto_numero = i;
            Hotel[i]->quarto_classe = 'M';
            Hotel[i]->quarto_ocupado = false;
            Hotel[i]->quarto_preco = 0;
            Hotel[i]->numero_ocupantes = 0;
        }
    }
};


void alugar_quarto()
{
    int min_room = 0;
    int max_room = 0;
    int numero = 0;
    int ocupantes = 0;
    char tipo = '0';
    int aluguel = 0;
    float quarto_preco = 0;

    printf("-- Menu de aluguel para quartos --\n");


    /**  Obtendo os dados do usuario **/

    /** Obtendo a classe do quarto **/
    printf("-- Qual tipo de quarto voce gostaria de alugar? (M,A,B,C) --\n");
    while(tipo == '0')
    {

        scanf("%c", &tipo);
        switch(tipo)
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
                printf("informe um tipo valido");
                tipo  = '0';
        }

    }
    for(int i = 0; i < 32; i++) {
        if(Hotel[i]->quarto_classe == tipo){
            /** procura quais são os indices para o tipo de quarto especificado **/
            if(min_room == 0)
            {
                min_room = i;
                max_room = i;
            }
            else {
                max_room += 1;
            }


            printf("%d ", Hotel[i]->quarto_numero);
        }}

    /** Obtendo o numero do quarto **/
    printf("-- Qual quarto (%d-%d) voce gostaria de alugar? --\n", min_room, max_room);
    while(numero == 0)
    {
        scanf("%d", &numero);
        if(numero < min_room || numero > max_room)
        {
            printf("-- O quarto informado nao e do tipo %c --\n", tipo);
            numero = 0;
        }
    }

    /** Obtendo o numero de ocupantes **/
    printf("-- Quantos ocupantes? (max 4 pessoas) --\n");
    while(ocupantes == 0)
    {
        scanf("%d", &ocupantes);
        if(ocupantes < 0 || ocupantes > 4)
        {
            printf("-- Por favor informe um numero valido de ocupantes --\n");
            ocupantes = 0;
        }
    }

    /** Verificando se o quarto está desocupado
    if(quarto_ocupado == true)
    printf("--  --\n");
    **/

    /** obtendo o preco final **/

    quarto_preco = aluguel * ocupantes;

    printf("-- o valor total do aluguel sera de %.2f --", quarto_preco);


}