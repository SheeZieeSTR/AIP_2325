#include <iostream> 
#include <memory> 
#include <stdexcept> 
#include <initializer_list> 
 
template<typename T> 
class Node { 
public: 
    T value; 
    std::unique_ptr<Node<T>> next; 
    Node* prev; 
 
    Node(T val) : value(val), next(nullptr), prev(nullptr) {} 
}; 
 
class QueueException : public std::runtime_error { 
public: 
    explicit QueueException(const std::string& message) 
        : std::runtime_error(message) {} 
}; 
 
class QueueEmptyException : public QueueException { 
public: 
    explicit QueueEmptyException(const std::string& message) 
        : QueueException(message) {} 
}; 
 
template<typename T> 
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
 
    SmartPointer(const SmartPointer&) = delete; 
    SmartPointer& operator=(const SmartPointer&) = delete; 
 
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
 
    T* get() const { 
        return ptr; 
    } 
}; 
 
template<typename T> 
class Queue { 
private: 
    std::unique_ptr<Node<T>> head; 
    Node<T>* tail; 
 
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
 
    ~Queue() = default; 
 
    void enqueue(const T& value); 
    void dequeue(); 
    const T& front() const; 
    const T& back() const; 
    bool isEmpty() const; 
    void clear(); 
    void display() const; 
    size_t size() const; 
}; 
 
template<typename T> 
void Queue<T>::enqueue(const T& value) { 
    auto newNode = std::make_unique<Node<T>>(value); 
    if (tail) { 
        tail->next = std::move(newNode); 
        tail->next->prev = tail; 
        tail = tail->next.get(); 
    } else { 
        head = std::move(newNode); 
        tail = head.get(); 
    } 
} 
 
template<typename T> 
void Queue<T>::dequeue() { 
    if (!head) { 
        throw QueueEmptyException("Queue is empty. Cannot dequeue."); 
    } 
    head = std::move(head->next); 
    if (head) { 
        head->prev = nullptr; 
    } else { 
        tail = nullptr; 
    } 
} 
 
template<typename T> 
const T& Queue<T>::front() const { 
    if (!head) { 
        throw QueueEmptyException("Queue is empty. Cannot access front."); 
    } 
    return head->value; 
} 
 
template<typename T> 
const T& Queue<T>::back() const { 
    if (!tail) { 
        throw QueueEmptyException("Queue is empty. Cannot access back."); 
    } 
    return tail->value; 
} 
 
template<typename T> 
bool Queue<T>::isEmpty() const { 
    return head == nullptr; 
} 
 
template<typename T> 
void Queue<T>::clear() { 
    while (head) { 
        head = std::move(head->next); 
    } 
    tail = nullptr; 
} 
 
template<typename T> 
void Queue<T>::display() const { 
    Node<T>* current = head.get(); 
    while (current) { 
        std::cout

Mihuil fuils, [08.12.2024 23:03]
<< current->value << " "; 
        current = current->next.get(); 
    } 
    std::cout << std::endl; 
} 
 
template<typename T> 
size_t Queue<T>::size() const { 
    size_t count = 0; 
    Node<T>* current = head.get(); 
    while (current) { 
        count++; 
        current = current->next.get(); 
    } 
    return count; 
} 
 
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
 
    const T& front() const { 
        return queue.front(); 
    } 
 
    const T& back() const { 
        return queue.back(); 
    } 
 
    bool isEmpty() const { 
        return queue.isEmpty(); 
    } 
 
    void clear() { 
        queue.clear(); 
    } 
 
    size_t size() const { 
        return queue.size(); 
    } 
}; 
 
int main() { 
    try { 
        A<int> a = {1, 2, 3, 4, 5}; 
 
        std::cout << "Initial Queue: "; 
        a.display(); 
 
        a.enqueue(6); 
        std::cout << "After enqueue(6): "; 
        a.display(); 
 
        std::cout << "Front: " << a.front() << std::endl; 
        std::cout << "Back: " << a.back() << std::endl; 
 
        a.dequeue(); 
        std::cout << "After dequeue(): "; 
        a.display(); 
 
        std::cout << "Queue Size: " << a.size() << std::endl; 
 
        a.clear(); 
        std::cout << "After clear(): "; 
        a.display(); 
 
        std::cout << "Is empty: " << (a.isEmpty() ? "Yes" : "No") << std::endl; 
 
        std::cout << "Attempting to access front on empty queue." << std::endl; 
        a.front(); 
 
    } catch (const QueueException& e) { 
        std::cerr << "Queue Exception: " << e.what() << std::endl; 
    } catch (const std::exception& e) { 
        std::cerr << "Exception: " << e.what() << std::endl; 
    } 
 
    return 0; 
}