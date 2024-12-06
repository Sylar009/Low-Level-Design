# Low-Level Design for Car Rental System

## Overview

A Car Rental System allows users to search, book, and rent cars. The system manages car inventory, user bookings, and payments while ensuring optimal use of the fleet. It supports various user types (e.g., customers, admins) and includes features such as car availability checking, pricing, and transaction management.

The design will follow S.O.L.I.D. principles to ensure modularity, scalability, and maintainability.

---

## System Requirements

1. <strong>User Registration and Login</strong>: Users must register and log in to use the system.
2. <strong>Car Inventory Management</strong>: Admins can add, update, and remove cars.
3. <strong>Search and Filter Cars</strong>: Users can search cars by type, price, brand, and availability.
4. <strong>Car Booking</strong>: Users can book cars for specific time periods.
5. <strong>Booking Management</strong>: Users can view, cancel, or update bookings.
6. <strong>Pricing and Billing</strong>: The system calculates rental costs based on duration and car type.
7. <strong>Payment Processing</strong>: Users can pay via various methods (credit card, wallet, etc.).
8. <strong>Car Availability</strong>: Cars unavailable due to bookings or maintenance are flagged.
9. <strong>Admin Dashboard</strong>: Admins can view bookings, earnings, and car status.
10. <strong>Notifications</strong>: Notify users about booking confirmation, cancellations, and due returns.
11. <strong>Multi-location Support</strong>: Cars can be rented and returned to different locations.
12. <strong>Vehicle Maintenance</strong>: Admins can flag cars for maintenance.
13. <strong>User Roles</strong>: Different permissions for admins and customers.
14. <strong>Discount and Offers</strong>: Admins can create discounts for promotional purposes.
15. <strong>Scalability</strong>: The system should handle growing inventory and user base.

---

## Class Diagram
``` plaintext

+--------------------+         +--------------------+
|        User        |<------->|      Booking       |
+--------------------+         +--------------------+
| - id               |         | - id              |
| - name             |         | - userId          |
| - email            |         | - carId           |
| - role             |         | - startDate       |
| - register()       |         | - endDate         |
| - login()          |         | - totalCost       |
+--------------------+         | - status          |
                               +--------------------+
        ^                                |
        |                                |
+--------------------+          +--------------------+
|      Admin         |          |       Car          |
+--------------------+          +--------------------+
| - manageInventory()|          | - id              |
| - viewReports()    |          | - model           |
+--------------------+          | - brand           |
                                | - location        |
                                | - isAvailable     |
                                | - calculateCost() |
+--------------------+          +--------------------+
|    Notification    |
+--------------------+
| - id               |
| - userId           |
| - message          |
| - sendNotification()|
+--------------------+
```

### Explanation:

1. <strong>User</strong>: Base class for all system users (e.g., Admin, Customer).
2. <strong>Admin</strong>: Derived from User, performs admin-specific actions like inventory and report management.
3. <strong>Booking</strong>: Represents a user's booking details.
4. <strong>Car</strong>: Represents cars in the inventory with details like availability and cost.
5. <strong>Notification</strong>: Manages notifications to users (e.g., booking confirmation).

### Relationships:

* A `User` can make multiple `Bookings`.
* Each `Booking` is associated with one `Car`.
* `Admin` inherits from `User`.

---

## Use Case Diagram
``` plaintext

          +----------------+
          |      User      |
          +----------------+
               /     \
+----------------+   +----------------+
|   Search Cars   |   |  Manage Booking|
+----------------+   +----------------+
               \     /
          +----------------+
          |  Admin/Customer |
          +----------------+
               |
   +---------------------------+
   |  Add/Update/Delete Cars    |
   +---------------------------+
               |
   +---------------------------+
   |  View Reports/Manage Fleet |
   +---------------------------+

```

## Use Cases:

1. <strong>Search Cars</strong>: Users search available cars based on filters.
1. <strong>Manage Booking</strong>: Users create, update, and cancel bookings.
1. <strong>Admin Tasks</strong>: Add, update, or delete cars and manage bookings.
1. <strong>View Reports</strong>: Admins can view system statistics.

