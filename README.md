# Project 2: Pong Variations

## CS-UY 3113

This project is a 2D Pong game built in C++ by *Riccardo Bean* as part of CS-UY 3113 coursework.

## Game Features

* Single-player mode against a computer-controlled opponent
* Two-player mode with local keyboard controls
* Three lives per player, displayed using a health bar
* Multiple balls that move independently and bounce off the screen boundaries
* Randomized ball speeds and directions
* Crazy Mode with increasing ball speeds and progressively smaller paddles
* Demon ball that introduces additional challenges in Crazy Mode
* Welcome screen, instructions screen, and game-over screens for each possible winner

## Controls

* `W` / `S` — Move Player 1's paddle up and down
* `↑` / `↓` — Move Player 2's paddle up and down in multiplayer mode
* `1` — Activate one extra ball
* `2` — Activate two extra balls
* `3` — Activate three extra balls
* `T` — Switch between AI and multiplayer modes during gameplay
* `P` — Pause the game
* `R` — Restart the game
* `M` — Return to the main menu from the instructions or game-over screen
* `Esc` — Pause the game or exit from the menu

## Crazy Mode

* Ball speeds increase by 20% every five seconds
* Paddles become smaller as the game progresses
* The demon ball appears after 15 seconds
* An additional ball is activated after 20 seconds if the first extra ball is not already active
* The game becomes progressively more difficult as the balls speed up and the paddles shrink

## Project structure

* `main.cpp` — Game setup, input handling, game logic, collision detection, and rendering
* `assets/game/` — Textures used for the background, paddles, balls, health bar, menus, and game-over screens
* `CS3113/` — The project's graphics and game support code
* `makefile` — Builds the application

## How to run it

From the project directory, build and run the program with:

```bash
make run
```

If the build succeeds, the application window should open and display the game.

## Credits

* **Hearts/Health Bar:** [Hearts UI](https://swooshwhoosh.itch.io/heartsui)
* **Keys/Buttons:** *Neon Input Prompts* by Oğuzhan Girgin, licensed under [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/). [Asset page](https://www.colorosse.com/assets/2d/ui/neon-input-prompts)
* **Space Background:** [Warped Space Backgrounds](https://ansimuz.itch.io/warped-space-backgrounds)
* **Pong Assets:** [Simple Ping Pong Assets](https://myebstudios.itch.io/simple-ping-pong-assets)
* **Demon:** [Spike Ball PNG File](https://josh017891.itch.io/spike-ball-png-file)

All other assets were created by myself.
