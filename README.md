*This project has been created as part of the 42 curriculum by jmateo-v, adrlinei.*

# Cub3D

## Description
Cub3D is a small 3D rendering engine inspired by the classic game Wolfenstein 3D.  
The goal of the project is to implement a raycasting-based renderer capable of displaying a 3D world from a 2D map.  
It introduces essential concepts in computer graphics, including:

- Raycasting and DDA (Digital Differential Analyzer)
- Player movement and rotation
- Texture loading and mapping
- Collision detection
- Real‑time rendering using MLX42

Cub3D bonus aims to broaden the mastery of these topics by providing more advanced challenges.  
The goal of this challenges is to implement a minimap, togable doors, and some sort of sprite or animations.  
The concepts included in the bonus are:  

- Minimap display
- Interactable doors
- Player interaction with the enviroment
- Animated sprites
- Sprite scaling 

The project aims to improve graphic programming on a more low level enviroment with the use of codams MLX42 and C coding skills.

---

## Instructions

### Requirements
- GCC or Clang  
- Make  
- MLX42  (included on the repo)
- GLFW (required by MLX42)  
- A valid `.cub` map file  

### Compilation
To compile the project:

```bash
make
```
This produces the executable:
cub3D

### Execution



Run the program with a valid map:
```bash
./cub3D maps/test_map_E.cub
```

A valid .cub file must contain:

- Texture paths for each wall: NO, SO, WE, EA
- Floor and ceiling colors in RGB format
- Exactly one player start position (N, S, E, or W)

Controls

- W / A / S / D — Move
- Left / Right arrows — Rotate
- Mouse movement — Rotate
- ESC — Quit

## Resources

Documentation & Tutorials

MLX42 https://github.com/codam-coding-college/MLX42

Raycasting tutorial by Lode Vandevenne: https://lodev.org/cgtutor/raycasting.html

MLX42 documentation https://github.com/codam-coding-college/MLX42/blob/master/docs/index.md

42 subject PDF

## Use of AI

AI was used in the following ways:

Writing boilerplate code and overall reducing manual typing

Making formatting Norminette way easier and faster

Making finding new resources easier

Helping structure the README file
