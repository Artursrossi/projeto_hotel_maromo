CREATE TYPE cargo_usuario AS ENUM('USUARIO', 'ADMINISTRADOR');

CREATE TABLE usuarios (
  codigo SERIAL PRIMARY KEY,
  nome VARCHAR(64) NOT NULL,
  email VARCHAR(32) NOT NULL,
  senha VARCHAR(16) NOT NULL,
  idade INTEGER NOT NULL,
  cargo cargo_usuario DEFAULT 'USUARIO',
  cadastrado_em TIMESTAMP DEFAULT current_timestamp
);