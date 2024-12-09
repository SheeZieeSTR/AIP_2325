#include <iostream>
#include <string>
#include <initializer_list>

namespace containers {

    template <typename T>
    class Queue {
    private:
        struct Node {
            T value;
            Node* next;

            Node(const T& val) : value(val), next(nullptr) {}
        };

        Node* front;  
        Node* rear;   
        size_t size;

    public:
        
        Queue() : front(nullptr), rear(nullptr), size(0) {}

        
        Queue(std::initializer_list<T> init_list) : front(nullptr), rear(nullptr), size(0) {
            for (const T& value : init_list) {
                enqueue(value);
            }
        }

        
        Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) {
            Node* current = other.front;
            while (current != nullptr) {
                enqueue(current->value);
                current = current->next;
            }
        }

        
        Queue& operator=(const Queue& other) {
            if (this != &other) {
                clear();
                Node* current = other.front;
                while (current != nullptr) {
                    enqueue(current->value);
                    current = current->next;
                }
            }
            return *this;
        }

        
        Queue(Queue&& other) noexcept : front(other.front), rear(other.rear), size(other.size) {
            other.front = nullptr;
            other.rear = nullptr;
            other.size = 0;
        }

        
        Queue& operator=(Queue&& other) noexcept {
            if (this != &other) {
                clear();
                front = other.front;
                rear = other.rear;
                size = other.size;
                other.front = nullptr;
                other.rear = nullptr;
                other.size = 0;
            }
            return *this;
        }

        
        ~Queue() {
            clear();
        }

        
        void enqueue(const T& value) {
            Node* new_node = new Node(value);
            if (rear == nullptr) {
                front = rear = new_node;  
            } else {
                rear->next = new_node;  
                rear = new_node;
            }
            ++size;
        }

        
        void dequeue() {
            if (front == nullptr) {
                throw std::out_of_range("Очередь пуста");
            }
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {  
                rear = nullptr;
            }
            delete temp;
            --size;
        }

        
        T& front_value() {
            if (front == nullptr) {
                throw std::out_of_range("Очередь пуста");
            }
            return front->value;
        }

        
        size_t get_size() const {
            return size;
        }

        
        bool is_empty() const {
            return size == 0;
        }

    private:
        
        void clear() {
            while (front != nullptr) {
                Node* temp = front;
                front = front->next;
                delete temp;
            }
            front = rear = nullptr;
            size = 0;
        }
    };

} 

int main() {
    containers::Queue<int> int_queue = {1, 2, 3};
    containers::Queue<double> double_queue = {1.1, 2.2, 3.3};
    containers::Queue<std::string> string_queue = {"один", "два", "три"};

    int_queue.enqueue(4);
    double_queue.enqueue(4.4);
    string_queue.enqueue("четыре");

    std::cout << "Очередь int: ";
    while (!int_queue.is_empty()) {
        std::cout << int_queue.front_value() << " ";
        int_queue.dequeue();
    }
    std::cout << std::endl;

    std::cout << "Очередь double: ";
    while (!double_queue.is_empty()) {
        std::cout << double_queue.front_value() << " ";
        double_queue.dequeue();
    }
    std::cout << std::endl;

    std::cout << "Очередь string: ";
    while (!string_queue.is_empty()) {
        std::cout << string_queue.front_value() << " ";
        string_queue.dequeue();
    }
    std::cout << std::endl;

    return 0;
}