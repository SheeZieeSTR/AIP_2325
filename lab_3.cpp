#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

class CustomException : public std::runtime_error {
public:
    explicit CustomException(const std::string &message) 
        : std::runtime_error(message) {}
};

#endif // EXCEPTION_H
#ifndef SMART_POINTER_H
#define SMART_POINTER_H

template <typename T>
class SmartPointer {
private:
    T* ptr;

public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    
    ~SmartPointer() {
        delete ptr;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    // Запрет копирования
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    // Перемещение
    SmartPointer(SmartPointer&& sp) noexcept : ptr(sp.ptr) {
        sp.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& sp) noexcept {
        if (this != &sp) {
            delete ptr;
            ptr = sp.ptr;
            sp.ptr = nullptr;
        }
        return *this;
    }
};

#endif // SMART_POINTER_H
#ifndef VECT_H
#define VECT_H

#include <iostream>
#include <list>
#include <initializer_list>



template <typename T>
class Vect {
private:
    std::list<T> data;

public:
    // Конструктор по умолчанию
    Vect() = default;

    // Конструктор от std::initializer_list
    Vect(std::initializer_list<T> init) : data(init) {}

    // Конструктор копирования
    Vect(const Vect& other) : data(other.data) {}

    // Оператор копирующего присваивания
    Vect& operator=(const Vect& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Конструктор перемещения
    Vect(Vect&& other) noexcept : data(std::move(other.data)) {}

    // Оператор перемещения
    Vect& operator=(Vect&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Метод добавления элемента
    void push_back(const T& value) {
        data.push_back(value);
    }

    // Метод удаления элемента
    void pop_back() {
        if (data.empty()) {
            throw CustomException("Attempt to pop from an empty vector");
        }
        data.pop_back();
    }

    // Метод вывода содержимого
    void display() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // Деструктор не обязателен, std::list сам управляет памятью
};

#endif // VECT_H
#include <iostream>


void showMenu() {
    std::cout << "1. Add item\n";
    std::cout << "2. Remove last item\n";
    std::cout << "3. Display items\n";
    std::cout << "4. Exit\n";
}

int main() {
    Vect<int> vect;
    int choice, value;

    while (true) {
        showMenu();
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to add: ";
                std::cin >> value;
                vect.push_back(value);
                break;

            case 2:
                try {
                    vect.pop_back();
                    std::cout << "Last item removed.\n";
                } catch (const CustomException& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;

            case 3:
                vect.display();
                break;

            case 4:
                return 0;

            default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
