#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
    static_assert(std::is_scalar_v<T>, "T must be a scalar type");
    
private:
    T x, y;

public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    T getX() const { return x; }
    T getY() const { return y; }
    
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }
};

#endif