#include <iostream> 
#include <stdexcept>  
#include <cmath>     
 
// Класс для обработки исключений 
class ZeroError : public std::runtime_error { 
public: 
    ZeroError(const std::string& message) : std::runtime_error(message) {} 
}; 
 
double computeZ1(double& x) { 
    if (x == 0) { 
        throw ZeroError("Ошибка: деление на ноль в z1."); 
    } 
    double numerator = 2 + (1 + x + (pow(x, 2) / (2 * x + pow(x, 2))) - (1 - x + (pow(x, 2) / (2 * x - pow(x, 2))))); 
    return pow(numerator, 2) * (5 - 2 * pow(x, 2)); 
} 
 
double computeZ2(double& x) { 
    if (x == 0) { 
        throw ZeroError("Ошибка: деление на ноль в z2."); 
    } 
    return 20 * x - 3; 
} 
 
int main() { 
    double x; 
 
    std::cout << "Введите значение x: "; 
    std::cin >> x; 
 
    try { 
        double z1 = computeZ1(x); 
        double z2 = computeZ2(x); 
        std::cout << "Результат z1: " << z1 << std::endl; 
        std::cout << "Результат z2: " << z2 << std::endl; 
    } catch (const ZeroError& e) { 
        std::cerr << e.what() << std::endl; 
    } 
 
    return 0; 
}