#include <iostream>
#include <initializer_list>
#include <string>
#include <limits>

using namespace std;

namespace containers {
    template <typename T>
    class BinaryTree {
    public:
        struct Node {
            T value;
        private:
            Node* left;
            Node* right;

            Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
            friend class BinaryTree; 
        };

        BinaryTree() : root(nullptr), size(0) {}

        BinaryTree(initializer_list<T> initList) : root(nullptr), size(0) {
            for (const auto& val : initList) {
                insert(val);
            }
        }

        BinaryTree(const BinaryTree& other) { copy(other.root); }
        BinaryTree(BinaryTree&& other) noexcept : root(other.root), size(other.size) {
            other.root = nullptr;
            other.size = 0;
        }

        BinaryTree& operator=(const BinaryTree& other) {
            if (this != &other) {
                clear();
                copy(other.root);
            }
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& other) noexcept {
            if (this != &other) {
                clear();
                root = other.root;
                size = other.size;
                other.root = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~BinaryTree() { clear(); }

        void insert(const T& value) {
            root = insert(root, value);
            ++size;
        }

        void remove(const T& value) {
            root = remove(root, value);
            --size;
        }

        void display() const { displayInOrder(root); }

    private:
        Node* root;
        int size;

        Node* insert(Node* node, const T& value) {
            if (!node) return new Node(value);
            if (value < node->value) node->left = insert(node->left, value);
            else node->right = insert(node->right, value);
            return node;
        }

        Node* remove(Node* node, const T& value) {
            if (!node) return node;
            if (value < node->value) node->left = remove(node->left, value);
            else if (value > node->value) node->right = remove(node->right, value);
            else {
                if (!node->left) return node->right;
                if (!node->right) return node->left;
                Node* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
            return node;
        }

        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current && current->left) current = current->left;
            return current;
        }

        void displayInOrder(Node* node) const {
            if (!node) return;
            displayInOrder(node->left);
            cout << node->value << " ";
            displayInOrder(node->right);
        }

        void clear() { clear(root); root = nullptr; size = 0; }

        void clear(Node* node) {
            if (!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
        }

        void copy(Node* node) {
            if (node) {
                insert(node->value);
                copy(node->left);
                copy(node->right);
            }
        }
    };
}

void displayMenu() {
    cout << "\n---Менюшка---\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент\n";
    cout << "3. Показать дерево\n";
    cout << "4. Изменить тип данных\n";
    cout << "5. Выход\n";
}

template <typename T>
void processTree(containers::BinaryTree<T>& tree) {
    int choice;
    T value;

    while (true) {
        displayMenu();
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {  
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Толька числа\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите значение для ввода: ";
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неправильный вывод.\n";
            }
            else {
                tree.insert(value);
            }
            break;
        case 2:
            cout << "Значение для удаления: ";
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неправильный вывод.\n";
            }
            else {
                tree.remove(value);
            }
            break;
        case 3:
            tree.display();
            cout << "\n";
            break;
        case 4:
            return; 
        case 5:
            exit(0);
        default:
            cout << "Неправильный выбор.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int dataType;

    while (true) {
        cout << "\nВыберите тип данных:\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. string\n";
        cout << "4. Выход\n";
        cout << "Ваш выбор: ";
        cin >> dataType;

        if (cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Пожалуйста число..\n";
            continue;
        }

        switch (dataType) {
        case 1: {
            containers::BinaryTree<int> tree;
            processTree(tree);
            break;
        }
        case 2: {
            containers::BinaryTree<double> tree;
            processTree(tree);
            break;
        }
        case 3: {
            containers::BinaryTree<string> tree;
            processTree(tree);
            break;
        }
        case 4:
            return 0;
        default:
            cout << "Выбор меджду 1 и 4.\n";
        }
    }
}