#include <iostream>
#include <initializer_list>
#include <string>
#include <limits>


using namespace std;

namespace containers {
	template <typename T>
	class List {
	public:
		struct Node {
			T value;
			Node* next;

			Node(const T& val) : value(val), next(nullptr) {}
		};

		List() : head(nullptr), size(0) {}

		List(initializer_list<T> initList) : head(nullptr), size(0) {
			for (const auto& val : initList) {
				push_back(val);
			}
		}

		List(const List& other) : head(nullptr), size(0) {
			copy(other.head);
		}

		List(List&& other) noexcept : head(other.head), size(other.size) {
			other.head = nullptr;
			other.size = 0;
		}

		List& operator=(const List& other) {
			if (this != &other) {
				clear();
				copy(other.head);
			}
			return *this;
		}

		List& operator=(List&& other) noexcept {
			if (this != &other) {
				clear();
				head = other.head;
				size = other.size;
				other.head = nullptr;
				other.size = 0;
			}
			return *this;
		}

		~List() { clear(); }

		void push_back(const T& value) {
			Node* newNode = new Node(value);
			if (!head) {
				head = newNode;
			}
			else {
				Node* current = head;
				while (current->next) {
					current = current->next;
				}
				current->next = newNode;
			}
			++size;
		}

		void remove(const T& value) {
			if (!head) return;

			if (head->value == value) {
				Node* temp = head;
				head = head->next;
				delete temp;
				--size;
				return;
			}

			Node* current = head;
			while (current->next && current->next->value != value) {
				current = current->next;
			}

			if (current->next) {
				Node* temp = current->next;
				current->next = current->next->next;
				delete temp;
				--size;
			}
		}

		void display() const {
			Node* current = head;
			while (current) {
				cout << current->value << " ";
				current = current->next;
			}
			cout << endl;
		}

	private:
		Node* head;
		size_t size;

		void clear() {
			while (head) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
			size = 0;
		}

		void copy(Node* node) {
			while (node) {
				push_back(node->value);
				node = node->next;
			}
		}
	};
}

void displayMenu() {
	cout << "\n--- Меню ---\n";
	cout << "1. Добавить элемент\n";
	cout << "2. Удалить элемент\n";
	cout << "3. Показать список\n";
	cout << "4. Изменить тип данных\n";
	cout << "5. Выход\n";
}

template <typename T>
void processList(containers::List<T>& list) {
	int choice;
	T value;

	while (true) {
		displayMenu();
		cout << "Выбор: ";
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Только числа\n";
			continue;
		}

switch (choice) {
case 1:
	cout << "Введите значение для добавления: ";
	cin >> value;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неправильный ввод.\n";
	}
	else {
		list.push_back(value);
	}
	break;
case 2:
	cout << "Введите значение для удаления: ";
	cin >> value;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неправильный ввод.\n";
	}
	else {
		list.remove(value);
	}
	break;
case 3:
	list.display();
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
			cout << "Пожалуйста, введите число.\n";
			continue;
		}

		switch (dataType) {
		case 1: {
			containers::List<int> list;
			processList(list);
			break;
		}
		case 2: {
			containers::List<double> list;
			processList(list);
			break;
		}
		case 3: {
			containers::List<string> list;
			processList(list);
			break;
		}
		case 4:
			return 0;
		default:
			cout << "Выбор между 1 и 4.\n";
		}
	}
}
