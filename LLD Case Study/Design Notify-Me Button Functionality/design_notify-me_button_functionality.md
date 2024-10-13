# Low Level Design for Notify-Me Button Functionality

### Overview
The "Notify-Me" button is a feature that allows users to be notified when a particular action or event occurs. This design will detail the functionality and architecture of a system where users click the button to subscribe to certain notifications. The system will follow S.O.L.I.D principles and utilize appropriate Design Patterns to ensure scalability, maintainability, and flexibility.

## System Requirements

1. <strong>Notification Subscription</strong>: Users can subscribe to specific events via the "Notify-Me" button.
2. <strong>Notification Trigger</strong>: The system should trigger a notification when the event occurs.
3. <strong>Multiple Notification Types</strong>: Support for various notification types (Email, SMS, Push Notification).
4. <strong>User Management</strong>: Ability to manage user information (name, email, phone, etc.).
5. <strong>Event Management</strong>: Manage events for which notifications are available.
6. <strong>Notification Preferences</strong>: Users should be able to specify preferences (e.g., email only).
7. <strong>Unsubscribe Mechanism</strong>: Users can unsubscribe from notifications anytime.
8. <strong>Notification Queue</strong>: Use a message queue to handle notifications asynchronously.
9. <strong>Error Handling</strong>: Handle errors in notification sending (retry mechanism).
10. <strong>Logging</strong>: Log all notification requests and results.
11. <strong>Scalability</strong>: System must handle many simultaneous notifications.
12. <strong>Security</strong>: Notifications should be sent only to authenticated and authorized users.
13. <strong>Performance</strong>: Notifications must be delivered in near real-time.
14. <strong>User Feedback: Provide user feedback when they subscribe (e.g., a success/failure message).
15. <strong>Notification History</strong>: Store notification history for future reference.

## Class Diagram

``` sql
+------------------+       1       +----------------------+
|      User        |----------------| NotificationService  |
+------------------+                +----------------------+
| - userId         |                | - sendNotification() |
| - name           |                | - subscribe()        |
| - email          |                | - unsubscribe()      |
+------------------+                +----------------------+
         | 1
         |                    1..*           1..*
+------------------+       +------------------------+
|  Event           |-------| NotificationPreference |
+------------------+       +------------------------+
| - eventId        |       | - userId               |
| - eventName      |       | - eventId              |
| - eventType      |       | - preferenceType       |
+------------------+       +------------------------+
         |
         | 1..*
+------------------+
| Notification     |
+------------------+
| - notificationId |
| - eventId        |
| - message        |
+------------------+

+------------------------+
| MessageQueue           |
+------------------------+
| - queue                |
| - enqueue()            |
| - dequeue()            |
+------------------------+
```

### Explanation:

* <strong>User</strong>: Stores user information like name, email, and unique userId.
* <strong>Event</strong>: Represents an event that users can subscribe to.
* <strong>NotificationService</strong>: Handles the core notification logic such as sending, subscribing, and unsubscribing.
* <strong>Notification</strong>: Represents an individual notification for a specific event.
* <strong>NotificationPreference</strong>: Represents user-specific preferences for notifications (e.g., email or SMS).
* <strong>MessageQueue</strong>: Asynchronous messaging system to manage notification delivery.

### Relationships:

* A `User` can have multiple `NotificationPreference` entries (1..* cardinality) for different events.
* Each `Event` can trigger multiple `Notification` messages.
* `NotificationService` is responsible for handling all notifications and uses `MessageQueue` to process them asynchronously.

### Use Case Diagram

```sql

  +----------------+                 
  |    User         | 
  +----------------+                 
          |                         
          v                         
+------------------+   1. Subscribe
| Notify-Me Button |------------------->(Subscribe to Event)
+------------------+                         
          |                         
          v                         
  +--------------------+       2. Notification
  | Notification System |-------------------> (Send Notification)
  +--------------------+                         
```

### Use Cases:

1. Subscribe to Event: User clicks the "Notify-Me" button to subscribe to an event.
2. Send Notification: System sends a notification when the event occurs.

## Database Schema Diagram

