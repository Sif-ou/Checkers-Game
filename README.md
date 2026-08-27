# C++ SDL2 Checkers Game

A fully-featured, classic Checkers (Draughts) implementation written in C++ using the SDL2 library for 2D rendering and event handling. 

This project features a complete logic engine for standard checkers mechanics, including valid move highlighting, forced captures, chained captures, and piece promotion to "Kings."

## 🎮 Play the Game (No Code Required)
If you just want to play the game on Windows without dealing with code or compilers, head over to the **Releases** tab on the right side of this GitHub repository. Download the latest `Checkers_Windows.zip`, extract the folder, and double-click `checkers.exe`!

## Features

* **Classic Checkers Rules**: Standard 8x8 board gameplay with two teams (Red vs. Black).
* **Interactive GUI**: Smooth mouse-driven tracking and piece selection.
* **Move Highlighting**: Visually displays valid moves and target tiles for the selected piece.
* **Forced Captures**: The game logic enforces mandatory captures. If a capture is available, the player is forced to take it.
* **Chained Captures**: Support for multiple successive jumps if the advantage persists.
* **King Promotion**: Pieces reaching the opponent's back row are upgraded to Kings, granting them the ability to move and capture in all four diagonal directions.
* **Debugging Tools**: Built-in keyboard shortcuts to print board states, team data, and manipulate turns directly from the console.

## Dependencies

To compile and modify this project, you need the following libraries installed on your system:
* [SDL2](https://www.libsdl.org/download-2.0.php) (Core window and rendering)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/) (For loading PNG assets)
* A C++11 (or higher) compatible compiler (e.g., g++, clang, MSVC)
* `make` (For running the build script)
* Note: All required DLL files are included.

## Assets Required

The game expects an `assets` directory in the root folder alongside the executable, containing the following image files:
* `assets/board.png` (The checkers board)
* `assets/pieces.png` (Spritesheet containing the Red and Black pieces, both normal and upgraded)
* `assets/move.png` (Highlight/focus square for tracking and movement)

## Controls

* **Left Mouse Click**: Select a piece / Move a piece to a highlighted square.
* **Esc**: Quit the game.
* **Left Shift**: Reload / Restart the game instance.

**Debug Controls (Outputs to Console):**
* **I**: Print the current internal board state and forced-take list.
* **P**: Print the alive/dead status of all pieces for both Red and Black teams.
* **N**: Print neighbor and direction data for the currently tracked piece.
* **T**: Manually swap the current turn.
* **X**: Manually edit a piece's direction/status via console input.

## Project Structure

* `main.cpp` - Entry point and game launcher loop.
* `game.cpp` / `.hpp` - Core game loop, SDL initialization, event polling, and state management (60 FPS cap).
* `board.cpp` / `.hpp` - Board initialization, grid rendering, and updating logical piece positions.
* `piece.cpp` / `.hpp` - Class definitions for individual `Piece` objects and `Team` management.
* `Movement.cpp` / `.hpp` - Pathfinding, move validation, and drawing movement highlights.
* `take.cpp` / `.hpp` - Complex logic for scanning the board for forced captures, chained takes, and King captures.
* `track.cpp` / `.hpp` - Translates mouse coordinates to board grid coordinates and handles selection focus.
* `struct.cpp` / `.hpp` - Core structures (`Cordinates`, `cell`), global constants, and helper math functions.

## Compilation (Cross-Platform)

This project includes a smart `Makefile` that automatically detects your operating system and applies the correct compiler paths. It officially supports **Windows**, **Linux**, and **macOS**.

### 1. Install SDL2
* **Linux (Ubuntu/Debian):** 
  ```bash
  sudo apt-get install libsdl2-dev libsdl2-image-dev
