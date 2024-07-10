#include <iostream>
#include <bitset>
using namespace std;

unsigned int bitField = 19;

void DisplayBits(unsigned int n) {
	for (int i = 31; i >= 0; i--) {
		cout << ((n >> i) & 1);
		if (i % 4 == 0) cout << " ";
	}
	cout << endl;
}

void TurnOn(int bit) {
	bitField |= (1 << bit);
}

void TurnOff(int bit) {
	bitField &= ~(1 << bit);
}

void Toggle(int bit) {
	bitField ^= (1 << bit);
}

void Negate() {
	bitField = ~bitField;
}

void LeftShift() {
	bitField <<= 1;
}

void RightShift() {
	bitField >>= 1;
}

int main() {
	while (true) {
		cout << "bitField: " << bitField << endl;
		cout << "Bits: ";
		DisplayBits(bitField);

		cout << "Choose Operation: " << endl;
		cout << "1: Turn On " << endl;
		cout << "2: Turn Off" << endl;
		cout << "3: Toggle " << endl;
		cout << "4: Negate " << endl;
		cout << "5: Left Shift " << endl;
		cout << "6: Right Shift " << endl;
		cout << "7: Exit " << endl;

		int choice;
		cin >> choice;

		if (choice == 7) break;

		int bit;
		if (choice >= 1 && choice <= 3) {
			cout << "Enter bit index (0-31): ";
			cin >> bit;
            if (bit < 0 || bit > 31) {
                cout << "Invalid bit index. Please enter a value between 0 and 31." << endl;
                continue;
            }

            switch (choice) {
            case 1:
                TurnOn(bit);
                break;
            case 2:
                TurnOff(bit);
                break;
            case 3:
                Toggle(bit);
                break;
            }
        }
        else {
            switch (choice) {
            case 4:
                Negate();
                break;
            case 5:
                LeftShift();
                break;
            case 6:
                RightShift();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
    return 0;
}