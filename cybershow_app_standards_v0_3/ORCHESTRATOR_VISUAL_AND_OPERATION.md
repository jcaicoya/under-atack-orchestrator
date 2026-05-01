# Orquestador Cybershow — diseño visual y operación

**Estado:** versión 0.1  
**Ámbito:** aplicación orquestadora / centro de control  
**Relación con el estándar común:** complementa `CYBERSHOW_APP_CONVENTIONS.md` y `QT_APP_LOOK_AND_FEEL.md`.

---

## 1. Propósito del documento

Este documento define cómo debe comportarse y verse la aplicación **orquestadora** del Cybershow.

El orquestador no es una aplicación escénica normal. Su objetivo no es presentar una secuencia de pantallas al público, sino permitir al operador elegir el modo de trabajo y lanzar/controlar las aplicaciones del show.

Por tanto, el orquestador debe compartir la identidad visual común del proyecto, pero **no debe forzarse a usar la misma estructura de navegación que las apps de show**.

---

## 2. Decisión principal

El orquestador es una **aplicación Cybershow especial**.

Debe compartir con el resto de aplicaciones:

- fondo común Qt;
- paleta de colores;
- tipografía;
- estilo de botones;
- estilo de tarjetas/paneles;
- estados visuales comunes;
- idioma y nomenclatura coherentes;
- reglas generales de operación segura;
- integración con `QProcess` para lanzar apps;
- convenciones de logging/configuración cuando apliquen.

Pero **no necesita compartir**:

- pantalla de setup estándar;
- barra inferior de navegación por escenas;
- navegación por flechas entre pantallas escénicas;
- números 1-9 para cambiar de escena;
- `Esc` como retorno a setup.

El patrón propio del orquestador es:

```text
Selector de modo → Pantalla específica del modo elegido
```

---

## 3. Estructura conceptual

La estructura prevista del orquestador es:

```text
Orquestador
├── ModeSelectorScreen
│   ├── Configurar
│   ├── Diseño
│   └── Show
│
├── ConfigureModeScreen
│   └── Lista/control de apps lanzadas con --configure
│
├── DesignModeScreen
│   └── Lista/control de apps lanzadas con --design
│
└── ShowModeScreen
    └── Control seguro de apps lanzadas con --show
```

En la versión actual, si solo existe un modo y una pantalla, la estructura mínima será:

```text
Orquestador
├── ModeSelectorScreen
└── ConfigureModeScreen
```

Los modos `Diseño` y `Show` pueden aparecer como tarjetas deshabilitadas o marcadas como “próximamente”, según convenga durante el desarrollo.

---

## 4. Pantalla inicial: selector de modo

El orquestador no debe arrancar en una pantalla de setup clásica. Debe arrancar en una pantalla de selección de modo.

Nombre recomendado de clase:

```cpp
ModeSelectorScreen
```

Nombre visible recomendado:

```text
CYBERSHOW
Centro de control
```

Estructura visual recomendada:

```text
┌──────────────────────────────────────────────────────────────┐
│                         CYBERSHOW                            │
│                    Centro de control                         │
│                                                              │
│        ┌────────────────┐ ┌────────────────┐ ┌─────────────┐ │
│        │   CONFIGURAR   │ │    DISEÑO      │ │    SHOW     │ │
│        │ Preparar apps  │ │ Ensayo técnico │ │ Actuación   │ │
│        └────────────────┘ └────────────────┘ └─────────────┘ │
│                                                              │
│              Estado general / perfil / ruta del show         │
└──────────────────────────────────────────────────────────────┘
```

### Tarjetas de modo

Cada modo debe representarse como una tarjeta grande y clara.

Cada tarjeta debe incluir:

- nombre del modo;
- descripción breve;
- estado: disponible, deshabilitado, próximamente, error;
- indicación visual de selección/foco;
- posibilidad de activación mediante click o teclado.

Ejemplo:

```text
CONFIGURAR
Preparar aplicaciones, ajustar parámetros y probar conexiones.
Estado: disponible
```

```text
DISEÑO
Ensayo técnico sin pantallas de setup.
Estado: próximamente
```

```text
SHOW
Modo seguro para actuación real.
Estado: próximamente
```

---

## 5. Modos del orquestador

### 5.1 Configurar

Modo pensado para preparación técnica y pruebas.

Debe lanzar las aplicaciones con:

```text
--configure
```

Características:

- permite abrir cada app en su pantalla de configuración;
- permite probar arranque/parada;
- permite comprobar rutas, puertos, perfiles y estado;
- puede mostrar más información técnica;
- puede permitir acciones de reset o prueba;
- puede usar datos demo o live según perfil seleccionado.

Nombre recomendado de clase:

```cpp
ConfigureModeScreen
```

### 5.2 Diseño

Modo pensado para ensayo técnico del flujo del show.

