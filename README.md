# 🏓 ConsolePong

> A tiny arcade living entirely inside the Windows console — Pong, a Tetris prototype and a real-time ray-traced demo, rendered character by character.

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?style=flat&logo=cplusplus&logoColor=white)
![WinAPI](https://img.shields.io/badge/WinAPI-Console%20API-0078D6?style=flat)
![IDE](https://img.shields.io/badge/Visual%20Studio-2022-5C2D91?style=flat)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=flat)
![License](https://img.shields.io/badge/License-MIT-green?style=flat)

## ✨ Features

- 🖥️ **Custom console renderer** — double-buffered drawing via `CreateConsoleScreenBuffer` + `WriteConsoleOutputCharacter`/`Attribute`, with text, rectangles and per-cell colors
- 🕹️ **Game selector menu** — pick a game with the keyboard, switch back any time
- 🏓 **Pong** — you vs. a ball-tracking AI paddle, with a live score HUD
- 🧱 **Tetris (work in progress)** — falling pieces, pause and horizontal movement; rotation and dropping are still stubs
- 🔴 **"3D Donut" demo** — a software ray tracer shading an animated sphere per console cell, with a movable camera
- 📊 **Debug overlay** — FPS and frame-time readout, plus a vsync toggle

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` / `S` | Navigate menu / move paddle (Pong) / move camera (demo) |
| `Enter` | Start selected game |
| `A` / `D` | Move piece (Tetris) / move camera (demo) |
| `P` | Pause (Tetris) |
| `X` | Back to the game menu |
| `F1` | Toggle debug overlay (FPS / frame time) |
| `F2` | Toggle vsync |
| `Q` | Quit |

## 🔨 Build

1. Clone the repo
   ```sh
   git clone https://github.com/kewldan/ConsolePong
   ```
2. Open `PingPong.sln` in [Visual Studio 2022](https://visualstudio.microsoft.com/) (v143 toolset)
3. Build and run — that's it, no external dependencies

## 📄 License

MIT — see [LICENSE](LICENSE).
