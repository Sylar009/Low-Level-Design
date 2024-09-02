# Elevator System Design

---

## 1. System Requirements

1. **Elevator Capacity**: Each elevator can hold a maximum of 10 passengers.
2. **Number of Floors**: The system supports a building with up to 20 floors.
3. **Elevator Call Buttons**: Each floor has up/down call buttons.
4. **Elevator Control**: Each elevator should be able to serve multiple floors and respond to floor requests.
5. **Passenger Request**: Passengers can request an elevator from a specific floor and input their desired destination floor.
6. **Priority Handling**: Requests should be handled based on the current direction of the elevator and the nearest call.
7. **Overload Detection**: The system should detect when the elevator is overloaded and prevent additional passengers from entering.
8. **Maintenance Mode**: Elevators should have a maintenance mode where they can be disabled for repair.
9. **Emergency Handling**: The system should have an emergency override feature to handle emergencies.
10. **Fault Detection**: The system should be able to detect and report faults in the elevator or control system.
11. **Real-Time Monitoring**: The system should support real-time monitoring of elevator positions and statuses.
12. **User Interface**: The system should have a user interface for inputting requests and monitoring elevator statuses.
13. **Safety Mechanisms**: The system should include safety mechanisms such as door sensors and emergency alarms.
14. **Energy Efficiency**: Elevators should be designed to operate in an energy-efficient manner.
15. **Scalability**: The system should be scalable to accommodate additional elevators or floors in the future.

---

## 2. Class Diagram

### Explanation

- **Elevator**: Represents an individual elevator.
  - **Attributes**: id, currentFloor, targetFloor, direction, status, capacity
  - **Methods**: moveToFloor(floor), openDoor(), closeDoor(), addPassenger(), removePassenger(), updateStatus()

- **ElevatorController**: Manages the elevator system, handling requests and controlling elevators.
  - **Attributes**: elevators (list of Elevator), floors (list of Floor), requests (list of Request)
  - **Methods**: dispatchElevator(request), handleRequest(request), updateElevatorStatus(elevator), addRequest(request)

- **Request**: Represents a user request.
  - **Attributes**: requestId, sourceFloor, destinationFloor, timestamp
  - **Methods**: getRequestDetails()

- **Floor**: Represents a floor in the building.
  - **Attributes**: floorNumber, upButton, downButton
  - **Methods**: pressButton(direction), getFloorNumber()

- **Passenger**: Represents a passenger using the elevator.
  - **Attributes**: passengerId, currentFloor, destinationFloor
  - **Methods**: requestElevator(sourceFloor, destinationFloor), boardElevator(elevator), exitElevator()

### Diagrammatic View (Plain Text)

```scss

+----------------+           +------------------+
|    Elevator    |           | ElevatorController|
+----------------+           +------------------+
| - id           | 1       * | - elevators      |
| - currentFloor |---------->| - floors         |
| - targetFloor  |           | - requests       |
| - direction    |           +------------------+
| - status       |           | + dispatchElevator() |
| - capacity     |           | + handleRequest()  |
+----------------+           | + updateElevatorStatus() |
| + moveToFloor()|           | + addRequest()    |
| + openDoor()   |           +------------------+
| + closeDoor()  |
| + addPassenger()|
| + removePassenger()|
| + updateStatus()|
+----------------+

+-----------+            +-------------+
|  Request  |            |   Floor     |
+-----------+            +-------------+
| - requestId| 1       1 | - floorNumber|
| - sourceFloor|-------->| - upButton   |
| - destinationFloor|     | - downButton |
| - timestamp|            +-------------+
+-----------+            | + pressButton()|
| + getRequestDetails() | | + getFloorNumber()|
+-----------+            +-------------+

+-----------+
| Passenger |
+-----------+
| - passengerId |
| - currentFloor|
| - destinationFloor|
+-----------+
| + requestElevator()|
| + boardElevator() |
| + exitElevator()  |
+-----------+
```

---

## 3. Use Case Diagram

### Explanation

- **Actors**:
  - **Passenger**: Interacts with the elevator system to request and use the elevator.
  - **Maintenance Personnel**: Interacts with the system to perform maintenance and handle faults.

- **Use Cases**:
  - **Request Elevator**: Passenger requests an elevator from a specific floor.
  - **Board Elevator**: Passenger boards the elevator.
  - **Exit Elevator**: Passenger exits the elevator.
  - **Service Elevator**: Maintenance Personnel performs maintenance.
  - **Handle Faults**: Maintenance Personnel addresses and resolves faults.

### Diagrammatic View (Plain Text)

```scss

          +-----------------+
          |   Passenger     |
          +-----------------+
          |                 |
          | + Request Elevator() |
          | + Board Elevator()   |
          | + Exit Elevator()    |
          +-----------------+
                   ^
                   |
                   |
          +-----------------+
          |  Maintenance    |
          |   Personnel     |
          +-----------------+
          |                 |
          | + Service Elevator() |
          | + Handle Faults()     |
          +-----------------+

```
---

## 4. Schema Diagram

### Explanation

