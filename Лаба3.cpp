#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>

using namespace std;

namespace containers {

template <typename T>
class NameClass {
public:
    struct Node {
        T value;
        Node* next;
        Node* prev;

    private:
        Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
        friend class NameClass<T>;
    };

    // Конструктор по умолчанию
    NameClass() : head(nullptr), tail(nullptr), size(0) {}

    // Конструктор от std::initializer_list<T>
    NameClass(initializer_list<T> init_list) : head(nullptr), tail(nullptr), size(0) {
        for (const T& val : init_list) {
            addToEnd(val);
        }
    }

    // Конструктор копирования
    NameClass(const NameClass& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            addToEnd(current->value);
            current = current->next;
        }
    }

    // Оператор копирующего присваивания
    NameClass& operator=(const NameClass& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                addToEnd(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    // Конструктор перемещения
    NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Оператор перемещающего присваивания
    NameClass& operator=(NameClass&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Деструктор
    ~NameClass() {
        clear();
    }

    // Метод добавления элемента в конец
    void addToEnd(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++size;
    }

    // Метод добавления элемента в произвольную позицию
    void addToPosition(size_t position, const T& value) {
        if (position > size) {
            throw std::out_of_range("Position out of range");
        }
        Node* newNode = new Node(value);
        if (position == 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (size == 0) tail = newNode;
        } else {
            Node* current = head;
            for (size_t i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
            if (position == size) tail = newNode;
        }
        ++size;
    }

    // Метод удаления элемента с конца
    void removeFromEnd() {
        if (tail) {
            Node* temp = tail;
            if (tail->prev) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                head = tail = nullptr;
            }
            delete temp;
            --size;
        }
    }

    // Метод удаления элемента из произвольной позиции
    void removeFromPosition(size_t position) {
        if (position >= size) {
            throw std::out_of_range("Position out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
        delete current;
        --size;
    }

    // Операция индексирования
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    // Получение размера
    size_t getSize() const {
        return size;
    }

    // Очистка списка
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

private:
    Node* head;
    Node* tail;
    size_t size;
};

} // namespace containers

void testInt() {
    containers::NameClass<int> list = {1, 2, 3, 4, 5};
    list.addToEnd(6);
    list.addToPosition(2, 7);
    list.removeFromEnd();
    list.removeFromPosition(2);
    cout << "List of integers: ";
    for (size_t i = 0; i < list.getSize(); ++i) {
        cout << list[i] << " ";
    }
    cout << endl;
}

void testDouble() {
    containers::NameClass<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};
    list.addToEnd(6.6);
    list.addToPosition(2, 7.7);
    list.removeFromEnd();
    list.removeFromPosition(2);
    cout << "List of doubles: ";
    for (size_t i = 0; i < list.getSize(); ++i) {
        cout << list[i] << " ";
    }
    cout << endl;
}

void testString() {
    containers::NameClass<string> list = {"one", "two", "three", "four", "five"};
    list.addToEnd("six");
    list.addToPosition(2, "seven");
    list.removeFromEnd();
    list.removeFromPosition(2);
    cout << "List of strings: ";
    for (size_t i = 0; i < list.getSize(); ++i) {
        cout << list[i] << " ";
    }
    cout << endl;
}

void displayMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Insert a value\n";
    cout << "2. Remove a value\n";
    cout << "3. Check if value exists\n";
    cout << "4. Display list size\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int choice;
    while (true) {
        cout << "Choose a type to test:\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. string\n";
        cout << "4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                testInt();
                break;
            case 2:
                testDouble();
                break;
            case 3:
                testString();
                break;
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    return 0;
}
