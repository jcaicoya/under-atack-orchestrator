# Orchestrator — Refactoring plan

Aligning with Cybershow standard v0.3.
One commit per step. Update this file as work progresses.

References:
- `cybershow_app_standards_v0_3/CYBERSHOW_APP_CONVENTIONS.md`
- `cybershow_app_standards_v0_3/QT_APP_LOOK_AND_FEEL.md`
- `cybershow_app_standards_v0_3/ORCHESTRATOR_VISUAL_AND_OPERATION.md`
- `cybershow_app_standards_v0_3/CYBERSHOW_REFACTOR_CHECKLIST.md`

---

## Step 1 — APP_SPEC.md [x]

Create the orchestrator's specification document using the standard template.

**Goal:** document the orchestrator identity, exceptions to the common standard, and its refactoring checklist.

**Files:**
- `APP_SPEC.md` (new)

**Notes:**
- The orchestrator is a special Cybershow app: no scene navigation bar, no setup screen, no --configure CLI parsing for itself.
- Exceptions to the common standard must be explicitly listed.

---

## Step 2 — Integrate common UI components [x]

Copy the shared visual components from the standards package into the project source tree.

**Goal:** make CyberTheme, CyberBackgroundWidget, and CyberPanel available to the orchestrator. No behavior change yet.

**Files:**
- `ui/CyberTheme.h` (copied from standards)
- `ui/CyberTheme.cpp` (copied from standards)
- `ui/CyberBackgroundWidget.h` (copied from standards)
- `ui/CyberBackgroundWidget.cpp` (copied from standards)
- `ui/CyberPanel.h` (copied from standards)
- `ui/CyberPanel.cpp` (copied from standards)
- `CMakeLists.txt` (add ui/ sources and include path)

**Notes:**
- Sources go in `ui/` subdirectory.
- Add `${CMAKE_CURRENT_SOURCE_DIR}/ui` to `target_include_directories`.
- No visual change to the running app yet.

---

## Step 3 — Apply global dark theme [x]

Apply the Cybershow visual identity to the running application.

**Goal:** the app looks like a Cybershow app. Dark background, correct palette, correct typography.

**Files:**
- `main.cpp` (apply `CyberTheme::globalStyleSheet()` to QApplication)
- `MainWindow.h` / `MainWindow.cpp` (use `CyberBackgroundWidget` as the central widget base; remove hardcoded colors and fonts)

**Notes:**
- `CyberTheme::globalStyleSheet()` sets `background: transparent` on all QWidgets, which lets CyberBackgroundWidget paint through children.
- CyberPanel, QPushButton, QTableWidget and QTextEdit all pick up their styles from the global stylesheet via objectName selectors.
- The existing mode buttons and layout remain functional — only colors and fonts change.

---

## Step 4 — Create ModeSelectorScreen [ ]

New initial screen for the orchestrator: three mode cards.

**Goal:** a clean central landing screen with three selectable modes. Keyboard and click navigation.

**Files:**
- `ui/ModeSelectorScreen.h` (new)
- `ui/ModeSelectorScreen.cpp` (new)
- `CMakeLists.txt` (add new files)

**Behavior:**
- Shows three cards: **CONFIGURAR**, **DISEÑO**, **SHOW**.
- DISEÑO and SHOW are disabled with a "próximamente" label.
- Keyboard: `1` selects/opens CONFIGURAR; `2`/`3` focus disabled cards; `←`/`→` change card focus; `Enter`/`Space` open focused card; click opens card.
- Signal emitted: `modeConfirmed(int modeIndex)`.
- Uses CyberBackgroundWidget, CyberPanel, CyberTheme palette.
- Title: **CYBERSHOW** / subtitle: *Centro de control*.

**Notes:**
- This screen is created but not yet wired into MainWindow in this step.
- Can be visually tested by temporarily setting it as the main widget.

---

## Step 5 — Two-screen architecture [ ]

MainWindow becomes a stacked container. App starts on ModeSelectorScreen.

**Goal:** complete navigation flow: Selector → ConfigureModeScreen → Selector (via Esc).

**Files:**
- `MainWindow.h` / `MainWindow.cpp` (refactored: adds QStackedWidget, wires both screens)
- `ui/ConfigureModeScreen.h` (new — extracted from current MainWindow content)
- `ui/ConfigureModeScreen.cpp` (new — extracted from current MainWindow content)
- `CMakeLists.txt` (add new files)

