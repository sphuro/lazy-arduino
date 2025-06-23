# Lazy Arduino

I am making a TUI for arduino cli that for new cli users.


## Project Architecture

```
lazy-arduino-c/
├── src/
│   ├── main.c               // Entry point
│   ├── ui.c / ui.h          // ncurses UI components
│   ├── arduino.c / .h       // Arduino CLI wrapper (compile/upload/list boards)
│   ├── serial.c / .h        // Serial monitor support
│   ├── config.c / .h        // Config file parser
│   └── utils.c / .h         // Helpers
├── assets/
├── Makefile
└── README.md

```


## Plan

- [ ] CLI Skeleton (Go with Cobra or Rust with Clap)
- [ ] TUI Framework setup (BubbleTea / tui-rs)
- [ ] `arduino-cli` wrapper module (calls, parses output)
- [ ] Board/Port detection screen
- [ ] Sketch selection screen (browse files)
- [ ] Compile/upload screen with logs
- [ ] Serial monitor (basic logging)

