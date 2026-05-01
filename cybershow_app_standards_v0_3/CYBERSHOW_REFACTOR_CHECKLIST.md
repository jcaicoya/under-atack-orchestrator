# Cybershow — Checklist de refactorización por aplicación

Usar esta lista para revisar cada aplicación Qt existente o nueva.

## 1. Documentación

- [ ] Existe `APP_SPEC.md` o equivalente para la app.
- [ ] Se han leído `QT_APP_LOOK_AND_FEEL.md` y `CYBERSHOW_APP_CONVENTIONS.md`.
- [ ] Se han documentado excepciones específicas de la app.

## 2. CLI y modos

- [ ] Sin argumentos equivale a `--configure`.
- [ ] `--configure` muestra Setup.
- [ ] `--design` arranca directamente en ejecución.
- [ ] `--show` arranca directamente en ejecución.
- [ ] Setup es inaccesible en `--design`/`--show`.
- [ ] Parámetros incompatibles producen error claro.
- [ ] Argumentos desconocidos producen error claro.
- [ ] `--fullscreen` / `--windowed` revisados.
- [ ] `--screen <index>` revisado o reservado.
- [ ] `--config <path>` revisado o reservado.
- [ ] `--profile <name>` revisado o reservado.

## 3. Navegación

- [ ] Desde Setup: Intro inicia show.
- [ ] Desde Setup: Espacio inicia show.
- [ ] Desde Setup: Flecha derecha inicia show.
- [ ] Desde Setup: `1` inicia show.
- [ ] Desde Setup: click en botón primario inicia show.
- [ ] Durante ejecución: flecha derecha avanza.
- [ ] Durante ejecución: flecha izquierda retrocede.
- [ ] Durante ejecución: números 1-9 van a pantalla correspondiente.
- [ ] Durante ejecución: click en barra inferior cambia pantalla.
- [ ] `Esc` vuelve a Setup solo en `--configure`.
- [ ] `Esc` no hace nada en `--show`/`--design`.
- [ ] No hay navegación circular por defecto.
- [ ] Se han eliminado atajos por letra para navegación principal.
- [ ] Los shortcuts no interfieren con campos editables.

## 4. Look & feel

- [ ] Fondo común aplicado.
- [ ] Setup con tarjeta central.
- [ ] Setup sin QR fijo.
- [ ] Setup sin mascota lateral fija.
- [ ] Botón primario común.
- [ ] Paneles comunes aplicados.
- [ ] Barra inferior común aplicada.
- [ ] Paleta común aplicada.
- [ ] Estados con colores normalizados.
- [ ] Textos de operador en español.

## 5. Pantallas

- [ ] Cada pantalla tiene número.
- [ ] Cada pantalla tiene id.
- [ ] Cada pantalla tiene título largo.
- [ ] Cada pantalla tiene título corto.
- [ ] Cada pantalla está clasificada como `operative` o `scenic`.
- [ ] Los números coinciden con la barra inferior.
- [ ] Pantallas deshabilitadas se muestran correctamente o no aparecen.

## 6. Orquestador

- [ ] Emite `CYBERSHOW_STATUS READY` al inicializar.
- [ ] Emite `CYBERSHOW_STATUS RUNNING` al entrar en ejecución.
- [ ] Emite `CYBERSHOW_SCREEN <n> <id>` al cambiar de pantalla.
- [ ] Emite `CYBERSHOW_STATUS ERROR <code>` ante error relevante.
- [ ] stdout no está contaminado con texto decorativo si se usa para orquestación.

## 7. Logging y configuración

- [ ] Hay logging interno con formato común o adaptación documentada.
- [ ] Configuración persistente revisada.
- [ ] `--config` contemplado o documentado como pendiente.
- [ ] `--profile demo/live/dev` contemplado o documentado como pendiente.
- [ ] No se guardan secretos reales en repositorio.

## 8. Seguridad escénica

- [ ] No se muestran datos personales reales por accidente.
- [ ] Modo demo usa datos simulados/controlados.
- [ ] Datos sensibles sanitizados antes de mostrarse.
- [ ] Acciones peligrosas requieren confirmación o están bloqueadas en show.

## 9. Verificación final

- [ ] Compila.
- [ ] Arranca sin argumentos.
- [ ] Arranca con `--configure`.
- [ ] Arranca con `--show`.
- [ ] Arranca con `--design`.
- [ ] Navegación probada con teclado.
- [ ] Navegación probada con click.
- [ ] Pantalla completa probada si aplica.
- [ ] Probada en portátil de desarrollo.
- [ ] Pendiente/probada en equipo de ensayo/backup.
