-- Executar no MySQL. Modelo proposto para N1; não substitui tabelas existentes.
CREATE DATABASE IF NOT EXISTS arcanjos CHARACTER SET utf8mb4;
USE arcanjos;
CREATE TABLE IF NOT EXISTS acessos (
  id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
  device VARCHAR(64) NOT NULL,
  uid VARCHAR(32) NOT NULL,
  status ENUM('autorizado','negado') NOT NULL,
  created_at TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3)
);