Debe lanzar las aplicaciones con:

```text
--design
```

Características previstas:

- las apps no muestran setup;
- se comportan como en ejecución;
- puede haber más controles que en show real;
- útil para probar tiempos, pantallas y transiciones;
- no debe exponer acciones destructivas sin confirmación.

Nombre recomendado de clase:

```cpp
DesignModeScreen
```

### 5.3 Show

Modo pensado para actuación real.

Debe lanzar las aplicaciones con:

```text
--show
```

Características previstas:

- interfaz más limpia y segura;
- menos botones técnicos;
- acciones peligrosas bloqueadas o protegidas;
- prioridad a estado general y control rápido;
- no debe abrir setups;
- no debe mostrar información de debug salvo error crítico.

Nombre recomendado de clase:

```cpp
ShowModeScreen
```

---

## 6. Navegación del orquestador

La navegación del orquestador es diferente de la navegación de las apps de show.

### 6.1 En `ModeSelectorScreen`

Shortcuts recomendados:

```text
1                seleccionar/abrir Configurar
2                seleccionar/abrir Diseño, si está disponible
3                seleccionar/abrir Show, si está disponible
Flecha izquierda cambiar selección al modo anterior
Flecha derecha   cambiar selección al modo siguiente
Intro            abrir modo seleccionado
Espacio          abrir modo seleccionado
Click            abrir modo pulsado
Alt+F4           salir de la aplicación
```

Si un modo está deshabilitado, no debe abrirse. Puede mostrarse un mensaje discreto de estado.

### 6.2 Dentro de una pantalla de modo

Shortcuts recomendados:

```text
Esc              volver al selector de modo
Alt+F4           salir de la aplicación
```

Otros atajos internos solo deben añadirse si son necesarios y deben documentarse en la propia pantalla.

### 6.3 Reglas importantes

- `Esc` en el orquestador vuelve al selector de modo, no a un setup.
- El orquestador no usa navegación por escenas con flechas izquierda/derecha.
- El orquestador no necesita barra inferior de escenas.
- Los números `1`, `2`, `3` se reservan para los modos principales en el selector.
- No se deben usar atajos por letras para acciones críticas.

---

## 7. Pantallas de modo

Las pantallas de modo deben usar layout tipo dashboard operativo.

Estructura recomendada para `ConfigureModeScreen`:

```text
┌──────────────────────────────────────────────────────────────┐
│ Configurar                                           Estado  │
│                                                              │
│ ┌──────────────────────────────────────────────────────────┐ │
│ │ Aplicaciones                                             │ │
│ │                                                          │ │
│ │ QR Controller       detenido   [Configurar] [Parar]      │ │
│ │ Public Wi-Fi         detenido   [Configurar] [Parar]      │ │
│ │ Ataque inicial       detenido   [Configurar] [Parar]      │ │
│ └──────────────────────────────────────────────────────────┘ │
│                                                              │
│ ┌──────────────────────┐ ┌────────────────────────────────┐ │
│ │ Estado general        │ │ Log / eventos recientes        │ │
│ └──────────────────────┘ └────────────────────────────────┘ │
│                                                              │
│ Esc: volver al selector                                      │
└──────────────────────────────────────────────────────────────┘
```

La lista de aplicaciones debe mostrar, como mínimo:

- nombre de la app;
- estado del proceso;
- modo de lanzamiento;
- acción principal;
- acción de parada si procede;
- último mensaje o error.

Estados recomendados:

```text
DETENIDA
LANZANDO
LISTA
EJECUTÁNDOSE
ERROR
FINALIZADA
```

---

## 8. Integración con aplicaciones del show

El orquestador debe lanzar las apps mediante `QProcess` usando los argumentos comunes definidos en `CYBERSHOW_APP_CONVENTIONS.md`.

Ejemplos:

```text
QRController.exe --configure
QRController.exe --design
QRController.exe --show
```

Cuando se implementen parámetros adicionales comunes, el orquestador podrá usar:

```text
--fullscreen
--windowed
--screen <index>
--config <path>
--profile <name>
```

Ejemplo futuro:

```text
PublicWifi.exe --show --fullscreen --screen 1 --config config/public-wifi.json --profile live
```

---

## 9. Manifiesto de aplicación

Cada app controlada por el orquestador debería tener, a medio plazo, una definición declarativa.

Nombre sugerido:

```text
app-manifest.json
```

Ejemplo:

```json
{
  "id": "qr-controller",
  "name": "QR Controller",
  "executable": "QRController.exe",
  "workingDirectory": "apps/qr-controller",
  "supportsConfigure": true,
  "supportsDesign": true,
  "supportsShow": true,
  "defaultProfile": "demo",
  "screens": [
    { "number": 1, "id": "qr", "title": "QR público" },
    { "number": 2, "id": "web", "title": "Web oficial" },
    { "number": 3, "id": "impact", "title": "Análisis de impacto" }
  ]
}
```

