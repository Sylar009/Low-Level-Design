#include "CircleFactory.h"
#include "Circle.h"

Shape *CircleFactory::createShape()
{
    return new Circle();
}