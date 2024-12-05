# Low-Level Design for Elevator System

## Overview
An Elevator System manages elevators in a building. It handles requests from users to move between floors while ensuring efficiency and safety. This system involves managing multiple elevators, handling user requests, and optimizing elevator operations using various strategies.

The system will adhere to S.O.L.I.D. principles to ensure modular, maintainable, and scalable design.

---

## System Requirements

1. <strong>Elevators</strong>: The system must support multiple elevators.
2. <strong>Floors</strong>: The system must handle a configurable number of floors.
3. <strong>User Requests</strong>: Users can request an elevator to go up or down.
4. <strong>Internal Commands</strong>: Users inside the elevator can select destination floors.
5. <strong>Display and Indicators</strong>: Elevators should display their current floor and direction.
6. <strong>Elevator Movement</strong>: Elevators move between floors based on requests.
7. <strong>Idle State</strong>: Elevators should be idle when there are no pending requests.
8. <strong>Weight Management</strong>: Elevators should monitor weight to avoid overloading.
9. <strong>Error Handling</strong>: The system should handle errors like stuck elevators or power failures.
10. <strong>Emergency Protocols</strong>: Include an emergency stop and alarm system.
11. <strong>Priority Requests</strong>: Emergency and VIP requests should have higher priority.
12. <strong>Optimization</strong>: The system should optimize elevator movement to reduce wait times.
13. <strong>Open/Close Doors</strong>: Elevators should open/close doors automatically at floors.
14. <strong>Maintenance Mode</strong>: Elevators can be set to maintenance mode.
15. <strong>Scalability</strong>: The system should support adding more elevators or floors in the future.

---

## Class Diagram

``` plaintext
+-------------------+         +-------------------+
|     Elevator      |<------->|    ElevatorSystem  |
+-------------------+         +-------------------+
| - id              |         | - elevators[]     |
| - currentFloor    |         | - floors          |
| - direction       |         | - processRequest()|
| - isIdle          |         +-------------------+
| - openDoor()      |
| - closeDoor()     |         +-------------------+
| - moveToFloor()   |         |       Floor        |
+-------------------+         +-------------------+
                             | - floorNumber      |
                             | - upRequest()      |
                             | - downRequest()    |
                             +-------------------+
    +-------------------+
    |       Request      |
    +-------------------+
    | - floorNumber      |
    | - direction        |
    | - isInternal       |
    +-------------------+

+-------------------+            +-------------------+
|       User        |            |   EmergencySystem |
+-------------------+            +-------------------+
| - requestElevator |            | - handleEmergency |
+-------------------+            +-------------------+

```
### Explanation:

1. <strong>Elevator</strong>: Represents individual elevators, including movement, door operations, and current state.
2. <strong>ElevatorSystem</strong>: Main controller managing elevators and requests.
3. <strong>Request</strong>: Represents user requests for elevators (internal or external).
4. <strong>Floor</strong>: Represents each floor and handles floor-specific requests.
5. <strong>EmergencySystem</strong>: Handles emergencies like alarms and elevator stops.
6. <strong>User</strong>: Represents users making requests to the system.

### Relationships:

* `ElevatorSystem` manages multiple `Elevators`.
* `User` generates Requests.
* `Request` is linked to a specific `Floor` and `Elevator`.
* `EmergencySystem` communicates with `Elevator` and `ElevatorSystem` for emergency handling.

---

## Use Case Diagram

``` plaintext
      +---------------------------+
      |        User               |
      +---------------------------+
                 |
     +-----------------------------+
     |      Request Elevator       |
     +-----------------------------+
                 |
  +----------------------+       +----------------------+
  | ElevatorSystem       |------>| Handle User Requests |
  +----------------------+       +----------------------+
                 |
+--------------------+        +------------------------+
| Assign Elevator    |------->| Move Elevator to Floor |
+--------------------+        +------------------------+
                 |
  +-------------------------+
  | Emergency/Stop Handling |
  +-------------------------+

```
## Use Cases:

1. <strong>Request Elevator</strong>: Users request elevators using buttons (up/down outside or floor selection inside).
2. <strong>Handle User Requests</strong>: The system processes requests and assigns elevators.
3. <strong>Move Elevator</strong>: Elevators move to fulfill requests.
4. <strong>Emergency Handling</strong>: In emergencies, the system stops elevators and triggers alarms.

---

## Schema Diagram

