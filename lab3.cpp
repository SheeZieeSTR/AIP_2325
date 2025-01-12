#include <iostream>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <string>

using namespace std;

namespace containers {

    template<typename T>
    class BinaryTree {
    private:
        struct Node {
            T value;
            unique_ptr<Node> left;
            unique_ptr<Node> right;

            Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
        };

        unique_ptr<Node> root;
        size_t size;

        void copyTree(const unique_ptr<Node>& source, unique_ptr<Node>& destination) {
            if (source) {
                destination = make_unique<Node>(source->value);
                copyTree(source->left, destination->left);
                copyTree(source->right, destination->right);
            }
        }

        void inorderTraversal(const Node* node) const {
            if (node) {
                inorderTraversal(node->left.get());
                cout << node->value << " ";
                inorderTraversal(node->right.get());
            }
        }

        void insertValue(unique_ptr<Node>& node, const T& value) {
            if (!node) {
                node = make_unique<Node>(value);
                ++size;
            } else if (value < node->value) {
                insertValue(node->left, value);
            } else if (value > node->value) {
                insertValue(node->right, value);
            } else {
                throw invalid_argument("Duplicate value not allowed in BinaryTree");
            }
        }

        void clear() {
            root.reset();
            size = 0;
        }

    public:
        BinaryTree() : root(nullptr), size(0) {}

        BinaryTree(initializer_list<T> initList) : BinaryTree() {
            for (const T& value : initList) {
                insert(value);
            }
        }

        BinaryTree(const BinaryTree& other) : BinaryTree() {
            copyTree(other.root, root);
        }

        BinaryTree& operator=(const BinaryTree& other) {
            if (this == &other) return *this;
            clear();
            copyTree(other.root, root);
            return *this;
        }

        BinaryTree(BinaryTree&& other) noexcept : root(move(other.root)), size(other.size) {
            other.size = 0;
        }

        BinaryTree& operator=(BinaryTree&& other) noexcept {
            if (this == &other) return *this;
            clear();
            root = move(other.root);
            size = other.size;
            other.size = 0;
            return *this;
        }

        ~BinaryTree() {
            clear();
        }

        void insert(const T& value) {
            insertValue(root, value);
        }

        size_t getSize() const {
            return size;
        }

        void display() const {
            inorderTraversal(root.get());
            cout << endl;
        }

        bool find(const T& value) const {
            Node* current = root.get();
            while (current) {
                if (value == current->value) {
                    return true;
                } else if (value < current->value) {
                    current = current->left.get();
                } else {
                    current = current->right.get();
                }
            }
            return false;
        }
    };
}

int main() {
    using namespace containers;

    try {
        BinaryTree<int> intTree = {5, 3, 7, 2, 4, 6, 8};
        intTree.display();
        intTree.insert(9);
        intTree.display();
        cout << "Find 6: " << (intTree.find(6) ? "Found" : "Not Found") << endl;

        BinaryTree<double> doubleTree = {1.1, 2.2, 3.3, 4.4};
        doubleTree.display();
        doubleTree.insert(5.5);
        doubleTree.display();

        BinaryTree<string> stringTree = {"apple", "banana", "cherry"};
        stringTree.display();
        stringTree.insert("date");
        stringTree.display();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
