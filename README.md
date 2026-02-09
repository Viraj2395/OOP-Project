# OOP-Project

CLI trading game built in C++ for an OOP course. Trade across physical and digital commodities, manage fees, track a portfolio, and progress day by day.

## Features
- Day-based price updates with volatility per commodity type
- Buy/sell flow with storage costs (physical) and transaction fees (digital)
- Portfolio view with holdings and total value
- Save/load game state to a local file
- Command-driven interface with help prompts

## Build
This project uses a simple Makefile and builds with `clang++`.

```sh
make
```

## Run
```sh
make run
```

## Commands (in-game)
- `next` - advance a day and update prices
- `commodity` - choose a commodity to buy/sell
- `portfolio` - view holdings and total value
- `save` - write progress to `savegame.txt`
- `load` - load progress from `savegame.txt`
- `help` - show the command list
- `exit` - quit the game

## Project Structure
- `main.cpp` - entry point
- `Game.*` - core loop and command handling
- `Commodity.*` - base commodity model
- `PhysicalCommodities.*` / `DigitalCommodities.*` - type-specific rules
- `Gems.*`, `Harvest.*`, `Crypto.*` - concrete commodity types

## Notes
- The save file is created in the project root as `savegame.txt`.
- This is a terminal-based game; no GUI is required.
