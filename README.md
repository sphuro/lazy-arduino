<p align="center">
  <img src="assets/Group4.png" alt="Lazy Arduino Logo" width="200"/>
</p>


# Lazy Arduino

I am making a TUI for arduino cli that for new cli users.

## Plan

- [x] CLI Skeleton
- [ ] TUI Framework setup
- [ ] `arduino-cli` wrapper module
- [ ] Board/Port detection screen
- [ ] Sketch selection screen
- [ ] Compile/upload screen with logs
- [ ] Serial monitor


## Current view

![alt text](assets/image.png)


## Planed File structure

  ```
lazy-arduino/
├── include/
│   ├── ui.h              # UI init/end and key bindings
│   ├── sketches.h        # Sketch list & handling
│   ├── boards.h          # Board panel & auto-refresh
│   ├── logs.h            # Log panel
│   ├── serial.h          # Serial monitor
│   ├── status.h          # Status bar
│   ├── pages.h           # Multi-page navigation
│   ├── arduino.h         # Compile/upload logic
│   ├── config.h          # Config management
│   └── state.h           # Shared state (selected sketch/board/etc.)
├── src/
│   ├── main.c            # Program entry
│   ├── ui.c              # Init screen, layout
│   ├── sketches.c        # Sketches panel logic
│   ├── boards.c          # Boards panel (w/ pthread updates)
│   ├── logs.c            # Compile/upload log viewer
│   ├── serial.c          # Serial monitor backend
│   ├── status.c          # Bottom bar info
│   ├── pages.c           # Switch between: Dashboard, Board Manager, Library Manager
│   ├── arduino.c         # Compile/upload wrapper
│   ├── config.c          # User config loader
│   └── state.c           # Global state management

  ```

## What my Project is:
- to remove the need for learning cli commands.
- for some can use this who doesnt uses cli much often but want to use it over ssh.
- if someone have low end sytem can use this instead of bulky arduino ide.

## Logs
- I am using wsl right now(yes :(  ) so to use the port for any micrcontroller so that wsl cna detect it i have installed `https://github.com/dorssel/usbipd-win/releases`
and run `usbipd list` to list all the ports and then ` usbipd bind --busid <BUSID>` this binds the usb device on windows so that i can forward it and then run `usbipd attach --busid 3-1 --wsl`
so that the usb device will be available in wsl.
- you have to run the `usbpid` command before connecting the micrcontroller every time so that wsl can read it.


---

## `Lazy Arduino IDE` – TUI Pages & Layout Specification

This document outlines all the major **TUI pages**, their **sections/windows**, and the purpose of each. Also included: how a global `status bar` helps user interaction.

---

## Page Overview

| Page Key | Name             | Purpose                                   |
| -------- | ---------------- | ----------------------------------------- |
| `F1`     | Dashboard        | Main view: sketches, boards, logs, serial |
| `F2`     | Board Manager    | View/Select boards, install/remove cores  |
| `F3`     | Library Manager  | View/Install/Remove libraries             |
| `F4`     | Example Sketches | Browse and import examples                |
| `F5`     | Settings         | Editor, default board, theme, paths       |

---

## Navigation Model

* Use `Tab` to cycle within panels.
* Use `F1–F5` or `[ ← / → ]` to switch pages.
* `q` always exits current page or program.
* `Enter` or `e` edits/open items.
* `c` compiles, `u` uploads, `s` saves.

---

## Status Bar (`status.c`)

The bottom bar across **all pages**, showing real-time status.

```
[Sketch: blink.ino]  [Board: ESP32 DevKit]  [Port: /dev/ttyUSB0]  [Page: Dashboard]  [Press F1–F5 | Tab | q]
```

This helps the user:

* **Know what’s selected** (sketch/board)
* **Current active page**
* **Quick shortcuts**

```c
// pseudo rendering
mvwprintw(status_win, 0, 1,
  "[Sketch: %s]  [Board: %s]  [Port: %s]  [Page: %s]",
   selected_sketch, selected_board, selected_port, current_page_name);
```

---

##  Page Layouts

---

### `F1` – Dashboard

```
+------------------+------------------------+
|   Sketches       |     Boards             |
|   [blink.ino]    |   [ESP32 DevKit]       |
|   [wifi.ino]     |   [Arduino Uno]        |
+------------------------------------------+
|   Compile / Upload Logs                  |
|   [Success: Uploaded at 18:43]           |
+------------------------------------------+
|   Serial Monitor                         |
|   [temp = 36.4]                          |
+------------------------------------------+
[Sketch: blink.ino] [Board: ESP32] ...
```

---

###  `F2` – Board Manager

```
+----------------------------------------+
| Installed Boards / Ports               |
| [ESP32 DevKit] on /dev/ttyUSB0         |
| [Arduino Uno] on /dev/ttyUSB1          |
+----------------------------------------+
| Available Cores                        |
| [✓] esp32 @ 2.0.11   [Install]         |
| [ ] attiny85         [Install]         |
+----------------------------------------+
| Board Actions                          |
| (u) Uninstall  (i) Install (r) Refresh |
+----------------------------------------+
[...]
```

---

###  `F3` – Library Manager

```
+----------------------------------------+
| Installed Libraries                    |
| [✓] Servo       [Uninstall]            |
| [✓] Adafruit_GFX [Uninstall]           |
+----------------------------------------+
| Available Libraries                    |
| [ ] OneWire     [Install]              |
| [ ] FastLED     [Install]              |
+----------------------------------------+
| (s) Search   (i) Install   (u) Uninstall |
+----------------------------------------+
```

---

###  `F4` – Examples Browser

```
+--------------------------+
| Categories               |
| [Arduino]                |
| [ESP32]                  |
| [Adafruit]               |
+--------------------------+
| Files                    |
| blink.ino                |
| wifi_scan.ino            |
| servo_test.ino           |
+--------------------------+
| (Enter) Load  (Tab) Focus |
+--------------------------+
```

---

### `F5` – Settings Page

```
+------------------------------------+
| Editor         : nano              |
| Default Board  : ESP32 DevKit      |
| Serial Port    : /dev/ttyUSB0      |
| Sketch Folder  : ~/Arduino         |
| Theme          : Arduino Classic   |
+------------------------------------+
| (e) Edit  (Tab) Next Field (s) Save |
+------------------------------------+
```

---

## Future Extensions

* JSON-based config system
* Dynamic plugin panel (e.g. OTA uploads)
* Git integration for sketches
* Highlight logs/errors

---

## Benefits of This Design

* Mirrors Arduino IDE experience.
* Pages are **modular**, and each gets its own C file.
* Responsive layout with `ncurses`, easier to maintain.
* `status.c` acts as the user compass.

