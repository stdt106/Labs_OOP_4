#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"

bool doubleEquals(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

TEST(RectangleTest, BasicOperations) {
    std::vector<std::pair<double, double>> points = {{0,0}, {4,0}, {4,3}, {0,3}};
    Rectangle rectangle(points);
    
    auto center = rectangle.calculateGeometricCenter();
    EXPECT_TRUE(doubleEquals(center.first, 2.0));
    EXPECT_TRUE(doubleEquals(center.second, 1.5));
    EXPECT_TRUE(doubleEquals(static_cast<double>(rectangle), 12.0));
}

TEST(RectangleTest, Equality) {
    std::vector<std::pair<double, double>> points1 = {{0,0}, {4,0}, {4,3}, {0,3}};
    std::vector<std::pair<double, double>> points2 = {{0,0}, {4,0}, {4,3}, {0,3}};
    std::vector<std::pair<double, double>> points3 = {{0,0}, {5,0}, {5,3}, {0,3}};
    
    Rectangle rect1(points1);
    Rectangle rect2(points2);
    Rectangle rect3(points3);
    
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(TrapezoidTest, AreaCalculation) {
    std::vector<std::pair<double, double>> points = {{0,0}, {4,0}, {3,2}, {1,2}};
    Trapezoid trapezoid(points);
    
    EXPECT_TRUE(doubleEquals(static_cast<double>(trapezoid), 6.0));
}

TEST(TrapezoidTest, GeometricCenter) {
    std::vector<std::pair<double, double>> points = {{0,0}, {4,0}, {3,2}, {1,2}};
    Trapezoid trapezoid(points);
    
    auto center = trapezoid.calculateGeometricCenter();
    EXPECT_TRUE(doubleEquals(center.first, 2.0));
    EXPECT_TRUE(doubleEquals(center.second, 1.0));
}

TEST(RhombusTest, AreaCalculation) {
    std::vector<std::pair<double, double>> points = {{0,0}, {2,2}, {4,0}, {2,-2}};
    Rhombus rhombus(points);
    
    EXPECT_TRUE(doubleEquals(static_cast<double>(rhombus), 8.0));
}

TEST(RhombusTest, GeometricCenter) {
    std::vector<std::pair<double, double>> points = {{1,0}, {2,2}, {3,0}, {2,-2}};
    Rhombus rhombus(points);
    
    auto center = rhombus.calculateGeometricCenter();
    EXPECT_TRUE(doubleEquals(center.first, 2.0));
    EXPECT_TRUE(doubleEquals(center.second, 0.0));
}

TEST(FigureTest, DifferentTypeComparison) {
    std::vector<std::pair<double, double>> rectPoints = {{0,0}, {4,0}, {4,3}, {0,3}};
    std::vector<std::pair<double, double>> trapPoints = {{0,0}, {4,0}, {3,2}, {1,2}};
    
    Rectangle rectangle(rectPoints);
    Trapezoid trapezoid(trapPoints);
    
    EXPECT_FALSE(rectangle == trapezoid);
    EXPECT_FALSE(trapezoid == rectangle);
}

TEST(FigureManagerTest, TotalArea) {
    std::vector<Figure*> figures;
    
    Rectangle* rect = new Rectangle({{0,0}, {4,0}, {4,3}, {0,3}});
    Trapezoid* trap = new Trapezoid({{0,0}, {4,0}, {3,2}, {1,2}});
    Rhombus* rhombus = new Rhombus({{0,0}, {2,2}, {4,0}, {2,-2}});
    
    figures.push_back(rect);
    figures.push_back(trap);
    figures.push_back(rhombus);
    
    double totalArea = 0.0;
    for (const auto& figure : figures) {
        totalArea += static_cast<double>(*figure);
    }
    
    EXPECT_TRUE(doubleEquals(totalArea, 26.0));
    
    for (auto figure : figures) {
        delete figure;
    }
}

TEST(FigureManagerTest, RemoveFromArray) {
    std::vector<Figure*> figures;
    
    Rectangle* rect = new Rectangle({{0,0}, {4,0}, {4,3}, {0,3}});      
    Trapezoid* trap = new Trapezoid({{0,0}, {4,0}, {3,2}, {1,2}});     
    
    figures.push_back(rect);
    figures.push_back(trap);
    
    delete figures[0];
    figures.erase(figures.begin());
    
    EXPECT_EQ(figures.size(), 1);
    
    for (auto figure : figures) {
        delete figure;
    }
}

TEST(RectangleTest, InputOutput) {
    Rectangle rect1({{0,0}, {4,0}, {4,3}, {0,3}});
    
    std::ostringstream oss;
    oss << rect1;
    std::string output = oss.str();
    
    EXPECT_FALSE(output.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}