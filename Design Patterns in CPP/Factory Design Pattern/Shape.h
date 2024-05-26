// Abstract Product Class - Shape
#ifndef SHAPE_H
#define SHAPE_H

#include <bits/stdc++.h>

using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape () = default;
};

#endif // SHAPE_H
