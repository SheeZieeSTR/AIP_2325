#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void generateInputFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 100; ++i) {
        int number = rand() % 101 - 50;
        outFile << number << endl;
    }
    outFile.close();
}

void processNumbers(const string& inputFilename, const string& outputFilename) {
    ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть входной файл для чтения.\n";
        return;
    }

    vector<int> numbers;
    int number;
    while (inFile >> number) {
        numbers.push_back(number);
    }
    inFile.close();

    int firstNegative = 0, lastNegative = 0;
    bool foundFirst = false, foundLast = false;

    for (const int& num : numbers) {
        if (num < 0) {
            if (!foundFirst) {
                firstNegative = num;
                foundFirst = true;
            }
            lastNegative = num;
            foundLast = true;
        }
    }

    if (!foundFirst || !foundLast) {
        cerr << "Не удалось найти отрицательные числа.\n";
        return;
    }

    int multiplier = 2 * (firstNegative + lastNegative);

    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть выходной файл для записи.\n";
        return;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        if ((i + 1) % 3 == 0) {
            outFile << numbers[i] * multiplier << endl;
        } else {
            outFile << numbers[i] << endl;
        }
    }
    outFile.close();
}

int main() {
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    generateInputFile(inputFilename);
    processNumbers(inputFilename, outputFilename);

    cout << "Генерация и обработка завершены." << endl;
    return 0;
}
