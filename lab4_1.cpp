#include <iostream>
#include <iomanip>
#include <cctype>

int main() {
    char ch;
    std::cout << "Введите символ (или 'выход' для завершения): ";
    while (std::cin >> ch) {
        if (tolower(ch) == 'в') {  // Проверка на слово 'выход'
            char next[4];
            std::cin.read(next, 4);
            if (tolower(next[0]) == 'ы' && tolower(next[1]) == 'х' && tolower(next[2]) == 'о' && tolower(next[3]) == 'д') {
                break;
            } else {
                std::cin.putback(next[3]);
                std::cin.putback(next[2]);
                std::cin.putback(next[1]);
                std::cin.putback(next[0]);
            }
        }
        char lower_ch = std::tolower(ch);
        std::cout << "Символ: " << lower_ch 
                  << ", Шестнадцатеричный код: " << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(lower_ch) 
                  << ", Восьмеричный код: " << std::oct << static_cast<int>(lower_ch) << std::dec << std::endl;
        std::cout << "Введите символ (или 'выход' для завершения): ";
    }
    return 0;
}
