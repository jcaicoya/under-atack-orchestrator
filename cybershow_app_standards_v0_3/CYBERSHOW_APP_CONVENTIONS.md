# Cybershow — Convenciones comunes para aplicaciones Qt

Versión: 0.3  
Estado: estándar base para refactorizar aplicaciones existentes y crear aplicaciones nuevas.

Este documento define el comportamiento común que deben implementar todas las aplicaciones Qt del Cybershow. La guía visual está en `QT_APP_LOOK_AND_FEEL.md`; este documento se centra en operación, navegación, argumentos de arranque, estados, configuración, logging y contrato con el orquestador.

---

## 1. Objetivo

Todas las aplicaciones deben comportarse como partes de un único sistema. El operador debe poder manejarlas con la misma lógica aunque cada aplicación tenga pantallas y propósito diferentes.

Principios:

- misma navegación por teclado;
- mismos argumentos de arranque;
- mismo concepto de modo configuración y modo show;
- mismo estilo de barra inferior;
- mismos estados de aplicación;
- mismo formato mínimo de logs y mensajes al orquestador;
- setup inaccesible durante show si se arranca con `--show` o `--design`.

---

## 2. Modos de arranque

Todas las aplicaciones deben aceptar estos argumentos:

| Argumento | Comportamiento |
|---|---|
| Sin argumentos | Equivale a `--configure` |
| `--configure` | Arranca mostrando Setup. Setup es accesible durante la ejecución mediante `Esc`. |
| `--design` | Arranca directamente en la primera pantalla de ejecución. Setup no aparece y no es accesible. |
| `--show` | Igual que `--design`, pensado para ejecución real desde el orquestador. |

`--design` y `--show` son equivalentes funcionalmente. Internamente pueden mapearse al mismo modo: `LaunchMode::Show`.

### Reglas obligatorias

- En `--configure`, la pantalla inicial es Setup.
- En `--configure`, desde ejecución, `Esc` vuelve a Setup.
- En `--show`/`--design`, la pantalla inicial es la primera pantalla de ejecución.
- En `--show`/`--design`, Setup no debe poder alcanzarse por teclado, botones, navegación interna ni código accidental.
- Si se pasan varios modos incompatibles, la aplicación debe mostrar error y salir.
- Si se pasa un argumento desconocido, la aplicación debe mostrar error y salir.

---

## 3. Argumentos CLI recomendados

Además de los modos de arranque, todas las aplicaciones deberían reservar estos argumentos, aunque alguna no los implemente todavía:

| Argumento | Descripción |
|---|---|
| `--fullscreen` | Arranca en pantalla completa. |
| `--windowed` | Arranca en ventana. |
| `--screen <index>` | Selecciona la pantalla/monitor donde abrir. |
| `--config <path>` | Carga configuración desde una ruta concreta. |
| `--profile <name>` | Selecciona perfil: por ejemplo `demo`, `live`, `dev`. |
| `--debug` | Activa ayudas de depuración solo en modo configuración. |

Ejemplos:

```bash
public-wifi.exe --configure --windowed --profile dev
public-wifi.exe --show --fullscreen --screen 1 --profile live
qr-controller.exe --design --windowed --profile demo
```

---

## 4. Modos de funcionamiento

No confundir modo de arranque con modo de funcionamiento.

### Modo de arranque

Define si aparece Setup:

- `--configure`
- `--show` / `--design`

### Modo de funcionamiento

Define si la app usa datos simulados o reales:

| Modo | Uso |
|---|---|
| `demo` | Datos simulados/controlados. Seguro para pruebas y demostraciones. |
| `live` | Datos reales del entorno de ensayo/show. |
| `dev` | Modo de desarrollo con ayudas extra. |

La app puede seleccionar el modo de funcionamiento mediante Setup, configuración persistente o `--profile`.

---

## 5. Navegación común

### Desde Setup

Cuando el foco no está dentro de un campo editable:

| Tecla / acción | Resultado |
|---|---|
| `Intro` | Iniciar show: ir a la primera pantalla de ejecución |
| `Espacio` | Iniciar show |
| `Flecha derecha` | Iniciar show |
| `1` | Iniciar show |
| Click en botón primario | Iniciar show |

Si el foco está en un `QLineEdit`, `QTextEdit`, `QPlainTextEdit`, `QSpinBox`, `QComboBox` editable u otro control de edición, los shortcuts globales no deben interferir con la edición.

### Durante ejecución

| Tecla / acción | Resultado |
|---|---|
| `Flecha derecha` | Siguiente pantalla |
| `Flecha izquierda` | Pantalla anterior |
| `1`-`9` | Ir directamente a la pantalla correspondiente |
| Click en barra inferior | Ir a la pantalla correspondiente |
| `Esc` en `--configure` | Volver a Setup |
| `Esc` en `--show`/`--design` | No hacer nada |
| `Alt+F4` | Cerrar la aplicación usando el comportamiento estándar del sistema |

### Reglas

- No usar atajos por letra para navegación principal.
- No usar `Esc` para cerrar la aplicación.
- No usar `Q`, `Ctrl+Q` o similares para cerrar durante operación normal.
- La navegación no debe ser circular por defecto.
- Flecha derecha en la última pantalla mantiene la última pantalla.
- Flecha izquierda en la primera pantalla mantiene la primera pantalla.
- Los números deben coincidir siempre con la barra inferior.

---

## 6. Atajos opcionales solo en configuración

Estos atajos son recomendados para desarrollo/ensayo, pero deben estar desactivados en `--show`/`--design` salvo decisión explícita:

