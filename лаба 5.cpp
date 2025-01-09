#include <iostream> 
#include <memory> 
#include <initializer_list> 
#include <utility> 
 
template<typename T> 
class Node { 
public: 
    T value; 
    std::unique_ptr<Node<T>> next; // Умный указатель на следующий узел 
 
    Node(T val) : value(val), next(nullptr) {} 
}; 
 
template<typename T> 
class Queue { 
private: 
    std::unique_ptr<Node<T>> head; // Умный указатель на голову очереди 
    Node<T>* tail; // Сырой указатель на хвост очереди 
 
public: 
    Queue() : head(nullptr), tail(nullptr) {} 
 
    Queue(std::initializer_list<T> init) : Queue() { 
        for (const auto& val : init) { 
            enqueue(val); 
        } 
    } 
 
    Queue(const Queue& other) : Queue() { 
        Node<T>* current = other.head.get(); 
        while (current) { 
            enqueue(current->value); 
            current = current->next.get(); 
        } 
    } 
 
    Queue(Queue&& other) noexcept : head(std::move(other.head)), tail(other.tail) { 
        other.tail = nullptr; 
    } 
 
    Queue& operator=(const Queue& other) { 
        if (this != &other) { 
            Queue temp(other); 
            std::swap(head, temp.head); 
            std::swap(tail, temp.tail); 
        } 
        return *this; 
    } 
 
    Queue& operator=(Queue&& other) noexcept { 
        if (this != &other) { 
            head = std::move(other.head); 
            tail = other.tail; 
            other.tail = nullptr; 
        } 
        return *this; 
    } 
 
    ~Queue() = default; // Умные указатели освободят память автоматически 
 
    void enqueue(const T& value) { 
        auto newNode = std::make_unique<Node<T>>(value); 
        if (tail) { 
            tail->next = std::move(newNode); 
            tail = tail->next.get(); // Обновляем хвост 
        } else { 
            head = std::move(newNode); 
            tail = head.get(); // Хвост - это голова 
        } 
    } 
 
    void dequeue() { 
        if (head) { 
            head = std::move(head->next); // Переход к следующему узлу 
            if (!head) { 
                tail = nullptr; // Если очередь пуста, обнуляем хвост 
            } 
        } 
    } 
 
    void display() const { 
        Node<T>* current = head.get(); // Получаем сырой указатель на голову 
        while (current) { 
            std::cout << current->value << " "; 
            current = current->next.get(); // Переходим к следующему узлу 
        } 
        std::cout << std::endl; 
    } 
}; 
 
template<typename T> 
class A { 
private: 
    Queue<T> queue; 
 
public: 
    A(std::initializer_list<T> init) : queue(init) {} 
 
    void enqueue(const T& value) { 
        queue.enqueue(value); 
    } 
 
    void dequeue() { 
        queue.dequeue(); 
    } 
 
    void display() const { 
        queue.display(); 
    } 
}; 
 
int main() { 
    A<int> a = {1, 2, 3, 4, 5}; 
 
    std::cout << "Initial Queue: "; 
    a.display(); 
 
    a.enqueue(6); 
    std::cout << "After enqueue(6): "; 
    a.display(); 
 
    a.dequeue(); 
    std::cout << "After dequeue(): "; 
    a.display(); 
 
    return 0; 
}