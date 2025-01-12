#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

int main() {
    std::ofstream outfile("output.txt");
    if (!outfile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    outfile << std::fixed << std::setprecision(3);
    for (double t = 0; t <= 3; t += 0.5) {
        double cosValue = std::cos(t);
        double oddValue = std::ceil(std::abs(cosValue));
        if (static_cast<int>(oddValue) % 2 == 0) {
            oddValue += 1; // If even, add 1 to make it odd
        }
        outfile << std::setw(10) << cosValue << std::setw(10) << oddValue << std::endl;
    }

    outfile.close();
    return 0;
}
