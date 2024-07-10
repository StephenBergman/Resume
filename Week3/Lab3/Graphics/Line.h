#pragma once
#include "Shape.h"
#include "Console.h"
#include "Point2D.h"
class Line : public Shape {
private: 
	Point2D endPt;

	void Plot(int x, int y) const {
		Console::SetCursorPosition(x, y);
		Console::Write(" ");
	}

	void PlotLine(int x0, int y0, int x1, int y1) const {
		int dx = abs(x1 - x0);
		int sx = x0 < x1 ? 1 : -1;
		int dy = -abs(y1 - y0);
		int sy = y0 < y1 ? 1 : -1;
		int error = dx + dy;

		while (true) {
			Plot(x0, y0);
			if (x0 == x1 && y0 == y1) break;
			int e2 = 2 * error;
			if (e2 >= dy) {
				if (x0 == x1) break;
				error += dy;
				x0 += sx;
			}
			if (e2 <= dx) {
				if (y0 == y1) break;
				error += dx;
				y0 += sy;
			}
		}
	}
public:
	Line(const Point2D& start, const Point2D end, ConsoleColor col)
		: Shape(start, col), endPt(end) {}

	Point2D getEndPt() const { return endPt; }
	void setEndPt(const Point2D& pt) { endPt = pt; }

	 void Draw() const override {
		Console::SetBackgroundColor(getColor());
		PlotLine(getStartPt().x, getStartPt().y, endPt.x, endPt.y);
		Console::Reset();
	}
};