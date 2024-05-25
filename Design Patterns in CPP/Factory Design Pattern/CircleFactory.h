// Concrete Creator Class - Circle Factory
#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

#include "ShapeFactory.h"

class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() override;
};

#endif // CIRCLEFACTORY_H