---

## Schema Diagram
``` plaintext

+--------------------+       +--------------------+
|        User        |       |      Booking       |
+--------------------+       +--------------------+
| userId (PK)        |       | bookingId (PK)     |
| name               |       | userId (FK)        |
| email              |       | carId (FK)         |
| role               |       | startDate          |
| password           |       | endDate            |
+--------------------+       | totalCost          |
                             +--------------------+

+--------------------+
|        Car         |
+--------------------+
| carId (PK)         |
| model              |
| brand              |
| location           |
| isAvailable        |
+--------------------+
```

### Cardinality:

* A `User` can have multiple `Bookings`.
* A `Car` can have zero or one `Booking` at any time.

---

## Activity Diagram
``` plaintext

+-------------------------+
|      Start User Action   |
+-------------------------+
             |
+-------------------------+
| Search Cars/Filters      |
+-------------------------+
             |
+-------------------------+
| View Available Cars      |
+-------------------------+
             |
+-------------------------+
| Select and Book Car      |
+-------------------------+
             |
+-------------------------+
| Calculate Cost/Payment   |
+-------------------------+
             |
+-------------------------+
| Confirm and Notify User  |
+-------------------------+
```
---

## Design Patterns
1. <strong>Singleton Pattern</strong>:
The `CarRentalSystem` ensures only one instance handles the system logic.

2. <strong>Factory Pattern</strong>:
Used for creating `User` objects (Admin or Customer).

3. <strong>Observer Pattern</strong>:
Notifications are sent to users when booking is confirmed or updated.

## C++ Code: Singleton and Factory Pattern

``` cpp
#include <iostream>
#include <vector>
#include <memory>

// Base User Class
class User {
protected:
    int id;
    std::string name, email;
public:
    User(int id, const std::string& name, const std::string& email) 
        : id(id), name(name), email(email) {}

    virtual void displayRole() = 0;
};

class Customer : public User {
public:
    Customer(int id, const std::string& name, const std::string& email) 
        : User(id, name, email) {}

    void displayRole() override {
        std::cout << "Customer: " << name << std::endl;
    }
};

class Admin : public User {
public:
    Admin(int id, const std::string& name, const std::string& email) 
        : User(id, name, email) {}

    void displayRole() override {
        std::cout << "Admin: " << name << std::endl;
    }
};

// Factory Pattern
class UserFactory {
public:
    static std::unique_ptr<User> createUser(const std::string& role, int id, const std::string& name, const std::string& email) {
        if (role == "Admin") {
            return std::make_unique<Admin>(id, name, email);
        } else {
            return std::make_unique<Customer>(id, name, email);
        }
    }
};

// Singleton for Car Rental System
class CarRentalSystem {
private:
    static CarRentalSystem* instance;
    CarRentalSystem() {}

public:
    static CarRentalSystem* getInstance() {
        if (!instance) {
            instance = new CarRentalSystem();
        }
        return instance;
    }

    void manageSystem() {
        std::cout << "Managing Car Rental System" << std::endl;
    }
};

CarRentalSystem* CarRentalSystem::instance = nullptr;

int main() {
    // Using Factory Pattern
    auto user1 = UserFactory::createUser("Customer", 1, "Alice", "alice@example.com");
    auto user2 = UserFactory::createUser("Admin", 2, "Bob", "bob@example.com");

    user1->displayRole();
    user2->displayRole();

    // Using Singleton Pattern
    CarRentalSystem* system = CarRentalSystem::getInstance();
    system->manageSystem();

    return 0;
}
```
--- 

## S.O.L.I.D. Principles Applied

1. <strong>SRP</strong>: Each class (e.g., `User`, `Car`, `Booking`) has a single responsibility.
2. <strong>OCP</strong>: New user types or features can be added without modifying existing classes.
3. <strong>LSP</strong>: Derived classes (`Customer`, `Admin`) can replace `User` without altering functionality.
4. <strong>ISP</strong>: Interfaces provide only necessary methods.
5. <strong>DIP</strong>: High-level modules (e.g., `CarRentalSystem`) depend on abstractions (`User`), not concrete classes.