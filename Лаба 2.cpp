#include <iostream>
#include <stdexcept>

using namespace std;

namespace containers {

template <typename T>
class PQueue {
public:
    struct Node {
        T value;
        int priority;
        Node* next;

        Node(T val, int pri) : value(val), priority(pri), next(nullptr) {}
    };

    PQueue() : head(nullptr), size(0) {}

    void enqueue(const T& value, int priority) {
        Node* newNode = new Node(value, priority);
        if (!head || head->priority < priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        ++size;
    }

    T dequeue() {
        if (!head) throw underflow_error("Очередь с приоритетами пуста");
        Node* nodeToRemove = head;
        T value = nodeToRemove->value;
        head = head->next;
        delete nodeToRemove;
        --size;
        return value;
    }

    size_t getSize() const {
        return size;
    }

private:
    Node* head;
    size_t size;
};

} // namespace containers

void showMenu() {
    cout << "Меню:\n1. Добавить элемент\n2. Извлечь элемент\n3. Показать размер очереди\n0. Выход\n";
}

int main() {
    using namespace containers;

    PQueue<int> pq;
    int choice, value, priority;

    do {
        showMenu();
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите значение: ";
                cin >> value;
                cout << "Введите приоритет: ";
                cin >> priority;
                pq.enqueue(value, priority);
                cout << "Элемент добавлен.\n";
                break;
            case 2:
                try {
                    cout << "Извлечен элемент: " << pq.dequeue() << endl;
                } catch (const underflow_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 3:
                cout << "Размер очереди: " << pq.getSize() << endl;
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Повторите попытку.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
