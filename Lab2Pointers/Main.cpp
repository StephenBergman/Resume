#include <iostream>
#include <cstdlib>
#include <ctime>
#include "car.h"
using namespace std;

void program1() {
    const int SIZE = 15;
    int arr[SIZE];

    srand((unsigned int)time(0));

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 100;
        cout << "\nValue: " << arr[i] << "\nAddress: " << &arr[i] << endl;
    }
}

void printIntAndPointer(int val, int* ptr) {
    cout << "\nValue: " << val << "\nPointer Address: " << ptr << endl;
}

void program2() {
    const int SIZE = 15;
    int arr[SIZE];

    srand((unsigned int)time(0));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < SIZE; ++i) {
        printIntAndPointer(arr[i], &arr[i]);
    }
}

void program3() {
    const int SIZE = 3;
    Car carArray[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        cout << "\nEnter car information " << (i + 1) << ":" << endl;
        inputCarInfo(carArray[i]);
    }

    cout << "\nPrinting cars..." << endl;
    for (int i = 0; i < SIZE; ++i) {
        printCar(carArray[i]);
    }

    cout << "\nPrinting car pointers..." << endl;
    for (int i = 0; i < SIZE; ++i) {
        printCarPointer(&carArray[i]);
    }

    int choice;
    do {
        cout << "\nSelect option: " << endl;
        cout << "1. Repaint a car" << endl;
        cout << "2. Add mileage to a car" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            int carIndex;
            EnumColorDefinition newColor;

            cout << "\nEnter car index (0-" << (SIZE - 1) << "): ";
            cin >> carIndex;
            cout << "\nEnter new color (0 for Red, 1 for Blue): ";
            int colorInput;
            cin >> colorInput;
            newColor = static_cast<EnumColorDefinition>(colorInput);

            if (carIndex >= 0 && carIndex < SIZE) {
                repaintCar(&carArray[carIndex], newColor);
                cout << "\nCar " << (carIndex + 1) << " repainted." << endl;
                cout << "\n"; printCarPointer(&carArray[carIndex]);
            }
            else {
                cout << "\nInvalid car index." << endl;
            }
            break;
        }
        case 2: {
            int carIndex, mileageToAdd;
            cout << "\nEnter car index (0-" << (SIZE - 1) << "): ";
            cin >> carIndex;
            cout << "\nEnter mileage to add: ";
            cin >> mileageToAdd;

            if (carIndex >= 0 && carIndex < SIZE) {
                addMileage(&carArray[carIndex], mileageToAdd);
                cout << "\nMileage added to Car " << (carIndex + 1) << "." << endl;
                printCarPointer(&carArray[carIndex]);
            }
            else {
                cout << "\nInvalid car index." << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        cout << "\nSelect program to run (1-3) or 0 to exit: ";
        cin >> choice;
        switch (choice) {
        case 1: program1(); break;
        case 2: program2(); break;
        case 3: program3(); break;
        case 0: break;
        default: cout << "\nInvalid choice, please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
