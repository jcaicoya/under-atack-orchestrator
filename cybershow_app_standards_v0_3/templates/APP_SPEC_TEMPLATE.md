# APP_SPEC — <Nombre de la aplicación>

Versión: 0.1  
Estado: pendiente de completar.

Este archivo contiene instrucciones específicas para adaptar esta aplicación al estándar Cybershow. Debe leerse junto a:

- `QT_APP_LOOK_AND_FEEL.md`
- `CYBERSHOW_APP_CONVENTIONS.md`

---

## 1. Identidad de la aplicación

- Nombre visible:
- Nombre interno:
- Ejecutable:
- Rol dentro del show:
- Tipo principal: operativa / escénica / mixta

---

## 2. Pantallas

| Nº | ID | Título largo | Título corto | Tipo | Notas |
|---:|---|---|---|---|---|
| 1 | principal | Principal | Principal | operative |  |
| 2 |  |  |  |  |  |
| 3 |  |  |  |  |  |

---

## 3. Setup

Parámetros que debe mostrar Setup:

- 
- 
- 

Parámetros que deben poder venir de configuración o CLI:

- 
- 
- 

Reglas especiales:

- 

---

## 4. Modo demo/live

Datos simulados en modo demo:

- 

Datos reales/controlados en modo live:

- 

---

## 5. Integración con orquestador

Mensajes mínimos emitidos:

- `CYBERSHOW_STATUS READY`
- `CYBERSHOW_STATUS RUNNING`
- `CYBERSHOW_SCREEN <n> <id>`
- `CYBERSHOW_STATUS ERROR <code>`

Eventos específicos de esta app:

```text
CYBERSHOW_EVENT <event-name> <payload>
```

---

## 6. Excepciones permitidas

Lista de diferencias justificadas respecto al estándar común:

- 

---

## 7. Checklist de refactorización

- [ ] CLI común implementada.
- [ ] `--configure` arranca en Setup.
- [ ] Sin argumentos equivale a `--configure`.
- [ ] `--design` y `--show` arrancan en ejecución.
- [ ] Setup es inaccesible en `--design`/`--show`.
- [ ] Navegación común implementada.
- [ ] Atajos por letra eliminados para navegación principal.
- [ ] Barra inferior común implementada.
- [ ] Fondo común aplicado.
- [ ] Estados visuales normalizados.
- [ ] Mensajes stdout para orquestador implementados.
- [ ] Logging interno revisado.
- [ ] Textos de operador revisados en español.
- [ ] Compila correctamente.
