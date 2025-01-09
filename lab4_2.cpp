#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;

// Функция для генерации входного файла с 100 случайными числами
void generateInputFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 101 - 50; // Генерация числа в диапазоне [-50, 50]
        outFile << randomNumber << endl;
    }

    outFile.close();
    cout << "Файл " << filename << " успешно создан." << endl;
}

// Функция для обработки чисел: замена нулей средним арифметическим
void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть входной файл: " << inputFilename << endl;
        return;
    }

    vector<int> numbers;
    int number;
    while (inFile >> number) {
        numbers.push_back(number);
    }
    inFile.close();

    // Вычисление среднего арифметического
    double sum = accumulate(numbers.begin(), numbers.end(), 0.0);
    double mean = sum / numbers.size();

    // Замена нулей на среднее арифметическое
    for (auto& num : numbers) {
        if (num == 0) {
            num = static_cast<int>(mean); // Приведение к целому числу
        }
    }

    // Запись в выходной файл
    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть выходной файл: " << outputFilename << endl;
        return;
    }

    for (const auto& num : numbers) {
        outFile << num << endl;
    }

    outFile.close();
    cout << "Файл " << outputFilename << " успешно создан." << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    const string inputFile = "input.txt";
    const string outputFile = "output.txt";

    generateInputFile(inputFile);  // Генерация входного файла
    processFile(inputFile, outputFile);  // Обработка файла

    return 0;
}
