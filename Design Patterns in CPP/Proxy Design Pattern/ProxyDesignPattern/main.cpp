#include <QCoreApplication>
#include <bits/stdc++.h>

using namespace std;

class Image {
public:
    virtual void display() = 0;
};

class RealImage : public Image {
private:
    std::string filename;

public:
    RealImage(const std::string& filename) : filename(filename) {
        // Simulate loading the image (this can be a resource-intensive operation)
        std::cout << "Loading image: " << filename << std::endl;
    }

    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

class ImageProxy : public Image {
private:
    RealImage* realImage; // Reference to the Real Object
    std::string filename;

public:
    ImageProxy(const std::string& filename) :
        realImage(nullptr),
        filename(filename) {}

    void display() override {
        // The Proxy checks if the Real Object is created and loads it if necessary
        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create a proxy to an image
    Image* image = new ImageProxy("example.jpg");

    // Display the image (the Proxy will load the Real Object if necessary)
    image->display();

    // Displaying the image again (the Proxy won't reload it)
    image->display();

    delete image; // Clean up

    return a.exec();
}
