#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include "../include/Figure.h"
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Array.h"

template<Scalar T>
class FigureManager {
private:
    Array<std::shared_ptr<Figure<T>>> figures;

public:
    void addFigure(std::shared_ptr<Figure<T>> figure) {
        figures.push_back(std::move(figure));
    }

    void printAllFigures() const {
        std::cout << "\n=== ALL FIGURES ===" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i << " (" << getFigureType(figures[i]) << "): ";
            std::cout << *figures[i] << std::endl;
            
            auto center = figures[i]->calculateGeometricCenter();
            double area = static_cast<double>(*figures[i]);
            
            std::cout << "  Center: " << center << std::endl;
            std::cout << "  Area: " << area << std::endl << std::endl;
        }
    }

    double calculateTotalArea() const {
        double total = 0;
        for (size_t i = 0; i < figures.size(); ++i) {
            total += static_cast<double>(*figures[i]);
        }
        return total;
    }

    void removeFigure(size_t index) {
        if (index < figures.size()) {
            figures.remove(index);
            std::cout << "Figure at index " << index << " removed." << std::endl;
        } else {
            std::cout << "Invalid index!" << std::endl;
        }
    }

    size_t getFigureCount() const {
        return figures.size();
    }

private:
    std::string getFigureType(const std::shared_ptr<Figure<T>>& figure) const {
        if (dynamic_cast<Square<T>*>(figure.get())) return "Square";
        if (dynamic_cast<Rectangle<T>*>(figure.get())) return "Rectangle";
        if (dynamic_cast<Trapezoid<T>*>(figure.get())) return "Trapezoid";
        return "Unknown";
    }
};

void demonstrateArrayTemplate() {
    std::cout << "=== DEMONSTRATING ARRAY TEMPLATE ===" << std::endl;
    
    Array<Figure<int>*> figureArray;
    Square<int> sq(5);
    Rectangle<int> rect(4, 6);
    
    figureArray.push_back(&sq);
    figureArray.push_back(&rect);
    
    std::cout << "Figure array size: " << figureArray.size() << std::endl;
    
    Array<Square<int>> squareArray;
    squareArray.push_back(Square<int>(3));
    squareArray.push_back(Square<int>(7));
    
    std::cout << "Square array size: " << squareArray.size() << std::endl;
    std::cout << "First square area: " << static_cast<double>(squareArray[0]) << std::endl;
}

int main() {
    FigureManager<double> manager;
    
    std::cout << "=== FIGURE MANAGER WITH TEMPLATES ===" << std::endl;

    auto square = std::make_shared<Square<double>>(5.0);
    auto rectangle = std::make_shared<Rectangle<double>>(4.0, 6.0);
    auto trapezoid = std::make_shared<Trapezoid<double>>(3.0, 6.0, 4.0);

    manager.addFigure(square);
    manager.addFigure(rectangle);
    manager.addFigure(trapezoid);

    manager.printAllFigures();

    std::cout << "Total area: " << manager.calculateTotalArea() << std::endl;

    std::cout << "\nRemoving figure at index 1..." << std::endl;
    manager.removeFigure(1);

    manager.printAllFigures();
    std::cout << "Total area after removal: " << manager.calculateTotalArea() << std::endl;

    demonstrateArrayTemplate();

    std::cout << "\n=== TESTING INPUT ===" << std::endl;
    std::cout << "Enter square side: ";
    double side;
    std::cin >> side;
    auto userSquare = std::make_shared<Square<double>>(side);
    std::cout << "Created square: " << *userSquare << std::endl;
    std::cout << "Area: " << static_cast<double>(*userSquare) << std::endl;

    return 0;
}