# Guía visual de aplicaciones Qt — Cybershow

**Versión:** 0.2  
**Estado:** guía viva. Incluye setup y primeras reglas para pantallas en ejecución.  
**Pendiente:** revisar esta guía tras aplicar los cambios a las tres aplicaciones y probarlas en portátil de ensayo/proyección.

---

## 1. Objetivo

Todas las aplicaciones Qt del show deben parecer parte de una misma familia visual, aunque cada una tenga personalidad propia.

La estética común debe ser:

- oscura;
- técnica;
- cyber;
- sobria;
- legible en portátil y, cuando proceda, en proyección;
- operable con teclado, números, atajos y botones inferiores;
- coherente entre setup, ejecución, pantallas escénicas y pantallas operativas.

No se busca que todas las pantallas sean idénticas. Se busca que compartan reglas de fondo, color, tipografía, navegación y componentes.

---

## 2. Principios generales

### 2.1. Coherencia antes que decoración

El diseño debe ayudar a operar el show. Los elementos visuales deben reforzar la sensación tecnológica, pero no distraer ni impedir leer.

### 2.2. Fondo común

Todas las apps deben usar un fondo Qt generado por código, no una imagen fija. El fondo debe actuar como una base común del sistema.

### 2.3. Dos familias de pantalla

Las pantallas en ejecución se dividen en dos familias:

1. **Pantallas operativas**: dashboards técnicos para operador, logs, listas, mapas, dispositivos, estado y análisis.
2. **Pantallas escénicas**: pantallas con impacto visual, pocos elementos, mensajes grandes, QR, radar, resultados o métricas principales.

Ambas comparten fondo, paleta, tipografía, navegación inferior y reglas de estado.

### 2.4. Español como idioma principal

La interfaz dirigida al operador o al público debe estar en español.

Se permite inglés en:

- logs simulados;
- nombres técnicos inevitables;
- payloads o datos generados por scripts;
- comandos o trazas de sistema cuando forman parte de la ficción escénica.

Ejemplos preferidos:

- `Configuración técnica` en vez de `Technical setup`.
- `Centro de control` en vez de `Command Center`.
- `Dispositivos + tráfico` en vez de `Devices + Raw Traffic`.
- `Perfil de riesgo` en vez de `Risk Profile`.
- `Análisis de cifrado` en vez de `Encryption Analysis`.

---

## 3. Fondo común Qt

### 3.1. Nombre interno

`Cyber Minimal Tech Background`

### 3.2. Descripción

Fondo negro profundo con degradado muy sutil, glows fríos de baja intensidad, retícula ligera y pequeños detalles tecnológicos en bordes, manteniendo la zona central limpia para paneles, tarjetas o contenido principal.

### 3.3. Capas visuales

Orden de pintado recomendado:

1. Base negro-azulada.
2. Degradado atmosférico.
3. Glows radiales muy difusos.
4. Retícula tenue.
5. Detalles geométricos en bordes.
6. Viñeta final.

### 3.4. Reglas

- El fondo no debe competir con el contenido.
- El centro debe quedar relativamente limpio.
- Los detalles se concentran en periferia y esquinas.
- En setup, el fondo debe ser más discreto.
- En pantallas escénicas puede usarse con algo más de intensidad, pero sin recargar.

---

## 4. Paleta común

### 4.1. Base

| Uso | Color recomendado |
|---|---|
| Fondo profundo | `#050608` |
| Fondo alternativo | `#080B10` |
| Panel | `#101318` |
| Panel elevado | `#151922` |
| Borde sutil | `#293241` |
| Borde activo | `#2EA8FF` |
| Texto principal | `#F2F5F8` |
| Texto secundario | `#8D96A3` |
| Texto técnico tenue | `#5F6B78` |

### 4.2. Acentos

| Uso | Color recomendado |
|---|---|
| Acción principal | azul eléctrico `#1688E8` |
| Estado OK | verde `#00FF55` |
| Información / enlace | cian `#00D1FF` |
| Aviso | ámbar `#FFB000` |
| Error / crítico | rojo `#FF3347` |
| Dato especial | violeta suave `#8B5CF6` |

### 4.3. Regla de color

- Azul: acción principal, foco activo, selección neutra.
- Verde: sistema correcto, live, conectado, detectado.
- Cian: información, red, enlaces, datos técnicos.
- Ámbar: atención, molestia, advertencia.
- Rojo: error, crítico, datos comprometidos, peligro.

