#include "../include/Rhombus.h"
#include <cmath>
#include <iostream>

std::pair<double, double> Rhombus::calculateGeometricCenter() const {
    double x_center = 0, y_center = 0;
    for (const auto &vertex : vertices) {
        x_center += vertex.first;
        y_center += vertex.second;
    }
    x_center /= 4;
    y_center /= 4;
    return {x_center, y_center};
}

Rhombus::operator double() const {
    double area = 0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::fabs(area) / 2;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) return false;
    
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i] != otherRhombus->vertices[i]) return false;
    }
    return true;
}

void Rhombus::print(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Rhombus::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 4; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}

Rhombus::Rhombus(const std::vector<std::pair<double, double>>& points) {
    if (points.size() == 4) {
        vertices = points;
    }
}