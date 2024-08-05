#include <QCoreApplication>
#include <iostream>
#include <string>

using namespace std;

// Component interface - defines the basic ice cream
// operations.
class IceCream {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

// Concrete Component - the basic ice cream class.
class VanillaIceCream : public IceCream {
public:
    string getDescription() const override
    {
        return "Vanilla Ice Cream";
    }

    double cost() const override { return 160.0; }
};

// Decorator - abstract class that extends IceCream.
class IceCreamDecorator : public IceCream {
protected:
    IceCream* iceCream;

public:
    IceCreamDecorator(IceCream* ic)
        : iceCream(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription();
    }

    double cost() const override
    {
        return iceCream->cost();
    }
};

// Concrete Decorator - adds chocolate topping.
class ChocolateDecorator : public IceCreamDecorator {
public:
    ChocolateDecorator(IceCream* ic)
        : IceCreamDecorator(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription()
               + " with Chocolate";
    }

    double cost() const override
    {
        return iceCream->cost() + 100.0;
    }
};

// Concrete Decorator - adds caramel topping.
class CaramelDecorator : public IceCreamDecorator {
public:
    CaramelDecorator(IceCream* ic)
        : IceCreamDecorator(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription() + " with Caramel";
    }

    double cost() const override
    {
        return iceCream->cost() + 150.0;
    }
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create a vanilla ice cream
    IceCream* vanillaIceCream = new VanillaIceCream();
    cout << "Order: " << vanillaIceCream->getDescription()
         << ", Cost: Rs." << vanillaIceCream->cost()
         << endl;

    // Wrap it with ChocolateDecorator
    IceCream* chocolateIceCream
        = new ChocolateDecorator(vanillaIceCream);
    cout << "Order: " << chocolateIceCream->getDescription()
         << ", Cost: Rs." << chocolateIceCream->cost()
         << endl;

    // Wrap it with CaramelDecorator
    IceCream* caramelIceCream
        = new CaramelDecorator(chocolateIceCream);
    cout << "Order: " << caramelIceCream->getDescription()
         << ", Cost: Rs." << caramelIceCream->cost()
         << endl;

    delete vanillaIceCream;
    delete chocolateIceCream;
    delete caramelIceCream;

    return a.exec();
}
