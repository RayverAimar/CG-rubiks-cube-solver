<div align="center">

# Rubik's Cube — OpenGL + Kociemba Solver

A C++ Rubik's Cube renderer in OpenGL with a built-in implementation of [Kociemba's two-phase algorithm](https://kociemba.org/cube.htm) for solving any scrambled state. Ships an in-app menu (ImGui) with two modes — a single 3×3×3 cube, or a 27-cube **HyperCube** that scrambles and reassembles itself.

[![CI](https://github.com/RayverAimar/CG-rubiks-cube-solver/actions/workflows/ci.yml/badge.svg)](https://github.com/RayverAimar/CG-rubiks-cube-solver/actions/workflows/ci.yml)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![OpenGL 3.3](https://img.shields.io/badge/OpenGL-3.3%20core-5586A4.svg?logo=opengl&logoColor=white)](https://www.opengl.org/)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

<img src="docs/hyper.png" alt="HyperCube — 27 Rubik's cubes scrambled together" width="720"/>

</div>

---

## Modes

Pick a mode from the main menu (Tab anywhere returns to it):

| | |
|---|---|
| <img src="docs/menu.png" width="360"/> | <img src="docs/rubik.png" width="360"/> |
| **Main menu** — choose between the two render modes. | **Rubik (3×3×3)** — a single cube. F/B/U/D/L/R to turn faces, S to scramble, Space to auto-solve with Kociemba. |

**HyperCube (27 cubes).** A 3×3×3 cluster of 27 independent Rubik's cubes. Scramble runs the outer rotations on the cluster first, then scrambles each inner cube. Auto-solve plays the reverse as a 3-phase animation:

1. **Expand** — the 27 sub-cubes drift outward so each has room to animate.
2. **Solve in place** — every sub-cube runs its own Kociemba solve.
3. **Reassemble** — solved cubes slide back to their original slot, then the cluster-level inverse moves run.

The status banner at the top reports what's active (`Scrambling – R`, `Auto-solving – U'`, etc.). The help overlay in the corner stays open until you toggle it with `H`.

## Build

The project pulls its window/input (GLFW), UI (Dear ImGui), and math (GLM) dependencies via CMake `FetchContent` — you don't need to install them manually.

**Requirements** (any one platform):

- CMake **≥ 3.24**
- A C++17 compiler — clang, gcc, or MSVC
- Git
- A working OpenGL 3.3 driver (any modern GPU)

**Same three commands on Linux, macOS, and Windows:**

```bash
git clone https://github.com/RayverAimar/CG-rubiks-cube-solver.git
cd CG-rubiks-cube-solver

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

The first configure takes ~1 minute (CMake clones GLFW 3.4, GLM 1.0.1, and ImGui 1.90 from source). Subsequent builds are incremental.

### Run

```bash
# Linux / macOS
./build/rubik

# Windows
build\Release\rubik.exe
```

### Linux — extra system packages

GLFW needs X11 / Wayland headers when building from source:

```bash
sudo apt install xorg-dev libxkbcommon-dev libwayland-dev wayland-protocols
```

For headless environments (CI, servers) prefix the run with `xvfb-run`:

```bash
xvfb-run -a ./build/rubik --screenshot-view rubik capture.ppm
```

## Controls

| Key | Action |
|-----|--------|
| `F` `B` `U` `D` `L` `R` | Rotate face clockwise (Front / Back / Up / Down / Left / Right) |
| `Shift` + face key | Rotate face counter-clockwise |
| `S` | Scramble (random sequence) |
| `Space` | Auto-solve with Kociemba's algorithm |
| `Tab` | Return to the main menu |
| `H` | Toggle the help overlay |
| `↑ ↓ ← →` | Move the camera |
| Mouse | Look around |
| Mouse wheel | Zoom |
| `Esc` | Quit |

## Project layout

```
CG-rubiks-cube-solver/
├── main.cpp                    Entry point, ImGui menu + key/mouse callbacks
├── include/
│   ├── open_gl_loader.h        GLFW window + GL context bootstrap
│   ├── camera.h                FPS-style camera
│   ├── shader.h                GLSL program loader
│   ├── point.h, vector3d.h,
│   │   matrix4d.h, math_ops.h  Custom 3D math primitives
│   ├── square.h, cube.h,
│   │   rubik.h, hyper_cube.h   Cube geometry + animation
│   └── solver/                 Kociemba two-phase solver (C++ port)
│       ├── coordcube.cpp       Coordinate representation
│       ├── cubiecube.cpp       Cubie-level operations
│       ├── facecube.cpp        Sticker-level state
│       ├── prunetable_helpers  Pruning heuristics
│       └── search.cpp          IDA* search
├── shaders/                    GLSL vertex + fragment shaders
├── external/glad/              Vendored GLAD loader (GL 3.3 core)
└── .github/workflows/ci.yml    Linux + macOS + Windows build matrix
```

## How it works

**Renderer.** Each of the 27 cubies is built from 6 `Square` instances batched into a single VAO. The `Rubik` class composes a 3×3×3 grid and animates face rotations via per-axis rotation matrices applied in the shader as `model · face_rotation · cubie_translation`. The HyperCube nests 27 of these.

**Solver.** When you press <kbd>Space</kbd>, the current cube state is encoded into the standard 54-character facelet string, fed into a C++ port of Herbert Kociemba's two-phase algorithm, and the resulting move sequence is replayed by the renderer at animation speed. In HyperCube mode each of the 27 sub-cubes runs an independent solve in parallel.

## Headless screenshots

The `--screenshot-view <view> <path>` flag renders a few warmed-up frames into a chosen mode and dumps the framebuffer as a PPM. Views: `menu`, `rubik`, `hyper`.

```bash
./build/rubik --screenshot-view hyper capture.ppm
sips -s format png capture.ppm --out capture.png   # macOS
convert capture.ppm capture.png                    # Linux (ImageMagick)
```

The legacy `--screenshot <path>` is kept for the CI smoke test (defaults to the HyperCube view).

## License

[MIT](LICENSE)