- **Elevator Table**:
  - **Attributes**: id (PK), currentFloor, targetFloor, direction, status, capacity
- **Request Table**:
  - **Attributes**: requestId (PK), sourceFloor, destinationFloor, timestamp
- **Floor Table**:
  - **Attributes**: floorNumber (PK), upButton, downButton
- **Passenger Table**:
  - **Attributes**: passengerId (PK), currentFloor, destinationFloor

### Diagrammatic View (Plain Text)

```lua

+------------------+
|   Elevator       |
+------------------+
| id (PK)          |
| currentFloor     |
| targetFloor      |
| direction        |
| status           |
| capacity         |
+------------------+

+------------------+
|   Request        |
+------------------+
| requestId (PK)   |
| sourceFloor      |
| destinationFloor |
| timestamp        |
+------------------+

+------------------+
|   Floor          |
+------------------+
| floorNumber (PK) |
| upButton         |
| downButton       |
+------------------+

+------------------+
|  Passenger       |
+------------------+
| passengerId (PK) |
| currentFloor     |
| destinationFloor |
+------------------+
```

### Cardinality

- **Elevator to Request**: One-to-Many (One elevator can handle multiple requests)
- **Request to Floor**: Many-to-One (Requests are tied to specific source and destination floors)
- **Passenger to Elevator**: Many-to-Many (Passengers can use multiple elevators; elevators can have multiple passengers)

---

## 5. Activity Diagram

### Explanation

- **Activities**:
  1. **Request Elevator**: Passenger requests an elevator.
  2. **Dispatch Elevator**: Controller dispatches an available elevator.
  3. **Elevator Moves**: Elevator moves to the requested floor.
  4. **Board Elevator**: Passenger boards the elevator.
  5. **Select Destination**: Passenger selects the destination floor.
  6. **Elevator Moves to Destination**: Elevator moves to the destination floor.
  7. **Passenger Exits**: Passenger exits at the destination floor.
  8. **Update Status**: System updates the status of the elevator.

### Diagrammatic View (Plain Text)

```sql

+---------------------+
|  Request Elevator   |
+---------------------+
          |
          v
+---------------------+
|  Dispatch Elevator  |
+---------------------+
          |
          v
+---------------------+
|   Elevator Moves    |
+---------------------+
          |
          v
+---------------------+
|   Board Elevator    |
+---------------------+
          |
          v
+---------------------+
| Select Destination  |
+---------------------+
          |
          v
+---------------------+
| Elevator Moves to   |
|   Destination       |
+---------------------+
          |
          v
+---------------------+
|   Passenger Exits   |
+---------------------+
          |
          v
+---------------------+
|   Update Status     |
+---------------------+
```

---

## 6. Code Structure Using Design Patterns and Principles in C++

### Design Patterns

- **Singleton Pattern**: For `ElevatorController` to ensure only one instance manages all elevators and requests.
- **Strategy Pattern**: For handling different elevator dispatching strategies.
- **Observer Pattern**: For updating the status of elevators and handling changes in real-time.

### Design Principles

- **Single Responsibility Principle**: Each class has a single responsibility.
- **Open/Closed Principle**: The system should be open for extension but closed for modification.
- **Liskov Substitution Principle**: Subtypes must be substitutable for their base types.
- **Interface Segregation Principle**: Clients should not be forced to depend on interfaces they do not use.
- **Dependency Inversion Principle**: Depend on abstractions, not on concretions.

### Code Structure

```cpp
// Elevator.h
class Elevator {
private:
    int id;
    int currentFloor;
    int targetFloor;
    std::string direction;
    std::string status;
    int capacity;

public:
    Elevator(int id);
    void moveToFloor(int floor);
    void openDoor();
    void closeDoor();
    void addPassenger();
    void removePassenger();
    void updateStatus();
};

// ElevatorController.h
class ElevatorController {
private:
    static ElevatorController* instance;
    std::vector<Elevator> elevators;
    std::vector<Request> requests;

    ElevatorController();

public:
    static ElevatorController* getInstance();
    void dispatchElevator(Request request);
    void handleRequest(Request request);
    void updateElevatorStatus(Elevator elevator);
    void addRequest(Request request);
};

// Request.h
class Request {
private:
    int requestId;
    int sourceFloor;
    int destinationFloor;
    time_t timestamp;

public:
    Request(int id, int src, int dest, time_t time);
    int getRequestId();
    int getSourceFloor();
    int getDestinationFloor();
    time_t getTimestamp();
};

// Floor.h
class Floor {
private:
    int floorNumber;
    bool upButton;
    bool downButton;

public:
    Floor(int number);
    void pressButton(std::string direction);
    int getFloorNumber();
};

// Passenger.h
class Passenger {
private:
    int passengerId;
    int currentFloor;
    int destinationFloor;

public:
    Passenger(int id, int src, int dest);
    void requestElevator(int sourceFloor, int destinationFloor);
    void boardElevator(Elevator& elevator);
    void exitElevator();
};
```

### This design provides a clear and modular approach to developing an elevator system, adhering to design principles and employing design patterns to manage complexity and scalability.