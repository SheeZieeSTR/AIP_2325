Main.cpp

#include <iostream>
#include <string>
#include "Vect.h"
#include "CustomException.h"

using namespace std;

void displayMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Показать положительные элементы\n";
    cout << "3. Показать отрицательные элементы\n";
    cout << "4. Изменить тип данных\n";
    cout << "5. Выход\n";
}

template <typename T>
void processVect(Vect<T>& vect) {
    int choice;
    T value;

    while (true) {
        displayMenu();
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите значение для добавления: ";
            cin >> value;
            vect.push_back(value);
            break;
        case 2: {
            cout << "Положительные элементы:\n";
            auto it = vect.positiveIterator();
            try {
                while (it.hasNext())
                    cout << it.next() << " ";
                cout << "\n";
            }
            catch (const CustomException& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            cout << "Отрицательные элементы:\n";
            auto it = vect.negativeIterator();
            try {
                while (it.hasNext())
                    cout << it.next() << " ";
                cout << "\n";
            }
            catch (const CustomException& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 4:
            return;
        case 5:
            exit(0);
        default:
            cout << "Неверный выбор.\n";
        }
    }
}

int main() {

    setlocale(LC_ALL, "RU");
    int dataType;

    while (true) {
        cout << "\nВыберите тип данных:\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. string\n";
        cout << "4. Выход\n";
        cout << "Ваш выбор: ";
        cin >> dataType;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число.\n";
            continue;
        }

        switch (dataType) {
        case 1: {
            Vect<int> vect;
            processVect(vect);
            break;
        }
        case 2: {
            Vect<double> vect;
            processVect(vect);
            break;
        }
        case 3: {
            Vect<string> vect;
            processVect(vect);
            break;
        }
        case 4:
            return 0;
        default:
            cout << "Выберите между 1 и 4.\n";
        }
    }
}

CustomException.h

#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class CustomException : public runtime_error {
public:
    explicit CustomException(const string& message) : runtime_error(message) {}
};

#endif

Exception.h

#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

using namespace std;

class Exception : public runtime_error {
public:
    explicit Exception(const string& message) : runtime_error(message) {}
};

#endif

SmartPointer.h

#pragma once
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

template <typename T>
class SmartPointer {
private:
    T* ptr;

public:
    explicit SmartPointer(T* ptr = nullptr) : ptr(ptr) {}

    ~SmartPointer() {
        delete ptr;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    T* get() const {
        return ptr;
    }
};

#endif

Stack.h

#pragma once
#ifndef STACK_H
#define STACK_H

#include "Vect.h"

using namespace std;

template <typename T>
class Stack {
private:
    Vect<T> data;

public:
    Stack() {}

    Stack(initializer_list<T> init) : data(init) {}

    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        data.pop_back();
    }

    T top() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }
};

#endif

Vect.h

#ifndef VECT_H
#define VECT_H

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <functional>
#include <type_traits> // Для std::is_arithmetic
#include "CustomException.h"

template <typename T>
class Vect {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vect() : data(nullptr), size(0), capacity(0) {}

    Vect(std::initializer_list<T> init) : size(init.size()), capacity(init.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const T& value : init)
            data[i++] = value;
    }

    Vect(const Vect& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    Vect& operator=(const Vect& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    Vect(Vect&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Vect& operator=(Vect&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~Vect() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        data[size++] = value;
    }

    void pop_back() {
        if (size == 0)
            throw CustomException("Vect is empty");
        --size;
    }

    const T& back() const {
        if (size == 0)
            throw CustomException("Vect is empty");
        return data[size - 1];
    }

    size_t getSize() const {
        return size;
    }

    const T& operator[](size_t index) const {
        if (index >= size)
            throw CustomException("Index out of bounds");
        return data[index];
    }

    bool empty() const {
        return size == 0;
    }

    // Итератор для фильтрации
    class Iterator {
    private:
        const Vect& vect;
        size_t index;
        std::function<bool(const T&)> filter;

    public:
        Iterator(const Vect& vect, std::function<bool(const T&)> filter, size_t start = 0)
            : vect(vect), index(start), filter(filter) {
            while (index < vect.size && !filter(vect.data[index]))
                ++index;
        }

        bool hasNext() const {
            return index < vect.size;
        }

        const T& next() {
            if (!hasNext())
                throw CustomException("No more elements");
            const T& value = vect.data[index];
            do {
                ++index;
            } while (index < vect.size && !filter(vect.data[index]));
            return value;
        }
    };

    // Итераторы для числовых типов
    template <typename U = T, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    Iterator positiveIterator() const {
        return Iterator(*this, [](const U& value) { return value > 0; });
    }

    template <typename U = T, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    Iterator negativeIterator() const {
        return Iterator(*this, [](const U& value) { return value < 0; });
    }

    // Обработка для строк или других типов
    template <typename U = T, typename std::enable_if<!std::is_arithmetic<U>::value, int>::type = 0>
    Iterator positiveIterator() const {
        return Iterator(*this, [](const U&) { return false; }); // Для нечисловых типов — пустая итерация
    }

    template <typename U = T, typename std::enable_if<!std::is_arithmetic<U>::value, int>::type = 0>
    Iterator negativeIterator() const {
        return Iterator(*this, [](const U&) { return false; });
    }
};

#endif
