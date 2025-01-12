#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void prepareInputFile(const string& inputFileName) {
    ofstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Не удалось открыть файл для записи: " << inputFileName << endl;
        return;
    }

    srand(time(nullptr));
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 101 - 50; 
        inputFile << randomNumber << "\n";
    }

    inputFile.close();
}

void processFiles(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Не удалось открыть входной файл: " << inputFileName << endl;
        return;
    }

    vector<int> numbers;
    int number;
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    if (numbers.empty()) {
        cerr << "Файл пуст или содержит некорректные данные." << endl;
        return;
    }

    int minNumber = *min_element(numbers.begin(), numbers.end());

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Не удалось открыть выходной файл: " << outputFileName << endl;
        return;
    }

    for (const int& num : numbers) {
        outputFile << num * minNumber << "\n";
    }

    outputFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    string inputFileName = "input.txt";
    string outputFileName = "output.txt";

    prepareInputFile(inputFileName);

    processFiles(inputFileName, outputFileName);

    cout << "Обработка завершена. Результаты записаны в " << outputFileName << endl;

    return 0;
}
