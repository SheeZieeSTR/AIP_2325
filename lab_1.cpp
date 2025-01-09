#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
class CustomException : public std::exception {
private:
    std::string message;
    double value;
    int errorCode;
public:
    CustomException(const std::string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
    double getValue() const {
        return value;
    }
    int getErrorCode() const {
        return errorCode;
    }
};
double pov(double x, int n) {
    return std::pow(x, n);
}
double calculate_Z1(double& b) {
    double denominator = std::sqrt(pov(b, 2) - 4) + (b + 2);
    if (denominator == 0) {
        throw CustomException("Ошибка: Деление на ноль", b, 1);
    }
    double numerator = std::sqrt(2 * b + 2 * std::sqrt(pov(b, 2) - 4));
    return numerator / denominator;
}
double calculate_Z2(double& b) {
    double denominator = std::sqrt(b + 2);
    if (denominator == 0) {
        throw CustomException("Ошибка: Деление на ноль", b, 2);
    }
    return 1 / denominator;
}
int main() {
    double b_value = 2; // Задайте значение b
    try {
        double Z1_result = calculate_Z1(b_value);
        double Z2_result = calculate_Z2(b_value);

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Z1: " << Z1_result << ", Z2: " << Z2_result << std::endl;
        std::cout << "Разница: " << std::abs(Z1_result - Z2_result) << std::endl;

    } catch (const CustomException& e) {
        std::cerr << "CustomException: " << e.what() 
                  << ", Value: " << e.getValue() 
                  << ", Error Code: " << e.getErrorCode() 
                  << std::endl;
    }

    return 0;
}
