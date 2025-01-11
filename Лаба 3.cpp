#include <iostream>
#include <list>
#include <exception>
#include <string>

using namespace std;

template <typename T>
class SmartPointer {
    T* ptr;
public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    ~SmartPointer() { delete ptr; }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    SmartPointer(SmartPointer&& sp) noexcept : ptr(sp.ptr) { sp.ptr = nullptr; }
    SmartPointer& operator=(SmartPointer&& sp) noexcept {
        if (this != &sp) {
            delete ptr;
            ptr = sp.ptr;
            sp.ptr = nullptr;
        }
        return *this;
    }
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;
};

template <typename T>
class Stack {
    list<T> elements;
public:
    void push(const T& value) { elements.push_back(value); }
    void pop() { 
        if (elements.empty()) throw out_of_range("Стек пуст");
        elements.pop_back(); 
    }
    T& top() { 
        if (elements.empty()) throw out_of_range("Стек пуст");
        return elements.back();
    }
    bool empty() const { return elements.empty(); }
};

template <typename T>
void testStack() {
    Stack<T> stack;
    T value;
    int choice;
    do {
        cout << "\nМеню:\n1. Добавить элемент\n2. Удалить элемент\n3. Показать вершину\n4. Проверить, пуст ли стек\n0. Выход\nВведите ваш выбор: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Введите значение: ";
                cin >> value;
                stack.push(value);
                cout << "Элемент добавлен.\n";
                break;
            case 2:
                try {
                    stack.pop();
                    cout << "Элемент удален.\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 3:
                try {
                    cout << "Вершина стека: " << stack.top() << endl;
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 4:
                cout << (stack.empty() ? "Стек пуст." : "Стек не пуст.") << endl;
                break;
            case 0:
                cout << "Выход из тестирования стека.\n";
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                break;
        }
    } while (choice != 0);
}

void displayMenu() {
    cout << "\nМеню тестирования стеков:\n";
    cout << "1. Тест стека с типом int\n";
    cout << "2. Тест стека с типом double\n";
    cout << "3. Тест стека с типом string\n";
    cout << "0. Выход\n";
    cout << "Выберите опцию: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                testStack<int>();
                break;
            case 2:
                testStack<double>();
                break;
            case 3:
                testStack<string>();
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
