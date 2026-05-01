# Cybershow Orchestrator — Development Context

> Working context file for ChatGPT, Codex, Claude or any coding assistant.
> Keep this file updated as the project evolves.
>
> Suggested filename: `CYBERSHOW_ORCHESTRATOR.md`
>
> If using Claude, this content can also be copied or symlinked to `CLAUDE.md`.

---

## 1. Project Summary

We are building a **desktop orchestrator/console** for a live cybersecurity show called **Cybershow**.

The show uses several C++/Qt desktop applications, one or more Android applications, videos, sounds, and later lighting. The orchestrator is not just a launcher: it should become the **control cabin** for the show.

The core idea:

> The orchestrator does not merely launch applications.  
> It activates and supervises show scenes.

The show currently includes or will include:

1. Desktop app to interact with a mobile phone.
2. Android app to interact with the previous desktop app.
3. Desktop app to change QR codes.
4. Desktop app for the public Wi-Fi / “we cannot decrypt WhatsApp” section.
5. Desktop app for the password oracle.
6. Desktop app to generate phishing messages and send them to the phone.
7. Android app to interact with the phishing desktop app.
8. Two videos before the show starts.
9. One video at the end.
10. Later: sounds/music.
11. Later: lighting control.

Some apps already exist as Windows executables. Others, such as the password oracle and phishing generator, have not yet been started. This is a good time to define the orchestrator architecture so new apps can be built to fit it.

---

## 2. Main Architectural Decision

We do **not** want one giant monolithic application containing all show logic.

We also do **not** want a collection of unrelated apps manually opened and closed during the show.

The chosen architecture is hybrid:

```text
Cybershow Orchestrator / Console
├── Launches existing executable apps
├── Passes configuration and launch parameters
├── Starts/stops/restarts apps
├── Later: positions apps on the projector/stage screen
├── Later: plays videos
├── Later: plays sounds
├── Later: triggers lighting presets
├── Later: controls scenes
└── Later: communicates with the mobile companion app
```

The Android side should eventually become a single **mobile companion app** with modes, rather than separate mobile apps per show section.

---

## 3. Development Language / Stack

The orchestrator will be a **C++/Qt desktop application**, built with **CMake**.

Initial target platform:

```text
Windows
C++ / Qt
CMake
Portable folder-based distribution
```

The user will create the initial CMake/Qt HelloWorld project.

---

## 4. Orchestrator Modes

The orchestrator will have three modes from the beginning, even if they initially behave the same:

```text
Configuration
Rehearsal
Live
```

Use **Rehearsal**, not “Demo”. “Demo” sounds like a reduced commercial/demo mode; “Rehearsal” better describes the operational purpose.

### 4.1 Configuration Mode

Purpose:

```text
Prepare and validate the show setup.
```

Used at home and during pre-show preparation.

Responsibilities:

```text
- Detect/list configured applications.
- Edit executable paths.
- Edit working directories.
- Edit launch arguments.
- Edit mode-specific arguments.
- Validate that configured paths exist.
- Launch an app manually to test it.
- Stop/restart an app manually to test it.
- Later: configure projector/stage screen.
- Later: configure video/sound/lighting resources.
```

This mode prepares the show. It is not meant to run the live performance.

### 4.2 Rehearsal Mode

Purpose:

```text
Manual control for testing, rehearsing, and repeating parts of the show.
```

This will likely be the most used mode during development and rehearsal.

Responsibilities:

```text
- Start/stop/restart apps using the stored configuration.
- Play videos manually.
- Later: trigger sounds manually.
- Later: trigger lighting presets manually.
- Repeat transitions.
- Jump to a specific section.
- Test the mobile connection.
- Test stage output.
- Provide emergency controls.
```

### 4.3 Live Mode

Purpose:

```text
Run the show using scenes, with minimal and safe controls.
```

Responsibilities:

```text
- Activate scenes.
- Prepare next scene.
- Move forward/backward through the show.
- Trigger app/video/sound/light actions.
- Show scene/app status.
- Provide emergency controls.
```

Live mode should not expose too many controls. In live performance, fewer buttons are safer.

---

## 5. Packaging Philosophy

Packaging must work from the beginning.

