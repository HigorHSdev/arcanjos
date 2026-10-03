-- No DBeaver, exportar o resultado como JSON (array de objetos).
-- Horário UTC para comparação consistente; a página exibe o texto sem conversão.
SET time_zone = '+00:00';
SELECT DATE_FORMAT(created_at, '%Y-%m-%dT%H:%i:%sZ') AS created_at,
       device, uid, status
FROM arcanjos.acessos
ORDER BY id DESC
LIMIT 1000;
