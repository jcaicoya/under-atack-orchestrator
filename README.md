# BAJO ATAQUE — Orchestrator

Centro de control del show de ciberseguridad en vivo **Bajo Ataque**. Lanza, supervisa y coordina aplicaciones del show, reproducción de vídeo y la pantalla de escenario/proyector desde un único panel de operador.

## Qué es

El orchestrator no es un simple lanzador. Es la cabina de control del espectáculo:

- coordina aplicaciones externas del show
- gestiona reproducción de vídeo
- controla una ventana de escenario en pantalla secundaria
- organiza escenas para configuración, ensayo y show

## Modos de operación

| Modo | Propósito |
|---|---|
| `CONFIGURAR` | Preparar ADB, apps Qt, apps Android y media |
| `ENSAYO` | Reordenar rundown, lanzar apps y reproducir vídeos |
| `SHOW` | Ejecutar escenas en orden durante la actuación |

## Arquitectura

### Ventana principal

`MainWindow` usa un `QStackedWidget` con cuatro pantallas:

| Índice | Pantalla | Descripción |
|---|---|---|
| 0 | `ModeSelectorScreen` | Selector inicial de modo |
| 1 | `ConfigureModeScreen` | Modo CONFIGURAR |
| 2 | `RehearsalModeScreen` | Modo ENSAYO |
| 3 | `ShowModeScreen` | Modo SHOW |

### Componentes principales

- `StageWindow`: ventana fullscreen sin bordes para proyector/pantalla secundaria.
- `AppManager`: ciclo de vida de ejecutables Qt externos vía `QProcess`.
- `AdbManager`: wrapper de `adb.exe`.
- `AndroidManager`: ciclo de vida de apps Android vía ADB.
- `MediaManager`: reproducción de vídeo/audio.
- `RundownConfig`: lista ordenada de escenas.
- `Logger`: mensajes de log en panel.

## Stack tecnológico

| Capa | Tecnología |
|---|---|
| Lenguaje | C++23 |
| Framework | Qt 6.7.3 |
| Build | CMake |
| Compilador | MSVC |
| Plataforma | Windows |
| Vídeo | `QMediaPlayer` + `QVideoWidget` |
| Apps externas | ejecutables Windows autocontenidos |
| Configuración | JSON en `config/` |

## Estructura del repositorio

```text
orchestrator/
├── .claude/CLAUDE.md
├── CODEX.md
├── README.md
├── RUNBOOK.md
├── NEXT_STEPS.md
├── CMakeLists.txt
├── package-release.ps1
├── config/
├── apps/
├── media/
├── resources/
└── src/
```

## Estado actual

- Ventana de operador fullscreen por defecto.
- Selector de modos y pantallas completas para CONFIGURAR, ENSAYO y SHOW.
- Gestión de apps Qt externas.
- Gestión de apps Android por ADB.
- Reproducción multimedia.
- Ventana de escenario en segunda pantalla.
- Configuración persistida en JSON.

## Reglas de diseño

- Todas las rutas deben ser relativas a la raíz del paquete.
- Cada app externa debe ser autocontenida en su carpeta dentro de `apps/`.
- La UI visible para operador está en español.
- Código, identificadores, claves JSON y comentarios en inglés.
- Primar robustez de show sobre eficiencia o sofisticación técnica.