Do **not** postpone packaging until the end. Each development phase should end with a portable package that can be tested on:

```text
- Main laptop
- Rehearsal/backup laptop
```

Preferred distribution model:

```text
Portable folder, not installer-first.
```

The user wants to distribute the orchestrator among several laptops. The package should be copyable as a folder.

### 5.1 Recommended Package Structure

```text
CybershowPackage/
├── CybershowConsole.exe
├── config/
│   └── apps.json
├── apps/
│   ├── MobileBridge/
│   │   ├── MobileBridge.exe
│   │   ├── Qt6Core.dll
│   │   ├── Qt6Gui.dll
│   │   ├── Qt6Widgets.dll
│   │   └── platforms/
│   │       └── qwindows.dll
│   │
│   ├── QRChanger/
│   │   ├── QRChanger.exe
│   │   ├── Qt6Core.dll
│   │   ├── Qt6Gui.dll
│   │   ├── Qt6Widgets.dll
│   │   └── platforms/
│   │       └── qwindows.dll
│   │
│   └── PublicWifi/
│       ├── PublicWifi.exe
│       ├── Qt6Core.dll
│       ├── Qt6Gui.dll
│       ├── Qt6Widgets.dll
│       └── platforms/
│           └── qwindows.dll
│
├── media/
│   ├── intro_1.mp4
│   ├── intro_2.mp4
│   └── final.mp4
│
├── sounds/
├── lights/
├── logs/
└── tools/
```

The `sounds/`, `lights/`, and `tools/` folders can initially be empty.

---

## 6. Important DLL Decision

Existing applications are executables with DLLs next to them.

The orchestrator must launch each application using the correct **working directory**, otherwise Qt DLLs/plugins may not be found.

Each app should be treated as a self-contained package:

```text
apps/PublicWifi/
├── PublicWifi.exe
├── required DLLs
├── platforms/
└── other resources
```

Do **not** rely on global PATH or a global Qt installation.

### 6.1 Do Not Store Executables/DLLs as Qt Resources

Do **not** embed external executables and their DLLs as Qt resources inside the orchestrator.

Reasons:

```text
- Windows cannot directly execute an .exe from Qt resources.
- They would have to be extracted to disk first.
- This complicates updates, antivirus behavior, permissions and cleanup.
- Resources are better suited for icons, templates, small JSON files, styles, etc.
```

Correct approach:

```text
Use a controlled external `apps/` folder inside the portable package.
```

### 6.2 Duplicate DLLs Per App Initially

Prefer:

```text
apps/QRChanger/Qt6Core.dll
apps/PublicWifi/Qt6Core.dll
apps/MobileBridge/Qt6Core.dll
```

over a shared DLL folder, at least initially.

Reason:

```text
Robustness is more important than disk space for a live show.
```

Each app remains autonomous and less likely to break when another app changes.

---

## 7. Configuration Files

Use **JSON** initially, not YAML.

Reason:

```text
- Qt has native JSON support.
- JSON is predictable.
- YAML adds dependency and indentation complexity.
```

### 7.1 Resource vs External Config

Use Qt resources only for defaults/templates.

Recommended behavior:

```text
1. On startup, look for `config/apps.json` next to the executable.
2. If it exists, load it.
3. If it does not exist, copy a default template from Qt resources.
4. Then use the external editable file.
```

This gives both:

```text
- Good first-run behavior.
- Editable real configuration without recompilation.
```

### 7.2 Paths

Use paths relative to the orchestrator package root.

Good:

```json
"executable": "apps/QRChanger/QRChanger.exe"
```

Avoid absolute user-specific paths:

```json
"executable": "C:/Users/Someone/Desktop/Cybershow/apps/QRChanger/QRChanger.exe"
```

### 7.3 Proposed Initial App Config Schema

This schema is intentionally more complete than Phase 1 needs, so later phases do not require a redesign.

```json
{
  "version": 1,
  "apps": [
    {
      "id": "public_wifi",
      "name": "Wi-Fi pública",
      "description": "Demo de red Wi-Fi pública y WhatsApp",
      "enabled": true,

      "executable": "apps/PublicWifi/PublicWifi.exe",
      "workingDirectory": "apps/PublicWifi",

      "arguments": [],
      "configurationArguments": [],
      "rehearsalArguments": [],
      "liveArguments": [],

      "startupPolicy": "manual",
      "closePolicy": "terminateThenKill",

      "expectedWindowTitle": "Cybershow - Public Wi-Fi",
      "category": "demo"
    }
  ]
}
```

