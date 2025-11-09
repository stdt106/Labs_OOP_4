// Figure.h
#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <iostream>
#include <vector>
#include <memory>
#include <concepts>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    Figure() = default;
    Figure(const Figure& other) {
        for (const auto& vertex : other.vertices) {
            vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
        }
    }

    Figure(Figure&& other) noexcept = default;

    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices.clear();
            for (const auto& vertex : other.vertices) {
                vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
            }
        }
        return *this;
    }

    Figure& operator=(Figure&& other) noexcept = default;

    virtual Point<T> calculateGeometricCenter() const = 0;
    virtual explicit operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        figure.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& figure) {
        figure.read(is);
        return is;
    }

protected:
    std::vector<std::unique_ptr<Point<T>>> vertices;
};

#endif