En la primera versión, esta información puede estar hardcodeada, pero la interfaz debe diseñarse pensando en que acabará viniendo de manifiestos.

---

## 10. Diferencia entre modo del orquestador y modo de una app

Es importante no confundir estos dos niveles.

### Modo del orquestador

Define cómo está trabajando el centro de control:

```text
Configurar
Diseño
Show
```

### Argumento de lanzamiento de una app

Define cómo se abre una aplicación concreta:

```text
--configure
--design
--show
```

Relación recomendada:

```text
Orquestador en Configurar → lanza apps con --configure
Orquestador en Diseño     → lanza apps con --design
Orquestador en Show       → lanza apps con --show
```

---

## 11. Estética visual

El orquestador debe usar el mismo sistema visual que el resto del Cybershow:

- fondo común `CyberBackgroundWidget`;
- tarjetas oscuras;
- bordes sutiles;
- acento azul/cian para selección principal;
- verde para listo/ok;
- ámbar para advertencias;
- rojo para error;
- gris para deshabilitado;
- tipografía clara y legible;
- nada de elementos decorativos que compitan con la operación.

El orquestador debe sentirse como el **centro de mando** del sistema, no como una app escénica ni como una pantalla de setup convencional.

---

## 12. Reglas de seguridad operacional

En `ConfigureModeScreen` pueden existir acciones técnicas, pero deben ser claras.

En `ShowModeScreen`, cuando se implemente:

- evitar botones destructivos;
- evitar cierres accidentales;
- evitar resets sin confirmación;
- mostrar solo información necesaria;
- priorizar estado general;
- no permitir abrir setups;
- no exponer debug salvo error crítico.

---

## 13. Implementación mínima recomendada ahora

Para la versión actual, implementar solo:

```text
ModeSelectorScreen
ConfigureModeScreen
```

Con `Diseño` y `Show` como opciones deshabilitadas o previstas.

### Flujo actual

```text
Arranque del orquestador
        ↓
ModeSelectorScreen
        ↓ click / Intro / 1
ConfigureModeScreen
        ↓ Esc
ModeSelectorScreen
```

### No implementar todavía si no hace falta

- navegación entre escenas;
- barra inferior de pantallas;
- manifiestos JSON;
- protocolo avanzado con apps;
- control remoto de pantalla concreta;
- modo Show completo;
- modo Diseño completo.

Pero la arquitectura debe dejar espacio para añadirlo.

---

## 14. Checklist para refactorizar el orquestador

Al adaptar el orquestador al estándar Cybershow, comprobar:

- [ ] Usa fondo común Qt.
- [ ] Usa paleta y botones comunes.
- [ ] No usa pantalla de setup estándar.
- [ ] Tiene `ModeSelectorScreen`.
- [ ] El modo Configurar está disponible.
- [ ] Los modos Diseño y Show están previstos aunque estén deshabilitados.
- [ ] `1`, `2`, `3` seleccionan modos en el selector.
- [ ] `Intro` y `Espacio` abren el modo seleccionado.
- [ ] Flechas izquierda/derecha cambian selección en el selector.
- [ ] `Esc` desde una pantalla de modo vuelve al selector.
- [ ] `Alt+F4` cierra la aplicación.
- [ ] No hay navegación por escenas ni barra inferior de apps de show.
- [ ] La pantalla Configurar lanza apps con `--configure`.
- [ ] El diseño permite añadir más adelante `--design` y `--show`.
- [ ] Los estados de procesos usan nomenclatura común.
- [ ] Los errores son visibles y comprensibles para el operador.

---

## 15. Prompt sugerido para Claude/Codex/Gemini

```text
Lee primero los documentos comunes del paquete Cybershow:

- CYBERSHOW_APP_CONVENTIONS.md
- QT_APP_LOOK_AND_FEEL.md
- ORCHESTRATOR_VISUAL_AND_OPERATION.md

Esta aplicación es el orquestador, no una app escénica normal.
No debe implementar pantalla de setup estándar ni navegación por escenas.
Debe implementar un selector de modo inicial y una pantalla específica para el modo Configurar.

Objetivo actual:
- aplicar la estética visual común;
- crear o adaptar ModeSelectorScreen;
- crear o adaptar ConfigureModeScreen;
- dejar Diseño y Show previstos, pero pueden estar deshabilitados;
- lanzar apps con --configure desde el modo Configurar;
- usar navegación del orquestador: 1/2/3, flechas, Intro, Espacio, Esc y Alt+F4;
- no introducir atajos por letras ni barra inferior de escenas.

Mantén la lógica funcional existente siempre que sea posible.
Si una parte del orquestador aún no existe, prepara la estructura mínima sin sobreingeniería.
```
