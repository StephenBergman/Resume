#ifndef CAR_H
#define CAR_H

enum EnumColorDefinition { Red, Blue };

struct Car {
    char Make[32];
    char Model[32];
    int Year;
    int Mileage;
    EnumColorDefinition Color;
};

void repaintCar(Car* ptrCar, EnumColorDefinition newColor);
void printCar(Car c);
void printCarPointer(Car* ptrCar);
void addMileage(Car* ptrCar, int milesToAdd);
void inputCarInfo(Car& car);

#endif 