``` plaintext
+-------------------+       +-------------------+       +-------------------+
|    Elevator       |       |   ElevatorSystem  |       |      Request      |
+-------------------+       +-------------------+       +-------------------+
| elevatorId (PK)   |       | systemId (PK)     |       | requestId (PK)    |
| currentFloor      |       | elevators[]       |       | floorNumber       |
| direction         |       | floors[]          |       | direction         |
| isIdle            |       +-------------------+       | isInternal        |
+-------------------+                                  +-------------------+

+-------------------+
|       Floor       |
+-------------------+
| floorNumber (PK)  |
| hasUpRequest      |
| hasDownRequest    |
+-------------------+

```

### Cardinality:

A System manages multiple Elevators and Floors.
Each Floor can generate multiple Requests.
A Request is linked to one Elevator.

--- 

## Activity Diagram

``` plaintext
+-------------------------+
|       Start Request      |
+-------------------------+
             |
+-------------------------+
|    User Presses Button   |
+-------------------------+
             |
+-------------------------+
|  System Receives Request |
+-------------------------+
             |
+-------------------------+
|   Assign Nearest Elevator|
+-------------------------+
             |
+-------------------------+
| Elevator Moves to Floor  |
+-------------------------+
             |
+-------------------------+
| Open/Close Doors         |
+-------------------------+
             |
+-------------------------+
|   Check for More Requests|
+-------------------------+
             |
  +-----------+------------+
  |                        |
  v                        v
+--------------------+   +----------------------+
| Serve Next Request |   | Stop Elevator (Idle) |
+--------------------+   +----------------------+

```

Design Patterns
1. <strong>Singleton Pattern</strong>:
The `ElevatorSystem` uses the Singleton pattern to ensure only one instance manages the elevators.

2. <strong>Observer Pattern</strong>:
Floors observe elevator states to know when they arrive.

3. <strong>Strategy Pattern</strong>:
Different algorithms can handle the request assignment logic (e.g., nearest elevator, round-robin).

---

## C++ Code: Singleton and Strategy Pattern
``` cpp

#include <iostream>
#include <vector>
#include <memory>

class Elevator {
private:
    int currentFloor;
    bool isIdle;
public:
    Elevator() : currentFloor(0), isIdle(true) {}

    void moveToFloor(int floor) {
        std::cout << "Moving to floor " << floor << std::endl;
        currentFloor = floor;
        isIdle = false;
    }

    void setIdle(bool idle) {
        isIdle = idle;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    bool getIsIdle() const {
        return isIdle;
    }
};

class AssignmentStrategy {
public:
    virtual Elevator* assignElevator(std::vector<Elevator*>& elevators, int requestedFloor) = 0;
};

class NearestElevatorStrategy : public AssignmentStrategy {
public:
    Elevator* assignElevator(std::vector<Elevator*>& elevators, int requestedFloor) override {
        Elevator* bestElevator = nullptr;
        int minDistance = INT_MAX;

        for (auto& elevator : elevators) {
            if (elevator->getIsIdle()) {
                int distance = abs(elevator->getCurrentFloor() - requestedFloor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestElevator = elevator;
                }
            }
        }
        return bestElevator;
    }
};

class ElevatorSystem {
private:
    static ElevatorSystem* instance;
    std::vector<Elevator*> elevators;
    std::unique_ptr<AssignmentStrategy> strategy;

    ElevatorSystem() {
        strategy = std::make_unique<NearestElevatorStrategy>();
    }

public:
    static ElevatorSystem* getInstance() {
        if (!instance) {
            instance = new ElevatorSystem();
        }
        return instance;
    }

    void addElevator(Elevator* elevator) {
        elevators.push_back(elevator);
    }

    void handleRequest(int requestedFloor) {
        Elevator* elevator = strategy->assignElevator(elevators, requestedFloor);
        if (elevator) {
            elevator->moveToFloor(requestedFloor);
        } else {
            std::cout << "No available elevators!" << std::endl;
        }
    }
};

ElevatorSystem* ElevatorSystem::instance = nullptr;

int main() {
    ElevatorSystem* system = ElevatorSystem::getInstance();
    Elevator elevator1, elevator2;
    system->addElevator(&elevator1);
    system->addElevator(&elevator2);

    system->handleRequest(5);
    system->handleRequest(2);

    return 0;
}
```

---

## S.O.L.I.D. Principles Applied
1. <strong>SRP</strong>: Each class (e.g., Elevator, ElevatorSystem, AssignmentStrategy) focuses on a single responsibility.
2. <strong>OCP</strong>: New strategies can be added without modifying existing classes.
3. <strong>LSP</strong>: Different AssignmentStrategy implementations can replace the base class.
4. <strong>ISP</strong>: Each interface or class provides only necessary methods.
5. <strong>DIP</strong>: ElevatorSystem depends on the abstraction (AssignmentStrategy), not specific implementations.