Fields:

```text
id                         Stable internal id.
name                       User-visible name.
description                Optional explanation.
enabled                    Whether app is visible/usable.
executable                 Relative path to .exe.
workingDirectory           Relative path used to launch the app.
arguments                  Common arguments.
configurationArguments     Arguments used in Configuration mode.
rehearsalArguments         Arguments used in Rehearsal mode.
liveArguments              Arguments used in Live mode.
startupPolicy              Initially manual.
closePolicy                Initially terminateThenKill.
expectedWindowTitle        Useful later for projector/window management.
category                   Optional grouping.
```

Apps may ignore arguments initially. New apps should be built to accept them from the start.

---

## 8. Launching External Apps

Use Qt’s process-launching mechanism, e.g. `QProcess`.

Required behavior:

```text
- Start app.
- Stop app.
- Restart app.
- Stop all apps.
- Track basic state.
- Handle failed starts.
- Detect when an app exits.
- Avoid launching duplicate instances unless explicitly allowed.
```

Basic states:

```text
Stopped
Starting
Running
Stopping
Error
```

Later states:

```text
Hidden
Visible
OnProjector
Crashed
Preparing
Ready
Active
```

Closing policy:

```text
1. Try polite termination.
2. Wait a short configurable period.
3. Force kill if still running.
```

Avoid force-kill as the default first action.

---

## 9. Logs and Diagnostics

Logs are important from Phase 1.

Need both:

```text
- Visible log panel in the orchestrator UI.
- Log file in `logs/`.
```

Log examples:

```text
[18:42:03] Starting PublicWifi.exe
[18:42:03] Working dir: apps/PublicWifi
[18:42:03] Args: --mode live --profile school
[18:42:04] PublicWifi running
[18:43:10] PublicWifi closed unexpectedly
```

Also useful:

```text
- Package diagnostics.
- Missing file warnings.
- Bad working directory warnings.
- Failed process start details.
```

---

## 10. Stage / Projector Strategy

There will definitely be a projector.

Two possible modes:

### 10.1 Mirror Mode

Laptop screen and projector show the same content.

Pros:

```text
- Simpler.
- Less technical risk.
- The audience sees a real Windows app.
```

Cons:

```text
- Audience sees the orchestrator.
- Audience may see Alt-Tab/window changes.
- Audience may see notifications or errors.
- Less theatrical control.
```

Could be used for early tests or as fallback.

### 10.2 Extended Screen Mode

Laptop is control screen. Projector is stage screen.

Preferred for final show.

```text
Laptop screen:
- Orchestrator
- Status
- Controls
- Logs

Projector:
- Apps
- Videos
- Black screen
- Logo
- Stage content only
```

This is more professional and safer for live performance.

The architecture should be designed with two conceptual screens from the beginning:

```text
Control Screen
Stage Screen
```

Projector/stage output is not Phase 1, but it must be considered before final Live mode.

---

## 11. Scenes

Scenes are not implemented in Phase 1.

Eventually, Live mode should operate through scenes.

A scene is a recipe of actions, not just “open one app”.

Example:

```text
Scene: Wi-Fi pública

Actions:
- stop previous video
- launch PublicWifi if not already running
- pass live parameters
- move app to stage screen
- set fullscreen
- switch mobile app to proper mode
- play sound/music if needed
- set light preset if available
- mark scene active
```

Important distinction:

```text
Prepare scene
Activate scene
```

Example:

```text
Prepare Password Oracle:
- launch app hidden
- load profile
- check it is running

Activate Password Oracle:
- move/show app on projector
- play sound effect
- mark scene as current
```

This distinction is valuable for live performance.

---

## 12. Emergency Controls

Emergency controls should appear relatively early.

Minimum emergency actions:

```text
- Black screen
- Show logo / waiting screen
- Stop all sounds
- Stop current app
- Restart current app
- Stop all apps
- Manual mode
```

The show must be able to continue if a scene fails.

