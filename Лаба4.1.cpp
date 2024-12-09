#include <iostream>
#include <iomanip> 

int main() {
    char ch;
    std::cout << "Введите символы (Ctrl+D для завершения ввода):" << std::endl;

    while (std::cin.get(ch)) { 
        std::cout << "Символ: " << ch
                  << " | Шестнадцатеричный: 0x" << std::hex << std::uppercase << (int)(unsigned char)ch
                  << " | Восьмеричный: 0" << std::oct << (int)(unsigned char)ch
                  << std::dec << std::endl; 
    }

    return 0;
}
