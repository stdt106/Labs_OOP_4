#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Array.h"

bool doubleEquals(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

TEST(SquareTest, AreaCalculation) {
    Square<double> square(5.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 25.0);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<double> rectangle(4.0, 6.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 24.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<double> trapezoid(3.0, 6.0, 4.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 18.0);
}

TEST(SquareTest, GeometricCenter) {
    Square<double> square(5.0);
    auto center = square.calculateGeometricCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 0.0);
    EXPECT_DOUBLE_EQ(center.getY(), 0.0);
}

TEST(ArrayTest, BasicOperations) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Square<double>>(5.0));
    figures.push_back(std::make_shared<Rectangle<double>>(4.0, 6.0));
    
    EXPECT_EQ(figures.size(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(*figures[0]), 25.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*figures[1]), 24.0);
}

TEST(ArrayTest, RemoveElement) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Square<double>>(5.0));
    figures.push_back(std::make_shared<Rectangle<double>>(4.0, 6.0));
    figures.push_back(std::make_shared<Trapezoid<double>>(3.0, 6.0, 4.0));
    
    EXPECT_EQ(figures.size(), 3);
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(*figures[0]), 25.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*figures[1]), 18.0);
}

TEST(FigureTest, DifferentTypes) {
    Square<int> squareInt(5);
    Square<float> squareFloat(5.0f);
    Square<double> squareDouble(5.0);
    
    EXPECT_DOUBLE_EQ(static_cast<double>(squareInt), 25.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(squareFloat), 25.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(squareDouble), 25.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}