# Projeto Hotel Maromo

Este é o repositório do Projeto Hotel Maromo, desenvolvido pela nossa equipe com o objetivo de criar um sistema de gerenciamento para hotéis.
O sistema oferece funcionalidades como cadastro de hóspedes, reservas, controle de pagamentos, entre outras.

## Índice

- [Visão Geral]
- [Funcionalidades]
- [Tecnologias Utilizadas]
- [Pré-requisitos]
- [Instalação e Execução]
- [Guia de Usuário]

## Visão Geral

O Projeto Hotel Maromo é uma aplicação que simplifica o gerenciamento de hotéis. Com uma interface intuitiva e recursos eficientes, o sistema permite:

- Registrar hóspedes e informações de contato.
- Gerenciar reservas, incluindo check-in e check-out.
- Controlar pagamentos e gerar relatórios financeiros.
- Configurar detalhes como número de quartos, tipos de acomodações e preços.

O projeto foi desenvolvido com foco em escalabilidade e facilidade de uso.

## Funcionalidades

- Cadastro de hóspedes: Insira e gerencie os dados dos hóspedes.
- Gerenciamento de reservas: Controle check-in, check-out e detalhes das estadias.
- Controle financeiro: Registre pagamentos e acompanhe receitas.
- Relatórios gerenciais: Geração de relatórios detalhados sobre ocupação e finanças.
- Configuração de quartos: Personalize informações sobre acomodações.

## Tecnologias Utilizadas

- Linguagem de programação: C, SQL
- Banco de Dados: PostgreSQL
- Versionamento: Git
- Virtualização de máquinas: Docker

## Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas em sua máquina:

- [Git](https://git-scm.com/)
- [PostgreSQL](https://www.postgresql.org/download/)
- [Docker](https://www.docker.com/products/docker-desktop/)
- [GCC](https://gcc.gnu.org/install/)

## Instalação e Execução

### 1. Clone este repositório:

```bash
    git clone https://github.com/Artursrossi/projeto_hotel_maromo.git
```

### 2. Configure o banco de dados:

    2.1 Suba o banco de dados dentro de um container docker, executando:
    ```bash
        docker-compose up -d
    ```

    2.2 Acesse o banco de dados utilizando o visualizador de banco de dados da sua preferência (ex:. HeidiSQL, Beekepper). Para isso você terá que utilizar as credenciais dentro do arquivo docker-compose.yml

    2.3 Dentro do executor de Query SQL do seu visualizador, Importe o arquivo migrations.sql para gerar o schema do banco de dados

    2.4 Dentro do executor de Query SQL do seu visualizador, Importe o arquivo seed.sql para popular dados pré-definidos às tabelas

### 3. Compile o projeto:

    ```bash
        gcc main.c usuario.c hotel.c models/usuarios.c models/hotel.c lib/psql.c utils/conversoes.c -o main -L "/usr/lib/x86_64-linux-gnu" -lpq
    ```

### 4.Execute a aplicação:

    ```bash
        ./main
    ```

## Guia de Usuário

- Link para o Guia de Usuário: https://docs.google.com/document/d/1nlHjmilQblPvTbxkxLIhxlNGVkz9HcD6762AxMo0ml0/edit?tab=t.0
