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
│   ├── ui.h              # Layout and color handling
│   ├── dashboard.h       # Dashboard panel structure
│   ├── serial.h          # Serial monitor handling
│   ├── arduino.h         # Compile & upload logic
│   ├── config.h          # Load/save user config
│   └── state.h           # Global UI state and enums
├── src/
│   ├── main.c            # Entry point
│   ├── ui.c              # Window setup, colors
│   ├── dashboard.c       # Panel logic
│   ├── serial.c          # Serial monitor
│   ├── arduino.c         # Compile/upload wrappers
│   ├── config.c          # Parse `~/.lazyarduino/config.ini`
│   └── state.c           # Manage UI panel state
├── assets/
│   └── banner.txt        # ASCII logo
├── Makefile
└── README.md

  ```
