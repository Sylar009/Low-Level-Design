# Low-Level Design for <strong>Snake and Ladder Game</strong>

## Overview
The Snake and Ladder game is a classic board game where players navigate their pieces from the start to the end of the board by rolling dice. The game incorporates snakes that move players backward and ladders that propel them forward. This software system is designed to simulate the Snake and Ladder game, allowing multiple players to participate, handle game mechanics such as dice rolls and player movements, manage snakes and ladders, and determine the winner. The design adheres to S.O.L.I.D. principles and leverages appropriate Design Patterns to ensure scalability, maintainability, and extensibility.

## System Requirements
1. <strong>Player Management</strong>: Allow multiple players to join the game with unique identifiers.
2. <strong>Board Configuration</strong>: Initialize the game board with a predefined number of squares, snakes, and ladders.
3. <strong>Snake and Ladder Management</strong>: Define the positions of snakes (start and end points) and ladders (start and end points) on the board.
4. <strong>Dice Rolling</strong>: Simulate dice rolls to determine the number of steps a player can move.
5. <strong>Player Movement</strong>: Move player pieces on the board based on dice outcomes, considering snakes and ladders.
6. <strong>Turn Management</strong>: Manage the sequence of player turns in a round-robin fashion.
7. <strong>Win Condition</strong>: Determine when a player has reached the final square and declare them as the winner.
8. <strong>Game State Management</strong>: Keep track of the current state of the game, including player positions and game progress.
9. <strong>User Interface</strong>: Provide a console-based or GUI-based interface for players to interact with the game.
10. <strong>Error Handling</strong>: Handle scenarios such as invalid moves, duplicate player names, or system failures gracefully.
11. <strong>Logging: Log game events such as dice rolls, player movements, encounters with snakes or ladders, and game outcomes.
12. <strong>Replay Option</strong>: Allow players to start a new game after a game ends.
13. <strong>Customization</strong>: Allow configuration of the number of players, board size, number of snakes and ladders.
14. <strong>Persistence</strong>: Optionally, save and load game states.
15. <strong>Notifications</strong>: Notify players of important events, such as their turn, encountering a snake or ladder, or winning the game.

## Class Diagram
``` sql
+-------------------+
|      Game         |
+-------------------+
| - board: Board    |
| - players: List<Player> |
| - dice: Dice      |
| - currentPlayerIndex: int |
| - isGameOver: bool|
+-------------------+
| + start()         |
| + playTurn()      |
| + checkWin()      |
| + endGame()       |
+-------------------+
         |
         | 1
         | contains
         |
+-------------------+
|      Board        |
+-------------------+
| - squares: List<Square> |
| - snakes: List<Snake>   |
| - ladders: List<Ladder> |
+-------------------+
| + initialize()    |
| + getSquare(int)  |
| + addSnake(Snake) |
| + addLadder(Ladder)|
+-------------------+
         |
         | 1..*
         |
+-------------------+      +------------------+
|      Square       |      |      Snake       |
+-------------------+      +------------------+
| - position: int   |      | - head: int      |
| - hasSnake: bool  |      | - tail: int      |
| - hasLadder: bool |      +------------------+
| - snake: Snake*   |
| - ladder: Ladder* |
+-------------------+
         |
         | 1..*
         |
+-------------------+
|      Ladder       |
+-------------------+
| - start: int      |
| - end: int        |
+-------------------+

+-------------------+
|      Player       |
+-------------------+
| - playerId: int   |
| - name: string    |
| - position: int   |
| - isWinner: bool  |
+-------------------+
| + move(int)       |
| + setPosition(int)|
+-------------------+

+-------------------+
|       Dice        |
+-------------------+
| - sides: int      |
+-------------------+
| + roll(): int     |
+-------------------+

+-------------------+
|     Logger        |
+-------------------+
| - logs: List<string> |
+-------------------+
| + log(string)     |
| + displayLogs()   |
+-------------------+

+-------------------+
|    Notification    |
+-------------------+
| + notify(string)  |
+-------------------+
```

### Explanation:

* </b>Game</b>: The core class that manages the entire game flow. It contains the board, list of players, the dice, and manages turns and game state.
* </b>Board</b>: Represents the game board with squares, snakes, and ladders. It initializes the board and manages the positions of snakes and ladders.
* </b>Square</b>: Represents each square on the board. It can have a snake or ladder.
* </b>Snake</b>: Represents a snake with a head (start position) and tail (end position).
* </b>Ladder</b>: Represents a ladder with a start and end position.
* </b>Player</b>: Represents each player with an ID, name, current position, and winner status. Handles movement.
* </b>Dice</b>: Simulates a dice with a certain number of sides. Can be rolled to get a random number.
* </b>Logger</b>: Logs important game events.
* </b>Notification</b>: Handles notifications to players about game events.

