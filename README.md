# DE1-SOC-miniproject

# Num Gusher

## Overview

Num Gusher is a simple game developed for an embedded system that interacts with hardware switches and buttons. The game displays a grid of pixels on a screen and allows players to guess a randomly generated number between 0 and 9. The game is implemented in C and uses custom functions to handle graphical output and interaction.

## Features

- **Graphics Drawing:** Draws lines and pixels to create game visuals and text on the screen.
- **Random Number Generation:** Custom random number generator to produce numbers between 0 and 9.
- **User Interaction:** Uses hardware switches and buttons to allow user input and control the game flow.
- **Instructions and Feedback:** Provides instructions on how to play and feedback based on the player's guess.

## Requirements

- An embedded system with a VGA display and switch/button interfaces.
- A C compiler capable of compiling code for the embedded system.

## Files

- `main.c`: Contains the main logic of the game, including functions for graphics rendering, game logic, and user interaction.

## Functions

- `void start()`: Initializes the game, displays the welcome message, and waits for the user to start the game.
- `void display(int SW_value)`: Displays a number pattern based on the switch value.
- `void write_pixel(int x, int y, int color)`: Writes a pixel with the specified color to the screen.
- `void vertical_line(int x, int y1, int y2, int thick, int color)`: Draws a vertical line.
- `void horizontal_line(int y, int x1, int x2, int thick, int color)`: Draws a horizontal line.
- `void draw_line(int x1, int y, int x2, short color)`: Draws a line of a fixed thickness.
- `void game()`: Manages the game loop and handles user input.
- `void processing(int SW_value)`: Processes the user's input and provides feedback.
- `void final_page()`: Displays the final page when the user wins the game.
- `void instructions()`: Displays the game instructions.
- `void clear_screen()`: Clears the entire screen.
- `void clear_screen2()`: Clears the screen and text area.
- `void write_char(int x, int y, char c)`: Writes a character to the screen at specified coordinates.
- `int my_rand()`: Custom random number generator function.

## Building and Running

1. **Set Up the Environment:** Ensure you have the necessary tools and libraries for compiling C code for your embedded system.

2. **Compile the Code:** Use your C compiler to build the project. For example:
   ```bash
   gcc -o num_gusher main.c
