'use strict';
let records = [];
const byId = id => document.getElementById(id);
const demo = [
  {created_at:'2026-01-01 09:00:00',device:'DEMO-01',uid:'00:11:22:33',status:'autorizado'},
  {created_at:'2026-01-01 09:03:00',device:'DEMO-01',uid:'AA:BB:CC:DD',status:'negado'},
  {created_at:'2026-01-01 09:07:00',device:'DEMO-01',uid:'00:11:22:33',status:'autorizado'}
];
function validateRecords(value) {
  if (!Array.isArray(value) || value.length > 10000) throw new Error('Use uma lista JSON com até 10.000 registros.');
  return value.map((row, index) => {
    if (!row || typeof row !== 'object') throw new Error(`Registro ${index + 1} inválido.`);
    const result = {};
    for (const key of ['device','uid','status']) {
      if (typeof row[key] !== 'string' || !row[key].trim() || row[key].length > 100) throw new Error(`Registro ${index + 1}: campo ${key} inválido.`);
      result[key] = row[key];
    }
    if (!['autorizado','negado'].includes(row.status)) throw new Error(`Registro ${index + 1}: status inválido.`);
    if (row.created_at != null && (typeof row.created_at !== 'string' || row.created_at.length > 100)) throw new Error(`Registro ${index + 1}: data inválida.`);
    result.created_at = row.created_at || 'Não informado';
    return result;
  });
}
function render() {
  byId('total').textContent=records.length;
  byId('allowed').textContent=records.filter(r=>r.status==='autorizado').length;
  byId('denied').textContent=records.filter(r=>r.status==='negado').length;
  const list=records.filter(r=>byId('filter').value==='todos'||r.status===byId('filter').value);
  const body=byId('records'); body.replaceChildren();
  for(const row of list){
    const tr=document.createElement('tr');
    for(const key of ['created_at','device','uid','status']){
      const td=document.createElement('td');
      if(key==='status'){const badge=document.createElement('span');badge.className=`status ${row.status}`;badge.textContent=row[key];td.append(badge);}
      else td.textContent=row[key];
      tr.append(td);
    }
    body.append(tr);
  }
  if(!list.length){const tr=document.createElement('tr');const td=document.createElement('td');td.colSpan=4;td.textContent='Nenhum registro para exibir.';tr.append(td);body.append(tr);}
}
byId('demo').addEventListener('click',()=>{records=validateRecords(demo);byId('source').textContent='DEMONSTRAÇÃO · dados fictícios, sem vínculo com a montagem real.';render();});
byId('clear').addEventListener('click',()=>{records=[];byId('import').value='';byId('source').textContent='Registros limpos.';render();});
byId('filter').addEventListener('change',render);
byId('import').addEventListener('change',async event=>{
  const file=event.target.files[0]; if(!file)return;
  try{
    if(file.size>2*1024*1024)throw new Error('O arquivo deve ter até 2 MB.');
    const parsed=validateRecords(JSON.parse(await file.text()));
    records=parsed;byId('source').textContent=`Arquivo importado: ${file.name}. Origem declarada pelo usuário; dados não verificados.`;render();
  }catch(error){byId('source').textContent=`Não foi possível importar: ${error.message} Os registros anteriores foram mantidos.`;}
  event.target.value='';
});
