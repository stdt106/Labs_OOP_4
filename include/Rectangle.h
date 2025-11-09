#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include <cmath>
#include <iostream>

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    T width, height;

public:
    Rectangle() : width(0), height(0) {}
    Rectangle(T width, T height) : width(width), height(height) {
        this->vertices.clear();
        this->vertices.push_back(std::make_unique<Point<T>>(-width/2, -height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(width/2, -height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(width/2, height/2));
        this->vertices.push_back(std::make_unique<Point<T>>(-width/2, height/2));
    }

    Point<T> calculateGeometricCenter() const override {
        return Point<T>(0, 0);
    }

    explicit operator double() const override {
        return static_cast<double>(width * height);
    }

    bool operator==(const Figure<T>& other) const override {
        const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&other);
        if (!otherRect) return false;
        return width == otherRect->width && height == otherRect->height;
    }

    void print(std::ostream& os) const override {
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
    }

    void read(std::istream& is) override {
        T w, h;
        is >> w >> h;
        *this = Rectangle(w, h);
    }

    T getWidth() const { return width; }
    T getHeight() const { return height; }
};

#endif