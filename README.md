# 🏙️ Rouge Skylines 🌆

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**A Roguelike City Builder** built in **2 weeks** as a **school project** with no prior C++ experience.

Rouge Skylines is a console-based roguelike city-building game written in C++ and powered by [Raylib](https://www.raylib.com/) for graphics and input. This project was crafted from scratch over two weeks as part of a class assignment.

---

## ✨ Key Highlights

- 🛠️ **Built from Zero:** No prior C++ knowledge—learned and implemented core features on the fly.
- 🎮 **Gameplay:** Manage resources, construct buildings, and survive dynamic roguelike events.
- 🎨 **Raylib Integration:** Simple 2D rendering and input handling.
- ⏱️ **Rapid Development:** Completed in just 14 days!

---

## 📁 Project Structure

```text
├── .idea/                ⚙️ IDE configs
├── RougeSkylines.sln     📝 Visual Studio solution
├── RougeSkylines/        💻 Source code
│   ├── RougeSkylines.cpp 🔗 Entry point & game loop
│   ├── building.*        🏗️ Building logic
│   ├── playerStats.*     📊 Player stats & progression
│   ├── shop.*            💰 Shop & transactions
│   ├── rnd.*             🎲 RNG utilities
│   ├── txtFormat.*       🖋️ Text rendering helpers
│   ├── txtInput.*        ⌨️ Input parsing
│   └── formater.*        💬 Console formatting
├── Eirian-Regular.ttf     🔤 Font resource
├── Peaberry-Mono.otf      🔤 Font resource
├── x64/                   🚧 Build artifacts (ignored)
└── UpgradeLog.htm         📝 Auto upgrade log
```

---

## 🔧 Requirements

- 🖥️ **OS:** Windows 10/11 (or any C++17-compatible environment)
- 🛠️ **IDE/Compiler:** Visual Studio 2019+ with C++ workload or CMake + GCC/Clang
- 📦 **Raylib:** Pre-built library (or build from source)

---

## 🚀 Build & Run

### Using Visual Studio
1. **Clone:**
   ```bash
   git clone https://github.com/Dr4kfire/Rouge-Skylines.git
   cd Rouge-Skylines
   ```
2. **Open:** `RougeSkylines.sln` in Visual Studio
3. **Build:** Choose **Release** or **Debug** and hit **Build**
4. **Run:** Locate `x64/Release/RougeSkylines.exe` and play!

### Using CMake (Command Line)
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
cd ../x64/Release
./RougeSkylines.exe
```

---

## 🛡️ License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

*Happy city-building and may your skylines stand tall!* 🎉

