# N‑Queens Visualizer

**C++ / SFML 3** implementation of the classic N‑Queens backtracking algorithm,  
with step‑by‑step animation, pause/step controls, and solution‑by‑solution navigation.

## Features
- Auto‑step & manual stepping.
- Pause on each complete solution.
- Adjustable board size (4–16).
- HUD overlay with status and speed controls.

## Build & Run

```powershell
# from project root
mkdir build && cd build
g++ ../main.cpp ../BacktrackingSolver.cpp -o visualizer.exe `
    -I../SFML-3.0.0/include -L../SFML-3.0.0/lib `
    -lsfml-graphics -lsfml-window -lsfml-system
.\visualizer.exe