### Relationships:

* A Game has one Board.
* A Game has multiple Players (1..*).
* A Board has multiple Squares (1..*).
* A Board has multiple Snakes and Ladders (1..*).
* Square may contain a Snake or a Ladder.
* Game uses Dice to roll.
* Game uses Logger and Notification for logging and notifications.

## Use Case Diagram
``` sql
+------------------+
|      Player      |
+------------------+
        |
        v
+--------------------------+
|      Join Game           |
+--------------------------+
        |
        v
+--------------------------+
|      Start Game          |
+--------------------------+
        |
        v
+--------------------------+
|      Roll Dice           |
+--------------------------+
        |
        v
+--------------------------+
|      Move Player         |
+--------------------------+
        |
        v
+--------------------------+
|      Encounter Event     |
| (Snake/Ladder)           |
+--------------------------+
        |
        v
+--------------------------+
|      Notify Player       |
+--------------------------+
        |
        v
+--------------------------+
|      Declare Winner      |
+--------------------------+
        |
        v
+--------------------------+
|      End Game            |
+--------------------------+
```

### Use Cases:

1. </b>Join Game</b>: Players can join the game by providing their names.
2. </b>Start Game</b>: Initiate the game once all players have joined.
3. </b>Roll Dice</b>: Players roll the dice to determine movement.
4. </b>Move Player</b>: Move the player's piece based on the dice roll.
5. </b>Encounter Event</b>: Check if the player lands on a snake or ladder and move accordingly.
6. </b>Notify Player</b>: Notify players about their moves and any encounters.
7. </b>Declare Winner</b>: Determine if a player has won the game by reaching the final square.
8. </b>End Game</b>: Conclude the game once a winner is declared.

## Database Schema Diagram

``` sql
+-------------------+       +---------------------+
|      Players      |       |       Board         |
+-------------------+       +---------------------+
| playerId (PK)     |       | boardId (PK)        |
| name              |       | totalSquares        |
| currentPosition   |       +---------------------+
| isWinner          |
+-------------------+

+-------------------+       +---------------------+
|      Snakes       |       |      Ladders        |
+-------------------+       +---------------------+
| snakeId (PK)      |       | ladderId (PK)       |
| headPosition      |       | startPosition       |
| tailPosition      |       | endPosition         |
+-------------------+       +---------------------+

+-------------------+       +---------------------+
|      Games        |       |      Moves          |
+-------------------+       +---------------------+
| gameId (PK)       |       | moveId (PK)         |
| boardId (FK)      |       | gameId (FK)         |
| isActive          |       | playerId (FK)       |
| startTime         |       | diceValue           |
| endTime           |       | fromPosition        |
| winnerId (FK)     |       | toPosition          |
+-------------------+       | timestamp           |
                            +---------------------+

+-------------------+
|      Logs         |
+-------------------+
| logId (PK)        |
| gameId (FK)       |
| eventDescription  |
| timestamp         |
+-------------------+
```

* <b>Players Table</b>: Stores player information such as ID, name, current position, and winner status.
* <b>Board Table</b>: Stores board-related information like total number of squares.
* <b>Snakes Table</b>: Stores information about snakes with head and tail positions.
* <b>Ladders Table</b>: Stores information about ladders with start and end positions.
* <b>Games Table</b>: Stores information about game instances, including active status, start and end times, and the winner.
* <b>Moves Table</b>: Records each move made by players, including dice value and positions.
* <b>Logs Table</b>: Stores logs of game events for record-keeping.

### Cardinality:

* One Game has multiple Players (1..*).
* One Game has multiple Moves (1..*).
* One Game has one Board (1).
* One Board has multiple Snakes and Ladders (1..*).
* Game can have one Winner (Player).
* One Game can have multiple Logs (1..*).
* Player can have multiple Moves (1..*).

--- 

### Explanation of Cardinality
* <b>Game to Players</b>: A single game involves multiple players (1..*), and each player belongs to one game at a time.
* <b>Game to Board</b>: Each game is played on one board, but a board can be reused across multiple games (1..1).
* <b>Board to Snakes/Ladders</b>: A board has multiple snakes and multiple ladders (1..* for both).
* <b>Game to Moves</b>: Each game consists of many moves, each associated with a specific player.
* <b>Game to Logs</b>: All logs pertain to one game, and a game can have multiple log entries.
* <b>Player to Moves</b>: A player can have multiple moves in a game.

## Activity Diagram