---

## 13. Videos

There are already some videos available for testing:

```text
- Two videos before the show starts.
- One video at the end.
```

Video support is not required in Phase 1 but is required for Rehearsal mode.

Eventually:

```text
Configuration:
- register videos
- validate paths

Rehearsal:
- play/stop videos manually

Live:
- videos are scene actions
```

A future video config may look like:

```json
{
  "videos": [
    {
      "id": "intro_1",
      "name": "Intro 1",
      "path": "media/intro_1.mp4"
    },
    {
      "id": "final",
      "name": "Final",
      "path": "media/final.mp4"
    }
  ]
}
```

---

## 14. Sounds

No sounds are ready yet, but architecture should leave room for them.

Eventually:

```text
Configuration:
- register sounds/music files
- set default volume if needed

Rehearsal:
- play sound manually
- stop all sounds

Live:
- sounds/music are scene actions
```

Potential actions:

```text
play_sound
play_music
stop_sound
stop_all_sounds
set_volume
```

---

## 15. Lighting

Lighting will come later.

Still, the scene action model should leave space for lighting from the beginning.

Eventually:

```text
Configuration:
- configure lighting device/software
- create presets
- test presets

Rehearsal:
- trigger presets manually

Live:
- scenes trigger lighting presets
```

Possible future action:

```text
set_light_scene
```

Do not hardcode lighting too early. Treat it as another action type in the scene system.

---

## 16. Proposed Implementation Phases

### Phase 1 — Orchestrator Skeleton

Goal:

```text
Create a C++/Qt console able to load app configuration and control basic external app lifecycle.
```

Includes:

```text
- CMake/Qt HelloWorld base.
- Main UI with three modes: Configuration, Rehearsal, Live.
- Load JSON config.
- Default config template as Qt resource.
- External editable config at `config/apps.json`.
- List configured apps.
- Start app.
- Stop app.
- Restart app.
- Stop All.
- Basic states: Stopped / Starting / Running / Error.
- Visible log panel.
- File log.
- Use executable + workingDirectory.
- Use relative paths from package root.
```

Does not include:

```text
- Scenes.
- Projector/stage screen.
- Window movement.
- Videos.
- Sounds.
- Stream Deck.
- Mobile communication.
- Lighting.
```

Success criteria:

```text
1. Copy package to main laptop.
2. Run CybershowConsole.exe.
3. See app list.
4. Start an app.
5. App opens with its DLLs.
6. Stop the app.
7. Restart the app.
8. Stop All leaves nothing running.
9. Bad paths produce clear errors.
10. App unexpected exit updates status.
```

---

### Phase 2 — Portable Packaging

Goal:

```text
Make the package copyable and usable on multiple laptops from early development.
```

Includes:

```text
- Final-ish package folder structure.
- Apps under `apps/`, each with own DLLs/plugins.
- Config under `config/`.
- Logs under `logs/`.
- Media/sounds/lights folders present.
- Relative paths only.
- Test on main laptop and backup laptop.
- Package diagnostics panel.
```

Success criteria:

```text
1. Zip/copy folder to backup laptop.
2. Run without installing Qt globally.
3. All configured app paths resolve.
4. Logs can be written.
5. Start/stop works on both laptops.
```

---

### Phase 3 — Configuration Mode

Goal:

```text
Make Configuration mode useful for preparing the show.
```

Includes:

```text
- Edit app name.
- Edit executable path.
- Edit working directory.
- Edit common arguments.
- Edit configuration/rehearsal/live arguments.
- Validate app entry.
- Test start/stop from Configuration mode.
- Save config.
- Possibly duplicate/import app entries.
```

Possible later improvement:

```text
Profiles:
- home
- rehearsal
- live main laptop
- live backup laptop
```

Success criteria:

```text
A user can configure an app without editing JSON manually and verify it launches correctly.
```

---

### Phase 4 — Rehearsal Mode

Goal:

```text
Manual control for rehearsing show elements.
```

Includes:

```text
- Manual app control using stored config.
- Video list.
- Play/stop video.
- Stop all apps.
- Black screen placeholder.
- Show logo/waiting screen placeholder.
- Placeholder area for sounds.
- Basic emergency controls.
```

