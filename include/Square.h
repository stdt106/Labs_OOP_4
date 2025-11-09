#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
#include <cmath>
#include <iostream>

template<Scalar T>
class Square : public Figure<T> {
private:
    T side;

public:
    Square() : side(0) {}
    Square(T side) : side(side) {
        T radius = side / std::sqrt(2.0);
        this->vertices.clear();
        this->vertices.push_back(std::make_unique<Point<T>>(-radius, -radius));
        this->vertices.push_back(std::make_unique<Point<T>>(radius, -radius));
        this->vertices.push_back(std::make_unique<Point<T>>(radius, radius));
        this->vertices.push_back(std::make_unique<Point<T>>(-radius, radius));
    }

    Point<T> calculateGeometricCenter() const override {
        return Point<T>(0, 0);
    }

    explicit operator double() const override {
        return static_cast<double>(side * side);
    }

    bool operator==(const Figure<T>& other) const override {
        const Square* otherSquare = dynamic_cast<const Square*>(&other);
        if (!otherSquare) return false;
        return side == otherSquare->side;
    }

    void print(std::ostream& os) const override {
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
    }

    void read(std::istream& is) override {
        T newSide;
        is >> newSide;
        *this = Square(newSide);
    }

    T getSide() const { return side; }
};

#endif