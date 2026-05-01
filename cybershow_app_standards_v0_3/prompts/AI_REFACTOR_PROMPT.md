# Prompt base para Claude / Codex / Gemini

Usa este prompt al abrir una aplicación Qt existente que queremos adaptar al estándar Cybershow.

---

## Prompt

Lee primero estos documentos del repositorio:

1. `QT_APP_LOOK_AND_FEEL.md`
2. `CYBERSHOW_APP_CONVENTIONS.md`
3. El archivo específico de esta app, si existe, por ejemplo:
   - `apps/ATAQUE_INICIAL_VISUAL_FIXES.md`
   - `apps/PUBLIC_WIFI_VISUAL_FIXES.md`
   - `apps/QR_CONTROLLER_VISUAL_FIXES.md`
   - `APP_SPEC.md`

Objetivo: refactorizar esta aplicación Qt para que cumpla el estándar común de Cybershow sin romper su funcionalidad actual.

Aplica los cambios de forma incremental y segura.

Tareas obligatorias:

1. Implementar argumentos de arranque comunes:
   - sin argumentos equivale a `--configure`;
   - `--configure` muestra Setup;
   - `--design` y `--show` arrancan en la primera pantalla de ejecución;
   - en `--design`/`--show`, Setup no debe ser accesible.

2. Implementar navegación común:
   - desde Setup: Intro, Espacio, Flecha derecha, `1` o click en botón primario inician el show;
   - durante ejecución: flechas izquierda/derecha, números y click en barra inferior;
   - `Esc` vuelve a Setup solo en `--configure`;
   - `Esc` no hace nada en `--design`/`--show`;
   - eliminar atajos por letra para navegación principal;
   - no navegación circular por defecto;
   - no interferir con campos editables.

3. Aplicar look & feel común:
   - fondo común Qt;
   - paneles comunes;
   - barra inferior común;
   - colores y estados comunes;
   - textos de operador en español;
   - setup con tarjeta central;
   - sin QR ni mascota lateral fija en setup.

4. Normalizar pantallas:
   - cada pantalla debe tener número, id, título, título corto, tipo `operative` o `scenic`, y estado habilitado;
   - los números deben coincidir con la barra inferior.

5. Añadir contrato mínimo con el orquestador:
   - emitir `CYBERSHOW_STATUS READY` al terminar la inicialización;
   - emitir `CYBERSHOW_STATUS RUNNING` al empezar ejecución;
   - emitir `CYBERSHOW_SCREEN <n> <id>` al cambiar de pantalla;
   - emitir `CYBERSHOW_STATUS ERROR <code>` si hay un error relevante.

6. Añadir o adaptar logging interno con formato común.

7. No introducir nuevas dependencias salvo que sean estrictamente necesarias.

8. Mantener el proyecto compilable después de cada bloque de cambios.

9. Al terminar, entrega un resumen con:
   - archivos modificados;
   - comportamiento implementado;
   - excepciones o dudas;
   - pasos manuales pendientes.

Restricciones:

- No reescribir toda la aplicación si no es necesario.
- No cambiar la lógica de negocio salvo que sea imprescindible para la integración.
- No eliminar pantallas existentes sin confirmación.
- No ocultar errores de compilación.
- No usar atajos de teclado distintos al estándar salvo excepción documentada.
