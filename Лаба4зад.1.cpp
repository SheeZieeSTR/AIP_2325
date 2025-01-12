#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	std::cout << std::fixed << std::setprecision(3);
	for (double t = 0; t <= 3; t += 0.5) {
		std::cout << std::setw(10) << std::cos(t) << std::endl;
	}
	return 0;
}
