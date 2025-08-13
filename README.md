## 🎮 cub3D

### 📌 About
cub3D is a 42 project inspired by the classic **Wolfenstein 3D**, developed to explore raycasting concepts, 2D/3D rendering, and image manipulation using **MiniLibX**, , following the strict [Norminette](https://github.com/42School/norminette) coding style.  
The goal is to create a simple graphics engine capable of:
- Rendering textured walls using raycasting
- Detecting collisions with the environment
- Allowing free player movement in a map
- Supporting custom map files
- Supporting different wall textures and floor/ceilling collors

---

### ⚙️ How to build<br> 
<details>
<summary>📦 Dependencies</summary><br>
- In order to compile and run the game, you will need several dependencies, which you can install on the terminal:
<br>

```bash
sudo apt-get install gcc make libxext-dev libx11-dev libbsd-dev libxrandr-dev libxi-dev libxinerama-dev
```
</details>
<details>
<summary>🏗️ Compilation</summary><br>

1. **Clone the repository**

```bash
https://github.com/mmiguelo/Cub3d.git
cd cub3d
```
2. **Install minilibx library**
   
```bash
make download
```
3. **Compile C files**
   
```bash
make
```
4. **Run the game**
   
```bash
./cub3D maps/valid/map.cub
```
5. **other make commands**

| Command | Description |
|---|---|
| make re | Recompiles the entire project |
| make clean | Removes object files |
| make fclean | Removes object files and executable |

</details>

---

### 🚀 Mandatory Project<br>
<details>
<summary>✨ Features</summary><br>
  
+ Parsing of custom ```.cub``` maps
+ Support for textures for each direction (N, S, E, W)
+ Customizable floor and ceiling colors
+ Wall rendering using raycasting algorithm
+ Free player movement with camera rotation

</details>

<details>
<summary>🎮 Controls</summary><br>

| Key   | Action            |
| ----- | ----------------- |
| `W`   | Move forward      |
| `S`   | Move backward     |
| `A`   | Strafe left       |
| `D`   | Strafe right      |
| `←`   | Rotate view left  |
| `→`   | Rotate view right |
| `ESC` | Exit game         |

</details>

---

### 🎯 Bonus
<details>
<summary>✨ Features</summary><br>

+ Real-time minimap rendering
+ Real time FPS visualizer
+ Addition of distance-based brightness falloff
+ Wall collision detection
+ Rotation of the point of view with the mouse

</details>

<details>
<summary>🎮 Controls</summary><br>

| Key   | Action            |
| ----- | ----------------- |
| `W`   | Move forward      |
| `S`   | Move backward     |
| `A`   | Strafe left       |
| `D`   | Strafe right      |
| `← / →` | Rotate camera  |
| *Mouse Move* | Rotate camera |
| `ESC` | Exit game         |

</details>

---

### TODO:

+ add minimap exemples and fps
+ add picture of dist-based brightness falloff
+ add demonstrating video

<p align="right">(<a href="#readme-top">get to top</a>)</p>
