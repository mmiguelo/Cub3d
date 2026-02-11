<a id="readme-top"></a>

<div align="center">

# 🏰 cub3D

A raycasting engine inspired by the legendary **Wolfenstein 3D** — built from scratch in C with MiniLibX

<br>

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norm-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)

</div>

---

### 📑 Table of Contents

- [📌 About](#-about)
- [⚙️ How to Build](#%EF%B8%8F-how-to-build)
- [🗺️ Map Format](#%EF%B8%8F-map-format)
- [🚀 Mandatory](#-mandatory)
- [🎯 Bonus](#-bonus)
- [🔦 How It Works — Raycasting](#-how-it-works--raycasting)
- [📂 Project Structure](#-project-structure)
- [📝 TODO](#-todo)
- [👥 Authors](#-authors)

---

### 📌 About

**cub3D** is a graphics project from the [42 School](https://42.fr) curriculum that challenges you to build a first-person 3D maze renderer using raycasting — the same technique that powered the original **Wolfenstein 3D** (1992).

The engine parses `.cub` map files, loads wall textures per cardinal direction, and renders a real-time perspective view using the **Digital Differential Analyzer (DDA)** algorithm, all within the constraints of the [Norminette](https://github.com/42School/norminette) coding standard.

> Built by **two developers** working in tandem — combining parsing, rendering, and an extensive bonus feature set.

---

### ⚙️ How to Build

<details>
<summary><b>📦 Dependencies</b></summary><br>

Install the required development libraries:

```bash
sudo apt-get install gcc make libxext-dev libx11-dev libbsd-dev libxrandr-dev libxi-dev libxinerama-dev
```

</details>

<details>
<summary><b>🏗️ Compilation</b></summary><br>

**1. Clone the repository**

```bash
git clone https://github.com/mmiguelo/Cub3d.git
cd Cub3d
```

**2. Download the MiniLibX library**

```bash
make download
```

**3. Compile and run**

```bash
make                              # Mandatory version
./cub3D maps/valid/map.cub

make bonus                        # Bonus version
./cub3D_bonus maps/valid/bonus.cub
```

</details>

<details>
<summary><b>🔧 Makefile Targets</b></summary><br>

| Target | Description |
|:---|:---|
| `make` | Compile the mandatory version |
| `make bonus` | Compile the bonus version |
| `make download` | Download MiniLibX into `./minilibx-linux` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executables |
| `make re` | Full recompile (mandatory + bonus) |

</details>

---

### 🗺️ Map Format

Maps use the `.cub` extension and follow this structure:

```
SO textures/wall.xpm          ← South wall texture
NO textures/wall_1_.xpm       ← North wall texture
WE textures/wall_2_.xpm       ← West wall texture
EA textures/wall_3_.xpm       ← East wall texture

F 191, 160, 116                ← Floor color (R, G, B)
C 229, 227, 196                ← Ceiling color (R, G, B)

        111111
        100001
        1000N1                 ← Map grid
        100001
        111111
```

**Map characters:**

| Char | Meaning |
|:---:|:---|
| `0` | Empty walkable space |
| `1` | Wall |
| `N` `S` `E` `W` | Player spawn (facing direction) |
| `D` | Door — always present *(bonus)* |
| `d` | Door — day only *(bonus)* |
| `n` | Door — night only *(bonus)* |

> The map must be fully enclosed by walls (`1`). Textures must be valid `.xpm` files, and RGB values must be in range `0–255`.

---

### 🚀 Mandatory

<details>
<summary><b>✨ Features</b></summary><br>

- Parsing and validation of `.cub` map files (textures, colors, map grid)
- Cardinal wall textures (`NO`, `SO`, `EA`, `WE`)
- Customizable floor and ceiling colors via RGB
- Real-time wall rendering using DDA raycasting
- Smooth player movement with wall collision detection
- Camera rotation via keyboard

</details>

<details>
<summary><b>🎮 Controls</b></summary><br>

| Key | Action |
|:---:|:---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `← / →` | Rotate camera |
| `ESC` | Quit game |

</details>

---

### 🎯 Bonus

<details>
<summary><b>✨ Features</b></summary><br>

| Feature | Description |
|:---|:---|
| **Minimap** | Real-time rotating minimap that updates dynamically with in-game events |
| **Day / Night Cycle** | Ambient lighting cycles through morning → noon → evening → night using 4 LERP color transitions |
| **Dynamic Ceiling Colors** | Ceiling color shifts smoothly to match time of day (sky blue → warm yellow → orange → dark blue) |
| **Distance Brightness** | Walls and surfaces darken with distance for depth perception |
| **Doors** | Interactive doors with open/close animation — supports *always*, *day-only*, and *night-only* modes |
| **Room Visibility** | Interior of rooms is visible when doors are open, even from outside |
| **Flashlight** | Toggleable flashlight with a realistic flicker effect |
| **Sprint** | Hold shift to run at increased speed |
| **Look Up / Down** | Vertical camera movement for enhanced perspective |
| **4D Mode (Indoor / Outdoor)** | Toggle between indoor and outdoor rendering in real time using `T` — dynamically switches floor/ceiling textures, lighting, and atmosphere |
| **FPS Counter** | Real-time frames-per-second display |
| **Mouse Look** | Camera rotation via mouse movement |

</details>

<details>
<summary><b>🎮 Controls</b></summary><br>

| Key / Input | Action |
|:---:|:---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `Shift` | Sprint / Run |
| `← / →` | Rotate camera left / right |
| `↑ / ↓` | Look up / down |
| *Mouse Move* | Rotate camera |
| `E` | Interact with door |
| `F` | Toggle flashlight |
| `T` | Toggle Indoor / Outdoor mode (4D switch) |
| `ESC` | Quit game |

</details>

---

### 🔦 How It Works — Raycasting

The engine casts one ray per screen column from the player's position. Each ray advances through the grid using the **DDA algorithm** until it hits a wall, calculating the perpendicular distance to determine wall height on screen.

```
                Player (P)
                    │
       ┌────────────┼────────────┐
       │     FOV 66°             │
       │    ╱       │       ╲    │
       │   ╱   ray  │  ray   ╲   │
       │  ╱         │         ╲  │
       │ ╱          │          ╲ │
       │╱           │           ╲│              
       ╱────────────┼────────────╲
      ╱             │             ╲
     ╱              │              ╲
    ╱               │               ╲
  ┌─────┬─────┬─────┬─────┬─────┬─────┐
  │  █  │     │     │     │     │  █  │  ← Grid cells
  ├─────┼─────┼─────┼─────┼─────┼─────┤
  │  █  │  █  │     │     │  █  │  █  │
  ├─────┼─────┼─────┼─────┼─────┼─────┤
  │  █  │  █  │  █  │  █  │  █  │  █  │
  └─────┴─────┴─────┴─────┴─────┴─────┘

  Each column on screen = 1 ray
  Wall height ∝ 1 / perpendicular_distance
```

**Pipeline overview:**

```
  .cub file                                              Frame buffer
  ────────                                               ────────────
  ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────────────┐
  │  Parser  │───▶│  Init &  │───▶│ Raycast  │───▶│  Render Textured │
  │  & Map   │    │  Player  │    │   DDA    │    │  Walls + F/C     │
  └──────────┘    └──────────┘    └──────────┘    └──────────────────┘
                                       │
                              ┌────────┴────────┐  (bonus)
                              ▼                 ▼
                        ┌──────────┐     ┌──────────┐
                        │ Minimap  │     │  Doors / │
                        │  + FPS   │     │  Lights  │
                        └──────────┘     └──────────┘
```

---

### 📂 Project Structure

```
Cub3d/
├── Makefile
├── includes/
│   ├── cub3D.h               # Main header (mandatory)
│   ├── cub3D_bonus.h         # Bonus header (extended features)
│   ├── ray.h                 # Raycasting structs
│   └── draw.h                # Drawing / rendering structs
├── src/                       # ── Mandatory sources ──
│   ├── main.c
│   ├── free.c
│   ├── init/
│   │   └── data.c
│   ├── parse/
│   │   ├── 01_parse.c        # Entry point for parsing
│   │   ├── 02_extensions.c   # File extension validation
│   │   ├── 03_textures.c     # Texture path parsing
│   │   ├── 04_color.c        # RGB color parsing
│   │   ├── 05_map.c          # Map grid parsing
│   │   └── 06_map_utils.c    # Map helper functions
│   └── game/
│       ├── game_loop.c        # Main loop (events + render)
│       ├── raycasting.c       # DDA raycasting core
│       ├── render.c           # Wall / texture rendering
│       ├── player.c           # Player position updates
│       ├── collisions.c       # Wall collision detection
│       ├── keypress_handler.c # Keyboard input
│       └── close_window.c     # Clean exit
├── src_bonus/                 # ── Bonus sources ──
│   ├── main_bonus.c
│   ├── cycle_bonus.c          # Day / night cycle logic
│   ├── init_bonus/
│   ├── parse_bonus/
│   │   └── 07_parse_doors_bonus.c
│   ├── game_bonus/
│   │   ├── raycasting_bonus.c
│   │   ├── render_bonus.c
│   │   ├── render_fc_bonus.c  # Floor / ceiling rendering
│   │   └── ...
│   ├── door_bonus/            # Door interaction & animation
│   ├── light_bonus/           # Distance-based brightness
│   ├── flashlight_bonus/      # Flashlight mechanic
│   ├── minimap_bonus/         # Rotating minimap renderer
│   ├── fps_bonus/             # FPS counter
│   └── free_bonus/
├── libft/                     # Custom C library (libft + ft_printf + GNL)
├── maps/
│   ├── valid/                 # Playable .cub maps
│   └── invalid/               # Edge-case test maps (29 files)
└── textures/
    ├── *.xpm                  # Wall textures (mandatory)
    └── bonus/                 # Bonus textures (doors, ceiling, floor, sun, moon…)
```

---

### 📝 TODO

<details open>
<summary><b>🎮 Game</b></summary>

- [ ] Add item inside a room to trigger end-game
- [ ] Create item that can only be collected during day / night
- [ ] Place clue item in easternmost part of map and another in westernmost part

</details>

<details open>
<summary><b>📸 GitHub</b></summary>

- [ ] Add screenshot of distance-based brightness falloff (before / after)
- [ ] Add demo video showcasing the full day / night cycle

</details>

---

<div align="center">

### 👥 Authors

[![mmiguelo](https://img.shields.io/badge/mmiguelo-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/mmiguelo)
[![frbranda](https://img.shields.io/badge/frbranda-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/KrispyFbacon)

</div>

<p align="right">(<a href="#readme-top">back to top</a>)</p>
