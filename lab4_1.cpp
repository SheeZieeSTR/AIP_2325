#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

void processString(const string& input) {
    string lowerCase, upperCase, hexNumbers, replacedSpaces;

    for (char ch : input) {
        if (isalpha(ch)) {
            // Разделение на нижний и верхний регистры
            lowerCase += tolower(ch);
            upperCase += toupper(ch);
        }
        else if (isdigit(ch)) {
            // Преобразование чисел в HEX
            stringstream ss;
            ss << hex << uppercase << static_cast<int>(ch - '0');
            hexNumbers += ss.str() + " ";
        }

        // Замена пробелов на #
        replacedSpaces += (ch == ' ') ? '#' : ch;
    }

    // Вывод результатов
    cout << "1) Все буквы в нижнем регистре: " << lowerCase << endl;
    cout << "2) Все буквы в верхнем регистре: " << upperCase << endl;
    cout << "3) Все числа в HEX формате: " << hexNumbers << endl;
    cout << "4) Строка с заменой пробелов на #: " << replacedSpaces << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    string input;

    cout << "Введите строку символов: ";
    getline(cin, input);  // Чтение строки с пробелами

    processString(input);

    return 0;
}
