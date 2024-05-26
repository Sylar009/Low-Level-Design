#include "SquareFactory.h"
#include "Square.h"

unique_ptr<Shape> SquareFactory::createShape()
{
    unique_ptr<Shape> square_factory(new Square());
    return square_factory;
}
