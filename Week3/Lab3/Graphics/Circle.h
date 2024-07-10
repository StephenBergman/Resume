#pragma once
#include "Console.h"
#include "Shape.h"


class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r, const Point2D& startPt, ConsoleColor col)
        : Shape(startPt, col), radius(r) {}

    int getRadius() const { return radius; }
    void setRadius(int r) { radius = r; }

    
    void Plot(int xc, int yc, int x, int y) const {
        Console::SetCursorPosition(xc + x, yc + y);
        Console::Write(" ");
        Console::SetCursorPosition(xc - x, yc + y);
        Console::Write(" ");
        Console::SetCursorPosition(xc + x, yc - y);
        Console::Write(" ");
        Console::SetCursorPosition(xc - x, yc - y);
        Console::Write(" ");
        Console::SetCursorPosition(xc + y, yc + x);
        Console::Write(" ");
        Console::SetCursorPosition(xc - y, yc + x);
        Console::Write(" ");
        Console::SetCursorPosition(xc + y, yc - x);
        Console::Write(" ");
        Console::SetCursorPosition(xc - y, yc - x);
        Console::Write(" ");
    }

    
    void DrawCircle(int xc, int yc, int r) const {
        int x = 0, y = r;
        int d = 3 - 2 * r;
        Plot(xc, yc, x, y);

        while (y >= x) {
            x = x + 1;
            if (d > 0) {
                y = y - 1;
                d = d + 4 * (x - y) + 10;
            }
            else {
                d = d + 4 * x + 6;
            }
            Plot(xc, yc, x, y);
        }
    }

     void Draw() const override {
        int xc = getStartPt().x;
        int yc = getStartPt().y;

        Console::SetBackgroundColor(getColor());
        DrawCircle(xc, yc, radius);
        Console::Reset();
    }
};

