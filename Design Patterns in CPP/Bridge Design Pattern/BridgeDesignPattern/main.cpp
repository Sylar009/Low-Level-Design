#include <QCoreApplication>
#include <iostream>

// Abstraction: Shape
class Shape {
public:
    virtual void draw() = 0;
};

// Implementations: Renderer (VectorRenderer and
// RasterRenderer)
class Renderer {
public:
    virtual void render() = 0;
};

class VectorRenderer : public Renderer {
public:
    void render() override
    {
        std::cout << "Rendering as a vector\n";
    }
};

class RasterRenderer : public Renderer {
public:
    void render() override
    {
        std::cout << "Rendering as a raster\n";
    }
};

// Concrete Abstractions: Circle and Square
class Circle : public Shape {
public:
    Circle(Renderer& renderer)
        : _renderer(renderer)
    {
    }

    void draw() override
    {
        std::cout << "Drawing a circle ";
        _renderer.render();
    }

private:
    Renderer& _renderer;
};

class Square : public Shape {
public:
    Square(Renderer& renderer)
        : _renderer(renderer)
    {
    }

    void draw() override
    {
        std::cout << "Drawing a square ";
        _renderer.render();
    }

private:
    Renderer& _renderer;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    VectorRenderer vectorRenderer;
    RasterRenderer rasterRenderer;

    Circle circle(vectorRenderer);
    Square square(rasterRenderer);

    circle.draw(); // Output: Drawing a circle Rendering as
        // a vector
    square.draw(); // Output: Drawing a square Rendering as
        // a raster

    return a.exec();
}
