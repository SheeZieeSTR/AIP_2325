#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <string>

using namespace std;

namespace containers {

    template<typename T>
    class RList {
    private:
        struct Node {
            T value;
            Node* next;

            Node(const T& val, Node* nextNode = nullptr) : value(val), next(nextNode) {}
        };

        Node* head;
        size_t size;

        void clear() {
            if (!head) return;

            Node* current = head->next;
            while (current != head) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            delete head;
            head = nullptr;
            size = 0;
        }

    public:
        RList() : head(nullptr), size(0) {}

        RList(initializer_list<T> initList) : RList() {
            for (const T& value : initList) {
                insert(size, value);
            }
        }

        RList(const RList& other) : RList() {
            Node* current = other.head;
            if (current) {
                do {
                    insert(size, current->value);
                    current = current->next;
                } while (current != other.head);
            }
        }

        RList& operator=(const RList& other) {
            if (this == &other) return *this;

            clear();

            Node* current = other.head;
            if (current) {
                do {
                    insert(size, current->value);
                    current = current->next;
                } while (current != other.head);
            }

            return *this;
        }

        RList(RList&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        RList& operator=(RList&& other) noexcept {
            if (this == &other) return *this;

            clear();

            head = other.head;
            size = other.size;

            other.head = nullptr;
            other.size = 0;

            return *this;
        }

        ~RList() {
            clear();
        }

        T& operator[](size_t index) {
            if (index >= size) throw out_of_range("Index out of range");

            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }

            return current->value;
        }

        void insert(size_t index, const T& value) {
            if (index > size) throw out_of_range("Index out of range");

            Node* newNode = new Node(value);
            if (size == 0) {
                head = newNode;
                head->next = head;
            } else if (index == 0) {
                Node* tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                newNode->next = head;
                head = newNode;
                tail->next = head;
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

        void erase(size_t index) {
            if (size == 0 || index >= size) throw out_of_range("Index out of range");

            if (size == 1) {
                delete head;
                head = nullptr;
            } else if (index == 0) {
                Node* tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                Node* temp = head;
                head = head->next;
                tail->next = head;
                delete temp;
            } else {
                Node* current = head;
                for (size_t i = 0; i < index - 1; ++i) {
                    current = current->next;
                }
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
            }

            --size;
        }

        size_t getSize() const {
            return size;
        }

        void display() const {
            if (size == 0) {
                cout << "[ ]\n";
                return;
            }

            Node* current = head;
            cout << "[ ";
            do {
                cout << current->value << " ";
                current = current->next;
            } while (current != head);
            cout << "]\n";
        }
    };
}

int main() {
    using namespace containers;

    RList<int> intList = {1, 2, 3, 4, 5};
    intList.display();
    intList.insert(2, 99);
    intList.display();
    intList.erase(0);
    intList.display();

    RList<double> doubleList = {1.1, 2.2, 3.3};
    doubleList.display();
    doubleList.insert(1, 4.4);
    doubleList.display();
    doubleList.erase(3);
    doubleList.display();

    RList<string> stringList = {"one", "two", "three"};
    stringList.display();
    stringList.insert(1, "inserted");
    stringList.display();
    stringList.erase(2);
    stringList.display();

    return 0;
}
