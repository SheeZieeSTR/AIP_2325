#include <iostream>
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
            Node(T val) : value(val), next(nullptr), prev(nullptr) {}
        };

    private:
        Node* head;
        Node* tail;
        size_t size;

    public:
        NameClass() : head(nullptr), tail(nullptr), size(0) {}
        NameClass(initializer_list<T> initList) : head(nullptr), tail(nullptr), size(0) {
            for (const T& val : initList) add_back(val);
        }

        NameClass(const NameClass& other) : head(nullptr), tail(nullptr), size(0) {
            for (Node* n = other.head; n; n = n->next) add_back(n->value);
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                for (Node* n = other.head; n; n = n->next) add_back(n->value);
            }
            return *this;
        }

        NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = other.tail = nullptr;
            other.size = 0;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;
                other.head = other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~NameClass() { clear(); }

        T& operator[](size_t index) {
            Node* n = head;
            for (size_t i = 0; i < index && n; ++i) n = n->next;
            if (!n) throw out_of_range("Index out of range");
            return n->value;
        }

        void add_back(const T& value) {
            Node* newNode = new Node(value);
            if (tail) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            else {
                head = tail = newNode;
            }
            ++size;
        }

        void remove_back() {
            if (!tail) throw out_of_range("List is empty");
            Node* temp = tail;
            if (tail->prev) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                head = tail = nullptr;
            }
            delete temp;
            --size;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            size = 0;
        }

        size_t get_size() const { return size; }
    };

}



int main() {
    using namespace containers;

    NameClass<int> intList{ 1, 2, 3 };
    intList.add_back(4);
    intList.remove_back();
    for (size_t i = 0; i < intList.get_size(); ++i)
        cout << "intList[" << i << "] = " << intList[i] << endl;

    NameClass<double> doubleList{ 1.1, 2.2 };
    doubleList.add_back(3.3);
    doubleList.remove_back();
    for (size_t i = 0; i < doubleList.get_size(); ++i)
        cout << "doubleList[" << i << "] = " << doubleList[i] << endl;

    NameClass<string> stringList{ "Cat", "Dog" };
    stringList.add_back("Frog");
    for (size_t i = 0; i < stringList.get_size(); ++i)
        cout << "stringList[" << i << "] = " << stringList[i] << endl;

    return 0;
}
