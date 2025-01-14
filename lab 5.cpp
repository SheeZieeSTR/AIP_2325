#include <iostream> 
#include <vector> 
#include <string> 
#include <exception> 
#include <memory> 
 
// Шаблонный класс Stack 
template <typename T> 
class Stack { 
private: 
    std::vector<T> elems; // элементы стека 
 
public: 
    void push(const T& elem); 
    void pop(); 
    T top() const; 
    bool empty() const; 
}; 
 
template <typename T> 
void Stack<T>::push(const T& elem) { 
    elems.push_back(elem); 
} 
 
template <typename T> 
void Stack<T>::pop() { 
    if (elems.empty()) { 
        throw std::out_of_range("Stack<>::pop: empty stack"); 
    } 
    elems.pop_back(); 
} 
 
template <typename T> 
T Stack<T>::top() const { 
    if (elems.empty()) { 
        throw std::out_of_range("Stack<>::top: empty stack"); 
    } 
    return elems.back(); 
} 
 
template <typename T> 
bool Stack<T>::empty() const { 
    return elems.empty(); 
} 
 
// Шаблонный класс умных указателей USmartPointer 
template <typename T> 
class USmartPointer { 
private: 
    T* ptr; 
 
public: 
    USmartPointer(T* p = nullptr); 
    ~USmartPointer(); 
    T& operator*(); 
    T* operator->(); 
}; 
 
template <typename T> 
USmartPointer<T>::USmartPointer(T* p) : ptr(p) {} 
 
template <typename T> 
USmartPointer<T>::~USmartPointer() { 
    delete ptr; 
} 
 
template <typename T> 
T& USmartPointer<T>::operator*() { 
    return *ptr; 
} 
 
template <typename T> 
T* USmartPointer<T>::operator->() { 
    return ptr; 
} 
 
// Класс для обработки исключений 
class ExceptionHandler { 
public: 
    static void handle(const std::exception& e) { 
        std::cerr << "Exception: " << e.what() << std::endl; 
    } 
}; 
 
// Функция меню для тестирования 
void menu() { 
    Stack<int> intStack; 
    Stack<double> doubleStack; 
    Stack<std::string> stringStack; 
    int choice; 
    int intValue; 
    double doubleValue; 
    std::string stringValue; 
 
    while (true) { 
        std::cout << "1. Push (int)\n2. Pop (int)\n3. Top (int)\n" 
                     "4. Push (double)\n5. Pop (double)\n6. Top (double)\n" 
                     "7. Push (string)\n8. Pop (string)\n9. Top (string)\n10. Exit\nChoice: "; 
        std::cin >> choice; 
 
        try { 
            switch (choice) { 
                case 1: 
                    std::cout << "Enter value: "; 
                    std::cin >> intValue; 
                    intStack.push(intValue); 
                    break; 
                case 2: 
                    intStack.pop(); 
                    break; 
                case 3: 
                    std::cout << "Top element: " << intStack.top() << std::endl; 
                    break; 
                case 4: 
                    std::cout << "Enter value: "; 
                    std::cin >> doubleValue; 
                    doubleStack.push(doubleValue); 
                    break; 
                case 5: 
                    doubleStack.pop(); 
                    break; 
                case 6: 
                    std::cout << "Top element: " << doubleStack.top() << std::endl; 
                    break; 
                case 7: 
                    std::cout << "Enter value: "; 
                    std::cin >> stringValue; 
                    stringStack.push(stringValue); 
                    break; 
                case 8: 
                    stringStack.pop(); 
                    break; 
                case 9: 
                    std::cout << "Top element: " << stringStack.top() << std::endl; 
                    break; 
                case 10: 
                    return; 
                default: 
                    std::cout << "Invalid choice!" << std::endl; 
            } 
        } catch (const std::exception& e) { 
            ExceptionHandler::handle(e); 
        } 
    } 
} 
 
int main() { 
    try { 
        Stack<int> intStack; 
        intStack.push(1); 
        intStack.push(2); 
        std::cout << "Top element: " << intStack.top() << std::endl; 
 
        USmartPointer<Stack<int>> sp(new Stack<int>); 
        sp->push(3); 
        sp->push(4); 
        std::cout << "Top element in smart pointer stack: " <<
sp->top() << std::endl; 
 
        while (!intStack.empty()) { 
            intStack.pop(); 
        } 
        intStack.pop(); // Это вызовет исключение 
    } catch (const std::exception& e) { 
        ExceptionHandler::handle(e); 
    } 
 
    menu(); 
    return 0; 
}
