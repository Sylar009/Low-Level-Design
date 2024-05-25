#include "Circle.h"
#include "Square.h"
#include "CircleFactory.h"
#include "SquareFactory.h"

int main()
{
    ShapeFactory* circleFactory = new CircleFactory();
    ShapeFactory* squareFactory = new SquareFactory();

    Shape* circle = circleFactory->createShape();
    Shape* square = squareFactory->createShape();

    circle->draw(); // Output: Drawing a Circle
    square->draw(); // Output: Drawing a Square
    
  
    delete circleFactory;
    delete squareFactory;
    delete circle;
    delete square;

    
      // Client code based on user-input
  
      /* cout << "Enter shape type (circle or square): ";
    string shapeType;
    cin >> shapeType;

    ShapeFactory* shapeFactory = nullptr;
    if (shapeType == "circle") {
        shapeFactory = new CircleFactory();
    } else if (shapeType == "square") {
        shapeFactory = new SquareFactory();
    } else {
        cout << "Invalid shape type entered." << endl;
        return 1;
    }

    Shape* shape = shapeFactory->createShape();
    shape->draw();

    delete shapeFactory;
    delete shape; */

    return 0;
}