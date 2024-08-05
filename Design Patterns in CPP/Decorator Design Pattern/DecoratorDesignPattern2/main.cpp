#include <QCoreApplication>
#include <iostream>
#include <string>

using namespace std;

// Component interface - defines the basic cake operations.
class Cake {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

// Concrete Component - the basic cake class.
class PlainCake : public Cake {
public:
    string getDescription() const override
    {
        return "Plain Cake";
    }

    double cost() const override { return 300.0; }
};

// Decorator - abstract class that extends Cake.
class CakeDecorator : public Cake {
protected:
    Cake* cake;

public:
    CakeDecorator(Cake* c)
        : cake(c)
    {
    }

    string getDescription() const override
    {
        return cake->getDescription();
    }

    double cost() const override { return cake->cost(); }
};

// Concrete Decorator - adds chocolate topping.
class ChocolateDecorator : public CakeDecorator {
public:
    ChocolateDecorator(Cake* c)
        : CakeDecorator(c)
    {
    }

    string getDescription() const override
    {
        return cake->getDescription() + " with Chocolate";
    }

    double cost() const override
    {
        return cake->cost() + 200.0;
    }
};

// Concrete Decorator - adds fruit decorations.
class FruitDecorator : public CakeDecorator {
public:
    FruitDecorator(Cake* c)
        : CakeDecorator(c)
    {
    }

    string getDescription() const override
    {
        return cake->getDescription() + " with Fruits";
    }

    double cost() const override
    {
        return cake->cost() + 150.0;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create a plain cake
    Cake* plainCake = new PlainCake();
    cout << "Plain Cake:" << plainCake->getDescription()
         << "\nCost:Rs." << plainCake->cost() << endl;

    // Wrap it with ChocolateDecorator
    Cake* chocolateCake = new ChocolateDecorator(plainCake);
    cout << "\nChocolate Cake:"
         << chocolateCake->getDescription() << "\nCost:Rs."
         << chocolateCake->cost() << endl;

    // Wrap it with FruitDecorator
    Cake* fruitCake1 = new FruitDecorator(chocolateCake);
    cout << "\nFruit Cake:" << fruitCake1->getDescription()
         << "\nCost:Rs." << fruitCake1->cost() << endl;

    // Clean up memory
    delete chocolateCake;
    delete fruitCake1;

    // Wrap plain cake with FruitDecorator
    Cake* fruitCake2 = new FruitDecorator(plainCake);
    cout << "\nFruit Cake:" << fruitCake2->getDescription()
         << "\nCost:Rs." << fruitCake2->cost() << endl;

    // Clean up memory
    delete plainCake;
    delete fruitCake2;

    return a.exec();
}