**Architecture:**
```
MainWindow (QMainWindow)
└── CyberBackgroundWidget (central widget)
    └── QStackedWidget
        ├── page 0: ModeSelectorScreen
        └── page 1: ConfigureModeScreen
```

**Navigation:**
- On startup: page 0 (ModeSelectorScreen).
- `modeConfirmed(0)` → switch to page 1.
- `Esc` inside ConfigureModeScreen → switch to page 0.
- `Alt+F4`: standard OS close (no code needed).

**Notes:**
- All existing functional logic (AppManager, Logger, config loading) moves to ConfigureModeScreen.
- The old top mode-toggle buttons (Configuration / Rehearsal / Live) are removed from the UI — mode is now determined by which screen the orchestrator is on.
- At this stage ConfigureModeScreen is visually unchanged (old layout, just extracted).

---

## Step 6 — ConfigureModeScreen visual + Spanish [ ]

Apply the Cybershow look and feel to the control panel.

**Goal:** ConfigureModeScreen looks and reads like a Cybershow operator screen.

**Files:**
- `ui/ConfigureModeScreen.h` / `ui/ConfigureModeScreen.cpp`

**Changes:**
- Wrap app list in a `CyberPanel` titled "Aplicaciones".
- Wrap log panel in a `CyberPanel` titled "Registro de eventos".
- Header row: left = screen title "Configurar"; right = general status label.
- Spanish state labels:

  | AppState    | Displayed label  | Color                |
  |-------------|-----------------|----------------------|
  | Stopped     | DETENIDA         | TextMuted `#5F6B78`  |
  | Starting    | LANZANDO         | Warning `#FFB000`    |
  | Running     | EJECUTÁNDOSE     | AccentGreen `#00FF55`|
  | Stopping    | DETENIENDO...    | Warning `#FFB000`    |
  | Error       | ERROR            | Error `#FF3347`      |

- Spanish button labels: **Iniciar** / **Parar** / **Reiniciar** / **Parar todo**.
- Hint line at bottom: *Esc: volver al selector*.
- Log panel: monospace font, text color AccentGreen `#00FF55` for normal lines, Error red for lines starting with "ERROR".

**Notes:**
- No functional logic changes in this step.
- Table background should use transparent/PanelBackground so it blends into CyberPanel.

---

## Step 7 — Mode-launch argument integration [ ]

AppManager passes the correct system argument to launched apps based on orchestrator mode.

**Goal:** apps launched from CONFIGURAR receive `--configure`; from DISEÑO receive `--design`; from SHOW receive `--show`.

**Files:**
- `AppManager.h` (rename ShowMode enum values)
- `AppManager.cpp` (update `argsFor()` to prepend mode arg)
- `ui/ConfigureModeScreen.cpp` (update ShowMode references)

**Changes:**
- Rename `ShowMode` enum:
  - `Configuration` → `Configure`
  - `Rehearsal` → `Design`
  - `Live` → `Show`
- In `argsFor()`, prepend the system mode argument as the first element:
  ```
  Configure → "--configure"
  Design    → "--design"
  Show      → "--show"
  ```
  Full arg list: `["--configure", ...common args..., ...mode-specific args...]`
- Default mode when entering ConfigureModeScreen: `ShowMode::Configure`.

**Notes:**
- Existing apps that don't yet accept `--configure` will receive an unknown argument. This is expected and acceptable — apps will be refactored incrementally to support it.
- The JSON fields `configurationArguments` / `rehearsalArguments` / `liveArguments` remain valid for app-specific extra args per mode.

---

## Completion checklist (ORCHESTRATOR_VISUAL_AND_OPERATION.md §14)

- [ ] Uses CyberBackgroundWidget as window base
- [ ] Uses CyberTheme palette and buttons
- [ ] No standard setup screen
- [ ] Has ModeSelectorScreen
- [ ] CONFIGURAR mode is available
- [ ] DISEÑO and SHOW are disabled / "próximamente"
- [ ] `1`, `2`, `3` select modes in the selector
- [ ] `Enter` and `Space` open the selected mode
- [ ] `←` / `→` change card focus in the selector
- [ ] `Esc` from a mode screen returns to the selector
- [ ] `Alt+F4` closes the application (OS default)
- [ ] No scene navigation bar
- [ ] Apps launched with `--configure` from CONFIGURAR
- [ ] Design allows `--design` and `--show` to be added later
- [ ] Process states use Spanish nomenclature
- [ ] Errors are visible and understandable for the operator
