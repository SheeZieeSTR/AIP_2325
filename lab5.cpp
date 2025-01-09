#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <string>

using namespace std;

// Исключение для пользовательских ошибок
class CustomException : public runtime_error {
public:
    explicit CustomException(const string& message) : runtime_error(message) {}
};

// Базовый интерфейс для итераторов
template <typename T>
class DequeIterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual ~DequeIterator() = default;
};

// Реализация одномерного динамического массива Vect
template <typename T>
class Vect {
public:
    Vect() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vect(initializer_list<T> init_list) : Vect() {
        for (const auto& item : init_list) {
            push_back(item);
        }
    }

    ~Vect() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize();
        }
        data_[size_++] = value;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw CustomException("Index out of bounds.");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw CustomException("Index out of bounds.");
        }
        return data_[index];
    }

    size_t size() const { return size_; }

    bool empty() const { return size_ == 0; }

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize() {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
};

// Реализация дека с использованием Vect
template <typename T>
class Deque {
public:
    Deque() = default;

    Deque(initializer_list<T> init_list) : deque_(init_list) {}

    void addFront(const T& value) {
        Vect<T> newDeque;
        newDeque.push_back(value);
        for (size_t i = 0; i < deque_.size(); ++i) {
            newDeque.push_back(deque_[i]);
        }
        deque_ = move(newDeque);
    }

    void addBack(const T& value) {
        deque_.push_back(value);
    }

    size_t size() const { return deque_.size(); }

    bool empty() const { return deque_.empty(); }

    // Forward declaration for iterators
    class FrontToBackIterator;
    class BackToFrontIterator;

    // Итератор для обхода дека спереди назад
    class FrontToBackIterator : public DequeIterator<T> {
    public:
        explicit FrontToBackIterator(const Vect<T>& deque) : deque_(deque), index_(0) {}

        bool hasNext() const override {
            return index_ < deque_.size();
        }

        T next() override {
            if (index_ >= deque_.size()) {
                throw CustomException("No more elements to iterate.");
            }
            return deque_[index_++];
        }

    private:
        const Vect<T>& deque_;
        size_t index_;
    };

    // Итератор для обхода дека сзади вперед
    class BackToFrontIterator : public DequeIterator<T> {
    public:
        explicit BackToFrontIterator(const Vect<T>& deque) : deque_(deque), index_(deque.size()) {}

        bool hasNext() const override {
            return index_ > 0;
        }

        T next() override {
            if (index_ == 0) {
                throw CustomException("No more elements to iterate.");
            }
            return deque_[--index_];
        }

    private:
        const Vect<T>& deque_;
        size_t index_;
    };

    FrontToBackIterator frontToBackIterator() const {
        return FrontToBackIterator(deque_);
    }

    BackToFrontIterator backToFrontIterator() const {
        return BackToFrontIterator(deque_);
    }

private:
    Vect<T> deque_;
};

class ExceptionHandling {
public:
    static void handle(const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
};

void displayMenu() {
    cout << "1. Добавить элемент в начало дека\n";
    cout << "2. Добавить элемент в конец дека\n";
    cout << "3. Показать все элементы дека (по порядку)\n";
    cout << "4. Показать все элементы дека (в обратном порядке)\n";
    cout << "5. Выйти\n";
    cout << "Введите ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    try {
        Deque<int> deque;
        int choice, value;

        while (true) {
            displayMenu();
            cin >> choice;

            if (choice == 5) break;

            switch (choice) {
            case 1:
                cout << "Введите значение для добавления в начало дека: ";
                cin >> value;
                deque.addFront(value);
                break;
            case 2:
                cout << "Введите значение для добавления в конец дека: ";
                cin >> value;
                deque.addBack(value);
                break;
            case 3:
                cout << "Элементы дека (спереди назад): ";
                for (auto it = deque.frontToBackIterator(); it.hasNext();) {
                    cout << it.next() << " ";
                }
                cout << endl;
                break;
            case 4:
                cout << "Элементы дека (сзади вперед): ";
                for (auto it = deque.backToFrontIterator(); it.hasNext();) {
                    cout << it.next() << " ";
                }
                cout << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }

    }
    catch (const exception& e) {
        ExceptionHandling::handle(e);
    }

    return 0;
}
