# BAJO ATAQUE — Orchestrator Runbook

## Requisitos

| Elemento | Requisito |
|---|---|
| SO | Windows 10/11 64-bit |
| Runtime | Visual C++ Redistributable |
| Qt | 6.7.3, empaquetado en el zip |
| Multimedia | backend FFmpeg con DLLs empaquetadas |
| Apps externas | autocontenidas en `apps/` |

## Arranque de la aplicación

- La ventana principal del operador arranca fullscreen por defecto en la pantalla principal.
- La ventana de escenario/proyector se activa aparte desde los controles de Escenario.
- Si solo hay una pantalla detectada, los controles de Escenario se ocultan.

## Manejo de la aplicación

### Selector de modo inicial

| Tecla | Acción |
|---|---|
| `1` | Abrir CONFIGURAR |
| `2` | Abrir ENSAYO |
| `3` | Abrir SHOW |
| `←` / `→` | Mover foco entre tarjetas |
| `Enter` / `Space` | Abrir modo enfocado |

### Dentro de cualquier modo

| Tecla | Acción |
|---|---|
| `Esc` | Volver al selector |
| `1` | Cambiar a CONFIGURAR |
| `2` | Cambiar a ENSAYO |
| `3` | Cambiar a SHOW |
| `F10` | Mostrar/ocultar panel de log |
| `←` | Modo anterior |
| `→` | Modo siguiente |

### Teclas adicionales en SHOW

| Tecla | Acción |
|---|---|
| `→` / `Space` | Escena siguiente |
| `Enter` | Activar escena actual |

### Pantalla de escenario/proyector

| Tecla | Acción |
|---|---|
| `Esc` | Desactivar escenario |

## Gestión de escenario

### Activación

1. En una pantalla de modo, usar la fila `Escenario`.
2. Seleccionar pantalla destino si hay dos o más pantallas.
3. Pulsar `Activar`.
4. La ventana se abre en la pantalla elegida con el logo de BAJO ATAQUE.
5. `Desactivar` cierra la ventana.

### Comportamiento automático

- El logo aparece al activar escenario y cuando no hay nada reproduciéndose.
- Si se reproduce un vídeo, aparece una ventana fullscreen de vídeo sobre la pantalla de escenario.
- Si se lanza una app, la ventana de escenario se oculta para dejar visible la app; al cerrarse, vuelve el logo.

## Gestión de ADB y apps Android

### Flujo previo a show

1. Conectar el dispositivo Android por USB o activar Wireless Debugging.
2. Ir a `CONFIGURAR -> ADB`.
3. Pulsar `Detectar` y comprobar que aparece `● <serial>`.
4. Pulsar `Probar` para verificar respuesta del dispositivo.
5. Opcionalmente usar ADB por WiFi para operación sin cable.

### Controles ADB

| Control | Función |
|---|---|
| `Detectar` | Ejecuta `adb devices` |
| `Probar` | Ejecuta `getprop ro.product.model`, hace vibrar el dispositivo y registra el modelo |
| `Desconectar` | Limpia estado; en WiFi hace `adb disconnect` |
| `Conectar` | Ejecuta `adb connect <ip:port>` |

### Lanzamiento de apps Android

1. Si `wsPort > 0`, se ejecuta `adb reverse tcp:<port> tcp:<port>`.
2. Después se ejecuta `adb shell am start -n <package>/<activity>`.
3. La app Android conecta a `localhost:<port>`.

## Gestión de releases

### Build manual

```powershell
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Empaquetado de release

```powershell
.\package-release.ps1
```

- Requiere PowerShell 7+ (`pwsh`).
- Ejecutar desde la raíz del proyecto.
- Genera `dist\bajo-ataque-orchestrator-vNN.zip`.
- Añade entrada en `releases.json` y crea tag git.
- `-Force` omite la comprobación de cambios sin commit.

### Contenido del paquete

- `under_attack_orchestrator.exe`
- DLLs Qt necesarias
- backend FFmpeg y sus DLLs
- plugins `platforms/qwindows.dll`
- plugins multimedia

### Despliegue en máquina destino

1. Copiar el zip.
2. Extraerlo.
3. Ejecutar `under_attack_orchestrator.exe`.

## Consideraciones operativas

- Las apps externas deben lanzar con `workingDirectory` propio.
- No compartir DLLs entre apps externas; cada una debe llevar las suyas.
- El vídeo usa `QVideoWidget` top-level independiente, no incrustado en `StageWindow`.
- Antes de `showFullScreen()` en ventana de escenario hay que fijar pantalla con `winId()` y `windowHandle()->setScreen()`.
