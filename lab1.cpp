#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class CustomException : public exception {
private:
    string errorMessage;
    double errorValue;
    int errorCode;
    
public:
    CustomException(const string& message, double value, int code)
        : errorMessage(message), errorValue(value), errorCode(code) {}
    
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
    
    double getErrorValue() const{
        return errorValue;
    }
    
    int getErrorCode() const{
        return errorCode;
    }
};

double calcZ1(double& x) {
    if(pow(x,2) - 9 < 0) throw CustomException("Корень из отрицательного числа", x, 2);
    
    double verh = (x + 1) * sqrt(pow(x,2) - 9) + x * (x + 2) - 3;
    double niz = (x - 1) * sqrt(pow(x,2) - 9) + pow(x, 2) - 2 * x - 3;
    
    if(niz == 0) throw CustomException("Деление на 0", x, 1);
    
    double z1 = verh / niz;
    
    if(isnan(z1)) throw CustomException("NaN z1", z1, 3);
    
    return z1;
}

double calcZ2(double& x) {
    if((x + 3) / (x - 3) < 0) throw CustomException("Корень из отрицательного числа", x, 2);
    
    
    if(x - 3 == 0) throw CustomException("Деление на 0", x, 1);
    
    double z2 = sqrt((x + 3) / (x - 3));
    
    if(isnan(z2)) throw CustomException("NaN z1", z2, 3);
    
    return z2;
}

int main() {

    setlocale(LC_ALL, "Russian");
    
    double x;
    
    cout << "Введите x: ";
    cin >> x;
    
    try {
        double z1 = calcZ1(x);
        double z2 = calcZ2(x);
        
        cout << "z1 = " << z1 << endl;
        cout << "z2 = " << z2 << endl;
        
        if(z1 == z2) {
            cout << "z1 и z2 приблизительно равны" << endl;
        } else {
            cout << "z1 и z2 различны" << endl;
        }
    }
    
    catch (const CustomException& ex) {
        cerr << "Произошла ошибка: " << ex.what() << endl;
        cerr << "Значение, вызвавшее ошибку: " << ex.getErrorValue() << endl;
        cerr << "Код ошибки: " << ex.getErrorCode() << endl;
    }

    return 0;
}
