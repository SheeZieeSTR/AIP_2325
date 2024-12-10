#include <iostream> 
#include <initializer_list> 
 
template <typename T> 
class RList { 
private: 
    struct Node { 
        T value;     
        Node* next; 
        Node* prev; 
 
        Node(const T& data) : value(data), next(nullptr), prev(nullptr) {} 
    }; 
 
    Node* head; 
    size_t size; 
 
public: 
    RList() : head(nullptr), size(0) {} 
 
    RList(std::initializer_list<T> init) : RList() { 
        for (const T& value : init) { 
            push_back(value); 
        } 
    } 
 
    ~RList() { 
        clear(); 
    } 
  
    void push_back(const T& value) { 
        Node* newNode = createNode(value); 
        if (size == 0) { 
            head = newNode; 
            head->next = head; 
            head->prev = head; 
        } else { 
            Node* tail = head->prev; 
            tail->next = newNode; 
            newNode->prev = tail; 
            newNode->next = head; 
            head->prev = newNode; 
        } 
        size++; 
    } 
 
    void remove(Node* node) { 
        if (size == 0 || node == nullptr) return; 
 
        if (node == head && size == 1) { 
            delete node; 
            head = nullptr; 
        } else { 
            Node* nextNode = node->next; 
            Node* prevNode = node->prev; 
 
            if (node == head) { 
                head = nextNode; 
            } 
            prevNode->next = nextNode; 
            nextNode->prev = prevNode; 
 
            delete node; 
        } 
        size--; 
    } 
  
    void clear() { 
        while (size > 0) { 
            remove(head); 
        } 
    } 
 
    void display() const { 
        if (size == 0) return; 
 
        Node* current = head; 
        do { 
            std::cout << current->value << " ";   
            current = current->next; 
        } while (current != head); 
        std::cout << std::endl; 
    } 
 
    size_t getSize() const { 
        return size; 
    } 
  
    bool isEmpty() const { 
        return size == 0; 
    } 
 
private: 
    
    Node* createNode(const T& value) { 
        return new Node(value); 
    } 
 
     
    Node(const Node&) = delete;  
    Node& operator=(const Node&) = delete; 
}; 
 
int main() { 
    RList<int> list = {1, 2, 3, 4, 5}; 
 
    std::cout << "Содержимое списка: "; 
    list.display(); 
 
    list.clear(); 
    std::cout << "Список очищен. Размер: " << list.getSize() << std::endl; 
 
    return 0; 
}