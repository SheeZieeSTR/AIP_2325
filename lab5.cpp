#include <iostream>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <stack>
#include <queue>

using namespace std;

namespace containers {

    class CustomException : public exception {
    private:
        string message;
    public:
        explicit CustomException(const string& msg) : message(msg) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };

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

        void insertValue(unique_ptr<Node>& node, const T& value) {
            if (!node) {
                node = make_unique<Node>(value);
                ++size;
            } else if (value < node->value) {
                insertValue(node->left, value);
            } else if (value > node->value) {
                insertValue(node->right, value);
            } else {
                throw CustomException("Повторяющееся значение не допускается в BinaryTree");
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

        class IteratorInterface {
        public:
            virtual ~IteratorInterface() = default;
            virtual bool hasNext() = 0;
            virtual T next() = 0;
        };

        class InOrderIterator : public IteratorInterface {
        private:
            stack<Node*> stack;

            void pushLeft(Node* node) {
                while (node) {
                    stack.push(node);
                    node = node->left.get();
                }
            }

        public:
            explicit InOrderIterator(Node* root) {
                pushLeft(root);
            }

            bool hasNext() override {
                return !stack.empty();
            }

            T next() override {
                if (stack.empty()) {
                    throw CustomException("В InOrderIterator больше нет элементов");
                }

                Node* current = stack.top();
                stack.pop();
                pushLeft(current->right.get());
                return current->value;
            }
        };

        class LevelOrderIterator : public IteratorInterface {
        private:
            queue<Node*> queue;

        public:
            explicit LevelOrderIterator(Node* root) {
                if (root) {
                    queue.push(root);
                }
            }

            bool hasNext() override {
                return !queue.empty();
            }

            T next() override {
                if (queue.empty()) {
                    throw CustomException("В LevelOrderIterator больше нет элементов");
                }

                Node* current = queue.front();
                queue.pop();

                if (current->left) queue.push(current->left.get());
                if (current->right) queue.push(current->right.get());

                return current->value;
            }
        };

        unique_ptr<IteratorInterface> getInOrderIterator() {
            if (!root) {
                throw CustomException("Невозможно создать итератор для пустого BinaryTree");
            }
            return make_unique<InOrderIterator>(root.get());
        }

        unique_ptr<IteratorInterface> getLevelOrderIterator() {
            if (!root) {
                throw CustomException("Невозможно создать итератор для пустого BinaryTree");
            }
            return make_unique<LevelOrderIterator>(root.get());
        }
    };
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    using namespace containers;

    try {
        BinaryTree<int> tree = {10, 5, 15, 3, 7, 12, 18};

        cout << "InOrder Traversal:" << endl;
        auto inOrderIt = tree.getInOrderIterator();
        while (inOrderIt->hasNext()) {
            cout << inOrderIt->next() << " ";
        }
        cout << endl;

        cout << "LevelOrder Traversal:" << endl;
        auto levelOrderIt = tree.getLevelOrderIterator();
        while (levelOrderIt->hasNext()) {
            cout << levelOrderIt->next() << " ";
        }
        cout << endl;

    } catch (const CustomException& e) {
        cerr << "CustomException: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
