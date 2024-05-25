#include "SquareFactory.h"
#include "Square.h"

Shape* SquareFactory::createShape()
{
    return new Square();
}