No usar verde como botón principal salvo en una pantalla escénica específica donde el verde sea parte de la ficción. El botón principal estándar es azul.

---

## 5. Tipografía

### 5.1. Familias recomendadas

- Interfaz general: `Inter`, `Segoe UI`, `Arial`, sans-serif.
- Logs y terminal: `JetBrains Mono`, `Consolas`, `Courier New`, monospace.

### 5.2. Tamaños orientativos

| Elemento | Tamaño |
|---|---:|
| Título de pantalla | 24–32 px |
| Título escénico | 36–56 px |
| Subtítulo / modo | 12–16 px |
| Texto normal | 13–16 px |
| Botón inferior | 12–14 px |
| Log técnico | 11–14 px |
| Métrica grande | 48–88 px |

### 5.3. Mayúsculas

Usar mayúsculas para:

- títulos escénicos;
- estados importantes;
- etiquetas técnicas breves;
- alertas.

Evitar mayúsculas en bloques largos de lectura.

---

## 6. Pantallas de configuración/setup

### 6.1. Objetivo

La pantalla de setup es una pantalla técnica de preparación. No debe contener QR público ni elementos escénicos grandes.

### 6.2. Estructura

- Fondo común Qt.
- Tarjeta central de configuración.
- Título superior o centrado: nombre del módulo + `Configuración técnica`.
- Campos y parámetros agrupados.
- Bloque de estado.
- Botones secundarios si hacen falta.
- Botón primario `INICIAR SHOW` en la parte inferior de la tarjeta.

### 6.3. Reglas

- No incluir QR en setup.
- No colocar a Cuarzito como elemento lateral fijo.
- No dejar paneles pegados a la izquierda salvo necesidad explícita.
- Mantener consistencia de campos y botones.
- Mostrar el estado técnico de forma clara.

---

## 7. Pantallas en ejecución

## 7.1. Pantallas operativas

Referencia visual principal: Public Wi-Fi.

Se usan para:

- centro de control;
- logs;
- listas de dispositivos;
- tráfico;
- mapas;
- análisis técnico;
- estados detallados.

### Estructura recomendada

```text
┌────────────────────────────────────────────────────────────┐
│ Título de pantalla                                         │
│                                                            │
│ ┌──────────────────────────────┐ ┌───────────────────────┐ │
│ │ Zona principal                │ │ Panel auxiliar        │ │
│ │                              │ │ Estado / eventos      │ │
│ │                              │ │ logs / datos          │ │
│ └──────────────────────────────┘ └───────────────────────┘ │
│                                                            │
│ [1 · Principal] [2 · Dispositivos] [3 · Mapa] [...]        │
└────────────────────────────────────────────────────────────┘
```

### Reglas

- Título arriba a la izquierda.
- Paneles con borde tenue.
- Datos técnicos en monoespaciada.
- Navegación inferior fija.
- Mantener márgenes constantes.
- Evitar grandes elementos decorativos.
- Usar panel derecho solo si aporta estado, eventos o contexto.

## 7.2. Pantallas escénicas

Referencias: radar de Ataque Inicial, QR público, análisis de impacto.

Se usan para:

- QR de entrada;
- radar;
- resultados;
- impacto;
- votaciones;
- estados dramáticos;
- pantallas mostrables al público.

### Estructura recomendada

```text
┌────────────────────────────────────────────────────────────┐
│                                                            │
│                    TÍTULO ESCÉNICO                         │
│                     subtítulo / modo                       │
│                                                            │
│              elemento principal grande                     │
│              QR / radar / métrica / alerta                 │
│                                                            │
│ [1 · ...] [2 · ...] [3 · ...] [4 · ...]                    │
└────────────────────────────────────────────────────────────┘
```

### Reglas

- Pocos elementos.
- Mucho aire.
- Tipografía grande.
- Mensaje principal claro.
- Barra inferior discreta pero presente si hay navegación.
- Puede usar variantes de color por app, pero sin romper paleta.

---

## 8. Navegación inferior común

Todas las apps con varias pantallas deben usar una barra inferior común.

### 8.1. Características

- Posición fija abajo.
- Botones distribuidos horizontalmente.
- Cada botón muestra número + nombre.
- La pantalla activa se destaca con borde claro o azul/cian.
- Los botones inactivos son oscuros y discretos.
- Los botones deshabilitados reducen opacidad.

### 8.2. Formato recomendado

