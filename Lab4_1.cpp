#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b, c;
    cout << "Введите коэффициенты квадратного уравнения (a, b, c): ";
    cin >> a >> b >> c;

    if (a == 0) {
        cout << "Это не квадратное уравнение, коэффициент 'a' не может быть равен 0." << endl;
        return 1;
    }

    double disck = b * b - 4 * a * c;
    cout << fixed << setprecision(4); 

    if (disck > 0) {
        double x1 = (-b + sqrt(disck)) / (2 * a);
        double x2 = (-b - sqrt(disck)) / (2 * a);
        cout << "Корни уравнения: "
            << setfill('#') << setw(10) << x1
            << " и " << setfill('#') << setw(10) << x2 << endl;
    }
    else if (disck == 0) {
        double x = -b / (2 * a);
        cout << "Уравнение имеет один корень: "
            << setfill('#') << setw(10) << x << endl;
    }
    else {
        cout << "Уравнение не имеет действительных корней." << endl;
    }
}
