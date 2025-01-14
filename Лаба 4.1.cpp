#include <iostream>
#include <iomanip>

using namespace std;


ostream& message(ostream& os) {
    return os << "Результат:";
}


ostream& hex_with_fill(ostream& os) {
    os << hex << setfill('$');
    return os;
}

int main() {
    int number = 255;
    cout << message << endl;
    cout << hex_with_fill << setw(10) << number << endl;
    return 0;
}
