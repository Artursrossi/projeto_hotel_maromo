#include "usuario.c"
#include "hotel.c"

int main(){
  Usuario usuario;

  strcpy(usuario.id, "a1a1-2b2b-3c3c");
  strcpy(usuario.nome, "Maromo");
  strcpy(usuario.email, "maromo@gmail.com");
  strcpy(usuario.senha, "maromo123");
  usuario.idade = 18;
  usuario.cargo = 0;
  strcpy(usuario.data_cadastro, "28/10/2024");

  registrar(&usuario);

  return 0;
}