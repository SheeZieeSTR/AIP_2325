#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class CustomException : public exception {
private:
    string errorMessage;
    double errorValue;
    int errorCode;

public:
    CustomException(const string& message, double value, int code)
        : errorMessage(message), errorValue(value), errorCode(code) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

double calculateZ1(double& a) {
    if (a == 0) throw CustomException("Деление на 0 Z1", a, 1);

    double part1 = (a + 2) / sqrt(2 * a);
    double part2 = a / (sqrt(2 * a) + 2);
    double part3 = 2 / (a - sqrt(2 * a));

    if (a - sqrt(2 * a) == 0) throw CustomException("Деление на 0 Z1", a, 1);

    double z1 = (part1 - part2 + part3) * ((sqrt(a) - sqrt(2)) / (a + 2));

    if (isnan(z1)) {
        throw CustomException("NaN Z1", z1, 3);
    }

    return z1;
}

double calculateZ2(double& a) {
    if (a + sqrt(2) == 0) throw CustomException("Деление на 0 Z2", a, 2);

    double z2 = 1 / (sqrt(a) + sqrt(2));

    if (isnan(z2)) {
        throw CustomException("NaN Z2", z2, 3);
    }

    return z2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a;

    cout << "Введите значение a: ";
    cin >> a;

    try {
        double z1 = calculateZ1(a);
        double z2 = calculateZ2(a);

        cout << "Z1 = " << z1 << endl;
        cout << "Z2 = " << z2 << endl;

        if (z1 == z2) {
            cout << "Значения Z1 и Z2 приблизительно равны." << endl;
        }
        else {
            cout << "Значения Z1 и Z2 различаются." << endl;
        }

    }
    catch (const CustomException& ex) {
        cerr << "Произошла ошибка: " << ex.what() << endl;
        cerr << "Значение, вызвавшее ошибку: " << ex.getErrorValue() << endl;
        cerr << "Код ошибки: " << ex.getErrorCode() << endl;
    }

    return 0;
}
