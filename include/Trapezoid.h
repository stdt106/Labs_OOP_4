#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <cmath>
#include <iostream>

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    T base1, base2, height;

public:
    Trapezoid() : base1(0), base2(0), height(0) {}
    Trapezoid(T base1, T base2, T height) : base1(base1), base2(base2), height(height) {
        this->vertices.clear();
        T offset = (base2 - base1) / 2;
        
        this->vertices.push_back(std::make_unique<Point<T>>(-base1/2, -height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(base1/2, -height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(base2/2, height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(-base2/2, height/2));
    }

    Point<T> calculateGeometricCenter() const override {
        T centerY = 0;
        return Point<T>(0, centerY);
    }

    explicit operator double() const override {
        return static_cast<double>((base1 + base2) * height / 2.0);
    }

    bool operator==(const Figure<T>& other) const override {
        const Trapezoid* otherTrap = dynamic_cast<const Trapezoid*>(&other);
        if (!otherTrap) return false;
        return base1 == otherTrap->base1 && 
               base2 == otherTrap->base2 && 
               height == otherTrap->height;
    }

    void print(std::ostream& os) const override {
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
    }

    void read(std::istream& is) override {
        T b1, b2, h;
        is >> b1 >> b2 >> h;
        *this = Trapezoid(b1, b2, h);
    }

    T getBase1() const { return base1; }
    T getBase2() const { return base2; }
    T getHeight() const { return height; }
};

#endif