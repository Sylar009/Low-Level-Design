// Concrete Product Class - Circle
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    void draw () override;
};

#endif // CIRCLE_H
