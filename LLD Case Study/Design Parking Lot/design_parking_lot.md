# Low-Level Design for <strong>Parking Lot System</strong>

## Overview
The parking lot system allows vehicles to enter, park, and exit a parking facility. The system will handle various types of vehicles (cars, bikes, trucks), manage parking slots, calculate parking fees based on time, and handle payment. It will also support different payment methods, track parking space availability, and ensure that the system is scalable and maintainable. The design follows S.O.L.I.D. principles to ensure that each component is modular and easy to extend.

## System Requirements

1. <strong>Vehicle Entry</strong>: Allow vehicles to enter the parking lot and assign them a parking slot.
2. <strong>Vehicle Exit</strong>: Allow vehicles to exit and calculate the parking fee based on the duration.
3. <strong>Parking Slot Management</strong>: Track available and occupied parking slots for different vehicle types.
4. <strong>Parking Fee Calculation</strong>: Calculate parking fees based on the duration of the vehicle's stay.
5. <strong>Payment Handling</strong>: Support multiple payment methods (cash, card, digital).
6. <strong>Parking Ticket</strong>: Generate a parking ticket with details like entry time, parking slot, and vehicle type.
7. <strong>Multiple Vehicle Types</strong>: Handle different types of vehicles (car, bike, truck), each needing different slot sizes.
8. <strong>Parking Lot Capacity</strong>: Track the total capacity and availability of the parking lot for different vehicle types.
9. <strong>Discount Management</strong>: Apply discounts (e.g., for electric vehicles, loyalty programs).
10. <strong>Parking Slot Reservation</strong>: Allow users to reserve parking slots in advance.
11. <strong>Overstay Penalty</strong>: Apply penalties for vehicles that overstay the reserved or allocated time.
12. <strong>User Notifications</strong>: Notify users of their parking status (e.g., slot allocated, payment due).
13. <strong>Security Features</strong>: Capture vehicle details (license plate, vehicle type) upon entry.
14. <strong>Error Handling</strong>: Handle errors like full capacity or invalid payments gracefully.
15. <strong>Parking Lot Reports</strong>: Generate reports of total revenue, slot usage, and vehicle types.

## Class Diagram

``` lua
+--------------------+     1      +---------------------+
|      Vehicle       |------------|     ParkingSlot      |
+--------------------+            +---------------------+
| - vehicleId        |            | - slotId            |
| - licensePlate     |            | - slotSize          |
| - vehicleType      |            | - isOccupied        |
+--------------------+            | - vehicle (FK)      |
       |                          +---------------------+
       |                                |
       |1..*                            | 1..*
+-------------------+              +--------------------+
|    ParkingLot     |<-------------|    ParkingLevel     |
+-------------------+              +--------------------+
| - lotId           |              | - levelId          |
| - name            |              | - slots            |
| - totalCapacity   |              |                    |
+-------------------+              +--------------------+
      | 1                                 |
      |                                   | 1..*
      |                                   v
+-------------------+              +--------------------+
|    Payment        |              |   ParkingTicket    |
+-------------------+              +--------------------+
| - paymentId       |              | - ticketId         |
| - amount          |              | - vehicle (FK)     |
| - paymentMethod   |              | - entryTime        |
+-------------------+              | - exitTime         |
      |                              | - parkingSlot     |
      v                              | - isPaid          |
+------------------+                 +------------------+
|  PaymentStrategy |  
+------------------+
| - pay()          |
+------------------+

+-------------------+
|      Discount     |
+-------------------+
| - discountId      |
| - discountValue   |
+-------------------+
```

### Explanation:

* `Vehicle`: Represents a vehicle with a license plate, ID, and type (car, bike, truck).
* `ParkingSlot`: Represents a parking slot with information about its size and whether it is occupied.
* `ParkingLot`: Manages the entire parking facility, which consists of multiple parking levels.
* `ParkingLevel`: Represents different levels in the parking lot. Each level has multiple slots.
* `ParkingTicket`: Generated when a vehicle enters the parking lot, capturing the entry and exit times and linked to the vehicle and parking slot.
* `Payment`: Handles the payment for parking fees, linked to the ticket.
* `PaymentStrategy`: An interface for different payment methods (e.g., cash, card, digital wallet).
* `Discount`: Represents discounts that may apply to the parking fee.

### Relationships:

* A `ParkingLot` contains multiple `ParkingLevel` instances (1..* relationship).
* Each `ParkingLevel` contains multiple `ParkingSlot` instances.
* Each `Vehicle` is assigned a `ParkingSlot`, and a `ParkingTicket` is generated.
* The `ParkingTicket` is linked to the `Vehicle` and is paid through the `Payment` system.
* The `Payment` class uses the Strategy Pattern to dynamically select a payment method.
* `Discounts` can be applied to the final amount in the `Payment`.

## Use Case Diagram

``` sql
      +-------------------+
      |   Parking System   |
      +-------------------+
            |
            v
    +------------------+     1. Enter Vehicle
    |  Enter Vehicle    |------------------> (Assign Slot)
    +------------------+
            |
            v
    +------------------+     2. Generate Ticket
    |  Generate Ticket  |------------------> (Assign Slot & Ticket)
    +------------------+
            |
            v
    +------------------+     3. Payment
    |  Calculate Fees   |------------------> (Apply Fee & Discounts)
    +------------------+
            |
            v
    +------------------+     4. Pay Fees
    |  Pay Parking Fees |------------------> (Payment Method)
    +------------------+
            |
            v
    +------------------+     5. Exit Vehicle
    |   Exit Vehicle    |------------------> (Release Slot)
    +------------------+
```

