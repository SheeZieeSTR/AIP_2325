#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;
    double value;
    int error_code;

public:
    CustomException(const std::string& msg, double val, int code)
        : message(msg), value(val), error_code(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const { return value; }
    int getErrorCode() const { return error_code; }
};

double calculate_z1(double x) {
    try {
        if (x * x - 9 < 0) {
            throw CustomException("Square root of a negative number encountered in Z1", x, 101);
        }

        double numerator = x * x + 2 * x - 3 + (x + 1) * std::sqrt(x * x - 9);
        double denominator = x * x - 2 * x - 3 + (x - 1) * std::sqrt(x * x - 9);

        if (denominator == 0) {
            throw CustomException("Division by zero encountered in Z1", x, 102);
        }

        return numerator / denominator;
    } catch (const CustomException& e) {
        std::cerr << e.what() << " (Value: " << e.getValue() << ", Error Code: " << e.getErrorCode() << ")\n";
        return NAN;
    }
}

double calculate_z2(double x) {
    try {
        if (x - 3 == 0) {
            throw CustomException("Division by zero encountered in Z2", x, 201);
        }

        if (x + 3 < 0) {
            throw CustomException("Square root of a negative number encountered in Z2", x, 202);
        }

        return std::sqrt((x + 3) / (x - 3));
    } catch (const CustomException& e) {
        std::cerr << e.what() << " (Value: " << e.getValue() << ", Error Code: " << e.getErrorCode() << ")\n";
        return NAN;
    }
}

int main() {
    double x_values[] = {5, 3, -5, 9, 0};

    for (double x : x_values) {
        std::cout << "Calculating for x = " << x << "\n";
        double z1 = calculate_z1(x);
        double z2 = calculate_z2(x);

        if (!std::isnan(z1) && !std::isnan(z2)) {
            std::cout << "Z1 = " << z1 << ", Z2 = " << z2 << "\n";
            if (std::fabs(z1 - z2) < 1e-6) {
                std::cout << "Z1 and Z2 are approximately equal.\n";
            } else {
                std::cout << "Z1 and Z2 are not equal.\n";
            }
        }
        std::cout << "-\n";
    }

    return 0;
}
