INSERT INTO usuarios (nome, email, senha, idade, cargo)
VALUES ('Marcos Roberto Moraes', 'maromo@email.com', 'maromo123', 40, 'ADMINISTRADOR'),
('Ana Célia', 'ana@email.com', 'ana123', 40, 'ADMINISTRADOR');

INSERT INTO quartos (numero, tipo, valor_diaria, ocupado)
VALUES (101, 'A', 110.50, false),
(102, 'A', 120.00, false),
(103, 'A', 130.50, false),
(104, 'A', 140.00, false),
(105, 'A', 150.50, false),
(201, 'B', 160.00, false),
(202, 'B', 170.50, false),
(203, 'B', 180.00, true),
(204, 'B', 190.50, false),
(205, 'B', 200.00, false),
(301, 'C', 210.50, false),
(302, 'C', 220.00, false),
(303, 'C', 230.50, false),
(304, 'C', 240.00, false),
(305, 'C', 250.50, false),
(401, 'D', 260.00, false),
(402, 'D', 270.50, false),
(403, 'D', 280.00, false),
(404, 'D', 290.50, false),
(405, 'D', 300.00, false),
(501, 'E', 310.50, true),
(502, 'E', 320.00, false),
(503, 'E', 330.50, false),
(504, 'E', 340.00, false),
(505, 'E', 350.50, false);

INSERT INTO registro_alugueis (quarto_escolhido, usuario_relacionado, periodo_dias, valor_total, numero_ocupantes)
VALUES (8, 1, 5, 900, 5),
(21, 2, 7, 2173.5, 2);
