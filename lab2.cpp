#include <iostream>
#include <set>
#include <initializer_list>
#include <limits>

using namespace std;

namespace containers {
    template <typename T>
    class MSet {
    public:

        MSet() = default;

        MSet(initializer_list<T> initList) {
            for (const auto& val : initList) {
                insert(val);
            }
        }


        void insert(const T& value) {
            elements.insert(value);
        }

        void remove(const T& value) {
            auto it = elements.find(value);
            if (it != elements.end()) {
                elements.erase(it);
            }
            else {
                cout << "Элемент не найден.\n";
            }
        }

        void display() const {
            if (elements.empty()) {
                cout << "Множество пусто.\n";
                return;
            }

            for (const auto& elem : elements) {
                cout << elem << " ";
            }
            cout << endl;
        }

        void clear() {
            elements.clear();
        }

    private:
        multiset<T> elements;
    };
}


template <typename T>
void processMSet(containers::MSet<T>& mset) {
    int choice;
    T value;

    while (true) {
        cout << "\n~~~ Меню ~~~\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Показать множество\n";
        cout << "4. Очистить множество\n";
        cout << "5. Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Пожалуйста, введите число.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите значение для добавления: ";
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректное значение.\n";
            }
            else {
                mset.insert(value);
            }
            break;
        case 2:
            cout << "Введите значение для удаления: ";
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректное значение.\n";
            }
            else {
                mset.remove(value);
            }
            break;
        case 3:
            mset.display();
            break;
        case 4:
            mset.clear();
            cout << "Множество очищено.\n";
            break;
        case 5:
            return;
        default:
            cout << "Некорректный выбор.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int dataType;

    while (true) {
        cout << "\nВыберите тип данных для множества:\n";
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
            containers::MSet<int> mset;
            processMSet(mset);
            break;
        }
        case 2: {
            containers::MSet<double> mset;
            processMSet(mset);
            break;
        }
        case 3: {
            containers::MSet<string> mset;
            processMSet(mset);
            break;
        }
        case 4:
            return 0;
        default:
            cout << "Выбор должен быть между 1 и 4.\n";
        }
    }
}
