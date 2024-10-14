# Low Level Design for <strong>Pizza Billing System</strong>

## Overview
The pizza billing system is designed to allow customers to order pizzas, customize them with toppings, and receive a bill based on their selections. The system will allow users to select pizzas from a menu, choose different toppings, apply discounts, and generate bills with the final total. The design will ensure that the system is scalable, maintainable, and follows S.O.L.I.D principles. Key features will include pizza customization, order management, and billing.

## System Requirements
1. <strong>Pizza Selection</strong>: Customers can choose pizzas from the menu (with different sizes and crust types).
2. <strong>Toppings Customization</strong>: Customers can add or remove toppings (extra cheese, olives, etc.).
3. <strong>Pizza Pricing</strong>: Each pizza has a base price, with additional toppings having separate prices.
4. <strong>Discount Management</strong>: Apply discounts (percentage-based or fixed) to orders.
5. <strong>Order Summary</strong>: Display an order summary before checkout.
6. <strong>Order Management</strong>: Ability to place, modify, and cancel orders.
7. <strong>Multiple Payment Options</strong>: Support for different payment methods (cash, card, or digital payments).
8. <strong>Bill Generation</strong>: Generate a detailed bill after the order is confirmed, showing the breakdown of prices.
9. <strong>Tax Calculation</strong>: Automatically calculate applicable taxes on the total order.
10. <strong>Order Status Tracking</strong>: Track the status of the order (Preparing, Ready, Delivered).
11. <strong>Customer Details</strong>: Capture and manage customer information (name, contact, address).
12. <strong>Pizza Add-ons</strong>: Support additional add-ons (like drinks or desserts) along with pizzas.
13. <strong>Error Handling</strong>: Handle cases where selected items are unavailable.
14. <strong>Notifications</strong>: Notify customers about order confirmation and order status via email/SMS.
15. <strong>User Feedback</strong>: Provide feedback on order success/failure with appropriate messages.

## Class Diagram
```lua
+------------------+       1       +-------------------+
|   Customer       |----------------|  Order            |
+------------------+                +-------------------+
| - customerId     |                | - orderId         |
| - name           |                | - totalAmount     |
| - contactInfo    |                | - orderStatus     |
+------------------+                | - paymentStatus   |
         | 1                         | - applyDiscount() |
         |                           +-------------------+
         |
         |                    1..*       
+------------------+       +------------------------+
|    Pizza         |-------|    Topping             |
+------------------+       +------------------------+
| - pizzaId        |       | - toppingId            |
| - size           |       | - name                 |
| - crustType      |       | - price                |
| - basePrice      |       +------------------------+
+------------------+
         |
         | 1..*
+------------------+
|    AddOn         |
+------------------+
| - addOnId        |
| - name           |
| - price          |
+------------------+

+------------------+       +-------------------+
|    Payment       |-------| PaymentStrategy    |
+------------------+       +-------------------+
| - paymentId      |       | - pay()            |
| - amount         |       +-------------------+
| - paymentMethod  |
+------------------+
```

### Explanation:

* `Customer`: Stores customer information such as name and contact details.
* `Order`: Represents the customer’s order and handles the total amount, status, and discount application.
* `Pizza`: Represents a pizza in the system, including details about its size, crust type, and base price.
* `Topping`: Represents toppings that can be added to pizzas, with their own prices.
* `AddOn`: Represents additional items such as drinks or desserts.
* `Payment`: Handles the payment details like amount and method.
* `PaymentStrategy`: An interface used for different payment methods (e.g., Cash, Card, Digital).

### Relationships:

A `Customer` can have multiple `Order` instances (1..*).
An `Order` can have multiple `Pizza` instances (1..*).
Each `Pizza` can have multiple `Topping` and `AddOn` instances.
The `Payment` class uses the Strategy Pattern to manage different payment methods.

## Use Case Diagram

``` sql
    +-------------------+                 
    |     Customer       |
    +-------------------+                 
           |                          
           v                          
    +--------------------+     1. Place Order
    |   Select Pizza      |-------------------> (Pizza Selection)
    +--------------------+                  
           |                          
           v                          
    +-------------------+       2. Customize Pizza
    |  Add Toppings      |-------------------> (Topping Selection)
    +-------------------+                  
           |                          
           v                          
    +-------------------+       3. Add Add-ons
    |  Add Add-ons       |-------------------> (Select Drinks/Desserts)
    +-------------------+                  
           |                          
           v                          
    +-------------------+       4. Checkout
    |   Confirm Order    |-------------------> (Review Order)
    +-------------------+                  
           |                          
           v                          
    +-------------------+       5. Payment
    |  Payment System    |-------------------> (Make Payment)
    +-------------------+
```

### Use Cases:

