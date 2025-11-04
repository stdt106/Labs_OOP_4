#ifndef FIGURE_H 
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>

class Figure {
public:
    virtual ~Figure() = default;

    virtual std::pair<double, double> calculateGeometricCenter() const = 0;
    virtual explicit operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
};

#endif