# CLAUDE.md - BAJO ATAQUE Orchestrator

Instrucciones de trabajo específicas para este subproyecto.

## Lectura obligatoria al empezar

Antes de trabajar aquí, lee y aplica también:

- `README.md`
- `RUNBOOK.md`
- `NEXT_STEPS.md`

## Qué contiene cada archivo

- `README.md`: qué es el orchestrator, arquitectura, stack y reglas generales de diseño.
- `RUNBOOK.md`: deploy, arranque, operación y manejo de escenario/ADB.
- `NEXT_STEPS.md`: pendientes y prioridades actuales.
- `.claude/CLAUDE.md`: reglas de trabajo específicas de este directorio.

No dupliques información entre estos archivos. Cada dato debe vivir en un único sitio.

## Forma de trabajar en este directorio

- El usuario se encarga de compilar, probar, hacer commits y hacer push.
- No des por validado el comportamiento del orchestrator sin prueba en hardware real cuando dependa de varias pantallas, proyector o ADB.
- Si cambias arquitectura, operación, flujo de show o backlog, actualiza el archivo correspondiente.
- Tras cada commit, `README.md`, `RUNBOOK.md` y `NEXT_STEPS.md` deben seguir reflejando el estado real del proyecto.

## Alcance de este archivo

Este archivo no debe repetir documentación general ni instrucciones operativas de uso diario; eso pertenece a `README.md` o `RUNBOOK.md`.