| Atajo | Resultado |
|---|---|
| `F11` | Alternar pantalla completa. Puede permitirse también en show si es útil. |
| `Ctrl+D` | Mostrar/ocultar overlay de debug. Solo en configuración. |
| `Ctrl+R` | Reiniciar pantalla actual. Solo en configuración. |

---

## 7. Barra inferior común

Todas las aplicaciones con varias pantallas deben usar una barra inferior común.

Reglas:

- misma posición: parte inferior;
- misma altura aproximada;
- mismos márgenes;
- número visible en cada botón;
- pantalla activa destacada;
- pantallas deshabilitadas en gris;
- click equivalente a pulsar el número;
- nombres cortos;
- no usar letras como atajos principales.

Ejemplo:

```text
[1 · Principal] [2 · Dispositivos] [3 · Mapa] [4 · Riesgo] [5 · Cifrado]
```

En pantallas escénicas puras se permite hacerla más discreta, pero no debería desaparecer salvo que haya una razón justificada.

---

## 8. Tipos de pantalla

Cada pantalla debe tener metadatos mínimos:

```cpp
struct ScreenDefinition {
    int number;
    QString id;
    QString title;
    QString shortTitle;
    ScreenKind kind; // Operative or Scenic
    bool enabled;
};
```

### Pantallas operativas

Para operador, datos, logs, dispositivos, análisis técnico.

Características:

- layout tipo dashboard;
- título superior izquierdo;
- paneles de datos;
- barra inferior visible;
- densidad media o alta;
- texto técnico y logs monoespaciados.

### Pantallas escénicas

Para momentos visibles al público o de alto impacto.

Características:

- composición centrada;
- pocos elementos;
- mensajes grandes;
- números o visualizaciones protagonistas;
- barra inferior discreta;
- misma paleta y fondo común.

---

## 9. Estados comunes

Todas las apps deben usar una terminología común de estados:

| Estado | Uso visual recomendado |
|---|---|
| `DISABLED` / `DESACTIVADO` | Gris |
| `PREPARING` / `PREPARANDO` | Ámbar o azul tenue |
| `READY` / `LISTO` | Verde |
| `RUNNING` / `EN EJECUCIÓN` | Azul/cian |
| `WARNING` / `ADVERTENCIA` | Ámbar |
| `ERROR` | Rojo |
| `FINISHED` / `FINALIZADO` | Verde o blanco según contexto |

Las etiquetas visibles al operador deberían estar en español. Los mensajes internos pueden usar inglés si son logs o protocolo.

---

## 10. Contrato mínimo con el orquestador

Inicialmente, si las aplicaciones se lanzan con `QProcess`, basta con emitir líneas normalizadas por stdout.

### Mensajes de estado

```text
CYBERSHOW_STATUS READY
CYBERSHOW_STATUS RUNNING
CYBERSHOW_STATUS ERROR <code>
CYBERSHOW_STATUS FINISHED
```

### Mensajes de pantalla

```text
CYBERSHOW_SCREEN 1 principal
CYBERSHOW_SCREEN 3 mapa
```

### Mensajes de log relevantes

```text
CYBERSHOW_LOG INFO network Server started on 192.168.1.10:8765
CYBERSHOW_LOG WARNING device No selected device
CYBERSHOW_LOG ERROR config Missing required token
```

### Reglas

- Estos mensajes deben escribirse en una línea completa.
- No deben mezclarse con texto decorativo.
- Si stdout se usa para el orquestador, el log humano detallado debe ir a archivo o stderr.
- El orquestador no debe depender de textos visuales de pantalla.

---

## 11. Logging interno

Todas las apps deberían guardar logs con formato común:

```text
timestamp | app | launchMode | profile | level | component | message
```

Ejemplo:

```text
2026-05-01T12:30:10.123 | public-wifi | show | live | INFO | navigation | screen=3 id=mapa
```

Ruta recomendada:

```text
logs/
  ataque-inicial.log
  public-wifi.log
  qr-controller.log
```

---

## 12. Configuración persistente

Estructura recomendada:

```text
config/
  ataque-inicial.json
  public-wifi.json
  qr-controller.json
```

Estructura base sugerida:

```json
{
  "profile": "demo",
  "window": {
    "fullscreen": false,
    "screen": 0,
    "width": 1280,
    "height": 720
  },
  "network": {},
  "show": {}
}
```

Reglas:

- Setup puede modificar la configuración.
- `--config <path>` debe permitir cargar un archivo alternativo.
- `--profile` puede seleccionar perfiles como `demo`, `live` o `dev`.
- Nunca guardar secretos reales en repositorio.

---

## 13. Seguridad escénica

Reglas comunes:

- No mostrar datos personales reales en pantalla de público salvo que sean ficticios, consentidos o controlados.
- En modo demo, usar datos preparados.
- Los datos sensibles deben pasar por una capa de sanitización antes de mostrarse.
- Acciones destructivas o externas deben requerir confirmación en configuración y estar bloqueadas o controladas en show.
- En caso de error, mostrar un mensaje útil al operador, no una excepción cruda al público.

---

## 14. Criterio de refactorización

Al adaptar una app existente:

1. Añadir parser común de CLI.
2. Implementar `LaunchMode` y bloquear Setup en show/design.
3. Sustituir navegación propia por navegación común.
4. Sustituir barra inferior por componente común.
5. Aplicar fondo, paneles, colores y tipografía de la guía visual.
6. Normalizar nombres de pantallas y números.
7. Añadir emisión mínima de estado para el orquestador.
8. Añadir logs con formato común.
9. Revisar que los campos editables no capturen shortcuts globales indebidamente.
10. Documentar excepciones específicas de la app en su archivo particular.
