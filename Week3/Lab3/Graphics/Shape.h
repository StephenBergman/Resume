#pragma once
#include "Point2D.h"
#include "Console.h"

class Shape {
private:
	Point2D startPt;
	ConsoleColor color;

public:
	Shape(const Point2D& pt, ConsoleColor col) : startPt(pt), color(col) {}
	Shape(int x, int y, ConsoleColor col) : startPt(x, y), color(col) {}

	Point2D getStartPt() const { return startPt; }
	ConsoleColor getColor() const { return color; }

	void setStartPt(const Point2D& pt) { startPt = pt; }
	void setColor(ConsoleColor col) { color = col; }

 virtual void Draw() const
	{
		Console::SetBackgroundColor(color);
		Console::SetCursorPosition(startPt.x, startPt.y);
		Console::Write(" ");
		Console::Reset();
	}
};