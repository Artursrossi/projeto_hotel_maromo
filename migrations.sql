CREATE TYPE cargo_usuario AS ENUM('USUARIO', 'ADMINISTRADOR');

CREATE TABLE usuarios (
  codigo SERIAL PRIMARY KEY,
  nome VARCHAR(64) NOT NULL,
  email VARCHAR(32) UNIQUE NOT NULL,
  senha VARCHAR(16) NOT NULL,
  idade INTEGER NOT NULL,
  cargo cargo_usuario DEFAULT 'USUARIO',
  cadastrado_em TIMESTAMP DEFAULT current_timestamp
);

CREATE TABLE quartos (
  codigo SERIAL PRIMARY KEY,
  numero SMALLINT NOT NULL,
  tipo CHAR(1) NOT NULL,
  valor_diaria NUMERIC(7,2) NOT NULL,
  preparado BOOLEAN NOT NULL,
  ocupado BOOLEAN NOT NULL,
  modificado_em TIMESTAMP DEFAULT current_timestamp,
  cadastrado_em TIMESTAMP DEFAULT current_timestamp
);

CREATE TABLE registro_alugueis (
  codigo SERIAL PRIMARY KEY,
  quarto_escolhido INTEGER REFERENCES quartos NOT NULL,
  usuario_relacionado INTEGER REFERENCES usuarios NOT NULL,
  periodo_dias SMALLINT NOT NULL,
  valor_total NUMERIC(7,2) NOT NULL,
  numero_ocupantes SMALLINT NOT NULL,
  alugado_em TIMESTAMP DEFAULT current_timestamp
);

CREATE  FUNCTION atualizar_modificado_em_quartos()
RETURNS TRIGGER AS $$
BEGIN
  NEW.modificado_em = now();
  RETURN NEW;
END;
$$ language 'plpgsql';

CREATE TRIGGER quartos_modificado_em
  BEFORE UPDATE
  ON
    quartos
  FOR EACH ROW
EXECUTE PROCEDURE atualizar_modificado_em_quartos();