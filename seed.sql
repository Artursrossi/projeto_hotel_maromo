INSERT INTO usuarios (nome, email, senha, idade, cargo)
VALUES ('Marcos Roberto Moraes', 'maromo@email.com', 'maromo123', 40, 'ADMINISTRADOR'),
('Ana Célia', 'ana@email.com', 'ana123', 40, 'ADMINISTRADOR');

INSERT INTO quartos (numero, tipo, valor_diaria)
VALUES (101, 'A', 110.50),
(102, 'A', 120.00),
(103, 'A', 130.50),
(104, 'A', 140.00),
(105, 'A', 150.50),
(201, 'B', 160.00),
(202, 'B', 170.50),
(203, 'B', 180.00),
(204, 'B', 190.50),
(205, 'B', 200.00),
(301, 'C', 210.50),
(302, 'C', 220.00),
(303, 'C', 230.50),
(304, 'C', 240.00),
(305, 'C', 250.50),
(401, 'D', 260.00),
(402, 'D', 270.50),
(403, 'D', 280.00),
(404, 'D', 290.50),
(405, 'D', 300.00),
(501, 'E', 310.50),
(502, 'E', 320.00),
(503, 'E', 330.50),
(504, 'E', 340.00),
(505, 'E', 350.50);

INSERT INTO registro_alugueis (quarto_escolhido, usuario_relacionado, periodo_dias, valor_total, numero_ocupantes)
VALUES (8, 1, 5, 900, 5),
(21, 2, 7, 2173.5, 2);
