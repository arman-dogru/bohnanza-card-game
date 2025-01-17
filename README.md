# 🌱 Bohnanza - C++ Card Game

This repository contains a **C++ implementation** of the **Bohnanza** card game, where players **trade, plant, and harvest beans** to earn coins. The game follows **object-oriented programming (OOP) principles** and uses **CMake** for build management.

---

## 🎮 Game Overview

Bohnanza is a strategic **bean farming card game** where players:
- Collect and plant bean cards in **fields**.
- Trade and negotiate **bean exchanges** with other players.
- Harvest **bean fields** for coins.
- The player with the **most coins** at the end **wins the game**.

---

## 📌 Features

- 🃏 **Card Management System** – Handles deck, hand, and discard pile.
- 🤝 **Trading System** – Allows players to trade bean cards.
- 🌾 **Field & Harvest Mechanics** – Simulates planting and harvesting beans.
- 🎭 **Multiplayer Simulation** – Turn-based gameplay structure.
- 🖥️ **Object-Oriented Design** – Encapsulated classes for game elements.

---

## 📂 Project Structure

```
bohnanza/
│── .idea/                      # IDE configuration files
│── cmake-build-debug/           # CMake build files
│── src/                         # Source code files
│   ├── Card.cpp                 # Card class implementation
│   ├── Card.h                   # Card class definition
│   ├── CardFactory.cpp           # Factory pattern for generating cards
│   ├── CardFactory.h
│   ├── Chain.h                   # Chains for collecting beans
│   ├── Deck.cpp                  # Deck handling logic
│   ├── Deck.h
│   ├── DiscardPile.cpp           # Discard pile management
│   ├── DiscardPile.h
│   ├── Hand.cpp                  # Player hand management
│   ├── Hand.h
│   ├── Player.cpp                # Player logic
│   ├── Player.h
│   ├── Table.cpp                 # Game table management
│   ├── Table.h
│   ├── TradeArea.cpp             # Trading zone logic
│   ├── TradeArea.h
│   ├── main.cpp                  # Main game loop
│── CMakeLists.txt                # CMake build configuration
│── Output.txt                     # Sample output file
│── SaveGame.txt                   # Save file for game state
```

---

## 🚀 Installation & Setup

### **1️⃣ Clone the Repository**
```sh
git clone https://github.com/arman-dogru/bohnanza.git
cd bohnanza
```

### **2️⃣ Build the Project Using CMake**
Ensure you have **CMake** installed, then run:
```sh
mkdir build
cd build
cmake ..
make
```

### **3️⃣ Run the Game**
After successful compilation:
```sh
./bohnanza
```

---

## 🔧 Dependencies

- **C++17 or later**
- **CMake** (for build automation)
- **GCC/Clang** (for compilation)

---

## 🏗 Future Enhancements

- **🖥️ GUI Implementation** – Add a graphical interface using **Qt** or **SFML**.
- **🌍 Online Multiplayer Mode** – Implement a **networked version**.
- **💾 Game Save/Load Feature** – Improve game state management.

---

## 🤝 Contributing

Contributions are welcome! If you'd like to improve the game or add new features, please fork the repository and submit a **pull request**.

---

## 📜 License

This project is licensed under the **MIT License**.

---

### ⭐ **Like this project? Consider starring the repository! 🌟**
