# 🐸 Frogger Game Project

## 📋 Overview
This is a classic **Frogger** game implementation written in **C** for Atmel AVR microcontrollers. The project recreates the iconic arcade game where you control a frog navigating across traffic and obstacles to reach the other side!

## 🎮 Game Features
- 🐸 **Frog Character** - Navigate your frog across the screen
- 🚗 **Traffic** - Dodge cars and trucks moving across the road
- 🚛 **Dynamic Obstacles** - Multiple vehicle types with different patterns
- 📺 **LCD Display** - Real-time game rendering on a character LCD display
- ⌨️ **Keyboard Input** - Control the frog with directional input
- 🎯 **Objective** - Reach the safe zone at the top of the screen

## 📁 Project Structure

### 🔧 Core Files
- **`main.c`** - Main game logic and loop
- **`lcd.c` / `lcd.h`** - LCD display driver and character output functions
- **`atmel_start.c` / `atmel_start.h`** - Atmel START generated initialization code
- **`driver_isr.c`** - Interrupt service routines

### 🛠️ Configuration & Headers
- **`Config/`** - Configuration files for clock and RTE components
  - `clock_config.h` - Clock configuration
  - `RTE_Components.h` - Runtime Environment components
- **`include/`** - Hardware abstraction headers
  - `driver_init.h` - Driver initialization
  - `atmel_start_pins.h` - Pin definitions
  - `port.h` - Port configuration
  - `protected_io.h` - Protected I/O operations
  - `system.h` - System definitions

### 📦 Source Code
- **`src/`** - Driver implementation
  - `driver_init.c` - Driver initialization implementation
  - `protected_io.S` - Protected I/O assembly code

### 🔨 Utilities
- **`utils/`** - Utility functions and helpers
  - `atomic.h` - Atomic operations
  - `compiler.h` - Compiler compatibility
  - `interrupt_avr8.h` - AVR8 interrupt handling
  - `assembler.h` - Assembler utilities

### 📚 Documentation
- **`doxygen/`** - Doxygen documentation generation
  - Mainpage and system documentation

### 🏗️ Build Files
- **`Debug/`** - Build output and compiled files
  - Object files, hex files, linker script output
- **`Frogger.cproj`** - Atmel Studio project file
- **`Frogger.atsln`** - Visual Studio solution file
- **`Makefile`** - Build automation script

## 🎯 Game Mechanics

### 🐸 Frog Movement
- Initial position: row 3, column 9
- Move across lanes avoiding traffic

### 🚗 Vehicle System
```c
drawCars()    // Display car sprites (##8)
drawTrucks()  // Display truck sprites (###>)
delete()      // Clear vehicle sprites
```

### 📺 LCD Display Functions
- `lcd_init()` - Initialize LCD in 4-bit mode
- `lcd_write_string()` - Display text strings
- `lcd_goto_position()` - Set cursor to specific row/column
- `lcd_line_one/two/three/four()` - Navigate to specific lines
- `lcd_clear_and_home()` - Clear display and reset cursor

## 🛠️ Technical Details

### Hardware
- **Microcontroller**: Atmel AVR (ATmega328PB)
- **Clock**: 16 MHz
- **Display**: Character LCD (4-line support)
- **I/O**: Digital input/output pins

### Build System
- **Compiler**: GCC AVR toolchain
- **Build Tool**: Make
- **IDE**: Atmel Studio

## 🚀 Getting Started

1. **Open Project** - Load `Frogger.atsln` in Atmel Studio
2. **Build** - Run Make or use the Build command
3. **Flash** - Upload the `.hex` file to your AVR microcontroller
4. **Play** - Use keyboard input to move the frog across the screen

## 👥 Authors
- Andrea Marcosano
- Ruth Dagnachew

## 📝 Version History
- **Created**: August 30, 2023

## 🎮 How to Play
1. Guide your frog from the bottom to the top of the screen
2. Avoid the traffic (cars 🚗 and trucks 🚛)
3. Navigate through multiple lanes
4. Reach the safe zone to win!

## 📞 Notes
This project demonstrates embedded systems programming including:
- Microcontroller initialization
- Driver development
- Real-time display control
- Interactive user input handling
- Game loop implementation

---

*Happy Hopping! 🐸*
