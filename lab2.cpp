#include <iostream> 
#include <initializer_list> 
#include <string> 
 
namespace containers { 
 
template <typename T> 
class NameClass { 
public: 
    // Вложенная структура Node 
    struct Node { 
        T value;           // Значение узла 
        Node* next;       // Указатель на следующий узел 
 
        // Приватный конструктор 
        Node(const T& val) : value(val), next(nullptr) {} 
    }; 
 
private: 
    Node* head;         // Указатель на вершину стека 
    size_t size;        // Размер стека 
 
public: 
    // Конструктор по умолчанию 
    NameClass() : head(nullptr), size(0) {} 
 
    // Конструктор от std::initializer_list<T> 
    NameClass(std::initializer_list<T> list) : head(nullptr), size(0) { 
        for (const auto& item : list) { 
            push(item); 
        } 
    } 
 
    // Конструктор копирования 
    NameClass(const NameClass& other) : head(nullptr), size(0) { 
        Node* current = other.head; 
        while (current) { 
            push(current->value); 
            current = current->next; 
        } 
    } 
 
    // Оператор копирующего присваивания 
    NameClass& operator=(const NameClass& other) { 
        if (this != &other) { 
            clear(); 
            Node* current = other.head; 
            while (current) { 
                push(current->value); 
                current = current->next; 
            } 
        } 
        return *this; 
    } 
 
    // Конструктор перемещения 
    NameClass(NameClass&& other) noexcept : head(other.head), size(other.size) { 
        other.head = nullptr; 
        other.size = 0; 
    } 
 
    // Оператор перемещающего присваивания 
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
 
    // Метод добавления элемента в стек 
    void push(const T& value) { 
        Node* newNode = new Node(value); 
        newNode->next = head;  // Новый узел указывает на предыдущую вершину 
        head = newNode;        // Обновляем вершину стека 
        size++; 
    } 
 
    // Метод удаления элемента из стека 
    void pop() { 
        if (head) { 
            Node* temp = head; 
            head = head->next; 
            delete temp; 
            size--; 
        } 
    } 
 
    // Метод для получения размера стека 
    size_t getSize() const { 
        return size; 
    } 
 
    // Метод для доступа к вершине стека 
    T top() const { 
        if (head) { 
            return head->value; 
        } 
        throw std::out_of_range("Stack is empty"); 
    } 
 
    // Метод для очистки стека 
    void clear() { 
        while (head) { 
            pop(); 
        } 
    } 
 
    // Деструктор 
    ~NameClass() { 
        clear(); 
    } 
}; 
 
} // namespace containers 
 
// Функция для демонстрации работы с классом Stack 
void stackMenu() { 
    using namespace containers; 
    NameClass<int> stackInt; 
 
    int choice; 
    int value; 
 
    do { 
        std::cout << "\nMenu:\n"; 
        std::cout << "1. Push\n"; 
        std::cout << "2. Pop\n"; 
        std::cout << "3. Top\n"; 
        std::cout << "4. Size\n"; 
        std::cout << "5. Clear\n"; 
        std::cout << "0. Exit\n"; 
        std::cout << "Choose an option: "; 
        std::cin >> choice; 
 
        switch (choice) { 
            case 1: 
                std::cout << "Enter value to push: "; 
                std::cin >> value; 
                stackInt.push(value); 
                break; 
            case 2: 
                try { 
                    stackInt.pop(); 
                    std::cout << "Popped element from the stack.\n"; 
                } catch (const std::out_of_range& e) { 
                    std::cout << e.what() << '\n'; 
                } 
                break; 
                case 3: 
                try { 
                    std::cout << "Top element: " << stackInt.top() << '\n'; 
                } catch (const
std::out_of_range& e) { 
                    std::cout << e.what() << '\n'; 
                } 
                break; 
            case 4: 
                std::cout << "Size of stack: " << stackInt.getSize() << '\n'; 
                break; 
            case 5: 
                stackInt.clear(); 
                std::cout << "Stack cleared.\n"; 
                break; 
            case 0: 
                std::cout << "Exiting...\n"; 
                break; 
            default: 
                std::cout << "Invalid option. Try again.\n"; 
        } 
    } while (choice != 0); 
} 

int main() { 
    stackMenu(); 
    return 0; 
}
