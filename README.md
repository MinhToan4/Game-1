# 2D Platformer Game

🎥 **Gameplay Demo Video**: **[Watch here](https://www.youtube.com/watch?v=NuZzsPUH6F8)**

## Project Overview
This is a 2D platformer game developed in C++ using the SFML library. The project demonstrates proficiency in game development, object-oriented programming, and multimedia integration. The game features a player character navigating through levels, engaging in combat with enemies, and managing resources like health and score.

## Key Features
- **Player Mechanics**: Implemented character movement, jumping, and shooting mechanics with smooth animations.
- **Enemy AI**: Developed autonomous enemy entities with patrol patterns and collision detection.
- **Dynamic Platforms**: Created moving platforms for enhanced level design and interactivity.
- **Health System**: Integrated a visual health bar for player status monitoring.
- **Audio Integration**: Added sound effects for actions such as shooting and enemy defeat using SFML's audio module.
- **Scoring and Progression**: Implemented a scoring system with level transitions and game over conditions.
- **Level Design**: Utilized TMX files for level parsing with TinyXML, supporting multiple levels.

## Technologies Used
- **Programming Language**: C++
- **Graphics Library**: SFML (Simple and Fast Multimedia Library) for rendering, window management, and input handling.
- **Audio**: SFML for sound effects and background music.
- **XML Parsing**: TinyXML for loading level data from TMX files.
- **Build System**: Makefile for Windows compilation.
- **Development Environment**: Visual Studio or compatible C++ compiler.

## System Requirements
- C++ Compiler (e.g., g++ or Visual Studio).
- SFML Library (version 2.x).
- TinyXML for level file parsing.

## Installation and Setup
1. Install SFML: Download and install SFML from the [official website](https://www.sfml-dev.org/download.php). Ensure DLLs are copied to the project directory or system PATH.
2. Clone or download the project repository.
3. Compile the project using the provided Makefile or manual compilation.

## Build and Run Instructions
### Using Makefile (Windows)
1. Open Command Prompt or PowerShell in the project directory.
2. Run: `make -f Makefile.win`
3. Execute: `game.exe`

### Manual Compilation
Compile with the following command:
```
g++ -o game.exe main.cpp source/*.cpp source/TinyXML/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
Run the executable: `./game.exe` (or `game.exe` on Windows).

## Controls
- **A / Left Arrow**: Move left
- **D / Right Arrow**: Move right
- **W / Up Arrow**: Jump
- **S / Down Arrow**: Crouch (if applicable)
- **Space**: Shoot
- **P**: Display leaderboard
- **Escape**: Exit game

## Project Structure
- `main.cpp`: Main entry point of the application.
- `source/`: Contains header files (.hpp) and implementations for classes such as Player, Enemy, Bullet, etc.
- `files/`: Stores assets including images, sounds, and level files (.tmx).
- `Makefile.win`: Build script for Windows.
- `build_instructions.md`: Build documentation (currently empty).