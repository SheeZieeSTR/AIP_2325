#include <iostream>
#include <list>
#include <stdexcept>
#include <iterator>


class CustomException : public std::exception {
public:
    explicit CustomException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }

private:
    std::string message_;
};


template <typename T>
class Stack {
public:
    
    Stack() = default;

    
    Stack(std::initializer_list<T> init_list) : data_(init_list) {}

    
    Stack(const Stack& other) : data_(other.data_) {}

   
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }

    
    Stack(Stack&& other) noexcept : data_(std::move(other.data_)) {}

    
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }


    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (data_.empty()) {
            throw CustomException("Набор пуст");
        }
        data_.pop_back();
    }

    T& top() {
        if (data_.empty()) {
            throw CustomException("Набор пуст");
        }
        return data_.back();
    }

    size_t size() const {
        return data_.size();
    }

    bool empty() const {
        return data_.empty();
    }

   
    class Iterator {
    public:
        virtual bool hasNext() = 0;
        virtual T next() = 0;
        virtual ~Iterator() = default;
    };

    class PositiveIterator : public Iterator {
    public:
        explicit PositiveIterator(const std::list<T>& data) : it_(data.begin()), end_(data.end()) {
            moveToNextPositive();
        }

        bool hasNext() override {
            return it_ != end_;
        }

        T next() override {
            if (it_ == end_) {
                throw CustomException("Больше нету положиельных элементов");
            }
            T value = *it_;
            ++it_;
            moveToNextPositive();
            return value;
        }

    private:
        typename std::list<T>::const_iterator it_;
        typename std::list<T>::const_iterator end_;

        void moveToNextPositive() {
            while (it_ != end_ && *it_ <= 0) {
                ++it_;
            }
        }
    };

    class NegativeIterator : public Iterator {
    public:
        explicit NegativeIterator(const std::list<T>& data) : it_(data.begin()), end_(data.end()) {
            moveToNextNegative();
        }

        bool hasNext() override {
            return it_ != end_;
        }

        T next() override {
            if (it_ == end_) {
                throw CustomException("Больше нету положиельных элементов");
            }
            T value = *it_;
            ++it_;
            moveToNextNegative();
            return value;
        }

    private:
        typename std::list<T>::const_iterator it_;
        typename std::list<T>::const_iterator end_;

        void moveToNextNegative() {
            while (it_ != end_ && *it_ >= 0) {
                ++it_;
            }
        }
    };

   
    PositiveIterator getPositiveIterator() const {
        return PositiveIterator(data_);
    }

    NegativeIterator getNegativeIterator() const {
        return NegativeIterator(data_);
    }

private:
    std::list<T> data_; 
};

int main() {
    try {
        Stack<int> stack = {1, -2, 3, -4, 5, -6, 7, 0};

        std::cout << "Положительные элементы: ";
        auto positiveIterator = stack.getPositiveIterator();
        while (positiveIterator.hasNext()) {
            std::cout << positiveIterator.next() << " ";
        }
        std::cout << std::endl;

        std::cout << "Отрицательные элементы: ";
        auto negativeIterator = stack.getNegativeIterator();
        while (negativeIterator.hasNext()) {
            std::cout << negativeIterator.next() << " ";
        }
        std::cout << std::endl;

    } catch (const CustomException& e) {
        std::cerr << "CustomException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}