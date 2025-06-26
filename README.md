<p align="center">
  <img src="Group4.png" alt="Lazy Arduino Logo" width="200"/>
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

