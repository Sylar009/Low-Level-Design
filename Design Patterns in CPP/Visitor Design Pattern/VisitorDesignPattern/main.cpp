#include <QCoreApplication>
#include <iostream>
#include <vector>

// Forward declarations
class Circle;
class Square;

// Visitor interface
class ShapeVisitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Square& square) = 0;
};

// Element interface
class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
};

// Concrete Element: Circle
class Circle : public Shape {
public:
    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

    void draw() {
        std::cout << "Drawing Circle\n";
    }
};

// Concrete Element: Square
class Square : public Shape {
public:
    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

    void draw() {
        std::cout << "Drawing Square\n";
    }
};

// Concrete Visitor: DrawingVisitor
class DrawingVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Drawing a Circle\n";
        circle.draw();
    }

    void visit(Square& square) override {
        std::cout << "Drawing a Square\n";
        square.draw();
    }
};

// Concrete Visitor: AreaVisitor
class AreaVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Calculating area of Circle\n";
        // Calculate and print area logic for Circle
    }

    void visit(Square& square) override {
        std::cout << "Calculating area of Square\n";
        // Calculate and print area logic for Square
    }
};

// Object Structure
class ShapeContainer {
public:
    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    void performOperations(ShapeVisitor& visitor) {
        for (Shape* shape : shapes) {
            shape->accept(visitor);
        }
    }

private:
    std::vector<Shape*> shapes;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create instances of shapes
    Circle circle;
    Square square;

    // Create a container and add shapes to it
    ShapeContainer container;
    container.addShape(&circle);
    container.addShape(&square);

    // Create visitors
    DrawingVisitor drawingVisitor;
    AreaVisitor areaVisitor;

    // Perform drawing operations
    container.performOperations(drawingVisitor);

    // Perform area calculation operations
    container.performOperations(areaVisitor);

    return a.exec();
}