``` diff
+----------------------------+
|         Start Game         |
+----------------------------+
             |
             v
+----------------------------+
| Initialize Board and Players|
+----------------------------+
             |
             v
+----------------------------+
|    Check if Game Over      |
+----------------------------+
         /       \
        /         \
      No           Yes
      |              |
      v              v
+-------------------+   +-------------------+
| Current Player's  |   | Declare Winner    |
| Turn              |   +-------------------+
+-------------------+           |
             |                   v
             v           +-------------------+
+---------------------------+ |
| Roll Dice                 | |
+---------------------------+ |
             |                   |
             v                   v
+---------------------------+ +-------------------+
| Move Player Based on Dice | | End Game           |
+---------------------------+ +-------------------+
             |
             v
+---------------------------+
| Check for Snake or Ladder |
+---------------------------+
             |
             v
+---------------------------+
| Update Player Position    |
+---------------------------+
             |
             v
+---------------------------+
| Log the Move              |
+---------------------------+
             |
             v
+---------------------------+
| Notify Players            |
+---------------------------+
             |
             v
+----------------------------+
| Next Player's Turn         |
+----------------------------+
             |
             v
+----------------------------+
| Loop Back to Check Game Over|
+----------------------------+
```

## Design Patterns

<b>Singleton Pattern for Logger</b>
The Singleton Pattern ensures that there is only one instance of the Logger class throughout the application, providing a global point of access to it.

<b>Strategy Pattern for Dice Rolling</b>
The Strategy Pattern allows the dice rolling mechanism to be interchangeable. For example, different dice types (standard 6-sided, 20-sided) can be implemented.

<b>Observer Pattern for Notifications</b>
The Observer Pattern is used to notify players about game events like dice rolls, player movements, and game status changes.

<b>C++ Code: Strategy Pattern for Dice Rolling</b>

``` cpp
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>

// Strategy Interface for Dice Rolling
class DiceStrategy {
public:
    virtual int roll() = 0;
    virtual ~DiceStrategy() = default;
};

// Concrete Strategy for Standard 6-sided Dice
class SixSidedDice : public DiceStrategy {
public:
    int roll() override {
        return (std::rand() % 6) + 1;
    }
};

// Concrete Strategy for 20-sided Dice
class TwentySidedDice : public DiceStrategy {
public:
    int roll() override {
        return (std::rand() % 20) + 1;
    }
};

// Context Class
class Dice {
private:
    std::unique_ptr<DiceStrategy> strategy;
public:
    void setStrategy(std::unique_ptr<DiceStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    int roll() {
        if (strategy)
            return strategy->roll();
        else
            return 0;
    }
};

int main() {
    std::srand(std::time(0)); // Seed for randomness

    Dice dice;

    // Use standard 6-sided dice
    dice.setStrategy(std::make_unique<SixSidedDice>());
    std::cout << "Rolling 6-sided dice: " << dice.roll() << std::endl;

    // Use 20-sided dice
    dice.setStrategy(std::make_unique<TwentySidedDice>());
    std::cout << "Rolling 20-sided dice: " << dice.roll() << std::endl;

    return 0;
}
```
<b>C++ Code: Singleton Pattern for Logger</b>

``` cpp

#include <iostream>
#include <vector>
#include <string>
#include <mutex>

// Singleton Logger Class
class Logger {
private:
    std::vector<std::string> logs;
    static Logger* instance;
    static std::mutex mtx;

    // Private Constructor
    Logger() {}

public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Static method to get the single instance
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const std::string& message) {
        logs.push_back(message);
    }

    void displayLogs() const {
        for (const auto& log : logs) {
            std::cout << log << std::endl;
        }
    }
};

// Initialize static members
Logger* Logger::instance = nullptr;
std::mutex Logger::mtx;

int main() {
    Logger* logger = Logger::getInstance();
    logger->log("Game started.");
    logger->log("Player1 rolled a 5.");
    logger->log("Player1 moved to position 5.");
    logger->displayLogs();

    return 0;
}
```

<b>C++ Code: Observer Pattern for Notifications</b>

``` cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Observer Interface
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// Subject Interface
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify(const std::string& message) {
        for(auto obs : observers) {
            obs->update(message);
        }
    }
};

// Concrete Observer
class Player : public Observer {
private:
    std::string name;
public:
    Player(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Notification to " << name << ": " << message << std::endl;
    }
};

// Concrete Subject
class GameEvent : public Subject {
public:
    void triggerEvent(const std::string& message) {
        notify(message);
    }
};

int main() {
    GameEvent gameEvent;

    Player player1("Alice");
    Player player2("Bob");

    gameEvent.attach(&player1);
    gameEvent.attach(&player2);

    gameEvent.triggerEvent("Player1 has rolled a 6.");
    gameEvent.triggerEvent("Player1 climbed a ladder to position 14.");
    
    return 0;
}
```

