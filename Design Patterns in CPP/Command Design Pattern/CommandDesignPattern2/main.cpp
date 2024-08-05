#include <QCoreApplication>
#include <iostream>
#include <vector>

// Receiver: Electronic Device
class ElectronicDevice {
private:
    std::string name;

public:
    ElectronicDevice(const std::string & n)
        : name(n)
    {
    }

    void turnOn()
    {
        std::cout << name << " :: is ON now " << std::endl;
    }

    void turnOff()
    {
        std::cout << name << " :: is OFF now" << std::endl;
    }
};

// Command interface
class Command {
public:
    virtual void execute() = 0;
};

// Concrete Command: Turn on
class TurnOnCommand : public Command {
private:
    ElectronicDevice& device;

public:
    TurnOnCommand(ElectronicDevice& dev)
        : device(dev)
    {
    }

    void execute() { device.turnOn(); }
};

// Concrete Command: Turn off
class TurnOffCommand : public Command {
private:
    ElectronicDevice& device;

public:
    TurnOffCommand(ElectronicDevice&dev)
        : device(dev)
    {
    }

    void execute() { device.turnOff(); }
};

// Invoker: Remote Control
class RemoteControl {
private:
    std::vector <Command*> commands;

public:
    void addCommand(Command* cmd)
    {
        commands.push_back(cmd);
    }

    void pressButton(int slot)
    {
        if (slot >= 0 && slot < commands.size()) {
            commands[slot]->execute();
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create electronic devices
    ElectronicDevice tv("TV");
    ElectronicDevice lights("Lights");

    // Create commands for turning devices on and off
    TurnOnCommand turnOnTV(tv);
    TurnOffCommand turnOffTV(tv);
    TurnOnCommand turnOnLights(lights);
    TurnOffCommand turnOffLights(lights);

    // Create a remote control
    RemoteControl remote;

    // Set commands for remote buttons
    remote.addCommand(&turnOnTV); // Button 0: Turn on TV
    remote.addCommand(&turnOffTV); // Button 1: Turn off TV
    remote.addCommand(&turnOnLights); // Button 2: Turn on Lights
    remote.addCommand(&turnOffLights); // Button 3: Turn off Lights

    // Press buttons on the remote
    remote.pressButton(0); // Turn on TV
    remote.pressButton(3); // Turn off Lights
    remote.pressButton(1); // Turn off TV
    remote.pressButton(2); // Turn on Lights

    return a.exec();
}