### Use Cases:

1. <strong>Enter Vehicle</strong>: The system captures the vehicle information and assigns a parking slot.
2. <strong>Generate Ticket</strong>: A parking ticket is generated with the vehicle details and entry time.
3. <strong>Calculate Fees</strong>: Upon exit, the system calculates the total parking fees based on the time spent.
4. <strong>Pay Fees</strong>: The user makes a payment using a preferred payment method.
5. <strong>Exit Vehicle</strong>: The vehicle exits the parking lot, and the parking slot is released.

## Database Schema Diagram

``` lua
+-------------------+       +---------------------+
|    Vehicles       |       |   ParkingSlots      |
+-------------------+       +---------------------+
| vehicleId (PK)    |       | slotId (PK)         |
| licensePlate      |       | isOccupied          |
| vehicleType       |       | vehicleId (FK)      |
+-------------------+       | slotSize            |
                             +---------------------+

+-------------------+       +---------------------+
|   ParkingLots     |       |   ParkingTickets     |
+-------------------+       +---------------------+
| lotId (PK)        |       | ticketId (PK)        |
| name              |       | vehicleId (FK)       |
| totalCapacity     |       | entryTime            |
+-------------------+       | exitTime             |
                             | parkingSlotId (FK)  |
                             | isPaid              |
                             +---------------------+

+-------------------+       +---------------------+
|   Payments        |       |   ParkingLevels      |
+-------------------+       +---------------------+
| paymentId (PK)    |       | levelId (PK)         |
| amount            |       | lotId (FK)           |
| paymentMethod     |       | slotId (FK)          |
+-------------------+       +---------------------+
```

* <strong>Vehicles Table</strong>: Stores the information about vehicles entering the parking lot.
* <strong>ParkingSlots Table</strong>: Tracks parking slot status (whether occupied or available) and is linked to a specific vehicle.
* <strong>ParkingLots Table</strong>: Stores information about the parking facility, including its name and capacity.
* <strong>ParkingTickets Table</strong>: Stores details about the parking ticket, including entry and exit times.
* <strong>Payments Table</strong>: Stores payment details for each parking ticket.
* <strong>ParkingLevels Table</strong>: Stores information about the different levels in the parking lot and the slots available at each level.

### Cardinality:

* One `ParkingLot` has multiple `ParkingLevels`.
* Each `ParkingLevel` contains multiple `ParkingSlots`.
* Each `ParkingSlot` can be occupied by one `Vehicle` at a time.
* Each `Vehicle` is associated with one `ParkingTicket`.
* Each `ParkingTicket` is linked to one `Payment`.

## Activity Diagram

``` sql
+----------------------------+
|        Vehicle Enters       |
+----------------------------+
           |
           v
+----------------------------+
|  Check Slot Availability    |
+----------------------------+
           |
           v
+----------------------------+
|   Assign Parking Slot       |
+----------------------------+
           |
           v
+----------------------------+
|   Generate Parking Ticket   |
+----------------------------+
           |
           v
+----------------------------+
|   Vehicle Stays in Slot     |
+----------------------------+
           |
           v
+----------------------------+
|   Vehicle Requests Exit     |
+----------------------------+
           |
           v
+----------------------------+
|   Calculate Parking Fees    |
+----------------------------+
           |
           v
+----------------------------+
|   Pay Fees & Exit Slot      |
+----------------------------+
```

## Design Patterns

<b>Strategy Pattern for Payment</b>
The Strategy Pattern is used for selecting the payment method dynamically at runtime. Each payment method is encapsulated as a separate class that implements the `PaymentStrategy` interface. The client (parking system) can select which payment strategy to use (cash, card, digital) based on the user’s preference.

---
<b>C++ Code: Strategy Pattern</b>

``` cpp

#include <iostream>
#include <memory>

class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class CashPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Cash." << std::endl;
    }
};

class CardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Credit/Debit Card." << std::endl;
    }
};

class DigitalWalletPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Digital Wallet." << std::endl;
    }
};

class Payment {
private:
    std::unique_ptr<PaymentStrategy> strategy;
public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        this->strategy = std::move(strategy);
    }

    void pay(int amount) {
        strategy->pay(amount);
    }
};

int main() {
    Payment payment;

    // Pay using Cash
    payment.setPaymentStrategy(std::make_unique<CashPayment>());
    payment.pay(200);

    // Pay using Card
    payment.setPaymentStrategy(std::make_unique<CardPayment>());
    payment.pay(500);

    // Pay using Digital Wallet
    payment.setPaymentStrategy(std::make_unique<DigitalWalletPayment>());
    payment.pay(300);

    return 0;
}
```
## Design Principles
* <strong>Single Responsibility Principle (SRP)</strong>: Each class is responsible for a single task. For example, `ParkingTicket` is responsible for managing the ticket data.
* <strong>Open/Closed Principle (OCP)</strong>: The system can be extended by adding new payment strategies without modifying the existing classes.
* <strong>Liskov Substitution Principle (LSP)</strong>: All payment strategies can replace the base `PaymentStrategy` without changing the behavior of the system.
* <strong>Interface Segregation Principle (ISP)</strong>: Payment methods implement only the methods they need via the `PaymentStrategy` interface.
* <strong>Dependency Inversion Principle (DIP)</strong>: High-level modules like `Payment` depend on abstractions (the `PaymentStrategy` interface) instead of concrete implementations.

---
This low-level design ensures that the parking lot system is modular, maintainable, and flexible enough to accommodate changes, such as new vehicle types, payment methods, or parking slot configurations.
