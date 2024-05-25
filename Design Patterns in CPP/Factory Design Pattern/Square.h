// Concrete Product Class - Square
#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape {
public:
    void draw () override;
};

#endif // SQUARE_H