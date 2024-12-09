#include <iostream>
#include <cmath>
#include <exception>
#include <string>

// Класс CustomException
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

    double get_value() const {
        return value;
    }

    int get_error_code() const {
        return error_code;
    }
};

// Функция для вычисления Z1
void compute_z1(double a, double& z1) {
    try {
        if ((2 * a + a * a) == 0 || (2 * a - a * a) == 0) {
            throw CustomException("Ошибка деления на ноль", a, 100);
        }
        z1 = (5 - 2 * a * a) / ((1 + a + a * a) / (2 * a + a * a) + 2 - (1 - a + a * a) / (2 * a - a * a));
    } catch (const CustomException& e) {
        std::cerr << "Ошибка в compute_z1: " << e.what() 
                  << " Значение: " << e.get_value() 
                  << " Код ошибки: " << e.get_error_code() << std::endl;
        z1 = NAN;
    }
}

// Функция для вычисления Z2
void compute_z2(double x, double& z2) {
    try {
        z2 = (4 - x * x) / 2;
    } catch (const CustomException& e) {
        std::cerr << "Ошибка в compute_z2: " << e.what() 
                  << " Значение: " << e.get_value() 
                  << " Код ошибки: " << e.get_error_code() << std::endl;
        z2 = NAN;
    }
}

int main() {
    double a = 1.0;
    double x = 1.0;
    double z1, z2;

    compute_z1(a, z1);
    compute_z2(x, z2);

    if (!std::isnan(z1) && !std::isnan(z2)) {
        if (std::fabs(z1 - z2) < 0.01) {
            std::cout << "Z1 и Z2 примерно равны" << std::endl;
        } else {
            std::cout << "Z1 и Z2 не равны" << std::endl;
        }
    }

    return 0;
}