```text
[ 1 · Principal ] [ 2 · Dispositivos ] [ 3 · Mapa ] [ 4 · Riesgo ] [ 5 · Cifrado ]
```

### 8.3. Mapeo

Los botones deben corresponder a:

- números del teclado;
- flechas izquierda/derecha;
- atajos específicos si los hay.

La navegación debe ser igual entre apps siempre que sea posible.

---

## 9. Componentes comunes

### 9.1. CyberPanel

Panel oscuro reutilizable para dashboards, logs, mapas y listas.

Reglas:

- fondo `#101318` o similar;
- borde `#293241`;
- radio suave;
- título en blanco;
- contenido con márgenes internos;
- versión `critical` con borde rojo.

### 9.2. MetricCard

Tarjeta grande para pantallas escénicas o dashboards.

Contiene:

- etiqueta;
- valor grande;
- subtítulo;
- borde de color opcional;
- estado.

Usos:

- impacto;
- votos;
- riesgo;
- resultados;
- métricas de tráfico.

### 9.3. LogPanel

Panel monoespaciado para trazas.

Reglas:

- texto verde/cian para actividad normal;
- rojo para eventos críticos;
- amarillo para avisos;
- baja saturación si hay mucho texto.

### 9.4. AlertBanner

Banda de alerta para eventos importantes.

Estados:

- info;
- warning;
- critical;
- success.

Debe ser muy visible, pero no romper el layout salvo en pantallas escénicas.

---

## 10. Estado del sistema

Los estados deben ser consistentes.

Ejemplo:

```text
● Conexión móvil: activa
● Servidor local: 192.168.0.33:8765
● Modo: LIVE
● Público: preparado
```

Colores:

- verde: activo/listo;
- amarillo: pendiente/advertencia;
- rojo: error/crítico;
- cian: información.

---

## 11. Personalidad por aplicación

Cada app puede tener un acento propio, pero debe permanecer dentro de la guía.

### Ataque Inicial

- Puede usar verde terminal como acento dominante en pantallas escénicas.
- Radar permitido.
- Apertura tipo terminal permitida.
- Debe unificar navegación, fondo y márgenes.

### Public Wi-Fi

- Debe ser la referencia principal para pantallas operativas.
- Mantener dashboard, paneles, mapas y logs.
- Quitar mascota/imagen de identidad en pantallas operativas.
- Traducir interfaz principal.

### QR Controller

- Puede tener pantallas muy limpias y escénicas.
- QR grande es una excepción justificada.
- Análisis de impacto es buena referencia para métricas escénicas.
- Debe unificar navegación inferior y fondo.

---

## 12. Checklist para nuevas pantallas

Antes de dar una pantalla por buena:

- [ ] Usa fondo común Qt.
- [ ] Usa paleta común.
- [ ] Usa español en títulos y controles.
- [ ] La navegación inferior sigue el patrón común.
- [ ] La pantalla encaja en familia operativa o escénica.
- [ ] Los estados usan colores coherentes.
- [ ] No hay QR en setup.
- [ ] No hay mascota lateral obligatoria.
- [ ] Los márgenes son consistentes.
- [ ] La pantalla se puede operar con teclado.
- [ ] La jerarquía visual es clara.
- [ ] El contenido crítico se lee de un vistazo.

---

## 13. Próximos pasos

1. Aplicar fondo común a las tres apps.
2. Sustituir barras inferiores por una implementación común.
3. Traducir títulos y controles principales.
4. Crear componentes comunes: `CyberPanel`, `BottomNavBar`, `MetricCard`, `AlertBanner`.
5. Rediseñar setup de cada app con la guía v0.2.
6. Revisar pantallas escénicas tras probar en condiciones de ensayo.

---

# Anexo v0.3 — Relación con convenciones de operación

La guía visual debe aplicarse junto con `CYBERSHOW_APP_CONVENTIONS.md`.

Resumen operativo obligatorio:

- Todas las apps aceptan `--configure`, `--design` y `--show`.
- Sin argumentos equivale a `--configure`.
- En `--show` y `--design`, Setup no aparece y es inalcanzable.
- La navegación principal usa flechas, números y click.
- Se eliminan atajos por letra para navegación principal.
- `Esc` vuelve a Setup solo en modo configuración.
- `Alt+F4` es la salida estándar.
- La barra inferior debe coincidir con los números de pantalla.
- Las pantallas se clasifican como operativas o escénicas.
- El contrato mínimo con el orquestador usa mensajes `CYBERSHOW_*` por stdout.
