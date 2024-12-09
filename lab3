SmartPointer.h


#ifndef SMART_POINTER_H
#define SMART_POINTER_H

template <typename T>
class SmartPointer {
private:
    T* ptr;

public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    ~SmartPointer() { delete ptr; }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    SmartPointer(SmartPointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};

#endif // SMART_POINTER_H









Stack.h


#ifndef STACK_H
#define STACK_H

#include "DynamicArray.h"
#include <stdexcept>

using namespace std;

template <typename T>
class Stack {
private:
    DynamicArray<T> array;

public:
    Stack() = default;
    Stack( initializer_list<T> list) : array(list) {}

    void push(const T& value) { array.pushBack(value); }
    void pop() { array.popBack(); }

    T top() const {
        if (array.isEmpty())
            throw  runtime_error("Stack is empty.");
        return array[array.getSize() - 1];
    }

    bool isEmpty() const { return array.isEmpty(); }
    size_t getSize() const { return array.getSize(); }
};

#endif







ExceptionHandler.h


#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <iostream>
#include <stdexcept>

using namespace std;

class ExceptionHandler {
public:
    static void handle(const  exception& ex) {
        cerr << "Error: " << ex.what() <<  endl;
    }
};

#endif











main.cpp


#include "Stack.h"
#include "ExceptionHandler.h"
#include <iostream>
#include <string>

using namespace std;

void displayMenu() {
     cout << "\n--- Menu ---\n";
     cout << "1. Push element\n";
     cout << "2. Pop element\n";
     cout << "3. Show top element\n";
     cout << "4. Exit\n";
}

template <typename T>
void processStack(Stack<T>& stack) {
    int choice;
    T value;

    while (true) {
        displayMenu();
         cout << "Choice: ";
         cin >> choice;

        try {
            switch (choice) {
            case 1:
                 cout << "Enter value to push: ";
                 cin >> value;
                stack.push(value);
                break;
            case 2:
                stack.pop();
                 cout << "Top element popped.\n";
                break;
            case 3:
                 cout << "Top element: " << stack.top() << "\n";
                break;
            case 4:
                return;
            default:
                 cout << "Invalid choice.\n";
            }
        }
        catch (const  exception& ex) {
            ExceptionHandler::handle(ex);
        }
    }
}

int main() {
    int dataType;

    while (true) {
         cout << "\nSelect data type:\n";
         cout << "1. int\n";
         cout << "2. double\n";
         cout << "3. string\n";
         cout << "4. Exit\n";
         cout << "Your choice: ";
         cin >> dataType;

        if ( cin.fail()) {
             cin.clear();
             cin.ignore( numeric_limits< streamsize>::max(), '\n');
             cout << "Please enter a number.\n";
            continue;
        }

        switch (dataType) {
        case 1: {
            Stack<int> stack;
            processStack(stack);
            break;
        }
        case 2: {
            Stack<double> stack;
            processStack(stack);
            break;
        }
        case 3: {
            Stack< string> stack;
            processStack(stack);
            break;
        }
        case 4:
            return 0;
        default:
             cout << "Choose between 1 and 4.\n";
        }
    }
}










DynamicArray.h


#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <initializer_list>
#include <stdexcept>

using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}
    DynamicArray( initializer_list<T> list) : DynamicArray() {
        for (const auto& elem : list)
            pushBack(elem);
    }
    ~DynamicArray() { delete[] data; }

    void pushBack(const T& value) {
        if (size == capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        data[size++] = value;
    }

    void popBack() {
        if (size == 0)
            throw  out_of_range("Cannot pop from an empty array.");
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size)
            throw  out_of_range("Index out of range.");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size)
            throw  out_of_range("Index out of range.");
        return data[index];
    }

    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

#endif
