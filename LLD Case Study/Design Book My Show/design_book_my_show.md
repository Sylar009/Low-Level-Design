# Low-Level Design for BookMyShow (Online Ticket Booking System)

## Overview
BookMyShow is an online platform that allows users to book tickets for movies, events, and shows. The system must handle multiple concurrent users, ensuring data consistency and a smooth booking experience.

---

## System Requirements

1. The system should allow users to browse movies, events, and their schedules.
2. Users should be able to search for available shows based on location, date, and genre.
3. Provide seat selection functionality.
4. Handle multiple users concurrently booking seats for the same show, ensuring no overbooking.
5. Implement payment integration for booking confirmation.
6. Allow users to view their booking history.
7. Admins should be able to manage shows (add, update, delete).
8. Notify users about upcoming shows or events based on their preferences.
9. Provide a cancellation option, with refund policies.
10. Ensure scalability to support high traffic during peak times.
11. Log all transactions for audit purposes.
12. Provide error handling and user-friendly error messages.
13. Ensure data security for sensitive information.
14. Allow integration with third-party services for marketing and notifications.
15. Support different platforms (web, mobile, API).

---

## Class Diagram

``` plaintext

+------------------+
|     User         |
+------------------+
| - userId         |
| - name           |
| - email          |
| - bookingHistory |
| + searchShows()  |
| + bookTicket()   |
+------------------+

+------------------+
|     Admin        |
+------------------+
| - adminId        |
| - name           |
| + manageShows()  |
+------------------+

+------------------+
|     Show         |
+------------------+
| - showId         |
| - movie/event    |
| - time           |
| - seats[]        |
| + getAvailableSeats() |
| + reserveSeat()  |
+------------------+

+------------------+
|     Seat         |
+------------------+
| - seatId         |
| - status         |
| + reserve()      |
| + release()      |
+------------------+

+------------------+
|     Payment      |
+------------------+
| - paymentId      |
| - amount         |
| - status         |
| + processPayment() |
+------------------+

+------------------+
| BookingManager   |
+------------------+
| - bookings[]     |
| + createBooking()|
| + cancelBooking()|
+------------------+

+------------------+
| Notification     |
+------------------+
| - userId         |
| - message        |
| + sendNotification() |
+------------------+
```

### Relationships:

`User` and `Admin` interact with `Show` and `BookingManager`.
`Show` contains multiple `Seat` objects.
`BookingManager` handles booking transactions and coordinates with `Payment`.
`Notification` is used to inform users about booking and events.

---

## Use Case Diagram

``` plaintext

+----------------------+
|        User          |
+----------------------+
        /   \
   Search   Book Ticket
       \     /
        Admin
          |
      Manage Shows
``` 
### Use Cases:

1. Search for shows and movies.
2. Book tickets.
3. Admin management of shows.
4. Notifications for events and bookings.

---


## Schema Diagram

``` plaintext

+------------------+
|      User        |
+------------------+
| userId (PK)      |
| name             |
| email            |
| bookingHistory[] |
+------------------+

+------------------+
|      Show        |
+------------------+
| showId (PK)      |
| movie/event      |
| time             |
| seats[]          |
+------------------+

+------------------+
|      Seat        |
+------------------+
| seatId (PK)      |
| status           |
+------------------+

+------------------+
|    Booking       |
+------------------+
| bookingId (PK)   |
| userId (FK)      |
| showId (FK)      |
| seatId (FK)      |
| paymentId (FK)   |
| status           |
+------------------+

+------------------+
|    Payment       |
+------------------+
| paymentId (PK)   |
| amount           |
| status           |
+------------------+
```

### Cardinality:

* One `User` can book multiple `Shows`.
* Each `Show` has multiple `Seats`.
* Each `Seat` is reserved for a single `Booking`.
* One `Payment` corresponds to one `Booking`.

---

## Activity Diagram
``` plaintext

+-------------------------+
| User Selects Show       |
+-------------------------+
            |
+-------------------------+
| User Selects Seat(s)    |
+-------------------------+
            |
+-------------------------+
| Check Seat Availability |
+-------------------------+
        /   \
   Available  Not Available
        |          |
+-------------------------+
| Reserve Seat            |
+-------------------------+
            |
+-------------------------+
| Process Payment         |
+-------------------------+
            |
+-------------------------+
| Confirm Booking         |
+-------------------------+
            |
+-------------------------+
| Notify User             |
+-------------------------+
```
### Concurrency Handling
To handle concurrent seat booking:

1. Use optimistic locking for seat reservations.
2. Implement database transactions to ensure atomic operations.
3. Apply thread synchronization in the application layer.
4. Use a distributed message queue for notification systems.

---

## Design Patterns
1. <strong>Singleton Pattern</strong>:
Used for managing a single instance of critical services like `BookingManager`.

2. <strong>Factory Pattern</strong>:
Used for creating different types of users (`User`, `Admin`).

3. <strong>Observer Pattern</strong>:
Used for notification services.

4. <strong>Strategy Pattern</strong>:
Used for different payment strategies (e.g., credit card, UPI).

---

## C++ Code for Booking with Observer Pattern

``` cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// Observer Interface
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

// Concrete Observer
class User : public Observer {
private:
    std::string name;

public:
    User(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Notification for " << name << ": " << message << "\n";
    }
};

// Subject
class NotificationService {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyAll(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

// Seat Class
class Seat {
private:
    int id;
    bool isReserved;

public:
    Seat(int id) : id(id), isReserved(false) {}

    bool reserve() {
        if (!isReserved) {
            isReserved = true;
            return true;
        }
        return false;
    }

    void release() {
        isReserved = false;
    }
};

// Booking Manager
class BookingManager {
private:
    NotificationService notificationService;

public:
    void bookSeat(Seat& seat, User& user) {
        if (seat.reserve()) {
            notificationService.addObserver(&user);
            notificationService.notifyAll("Booking confirmed!");
        } else {
            std::cout << "Seat is already reserved.\n";
        }
    }
};

// Main Function
int main() {
    Seat seat1(101);
    User user1("John");

    BookingManager bookingManager;
    bookingManager.bookSeat(seat1, user1);

    return 0;
}
```

---

## S.O.L.I.D. Principles
1. <strong></strong>SRP</strong>: Separate responsibilities for booking, payment, and notification handling.
2. <strong>OCP</strong>: Easily extendable for new payment methods or notification systems.
3. <strong>LSP</strong>: Replaceable `Observer` implementations without changing `NotificationService`.
4. <strong>ISP</strong>: Classes expose only relevant methods.
5. <strong>DIP</strong>: Abstractions like `Observer` and `NotificationService` decouple the system.