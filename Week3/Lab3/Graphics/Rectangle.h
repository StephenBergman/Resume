#pragma once
#include "Shape.h"
#include "Line.h"
#include <vector>

class Rectangle : public Shape {
	int width;
	int height;
	std::vector<Line> lines;

public:
	Rectangle(int w, int h, const Point2D& startPt, ConsoleColor color)
		: Shape(startPt, color), width(w), height(h) {

		Point2D topRight(startPt.x + width, startPt.y);
		Point2D bottomLeft(startPt.x, +startPt.y + height);
		Point2D bottomRight(startPt.x + width, startPt.y + height);

		lines.emplace_back(startPt, topRight, color);
		lines.emplace_back(topRight, bottomRight, color);
		lines.emplace_back(bottomLeft, bottomRight, color);
		lines.emplace_back(startPt, bottomLeft, color);
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }

 void Draw() const override {
		for (const auto& line : lines) {
			line.Draw();
			Console::Reset();
		}
	}
};