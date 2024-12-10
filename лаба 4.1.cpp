#include <iostream> 
#include <string> 
#include <cctype> 
 
class StringProcessor { 
private: 
    std::string input; 
 
public: 
    void inputString() { 
        std::cout << "Введите строку: "; 
        std::getline(std::cin, input); 
    } 
 
    friend std::ostream& operator<<(std::ostream& os, const StringProcessor& sp); 
}; 
 
std::ostream& operator<<(std::ostream& os, const StringProcessor& sp) { 
    for (char ch : sp.input) { 
        if (!std::isupper(ch) && !std::isdigit(ch)) { 
            os << ch; 
        } 
    } 
    return os; 
} 
 
int main() { 
    StringProcessor sp; 
    sp.inputString(); 
    std::cout << "Результат: " << sp << std::endl; 
    return 0; 
}