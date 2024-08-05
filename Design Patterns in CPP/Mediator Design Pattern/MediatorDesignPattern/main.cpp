#include <QCoreApplication>
#include <iostream>
#include <string>

// Colleague Interface
class Airplane {
public:
    virtual void requestTakeoff() = 0;
    virtual void requestLanding() = 0;
    virtual void notifyAirTrafficControl(const std::string& message) = 0;
};

// Mediator Interface
class AirTrafficControlTower {
public:
    virtual void requestTakeoff(Airplane* airplane) = 0;
    virtual void requestLanding(Airplane* airplane) = 0;
};

// Concrete Colleague
class CommercialAirplane : public Airplane {
private:
    AirTrafficControlTower* mediator;

public:
    CommercialAirplane(AirTrafficControlTower* mediator) :
        mediator(mediator) {}

    void requestTakeoff() override {
        mediator->requestTakeoff(this);
    }

    void requestLanding() override {
        mediator->requestLanding(this);
    }

    void notifyAirTrafficControl(const std::string& message) override {
        std::cout << "Commercial Airplane: " << message << std::endl;
    }
};


// Concrete Mediator
class AirportControlTower : public AirTrafficControlTower {
public:
    void requestTakeoff(Airplane* airplane) override {
        // Logic for coordinating takeoff
        airplane->notifyAirTrafficControl("Requesting takeoff clearance.");
    }

    void requestLanding(Airplane* airplane) override {
        // Logic for coordinating landing
        airplane->notifyAirTrafficControl("Requesting landing clearance.");
    }
};

// Main class
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Instantiate the Mediator (Airport Control Tower)
    AirTrafficControlTower* controlTower = new AirportControlTower();

    // Instantiate Concrete Colleagues (Commercial Airplanes)
    Airplane* airplane1 = new CommercialAirplane(controlTower);
    Airplane* airplane2 = new CommercialAirplane(controlTower);

    // Set up the association between Concrete Colleagues and the Mediator
    airplane1->requestTakeoff();
    airplane2->requestLanding();

    // Output:
    // Commercial Airplane: Requesting takeoff clearance.
    // Commercial Airplane: Requesting landing clearance.

    delete controlTower;
    delete airplane1;
    delete airplane2;

    return a.exec();
}
