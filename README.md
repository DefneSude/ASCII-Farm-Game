# 🌾 ASCII Farm Game

**A text-based farming simulation game written in C, featuring dynamic weather, a market economy, and a time-based save system.**

This project is a console-based simulation where players manage a farm, grow crops, and trade resources. It utilizes the standard C library along with `windows.h` and `conio.h` for console manipulation, coloring, and keyboard input handling.

## 🌟 Key Features

* **🌱 Farming Mechanics:** A complete cycle of buying seeds, planting, watering, and harvesting wheat. 
* **⛅ Dynamic Weather & Time:** Random weather events occur daily. Rain automates watering, while extreme heat causes evaporation. The game features a real-time tracking system that influences in-game hours and minutes.
* **💧 Water Management:** Manage your limited water supply and refill from the well when needed.
* **💰 Market Economy:** Sell harvested wheat to earn money and purchase new seeds or energy drinks from the interactive shop.
* **🔋 Energy System:** Players have limited moves per day and must manage their energy by napping or consuming items to avoid collapsing.
* **💾 Save/Load System:** Robust file handling allows you to save progress, map state, and resources to resume later (uses `farm_save.txt`).
* **🎨 Colorful Interface:** Enhanced visual experience using console text coloring to differentiate field elements and UI components.

## 🗺️ Map Legend (Symbols)

The game uses specific ASCII characters and colors to represent the state of your field:
* `.` : Empty Area
* `S` : Seed (Yellow)
* `W` : Watered Seed (Blue)
* `G` : Grown Crop - Ready to Harvest (Green)
* `D` : Dried Seed - Needs saving (Orange)
* `!` : Dried Wheat (Orange)
* `?` : Saved Crop (Light Blue)
* `X` : Dead Crop (Red)

## 🎮 Controls

| Key / Input | Action |
| :--- | :--- |
| **Arrow Keys (← →)** | Navigate through the menu bar and shop items |
| **ENTER** | Select an action |
| **ESC** | Exit the game or current menu |
| **Coordinate Input** | Enter `Row` and `Column` numbers to interact with the field |

## 🚀 How to Run

This project is designed for **Windows** environments (due to the use of `windows.h` and `conio.h`).

### 1. Compile
You can use any C compiler (like GCC) or an IDE (Dev-C++, Code::Blocks, Visual Studio).

**Using GCC:**
```bash
gcc main.c -o farm.exe



Execute the generated file:



```bash
./farm.exe

📂 Project Structure

* main.c: The entry point and game loop.



* farm\_functions.c: Contains game logic (planting, harvesting, weather algorithms).



* farm\_config.h: Configuration definitions and global variables.



* farm\_save.txt: Stores game data (created automatically after saving).