Success criteria:

```text
The team can rehearse app launches and video playback from one place.
```

---

### Phase 5 — Stage Screen / Projector

Goal:

```text
Support separate control screen and stage/projector screen.
```

Includes:

```text
- Detect displays.
- Select control screen.
- Select stage screen.
- Open videos on stage screen.
- Later: move app windows to stage screen.
- Black screen on stage.
- Logo/waiting screen on stage.
- Mirror fallback strategy.
```

Success criteria:

```text
Orchestrator stays on laptop while audience content appears on projector.
```

---

### Phase 6 — Live Mode / Scenes

Goal:

```text
Run the show through scenes.
```

Includes:

```text
- Scene list.
- Current scene.
- Next scene.
- Previous scene.
- Prepare scene.
- Activate scene.
- Scene action model.
- App actions.
- Video actions.
- Placeholder sound/light actions.
- Scene status.
```

Possible scene states:

```text
NotPrepared
Preparing
Ready
Active
Completed
Failed
Skipped
```

Success criteria:

```text
Operator can progress through the show using scene controls rather than manual app/video buttons.
```

---

### Phase 7 — Sound

Goal:

```text
Add sound/music control.
```

Includes:

```text
- Register sound files.
- Play sound.
- Stop sound.
- Stop all sounds.
- Optional volume control.
- Sounds as scene actions.
```

---

### Phase 8 — Lighting

Goal:

```text
Add lighting control.
```

Includes:

```text
- Configure lighting backend/device/software.
- Define lighting presets.
- Trigger presets manually in Rehearsal.
- Trigger presets automatically in Live scenes.
```

Lighting should be modeled as scene actions, not as special-case code.

---

### Phase 9 — Robustness for Live Show

Goal:

```text
Make the system safe for performance.
```

Includes:

```text
- Better error recovery.
- Clear operator alerts.
- Checklist before show.
- Logs review.
- Stop/restart current scene/app.
- Manual fallback mode.
- Backup laptop validation.
- Full-show rehearsal mode.
```

---

## 17. Suggested Initial UI

Phase 1 UI can be simple.

```text
CYBERSHOW ORCHESTRATOR

Mode:
[ Configuration ] [ Rehearsal ] [ Live ]

Applications:
------------------------------------------------------
Name              State       Actions
------------------------------------------------------
Wi-Fi pública     Running     [Start] [Stop] [Restart]
QR Changer        Stopped     [Start] [Stop] [Restart]
Mobile Bridge     Error       [Start] [Stop] [Restart]
------------------------------------------------------

[Stop All]

Log:
[12:31:04] Starting Wi-Fi pública...
[12:31:05] Wi-Fi pública running.
[12:31:20] Stopping Wi-Fi pública...
```

Later:

```text
- Stage/proyector status.
- Mobile status.
- Current scene.
- Next scene.
- Emergency buttons.
```

---

## 18. Important Design Rules

```text
1. Configuration prepares.
2. Rehearsal tests.
3. Live executes.
4. Packaging is validated in every phase.
5. Paths should be relative.
6. Apps should be launched from their own working directory.
7. Do not embed external apps/DLLs in Qt resources.
8. Keep each existing app autonomous initially.
9. Prefer robustness over disk-size optimization.
10. Design scene actions generically so videos, sounds and lights fit later.
11. Keep emergency controls available.
12. Keep visible and file logs from the beginning.
```

---

## 19. Immediate Next Step

The user will create a basic Qt/CMake HelloWorld.

Next coding task after that:

```text
Implement Phase 1:
- app config loading
- basic app list UI
- QProcess-based start/stop/restart
- working directory support
- basic states
- visible log
- file log
- Stop All
```

Use the package-oriented structure even in the first prototype.

---

## 20. Notes for Coding Assistants

When continuing this project:

```text
- Do not jump directly to scenes before Phase 1 and packaging are stable.
- Do not over-engineer the UI early.
- Prefer small increments that can be tested on both laptops.
- Keep the JSON schema simple but future-friendly.
- Keep all code and identifiers in English.
- User discussions may be in Spanish, but code should be English.
- The user works with C++/Qt/CMake.
- The user values practical robustness for a live show over theoretical elegance.
```

