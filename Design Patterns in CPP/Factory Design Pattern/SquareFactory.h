// Concrete Creator Class - Square Factory
#ifndef SQUAREFACTORY_H
#define SQUAREFACTORY_H

#include "ShapeFactory.h"

class SquareFactory : public ShapeFactory {
public:
    unique_ptr<Shape> createShape() override;
};

#endif // SQUAREFACTORY_H