1. <strong>Pizza Selection</strong>: Customer selects the pizza type, size, and crust.
2. <strong>Topping Selection</strong>: Customer customizes the pizza by adding or removing toppings.
3. <strong>Add Add-ons</strong>: Customer selects additional items like drinks or desserts.
4. <strong>Review Order</strong>: Customer reviews the order summary before confirming.
5. <strong>Payment</strong>: Customer makes the payment via the payment system.

## Database Schema Diagram
``` lua
+------------------+       +------------------------+
|    Customers     |       |   Orders               |
+------------------+       +------------------------+
| customerId (PK)  |<---1--| orderId (PK)           |
| name             |       | customerId (FK)        |
| contactInfo      |       | totalAmount            |
+------------------+       | orderStatus            |
                            +------------------------+

+------------------+       +------------------------+
|    Pizzas        |       |  Toppings              |
+------------------+       +------------------------+
| pizzaId (PK)     |       | toppingId (PK)         |
| orderId (FK)     |       | pizzaId (FK)           |
| size             |       | name                   |
| crustType        |       | price                  |
| basePrice        |       +------------------------+
+------------------+                                

+------------------+       +------------------------+
|   AddOns         |       |   Payments             |
+------------------+       +------------------------+
| addOnId (PK)     |       | paymentId (PK)         |
| name             |       | orderId (FK)           |
| price            |       | amount                 |
+------------------+       | paymentMethod          |
                            +------------------------+
```
* <strong>Customers Table</strong>: Stores customer information.
* <strong>Orders Table</strong>: Stores orders placed by customers.
* <strong>Pizzas Table</strong>: Stores pizza information related to the order.
* <strong>Toppings Table</strong>: Stores the toppings for a pizza.
* <strong>AddOns Table</strong>: Stores add-ons like drinks and desserts.
* <strong>Payments Table</strong>: Stores payment information.

### Cardinality:

* One `Customer` can place multiple `Orders`.
* Each `Order` can have multiple `Pizzas`.
* Each `Pizza` can have multiple `Toppings`.
* Each `Order` can have multiple `AddOns`.
* Each `Order` is linked to a single `Payment`.

## Activity Diagram
``` sql
+---------------------------+
|        Customer            |
+---------------------------+
           |
           v
+---------------------------+
|  Select Pizza from Menu    |
+---------------------------+
           |
           v
+---------------------------+
|  Customize Toppings        |
+---------------------------+
           |
           v
+---------------------------+
|  Add Add-ons (Optional)    |
+---------------------------+
           |
           v
+---------------------------+
|  Review and Confirm Order  |
+---------------------------+
           |
           v
+---------------------------+
|  Make Payment              |
+---------------------------+
           |
           v
+---------------------------+
|  Generate Bill             |
+---------------------------+
```

## Design Patterns

<b>Strategy Pattern for Payment Processing</b>
The Strategy Pattern allows us to use different payment methods like cash, card, or digital payments. The payment method is selected dynamically at runtime.

<b>Code for Strategy Pattern in C++</b>

``` cpp
#include <iostream>
#include <memory>

// Strategy Interface
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategy for Credit Card Payment
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Credit Card." << std::endl;
    }
};

// Concrete Strategy for Cash Payment
class CashPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Cash." << std::endl;
    }
};

// Concrete Strategy for Digital Wallet Payment
class DigitalWalletPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Digital Wallet." << std::endl;
    }
};

// Payment Context
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

    // Customer selects Credit Card Payment
    payment.setPaymentStrategy(std::make_unique<CreditCardPayment>());
    payment.pay(500);

    // Customer selects Cash Payment
    payment.setPaymentStrategy(std::make_unique<CashPayment>());
    payment.pay(300);

    // Customer selects Digital Wallet Payment
    payment.setPaymentStrategy(std::make_unique<DigitalWalletPayment>());
    payment.pay(450);

    return 0;
}
```

## Design Principles
* <strong>Single Responsibility Principle (SRP)</strong>: Each class in the system has a single responsibility. For example, `Order` class handles the management of an order, while `Pizza` is responsible for pizza details.
* <strong>Open-Closed Principle (OCP)</strong>: The system is open for extension (e.g., adding new types of pizzas, toppings, or payments) but closed for modification.
* <strong>Liskov Substitution Principle (LSP)</strong>: Subclasses (e.g., different payment strategies) can replace their base class (`PaymentStrategy`) without affecting the functionality.
* <strong>Interface Segregation Principle (ISP)</strong>: Different interfaces for different payment strategies ensure that classes are not forced to implement unnecessary methods.
* <strong>Dependency Inversion Principle (DIP)</strong>: High-level modules like `Payment` depend on abstractions (`PaymentStrategy`), not low-level concrete implementations.

---
This detailed low-level design for the pizza billing system includes all aspects from class diagrams to code implementation using design patterns, following design principles to ensure that the system is robust, scalable, and maintainable.