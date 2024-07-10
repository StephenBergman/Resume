#include <iostream>
#include "Console.h"
#include "Input.h"
#include <algorithm>
#include <memory>
#include "Tester.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "ShapeFactory.h"

int main()
{
	Tester graphicsTest;
	srand((unsigned int)time(NULL)); //seed the random # generator

	Console::ResizeWindow(150, 30);

	int menuSelection = 0;
	std::vector<std::string> menuOptions{ "1. Draw Shape", "2. Draw Line", "3. Draw Rectangle", "4. Draw Triangle",  "5. Draw Circle", "6. Draw Random Shapes", "7. Exit" };

	do
	{
		Console::Clear();
		menuSelection = Input::GetMenuSelection(menuOptions);
		Console::Clear();


		//----------------------------------------------------------------
		//                                                              //
		//    Call your methods in the appropriate case statement       //
		//                                                              //
		switch (menuSelection)
		{
		case 1:
		{
			int width = Console::GetWindowWidth();
			int height = Console::GetWindowHeight();
			int x = rand() % width;
			int y = rand() % height;
			Point2D randomPoint(x, y);
			ConsoleColor color = ConsoleColor::Blue;
			Shape shape(randomPoint, color);
			shape.Draw();
			break;
		}
		case 2:
		{
			int width = Console::GetWindowWidth();
			int height = Console::GetWindowHeight();
			int x0 = rand() % width;
			int y0 = rand() % height;
			int x1 = rand() % width;
			int y1 = rand() % height;

			Point2D startPoint(x0, y0);
			Point2D endPoint(x1, y1);
			ConsoleColor color = ConsoleColor::Red;

			std::unique_ptr<Shape> shape = std::make_unique<Line>(startPoint, endPoint, color);

			shape->Draw();

			break;
		}
		case 3:
		{
			int width = Console::GetWindowWidth();
			int height = Console::GetWindowHeight();

			int rectWidth = rand() % (width / 2);
			int rectHeight = rand() % (height / 2);

			int x = rand() % (width - rectWidth);
			int y = rand() % (height - rectHeight);

			Point2D startPoint(x, y);

			ConsoleColor color = ConsoleColor::Green;

			std::unique_ptr<Shape> shape = std::make_unique<Rectangle>(rectWidth, rectHeight, startPoint, color);
			shape->Draw();

			break;
		}
		case 4:
		{
			int width = Console::GetWindowWidth();
			int height = Console::GetWindowHeight();

			int x1 = rand() % (width - 1);
			int y1 = rand() % (height -1);
			int x2 = rand() % (width -1);
			int y2 = rand() % (height -1);
			int x3 = rand() % (width -1);
			int y3 = rand() % (height -1);

			Point2D p1(x1, y1);
			Point2D p2(x2, y2);
			Point2D p3(x3, y3);

			ConsoleColor color = ConsoleColor::Cyan;

			std::unique_ptr<Shape> shape = std::make_unique<Triangle>(p1, p2, p3, color);

			shape->Draw();

			break;
		}
		case 5:
		{
			int width = Console::GetWindowWidth();
			int height = Console::GetWindowHeight();

			ConsoleColor color = ConsoleColor::Yellow;

			int maxRadius = std::min(width, height) / 2;
			int radius = rand() % maxRadius;

			int centerX = rand() % (width - 2 * radius) + radius;
			int centerY = rand() % (height - 2 * radius) + radius;

			Point2D center(centerX, centerY);

			std::unique_ptr<Shape> shape = std::make_unique<Circle>(radius, center, color);
			shape->Draw();

			break;
		}
		case 6:
		{
			std::vector<std::unique_ptr<Shape>> shapes;

			for (int i = 0; i < 100; ++i) {
				auto randomShape = ShapeFactory::RandomShape();
				shapes.push_back(std::move(randomShape));
			}

			for (const auto& shape : shapes) {
				shape->Draw();
			}
			break;
		}
		default:
			break;
		}

		Input::PressEnter(true);

	} while (menuSelection != menuOptions.size());
}