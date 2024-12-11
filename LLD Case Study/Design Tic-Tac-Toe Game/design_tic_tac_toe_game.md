# Low-Level Design for Tic-Tac-Toe Game

## Overview

Tic-Tac-Toe is a simple two-player game played on a 3x3 grid. The players take turns marking a cell with their symbol (X or O). The winner is the first to get three symbols in a row, column, or diagonal. This low-level design focuses on creating a reusable, 
modular, and extensible architecture for the game.

---

## System Requirements

1. The system should allow two players to play Tic-Tac-Toe.
2. The grid should be a 3x3 matrix but scalable for other board sizes.
3. The players should alternate turns.
4. The system should validate the player's moves (e.g., ensure moves are made in empty cells).
5. Detect win conditions (rows, columns, diagonals).
6. Detect a draw when all cells are filled, and no player wins.
7. Display the current state of the board after every move.
8. Allow restarting the game without restarting the application.
9. Allow players to choose their symbols (X or O).
10. Keep track of player scores across multiple rounds.
11. Provide feedback on invalid moves.
12. Use a strategy to let one player start the game randomly.
13. Ensure the system is extendable to allow AI-based players in the future.
14. Implement a clean and intuitive interface for interaction.
15. Ensure robust error handling and thread safety.

---

## Class Diagram
``` plaintext

+------------------+
|     Game         |
+------------------+
| - board          |
| - players[]      |
| - currentPlayer  |
| + start()        |
| + playTurn()     |
| + checkWin()     |
| + checkDraw()    |
| + switchPlayer() |
+------------------+
          |
          v
+------------------+
|    Board         |
+------------------+
| - grid[][]       |
| + initialize()   |
| + printBoard()   |
| + isCellEmpty()  |
| + markCell()     |
+------------------+
          |
          v
+------------------+
|    Player        |
+------------------+
| - name           |
| - symbol         |
| + makeMove()     |
+------------------+
```

### Explanation:

1. <strong>Game</strong>: The core class managing the flow and rules of the game.
2. <strong>Board</strong>: Represents the game grid and manages its state.
3. <strong>Player</strong>: Represents each player and their moves.

### Relationships:

* `Game` has a composition relationship with `Board` and `Player`.
* `Player` interacts with `Board` to make moves.

---

## Use Case Diagram
``` plaintext

+--------------------+
|       Player       |
+--------------------+
         |
+----------------------+
| Start a New Game     |
+----------------------+
         |
+----------------------+
| Take a Turn          |
+----------------------+
         |
+----------------------+
| View Game Result     |
+----------------------+
         |
+----------------------+
| Restart Game         |
+----------------------+
```

### Use Cases:

1. Start a new game.
2. Take a turn and mark the board.
3. View game results (win, lose, draw).
4. Restart the game.

---

## Schema Diagram
``` plaintext

+---------------------+
|     Player          |
+---------------------+
| playerId (PK)       |
| name                |
| symbol              |
+---------------------+

+---------------------+
|     GameState       |
+---------------------+
| gameId (PK)         |
| boardState          |
| currentPlayer       |
| result              |
+---------------------+
```
### Cardinality:

* A `GameState` tracks one ongoing game.
* A `Player` participates in multiple games.

--- 

## Activity Diagram
``` plaintext

+-------------------------+
| Start Game              |
+-------------------------+
            |
+-------------------------+
| Initialize Board        |
+-------------------------+
            |
+-------------------------+
| Current Player Moves    |
+-------------------------+
            |
+-------------------------+
| Validate Move           |
+-------------------------+
        /   \
    Valid    Invalid
     |           |
+-------------------------+
| Mark Board             |
+-------------------------+
            |
+-------------------------+
| Check Win or Draw       |
+-------------------------+
        /   \
    Yes     No
     |        |
+-------------------------+
| Display Result          |
+-------------------------+
```
---

## Design Patterns
1. <strong>Singleton Pattern</strong>:
Used to manage a single game instance to ensure all game activities are consistent.

2. <strong>Factory Pattern</strong>:
Used to create Player instances with custom names and symbols.

3. <strong>Strategy Pattern</strong>:
Future extensibility to add AI-based strategies for one or both players.

---

## C++ Code

```cpp

#include <iostream>
#include <vector>
#include <string>

class Board {
private:
    std::vector<std::vector<char>> grid;
    int size;

public:
    Board(int size = 3) : size(size), grid(size, std::vector<char>(size, ' ')) {}

    void printBoard() {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << "|" << cell;
            }
            std::cout << "|\n";
        }
    }

    bool isCellEmpty(int x, int y) {
        return grid[x][y] == ' ';
    }

    void markCell(int x, int y, char symbol) {
        grid[x][y] = symbol;
    }

    bool checkWin(char symbol) {
        // Check rows, columns, and diagonals
        for (int i = 0; i < size; ++i) {
            if (std::all_of(grid[i].begin(), grid[i].end(), [symbol](char c) { return c == symbol; }))
                return true;

            bool colWin = true;
            for (int j = 0; j < size; ++j) {
                if (grid[j][i] != symbol) colWin = false;
            }
            if (colWin) return true;
        }

        // Diagonals
        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; ++i) {
            diag1 &= (grid[i][i] == symbol);
            diag2 &= (grid[i][size - i - 1] == symbol);
        }
        return diag1 || diag2;
    }
};

class Player {
private:
    std::string name;
    char symbol;

public:
    Player(std::string name, char symbol) : name(std::move(name)), symbol(symbol) {}

    char getSymbol() const {
        return symbol;
    }

    std::string getName() const {
        return name;
    }

    void makeMove(Board& board) {
        int x, y;
        do {
            std::cout << name << " (" << symbol << "), enter your move (row and column): ";
            std::cin >> x >> y;
        } while (!board.isCellEmpty(x, y));
        board.markCell(x, y, symbol);
    }
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game(Player p1, Player p2) : board(3), player1(std::move(p1)), player2(std::move(p2)), currentPlayer(&player1) {}

    void start() {
        bool gameOn = true;
        while (gameOn) {
            board.printBoard();
            currentPlayer->makeMove(board);

            if (board.checkWin(currentPlayer->getSymbol())) {
                board.printBoard();
                std::cout << currentPlayer->getName() << " wins!\n";
                gameOn = false;
            } else {
                currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            }
        }
    }
};

int main() {
    Player p1("Player1", 'X');
    Player p2("Player2", 'O');
    Game game(p1, p2);
    game.start();
    return 0;
}
```

---

## S.O.L.I.D. Principles
1. <strong>SRP</strong>: Classes like Board, Player, and Game have a single responsibility.
2. <strong>OCP</strong>: The design supports future extension (e.g., AI players).
3. <strong>LSP</strong>: Player strategies can replace the current ones without breaking the system.
4. <strong>ISP</strong>: Minimal methods are exposed in interfaces.
5. <strong>DIP</strong>: Game logic depends on abstractions (Player, Board).