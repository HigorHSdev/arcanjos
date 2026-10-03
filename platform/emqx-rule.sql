SELECT
  payload.device AS device,
  payload.uid AS uid,
  payload.status AS status
FROM "arcanjos/acesso"
WHERE payload.status = 'autorizado' OR payload.status = 'negado'
