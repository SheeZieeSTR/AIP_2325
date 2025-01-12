#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    
    double y;
    
    for(double t = 0; t <= 3; t += 0.5){
        y = cos(t);
        
        cout << setw(10) << setfill(' ') << setprecision(3) << y << endl;
    }
    
    return 0;
}
