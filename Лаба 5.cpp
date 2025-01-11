#include <iostream>
#include <list>
#include <exception>
#include <string>

using namespace std;

class CustomException : public exception {
    string message;
public:
    explicit CustomException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

template <typename T>
class Stack {
    list<T> elements;
public:
    void push(const T& value) { elements.push_back(value); }
    void pop() {
        if (elements.empty()) throw CustomException("Stack<>::pop(): стек пуст");
        elements.pop_back();
    }
    T& top() {
        if (elements.empty()) throw CustomException("Stack<>::top(): стек пуст");
        return elements.back();
    }
    bool empty() const { return elements.empty(); }

    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }
    auto rbegin() { return elements.rbegin(); }
    auto rend() { return elements.rend(); }
};

template <typename T>
void inputValues(Stack<T>& stack) {
    T value;
    char choice;
    do {
        cout << "Введите значение: ";
        cin >> value;
        stack.push(value);
        cout << "Добавить еще одно значение? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

template <typename T>
void iterateStack(Stack<T>& stack, bool reverse = false) {
    if (stack.empty()) {
        cout << "Стек пуст\n";
        return;
    }
    cout << "Итерация по стеку " << (reverse ? "в обратном порядке: " : "в прямом порядке: ");
    if (reverse) {
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) cout << *it << " ";
    } else {
        for (auto it = stack.begin(); it != stack.end(); ++it) cout << *it << " ";
    }
    cout << endl;
}

void displayMenu() {
    cout << "\nМеню:\n"
         << "1. Ввод данных для стека int\n"
         << "2. Ввод данных для стека double\n"
         << "3. Ввод данных для стека string\n"
         << "4. Обход стека int в прямом порядке\n"
         << "5. Обход стека double в прямом порядке\n"
         << "6. Обход стека string в прямом порядке\n"
         << "7. Обход стека int в обратном порядке\n"
         << "8. Обход стека double в обратном порядке\n"
         << "9. Обход стека string в обратном порядке\n"
         << "10. Выход\n"
         << "Выберите опцию: ";
}

int main() {
    int choice;
    Stack<int> intStack;
    Stack<double> doubleStack;
    Stack<string> stringStack;

    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1: inputValues(intStack); break;
            case 2: inputValues(doubleStack); break;
            case 3: inputValues(stringStack); break;
            case 4: iterateStack(intStack); break;
            case 5: iterateStack(doubleStack); break;
            case 6: iterateStack(stringStack); break;
            case 7: iterateStack(intStack, true); break;
            case 8: iterateStack(doubleStack, true); break;
            case 9: iterateStack(stringStack, true); break;
            case 10: cout << "Выход...\n"; break;
            default: cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    } while (choice != 10);

    return 0;
}
