#include <iostream>
#include <cmath>
#include <exception>
#include <string>

using namespace std;

class CustomException : public exception {
    string message;
    double value;
    int code;
public:
    CustomException(const string& msg, double val, int c) : message(msg), value(val), code(c) {}
    const char* what() const noexcept override { return message.c_str(); }
    double getValue() const { return value; }
    int getCode() const { return code; }
};

double calculateZ1(double m) {
    if (m * m - 4 < 0) throw CustomException("Отрицательный корень", m, 1);
    double denom = m + sqrt(m * m - 4) + 2;
    if (denom == 0) throw CustomException("Деление на ноль", m, 2);
    return sqrt(2 * m + 2 * sqrt(m * m - 4)) / denom;
}

double calculateZ2(double m) {
    if (m + 2 < 0) throw CustomException("Отрицательный корень", m, 1);
    double denom = sqrt(m + 2);
    if (denom == 0) throw CustomException("Деление на ноль", m, 2);
    return 1 / denom;
}

int main() {
    try {
        double m;
        cout << "Введите значение: ";
        cin >> m;
        double Z1 = calculateZ1(m), Z2 = calculateZ2(m);
        cout << "Z1 = " << Z1 << "\nZ2 = " << Z2 << "\n";
        cout << ((abs(Z1 - Z2) < 1e-6) ? "Равны\n" : "Не равны\n");
    } catch (const CustomException& e) {
        cerr << "Ошибка: " << e.what() << ", значение: " << e.getValue() << ", код: " << e.getCode() << '\n';
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
    return 0;
}
