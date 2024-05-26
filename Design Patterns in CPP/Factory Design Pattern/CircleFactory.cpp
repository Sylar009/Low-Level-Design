#include "CircleFactory.h"
#include "Circle.h"

unique_ptr<Shape> CircleFactory::createShape()
{
    unique_ptr<Shape> circle_factory(new Circle());
    return circle_factory;
}
