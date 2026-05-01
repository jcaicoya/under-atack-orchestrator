# Cybershow App Standards v0.3

Este paquete contiene la guía y los componentes base para unificar las aplicaciones Qt del Cybershow.

## Documentos principales

- `QT_APP_LOOK_AND_FEEL.md`  
  Guía visual: fondo común, setup, pantallas operativas, pantallas escénicas, colores, componentes y estilo.

- `CYBERSHOW_APP_CONVENTIONS.md`  
  Convenciones de comportamiento: navegación, CLI, modos de arranque, estados, logging, configuración y contrato con el orquestador.

- `prompts/AI_REFACTOR_PROMPT.md`  
  Prompt base para pedir a Claude, Codex o Gemini que refactorice una aplicación existente siguiendo el estándar.

- `templates/APP_SPEC_TEMPLATE.md`  
  Plantilla para crear instrucciones específicas de una aplicación.

## Documentos por aplicación

- `apps/ATAQUE_INICIAL_VISUAL_FIXES.md`
- `apps/PUBLIC_WIFI_VISUAL_FIXES.md`
- `apps/QR_CONTROLLER_VISUAL_FIXES.md`

Estos archivos describen ajustes visuales concretos detectados en las aplicaciones actuales.

## Código Qt reutilizable

Carpeta `ui/`:

- `CyberBackgroundWidget`
- `CyberTheme`
- `BottomNavBar`
- `CyberPanel`
- `MetricCard`
- `AlertBanner`
- ejemplos de setup y runtime

Carpeta `common/`:

- `CyberAppMode`: parser CLI común
- `CyberNavigationController`: navegación común por teclado
- `ScreenDefinition`: metadatos comunes de pantallas
- `CyberOrchestratorProtocol`: emisión mínima de estado por stdout

## Cómo usarlo con una app existente

1. Copiar este paquete o enlazar sus documentos en el repositorio de la app.
2. Crear un `APP_SPEC.md` propio a partir de `templates/APP_SPEC_TEMPLATE.md`.
3. Abrir la app con Claude/Codex/Gemini.
4. Usar el prompt `prompts/AI_REFACTOR_PROMPT.md`.
5. Pedir refactorización incremental, compilando después de cada bloque.

## Orden recomendado de refactorización

1. CLI común y modos de arranque.
2. Navegación común.
3. Barra inferior común.
4. Fondo y tema visual común.
5. Pantallas operativas/escénicas normalizadas.
6. Protocolo mínimo con orquestador.
7. Logging/configuración común.
8. Ajustes específicos de cada app.
