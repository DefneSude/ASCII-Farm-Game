\# 🌾 ASCII Farm Game



\*\*A text-based farming simulation game written in C, featuring dynamic weather, a market economy, and a save system.\*\*



This project is a console-based simulation where players manage a farm, grow crops, and trade resources. It utilizes the standard C library along with `windows.h` for console manipulation and coloring.



\## 🌟 Key Features



\* \*\*🌱 Farming Mechanics:\*\* A complete cycle of buying seeds, planting, watering, and harvesting crops.

\* \*\*🌦️ Dynamic Weather System:\*\* Random weather events occur daily. Rain automates watering, while extreme heat causes evaporation.

\* \*\*💧 Water Management:\*\* Manage your limited water supply and refill from the well when needed.

\* \*\*💰 Market Economy:\*\* Sell harvested wheat to earn money and purchase new seeds from the shop.

\* \*\*💾 Save/Load System:\*\* Robust file handling allows you to save progress and resume later (uses `farm\_save.txt`).

\* \*\*🎨 Colorful Interface:\*\* Enhanced visual experience using console text coloring.



\## 🎮 Controls



| Key / Input | Action |

| :--- | :--- |

| \*\*Arrow Keys (← →)\*\* | Navigate through the menu bar |

| \*\*ENTER\*\* | Select an action |

| \*\*ESC\*\* | Exit the game |

| \*\*Coordinate Input\*\* | Enter `Row` and `Column` numbers to interact with the field |



\## 🚀 How to Run



This project is designed for \*\*Windows\*\* environments (due to the use of `windows.h` and `conio.h`).



\### 1. Compile

You can use any C compiler (like GCC) or an IDE (Dev-C++, Code::Blocks, Visual Studio).



\*\*Using GCC:\*\*

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





