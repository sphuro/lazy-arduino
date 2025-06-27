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