```lua

+------------------+       +------------------------+
|      Users       |       |     NotificationPrefs  |
+------------------+       +------------------------+
| userId (PK)      |<---1--| prefId (PK)            |
| name             |       | userId (FK)            |
| email            |       | eventId (FK)           |
+------------------+       | notificationType       |
                            +------------------------+

+------------------+       +------------------------+
|     Events       |       |      Notifications     |
+------------------+       +------------------------+
| eventId (PK)     |<---1--| notificationId (PK)    |
| eventName        |       | eventId (FK)           |
| eventType        |       | message                |
+------------------+       +------------------------+
```

* Users Table: Stores user information.
* NotificationPrefs Table: Stores user preferences for notifications.
* Events Table: Stores events that trigger notifications.
* Notifications Table: Stores the notifications that were sent to users.

### Cardinality:

* `Users` to `NotificationPrefs`: One user can have multiple preferences (1..*).
* `Events` to `Notifications`: One event can generate many notifications (1..*).

## Activity Diagram

``` sql

+---------------------------+
|        User                |
+---------------------------+
           |
           v
+---------------------------+
| Click Notify-Me Button     |
+---------------------------+
           |
           v
+---------------------------+
| Notification Service       |
+---------------------------+
           |
           v
+---------------------------+
| Update Preferences         |
+---------------------------+
           |
           v
+---------------------------+
| Wait for Event Trigger     |
+---------------------------+
           |
           v
+---------------------------+
| Send Notification          |
+---------------------------+
           |
           v
+---------------------------+
| Update Notification Log    |
+---------------------------+
```

## Design Patterns

### Observer Pattern
The Observer pattern is used for managing the relationship between users (subscribers) and events (subjects). When an event is triggered, all the users (observers) subscribed to that event will be notified.

### Code for Observer Pattern in C++

``` cpp
#include <iostream>
#include <vector>
#include <string>

// Observer Interface
class IObserver {
public:
    virtual void update(const std::string &message) = 0;
};

// Concrete Observer (User)
class User : public IObserver {
    std::string name;
public:
    User(const std::string &name) : name(name) {}
    void update(const std::string &message) override {
        std::cout << name << " received notification: " << message << std::endl;
    }
};

// Subject Interface
class ISubject {
public:
    virtual void addObserver(IObserver *observer) = 0;
    virtual void removeObserver(IObserver *observer) = 0;
    virtual void notifyObservers(const std::string &message) = 0;
};

// Concrete Subject (Event)
class Event : public ISubject {
    std::vector<IObserver*> observers;
public:
    void addObserver(IObserver *observer) override {
        observers.push_back(observer);
    }

    void removeObserver(IObserver *observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string &message) override {
        for (auto observer : observers) {
            observer->update(message);
        }
    }

    void triggerEvent(const std::string &eventName) {
        std::cout << "Event " << eventName << " triggered!" << std::endl;
        notifyObservers("Event " + eventName + " occurred.");
    }
};

// Main Function
int main() {
    User user1("Alice");
    User user2("Bob");

    Event event1;
    event1.addObserver(&user1);
    event1.addObserver(&user2);

    event1.triggerEvent("New Product Launch");

    return 0;
}
```

## Design Principles
* <strong>Single Responsibility Principle (SRP)</strong>: Each class in the design has only one reason to change. For instance, `User` manages user details, while `NotificationService` manages notification logic.
* <strong>Open-Closed Principle (OCP)</strong>: The system can easily be extended by adding new types of notifications (e.g., adding a new notification type like push notifications).
* <strong>Liskov Substitution Principle (LSP)</strong>: Any subclass or derived class should be substitutable for its base class. This is achieved in the Observer pattern where `User` can act as an `Observer`.
* <strong>Interface Segregation Principle (ISP)</strong>: The system uses small, specific interfaces like `IObserver` and `ISubject`.
* <strong>Dependency Inversion Principle (DIP)</strong>: High-level modules (like `NotificationService`) do not depend on low-level modules but on abstractions (e.g., `IObserver`, `ISubject`).

#
This is a comprehensive low-level design for the Notify-Me button feature. The design principles and patterns applied ensure maintainability, scalability, and adherence to OOP best practices.