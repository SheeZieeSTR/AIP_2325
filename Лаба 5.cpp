#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Класс NameClass с итератором
template <typename T>
class NameClass {
public:
    // Вложенный итератор
    class Iterator {
    public:
        Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() { return *ptr; }
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

    private:
        T* ptr;
    };

    void add(const T& value) {
        values.push_back(value);
    }

    void sortValues() {
        sort(values.begin(), values.end());
    }

    Iterator find(const T& value) {
        auto it = std::find(values.begin(), values.end(), value);
        return Iterator(it != values.end() ? &(*it) : nullptr);
    }

    Iterator begin() {
        return Iterator(values.data());
    }

    Iterator end() {
        return Iterator(values.data() + values.size());
    }

    void displayAll() {
        for (const T& value : values) {
            cout << value << " ";
        }
        cout << endl;
    }

private:
    vector<T> values;
};

// Функция отображения меню
void displayMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Insert a value\n";
    cout << "2. Display all values\n";
    cout << "3. Sort values\n";
    cout << "4. Find a value\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    NameClass<int> values;
    int choice = 0;

    while (choice != 5) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            values.add(value);
            break;
        }
        case 2: {
            cout << "All values: ";
            values.displayAll();
            break;
        }
        case 3: {
            values.sortValues();
            cout << "Values sorted." << endl;
            break;
        }
        case 4: {
            int value;
            cout << "Enter value to find: ";
            cin >> value;
            auto it = values.find(value);
            if (*it != *values.end()) {
                cout << "Value " << value << " found." << endl;
            } else {
                cout << "Value " << value << " not found." << endl;
            }
            break;
        }
        case 5:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
