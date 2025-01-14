Vect.h 


#ifndef VECT_H
#define VECT_H

#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vect {
public:
    Vect() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vect(std::initializer_list<T> init_list) : Vect() {
        for (const auto& item : init_list) {
            push_back(item);
        }
    }

    ~Vect() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize();
        }
        data_[size_++] = value;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds.");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds.");
        }
        return data_[index];
    }

    size_t size() const { return size_; }

    bool empty() const { return size_ == 0; }

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize() {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
};

#endif // VECT_H





deque.h

  
#ifndef DEQUE_H
#define DEQUE_H

#include "Vect.h"
#include <initializer_list>
#include <utility>

template <typename T>
class Deque {
public:
    Deque() = default;

    Deque(std::initializer_list<T> init_list) : deque_(init_list) {}

    void addFront(const T& value) {
        Vect<T> newDeque;
        newDeque.push_back(value);
        for (size_t i = 0; i < deque_.size(); ++i) {
            newDeque.push_back(deque_[i]);
        }
        deque_ = std::move(newDeque);
    }

    void addBack(const T& value) {
        deque_.push_back(value);
    }

    size_t size() const { return deque_.size(); }

    bool empty() const { return deque_.empty(); }

    // Forward declaration for iterators
    class FrontToBackIterator;
    class BackToFrontIterator;

    // Итератор для обхода дека спереди назад
    class FrontToBackIterator {
    public:
        explicit FrontToBackIterator(const Vect<T>& deque) : deque_(deque), index_(0) {}

        bool hasNext() const {
            return index_ < deque_.size();
        }

        T next() {
            if (index_ >= deque_.size()) {
                throw std::out_of_range("No more elements to iterate.");
            }
            return deque_[index_++];
        }

    private:
        const Vect<T>& deque_;
        size_t index_;
    };

    // Итератор для обхода дека сзади вперед
    class BackToFrontIterator {
    public:
        explicit BackToFrontIterator(const Vect<T>& deque) : deque_(deque), index_(deque.size()) {}

        bool hasNext() const {
            return index_ > 0;
        }

        T next() {
            if (index_ == 0) {
                throw std::out_of_range("No more elements to iterate.");
            }
            return deque_[--index_];
        }

    private:
        const Vect<T>& deque_;
        size_t index_;
    };

    FrontToBackIterator frontToBackIterator() const {
        return FrontToBackIterator(deque_);
    }

    BackToFrontIterator backToFrontIterator() const {
        return BackToFrontIterator(deque_);
    }

private:
    Vect<T> deque_;
};

#endif // DEQUE_H




Exceptionhandling.h


#ifndef EXCEPTION_HANDLING_H
#define EXCEPTION_HANDLING_H

#include <iostream>
#include <stdexcept>

class ExceptionHandling {
public:
    static void handle(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
};

#endif // EXCEPTION_HANDLING_H





Smartpointer.h


#ifndef SMART_POINTER_H
#define SMART_POINTER_H

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T* ptr = nullptr) : ptr_(ptr) {}

    ~SmartPointer() {
        delete ptr_;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    SmartPointer(SmartPointer&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

private:
    T* ptr_;
};

#endif // SMART_POINTER_H





Main.cpp 

  
#include "Deque.h"
#include "ExceptionHandling.h"
#include <iostream>
#include <string>

using namespace std;

void displayMenu() {
    cout << "1. Добавить элемент в начало дека\n";
    cout << "2. Добавить элемент в конец дека\n";
    cout << "3. Показать все элементы дека (спереди назад)\n";
    cout << "4. Показать все элементы дека (сзади вперед)\n";
    cout << "5. Выйти\n";
    cout << "Введите ваш выбор: ";
}

template <typename T>
void runDequeDemo() {
    try {
        Deque<T> deque;
        int choice;
        T value;

        while (true) {
            displayMenu();
            cin >> choice;

            if (choice == 5) break;

            switch (choice) {
            case 1:
                cout << "Введите значение для добавления в начало дека: ";
                cin >> value;
                deque.addFront(value);
                break;
            case 2:
                cout << "Введите значение для добавления в конец дека: ";
                cin >> value;
                deque.addBack(value);
                break;
            case 3:
                cout << "Элементы дека (спереди назад): ";
                for (auto it = deque.frontToBackIterator(); it.hasNext();) {
                    cout << it.next() << " ";
                }
                cout << endl;
                break;
            case 4:
                cout << "Элементы дека (сзади вперед): ";
                for (auto it = deque.backToFrontIterator(); it.hasNext();) {
                    cout << it.next() << " ";
                }
                cout << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }

    }
    catch (const exception& e) {
        ExceptionHandling::handle(e);
    }
}

int main() {

    setlocale(LC_ALL, "RU");

    cout << "Демонстрация шаблонного класса Deque:\n";
    cout << "Выберите тип данных:\n";
    cout << "1. int\n";
    cout << "2. double\n";
    cout << "3. string\n";
    cout << "Введите ваш выбор: ";

    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
    case 1:
        runDequeDemo<int>();
        break;
    case 2:
        runDequeDemo<double>();
        break;
    case 3:
        runDequeDemo<string>();
        break;
    default:
        cout << "Неверный выбор.\n";
        break;
    }

    return 0;
}

