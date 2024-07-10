#include "ShapeFactory.h"




namespace {
    bool initialized = false;
}

Point2D ShapeFactory::RandomPoint() {
    int width = Console::GetWindowWidth();
    int height = Console::GetWindowHeight();
    int x = rand() % width;
    int y = rand() % height;
    return Point2D(x, y);
}

ConsoleColor ShapeFactory::RandomColor() {
    int numColors = 8; 
    return static_cast<ConsoleColor>(rand() % numColors);
}

std::unique_ptr<Shape> ShapeFactory::RandomShape() {
    int choice = rand() % 4; 
    switch (choice) {
    case 0: return RandomLine();
    case 1: return RandomRectangle();
    case 2: return RandomTriangle();
    case 3: return RandomCircle();
    default: return RandomLine(); 
    }
}

std::unique_ptr<Line> ShapeFactory::RandomLine() {
    Point2D startPoint = RandomPoint();
    Point2D endPoint = RandomPoint();
    ConsoleColor color = RandomColor();
    return std::make_unique<Line>(startPoint, endPoint, color);
}

std::unique_ptr<Rectangle> ShapeFactory::RandomRectangle() {
    int width = rand() % (Console::GetWindowWidth() / 2);
    int height = rand() % (Console::GetWindowHeight() / 2);
    Point2D startPoint = RandomPoint();
    ConsoleColor color = RandomColor();
    return std::make_unique<Rectangle>(width, height, startPoint, color);
}

std::unique_ptr<Triangle> ShapeFactory::RandomTriangle() {
    Point2D p1 = RandomPoint();
    Point2D p2 = RandomPoint();
    Point2D p3 = RandomPoint();
    ConsoleColor color = RandomColor();
    return std::make_unique<Triangle>(p1, p2, p3, color);
}

std::unique_ptr<Circle> ShapeFactory::RandomCircle() {
    int radius = rand() % std::min(Console::GetWindowWidth(), Console::GetWindowHeight()) / 4;
    Point2D center = RandomPoint();
    ConsoleColor color = RandomColor();
    return std::make_unique<Circle>(radius, center, color);
}

