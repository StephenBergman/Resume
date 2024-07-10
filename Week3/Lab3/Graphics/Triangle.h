#pragma once
#include "Shape.h"
#include "Line.h"
#include <vector>

class Triangle : public Shape {
private:
	Point2D p2;
	Point2D p3;
	std::vector<Line> lines;

public:
	Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, ConsoleColor color)
		: Shape(p1, color), p2(p2), p3(p3) {

		lines.emplace_back(p1, p2, color);
		lines.emplace_back(p2, p3, color);
		lines.emplace_back(p3, p1, color);
	}

	Point2D getP2() const { return p2; }
	Point2D getP3() const { return p3; }

	void setP2(const Point2D& point) { p2 = point; }
	void setP3(const Point2D& point) { p3 = point; }

	void Draw() const override {
		for (const auto& line : lines) {
			line.Draw();
			Console::Reset();
		}
	}
};