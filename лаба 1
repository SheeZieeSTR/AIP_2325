#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

// Класс CustomException
class CustomException : public std::exception {
private:
    std::string message;
    double value;
    int error_code;

public:
    CustomException(const std::string &msg, double val, int code)
        : message(msg), value(val), error_code(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getErrorCode() const {
        return error_code;
    }
};

// Функция для вычисления Z1
void calculate_z1(const double &x, double &z1) {
    try {
        double numerator = (x + 1) * std::sqrt(x * x - 9) + x * (x + 2) - 3;
        double denominator = (x - 1) * std::sqrt(x * x - 9) + x * x - 2 * x - 3;

        if (denominator == 0) {
            throw CustomException("Division by zero error", x, 102);
        }

        z1 = numerator / denominator;
    } catch (const CustomException &e) {
        std::cerr << "Error: " << e.what() << " (Value: " << e.getValue() << ", Error Code: " << e.getErrorCode() << ")\n";
        z1 = NAN;
    }
}

// Функция для вычисления Z2
void calculate_z2(const double &x, double &z2) {
    try {
        if ((x - 3) == 0) {
            throw CustomException("Division by zero error", x, 102);
        }

        double value = (x + 3) / (x - 3);
        if (value < 0) {
            throw CustomException("Complex number error", x, 101);
        }

        z2 = std::sqrt(value);
    } catch (const CustomException &e) {
        std::cerr << "Error: " << e.what() << " (Value: " << e.getValue() << ", Error Code: " << e.getErrorCode() << ")\n";
        z2 = NAN;
    }
}

int main() {
    double x = 5;
    double z1, z2;

    calculate_z1(x, z1);
    calculate_z2(x, z2);

    std::cout << "Z1 for x = " << x << " is " << z1 << "\n";
    std::cout << "Z2 for x = " << x << " is " << z2 << "\n";

    return 0;
}
