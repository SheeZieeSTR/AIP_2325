#include <iostream>
#include <list>
#include <stdexcept>


template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T* ptr = nullptr) : ptr_(ptr) {}
    ~SmartPointer() { delete ptr_; }

    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

private:
    T* ptr_;
};


template <typename T>
class Stack {
public:
    Stack() = default;
    Stack(std::initializer_list<T> init_list) : data_(init_list) {}
    Stack(const Stack& other) : data_(other.data_) {}
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }
    Stack(Stack&& other) noexcept : data_(std::move(other.data_)) {}
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
    void push(const T& value) {
        data_.push_back(value);
    }
    void pop() {
        if (data_.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        data_.pop_back();
    }
    T& top() {
        if (data_.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data_.back();
    }
    size_t size() const {
        return data_.size();
    }
private:
    std::list<T> data_; 
};

class ExceptionHandling {
public:
    static void handle(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
};
int main() {
    try {
        Stack<int> intStack = {1, 2, 3, 4, 5};
        intStack.push(6);
        std::cout << "Size of intStack: " << intStack.size() << std::endl;
        std::cout << "Top of intStack: " << intStack.top() << std::endl;
        intStack.pop();
        std::cout << "Size of intStack after pop: " << intStack.size() << std::endl;

        Stack<double> doubleStack = {1.1, 2.2, 3.3, 4.4, 5.5};
        doubleStack.push(6.6);
        std::cout << "Size of doubleStack: " << doubleStack.size() << std::endl;

        Stack<std::string> stringStack = {"one", "two", "three"};
        stringStack.push("four");
        std::cout << "Size of stringStack: " << stringStack.size() << std::endl;
        std::cout << "Top of stringStack: " << stringStack.top() << std::endl;

    } catch (const std::exception& e) {
        ExceptionHandling::handle(e);
    }
    return 0;
}