## Design Principles
* <strong>Single Responsibility Principle (SRP)</strong>: Each class has a single responsibility. For example, the `Player` class manages player-specific data and behavior, while the `Game` class manages the overall game flow.

* <strong>Open/Closed Principle (OCP)</strong>: The system is open for extension but closed for modification. For example, new types of dice can be added by implementing the `DiceStrategy` interface without altering existing code.

* <strong>Liskov Substitution Principle (LSP)</strong>: Subclasses can replace their base classes without affecting the system. For example, any `DiceStrategy` implementation can be used interchangeably with the `Dice` class.

* <strong>Interface Segregation Principle (ISP)</strong>: Interfaces are specific to clients’ needs. For example, `Observer` and `Subject` interfaces in the Observer pattern are minimal and focused.

* <strong>Dependency Inversion Principle (DIP)</strong>: High-level modules do not depend on low-level modules but on abstractions. For example, `Game` depends on the `DiceStrategy` interface rather than concrete dice implementations.

--- 

## Detailed Component Descriptions

1. <strong>Game Class</strong>

    * <b>Responsibilities</b>:

        * Initialize and manage the game.
        * Manage player turns and game progression.
        * Check for win conditions.
        * Coordinate interactions between players, board, dice, logger, and notifications.

    * <b>Methods</b>:

        * `start()`: Initializes the board, players, and starts the game loop.
        * `playTurn()`: Executes a single turn for the current player.
        * `checkWin()`: Checks if the current player has won the game.
        * `endGame()`: Ends the game and declares the winner.
2. <strong>Board Class</strong>

    * <b>Responsibilities</b>:

        * Initialize the game board with squares, snakes, and ladders.
        * Manage the placement of snakes and ladders.
        * Provide information about specific squares.
    
    * <b>Methods</b>:

        * `initialize()`: Sets up the board with default or customized configurations.
        * `getSquare(int)`: Retrieves a specific square based on position.
        * `addSnake(Snake)`: Adds a snake to the board.
        * `addLadder(Ladder)`: Adds a ladder to the board.
        
3. <strong>Square Class</strong>

    * <b>Responsibilities</b>:

        * Represent each square on the board.
        * Indicate if the square has a snake or ladder.
        * Reference the snake or ladder if present.

4. <strong>Snake and Ladder Classes</strong>

    * <b>Responsibilities</b>:

        * Represent snakes and ladders with start and end positions.
        * Provide information about their positions on the board.

5. <strong>Player Class</strong>

    * <b>Responsibilities</b>:

        * Represent each player in the game.
        * Manage player-specific data like name, position, and winner status.
        * Handle player movements based on dice rolls.

    * <b>Methods</b>:

        * `move(int)`: Moves the player based on the dice roll.
        * `setPosition(int)`: Sets the player's position on the board.

6. <strong>Dice Class</strong>

    * <b>Responsibilities</b>:

        * Simulate dice rolls using different strategies.
        * Allow changing dice types dynamically.

    * <b>Methods</b>:

        * `roll()`: Rolls the dice and returns a random number based on the strategy.

7. <strong>Logger Class</strong>

    * <b>Responsibilities</b>:

        * Log important game events for record-keeping.
        * Provide a way to display logs.

    * <b>Methods</b>:

        * `log(string)`: Logs a message.
        * `displayLogs()`: Displays all logged messages.

8. <strong>Notification Class</strong>

    * <b>Responsibilities</b>:

        * Notify players about game events like dice rolls, movements, and game status changes.

    * <b>Methods</b>:

        * notify(string): Sends a notification message to players.

---

## Design Patterns and Their Usage

1. <strong>Singleton Pattern (Logger)</strong>:

    * Ensures only one instance of the Logger exists.
    * Provides a global point of access to the Logger instance.

2. <strong>Strategy Pattern (Dice)</strong>:

    * Allows different dice rolling mechanisms (e.g., 6-sided, 20-sided).
    * Enables dynamic switching of dice types at runtime.

3. <strong>Observer Pattern (Notification)</strong>:

    * Allows the system to notify multiple players about game events.
    * Decouples the notification mechanism from the game logic.

---
## Conclusion
This low-level design for the Snake and Ladder game provides a comprehensive blueprint for implementing the game software. By adhering to S.O.L.I.D. principles and utilizing Design Patterns like Singleton, Strategy, and Observer, the design ensures that the system is modular, scalable, and maintainable. The provided C++ code snippets demonstrate the practical implementation of these patterns, facilitating flexible and efficient game mechanics. This design not only covers the core functionalities but also ensures that the system can be easily extended and maintained in the future.