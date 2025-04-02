# 🎮 Tetris Game

A classic Tetris game built with **C++** and **SFML** (Simple and Fast Multimedia Library). This project was made focusing on game logic, object-oriented design, and graphical rendering.

## 🧩 Features

- Real-time gameplay with falling tetrominoes
- Rotation and movement controls
- Line clearing
- Game Over screen
- Dynamic piece colors and responsive UI

## 🛠️ Built With

- **C++**
- **SFML** (Graphics, Window, Audio modules)

## 🚀 Getting Started

### Prerequisites

- C++17 or later
- SFML (v2.5 or later)

### 🎮 Controls
Key	Action
  ← / → **OR** A / D	Move piece left/right
  ↑ **OR** W	Rotate piece
  ↓	**OR** S Drop faster

## 📸 Screenshots
<img width="595" alt="Game start screen" src="https://github.com/user-attachments/assets/0a4bc65a-c60d-4c85-83f8-0b9a9aedd752" />
<img width="598" alt="Initial gameplay" src="https://github.com/user-attachments/assets/88ca97fb-ee79-4bbb-8e54-ae893bf91e28" />

# 📚 Lessons Learned
This project helped reinforce my understanding of:
- **Object-oriented programming**: Designing modular classes like `Field` and `Block` to represent game elements
- **Data structures**:
  - Used a **2D array** to represent the game board grid and store block positions
  - Applied a **queue** to manage upcoming tetrominoes, similar to Tetris's preview feature
  - Utilized **vectors** for flexible block shape and collision data
- **SFML fundamentals**: Rendering, input handling, and window management
- **Game loop logic**: Managing frame-based updates and smooth gameplay timing
- **Debugging and design**: Top-down planning, breaking down features into manageable pieces, and testing edge cases



