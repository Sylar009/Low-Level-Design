#include <QCoreApplication>
#include <iostream>
#include <string>

// Legacy Printer (Adaptee)
class LegacyPrinter {
public:
    void printInUppercase(const std::string& text)
    {
        std::cout << "Printing: " << text << std::endl;
    }
};

// Modern Computer (Client)
class ModernComputer {
public:
    void sendCommand(const std::string& command)
    {
        std::cout << "Sending command: " << command
            << std::endl;
    }
};

// Adapter class to make the LegacyPrinter compatible with
// ModernComputer
class PrinterAdapter {
private:
    LegacyPrinter legacyPrinter;

public:
    void sendCommand(const std::string& command)
    {
        // Convert the command to uppercase and pass it to
        // the LegacyPrinter
        std::string uppercaseCommand = command;
        for (char& c : uppercaseCommand) {
            c = std::toupper(c);
        }
        legacyPrinter.printInUppercase(uppercaseCommand);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModernComputer computer;
    PrinterAdapter adapter;

    computer.sendCommand("Print this in lowercase");
    adapter.sendCommand(
        "Print this in lowercase (adapted)");

    return a.exec();
}
