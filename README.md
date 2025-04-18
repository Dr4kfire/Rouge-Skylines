# Rouge Skylines

**A Roguelike City Builder** built in **2 weeks** as a **school project** with no prior C++ experience.

Rouge Skylines is a simple console-based roguelike city-building game written in C++ and utilizing [Raylib](https://www.raylib.com/) for graphics and input handling. The project was implemented from scratch over two weeks as part of a class assignment.

## Project Structure

- `.idea/` - IDE configuration files
- `RougeSkylines.sln` - Visual Studio solution file
- `RougeSkylines/` - Main game source directory
  - `RougeSkylines.cpp` - Entry point
  - `building.cpp` / `building.h` - Building placement and management logic
  - `formater.cpp` / `formater.h` - Text formatting utilities for console output
  - `playerStats.cpp` / `playerStats.h` - Tracking player health, resources, and progress
  - `rnd.cpp` / `rnd.h` - Random number generation and seed management
  - `shop.cpp` / `shop.h` - In-game shop functionality and item transactions
  - `txtFormat.cpp` / `txtFormat.h` - Formatting for special text displays (menus, messages)
  - `txtInput.cpp` / `txtInput.h` - Parsing and validation of user input
  - `Eirian-Regular.ttf`, `Peaberry-Mono.otf` - Font resources used for rendering text via Raylib
- `x64/` - Built binaries and intermediate files (ignored in source control)
- `UpgradeLog.htm` - Automatic upgrade history log

## Code Overview

The code is organized into clear, modular components that separate concerns:

- **Game Loop & Entry**: `RougeSkylines.cpp` handles initialization and the main loop.
- **Gameplay Modules**: Buildings, player stats, shop and RNG are each encapsulated in their own files.
- **Input/Output**: Text formatting and user input parsing are managed by dedicated formatter and input utilities.
- **Graphics & Input Handling**: Raylib powers the rendering of the console-like UI and captures keyboard interactions.

## Requirements

- Windows OS (tested on Windows 10/11)
- Microsoft Visual Studio 2019 or later with C++ workload
- (Optional) Any modern C++17-compatible compiler and CMake

## Building the Game

1. Clone the repository:
   ```bash
   git clone https://github.com/Dr4kfire/Rouge-Skylines.git
   cd Rouge-Skylines
   ```
2. Open `RougeSkylines.sln` in Visual Studio.
3. Build the solution in **Release** or **Debug** configuration.
4. The executable will be located in `x64/Release/` or `x64/Debug/`.

_For command-line (CMake) builds:_
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Running the Game

From the output folder (e.g., `x64/Release/`), run:
```bash
RougeSkylines.exe
```
Use the console interface to build your city, manage resources, and survive roguelike challenges.

## License

This project is under the MIT license. For more information check the LICENSE.md file.

