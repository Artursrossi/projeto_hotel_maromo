#include <stdio.h>
#include "hotel.h"

void inicializa_hotel()
{

};

void alugar_quarto()
{
    int numero = 0;
    int ocupantes = 0;
    char tipo = '0';

    printf("-- Menu de aluguel para quartos --\n");


    /**  Obtendo os dados do usuario **/

    /** Obtendo a classe do quarto **/
    printf("-- Qual tipo de quarto voce gostaria de alugar? (A,B,C) --\n");
    while(tipo  == '0')
    {

        scanf(" %c", &tipo);
        switch(tipo)
        {
            case 'A':
            {}
            case 'B':
            {}
            case 'C':
            {}
            default:
                printf("informe um tipo valido");
                tipo  = '0';
        }

    }

    /** Obtendo o numero do quarto **/
    printf("-- Qual quarto (1-100) voce gostaria de alugar? --\n");
        while(numero == 0)
        {
        scanf("%d", &numero);
        if(numero < 0 || numero > 100)
        {
            printf("-- Por favor informe um numero valido --\n");
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

    /** Obtendo o tipo de quarto **/
    printf("-- Quantos ocupantes? (max 4 pessoas) --\n");






}