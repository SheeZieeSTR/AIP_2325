#include <iostream>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <string>
#include <iterator>

// Custom exception class
class CustomException : public std::exception {
private:
    std::string message;
    int error_code;

public:
    CustomException(const std::string& msg, int code)
        : message(msg), error_code(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    int getErrorCode() const { return error_code; }
};

// Node structure
template <typename T>
struct Node {
    T value;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;

    Node(const T& val) : value(val), next(nullptr), prev() {}
};

// Template List class
template <typename T>
class List {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t size;

public:
    // Default constructor
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Constructor from initializer list
    List(std::initializer_list<T> init_list) : List() {
        for (const T& value : init_list) {
            push_back(value);
        }
    }

    // Copy constructor
    List(const List<T>& other) : List() {
        for (auto node = other.head; node != nullptr; node = node->next) {
            push_back(node->value);
        }
    }

    // Move constructor
    List(List<T>&& other) noexcept
        : head(std::move(other.head)), tail(std::move(other.tail)), size(other.size) {
        other.size = 0;
    }

    // Copy assignment operator
    List& operator=(const List<T>& other) {
        if (this != &other) {
            clear();
            for (auto node = other.head; node != nullptr; node = node->next) {
                push_back(node->value);
            }
        }
        return *this;
    }

    // Move assignment operator
    List& operator=(List<T>&& other) noexcept {
        if (this != &other) {
            clear();
            head = std::move(other.head);
            tail = std::move(other.tail);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    // Destructor
    ~List() {
        clear();
    }

    // Push back
    void push_back(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (tail) {
            tail->next = new_node;
            new_node->prev = tail;
        } else {
            head = new_node;
        }
        tail = new_node;
        ++size;
    }

    // Pop back
    void pop_back() {
        if (!tail) {
            throw CustomException("Cannot pop from an empty list", 101);
        }
        if (tail == head) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev.lock();
            tail->next = nullptr;
        }
        --size;
    }

    // Size
    size_t get_size() const {
        return size;
    }

    // Clear list
    void clear() {
        while (head) {
            head = head->next;
        }
        tail = nullptr;
        size = 0;
    }

    // Print list
    void print() const {
        for (auto node = head; node != nullptr; node = node->next) {
            std::cout << node->value << " ";
        }
        std::cout << std::endl;
    }
};

// Main function to test the List class
template <typename T>
void test_list() {
    try {
        List<T> list = {1, 2, 3, 4, 5};
        list.print();

        list.push_back(6);
        list.print();

        list.pop_back();
        list.print();

        std::cout << "Size: " << list.get_size() << std::endl;

        list.clear();
        std::cout << "List cleared. Size: " << list.get_size() << std::endl;
    } catch (const CustomException& e) {
        std::cerr << "Error: " << e.what() << " (Code: " << e.getErrorCode() << ")" << std::endl;
    }
}

int main() {
    std::cout << "Testing List with int:\n";
    test_list<int>();

    std::cout << "\nTesting List with double:\n";
    test_list<double>();

    std::cout << "\nTesting List with std::string:\n";
    test_list<std::string>();

    return 0;
}
