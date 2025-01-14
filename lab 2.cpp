#include <iostream>
#include <initializer_list>
#include <string>
#include <stdexcept>

namespace containers {

    template<typename T>
    class NameClass {
    public:
        struct Node {
        private:
            T value;
            Node* next;

            Node(const T& val) : value(val), next(nullptr) {}
            Node(T&& val) : value(std::move(val)), next(nullptr) {}

            friend class NameClass<T>;
        };

    private:
        Node* head;
        size_t size;

    public:
        NameClass() : head(nullptr), size(0) {}

        NameClass(std::initializer_list<T> initList) : head(nullptr), size(0) {
            for (const T& value : initList) {
                push_back(value);
            }
        }

        NameClass(const NameClass& other) : head(nullptr), size(0) {
            Node* current = other.head;
            for (size_t i = 0; i < other.size; ++i) {
                push_back(current->value);
                current = current->next;
            }
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                for (size_t i = 0; i < other.size; ++i) {
                    push_back(current->value);
                    current = current->next;
                }
            }
            return *this;
        }

        NameClass(NameClass&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                size = other.size;
                other.head = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~NameClass() {
            clear();
        }

        T& operator[](size_t index) {
            if (index >= size) throw std::out_of_range("Index out of range");
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void push_back(const T& value) {
            Node* newNode = new Node(value);
            if (!head) {
                head = newNode;
                head->next = head;
            } else {
                Node* tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                tail->next = newNode;
                newNode->next = head;
            }
            ++size;
        }

        void push_back(T&& value) {
            Node* newNode = new Node(std::move(value));
            if (!head) {
                head = newNode;
                head->next = head;
            } else {
                Node* tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                tail->next = newNode;
                newNode->next = head;
            }
            ++size;
        }

        void insert(size_t index, const T& value) {
            if (index > size) throw std::out_of_range("Index out of range");
            Node* newNode = new Node(value);

            if (index == 0) {
                if (!head) {
                    head = newNode;
                    head->next = head;
                } else {
                    Node* tail = head;
                    while (tail->next != head) {
                        tail = tail->next;
                    }
                    newNode->next = head;
                    tail->next = newNode;
                    head = newNode;
                }
            } else {
                Node* current = head;
                for (size_t i = 0; i < index - 1; ++i) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            ++size;
        }

        void pop_back() {
            if (!head) throw std::underflow_error("List is empty");
            if (size == 1) {
                delete head;
                head = nullptr;
            } else {
                Node* current = head;
                while (current->next->next != head) {
                    current = current->next;
                }
                delete current->next;
                current->next = head;
            }
            --size;
        }

        size_t get_size() const {
            return size;
        }

        void clear() {
            while (size > 0) {
                pop_back();
            }
        }
    };

    template<typename T>
    class RList {
        // Similar implementation for circular singly linked list
    };
}

int main() {
    using namespace containers;

    NameClass<int> intVector = {1, 2, 3, 4, 5};
    NameClass<double> doubleVector = {1.1, 2.2, 3.3};
    NameClass<std::string> stringVector = {"Hello", "World", "C++"};

    std::cout << "Integer vector contents:" << std::endl;
    for (size_t i = 0; i < intVector.get_size(); ++i) {
        std::cout << intVector[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Double vector contents:" << std::endl;
    for (size_t i = 0; i < doubleVector.get_size(); ++i) {
        std::cout << doubleVector[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "String vector contents:" << std::endl;
    for (size_t i = 0; i < stringVector.get_size(); ++i) {
        std::cout << stringVector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
