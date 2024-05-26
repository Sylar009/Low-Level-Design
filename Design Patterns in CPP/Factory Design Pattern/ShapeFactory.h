// Abstract Creator class - ShapeFactory
#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h"

class ShapeFactory {
public:
    virtual unique_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() {};
};

#endif // SHAPEFACTORY_H
