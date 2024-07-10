#include "car.h"
#include <iostream>
using namespace std;

void repaintCar(Car* ptrCar, EnumColorDefinition newColor) {
    ptrCar->Color = newColor;
}

void printCar(Car c) {
    cout << c.Year << " ";
    switch (c.Color) {
    case Red: cout << "Red "; break;
    case Blue: cout << "Blue "; break;
    default: cout << "Unknown color "; break;
    }
    cout << c.Make << " " << c.Model << " with " << c.Mileage << " miles" << endl;
}

void printCarPointer(Car* ptrCar) {
    printCar(*ptrCar);
}

void addMileage(Car* ptrCar, int milesToAdd) {
    ptrCar->Mileage += milesToAdd;
}

void inputCarInfo(Car& car) {
    cout << "Make: ";
    cin.ignore();
    cin.getline(car.Make, 32);

    cout << "Model: ";
    cin.getline(car.Model, 32);

    cout << "Year: ";
    cin >> car.Year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Mileage: ";
    cin >> car.Mileage;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int colorInput;
    cout << "Color (0 for Red, 1 for Blue): ";
    cin >> colorInput;
    car.Color = (EnumColorDefinition)colorInput;
}
