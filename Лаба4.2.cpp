#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;


int generateRandomNumber() {
    return rand() % 101 - 50;  
}


double calculateAverage(const vector<int>& numbers) {
    double sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum / numbers.size();
}


void processFiles(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Ошибка при открытии файлов!" << endl;
        return;
    }

    vector<int> numbers;
    int num;

    
    while (inputFile >> num) {
        numbers.push_back(num);
    }

    
    double average = calculateAverage(numbers);

    
    for (int num : numbers) {
        if (num % 2 != 0) {  
            outputFile << num / average << endl;
        } else {
            outputFile << num << endl;
        }
    }
}

int main() {
    srand(time(0));  

    
    ofstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cout << "Ошибка при создании входного файла!" << endl;
        return 1;
    }

    for (int i = 0; i < 100; ++i) {
        inputFile << generateRandomNumber() << endl;
    }

    inputFile.close();

    
    processFiles("input.txt", "output.txt");

    cout << "Файлы обработаны!" << endl;

    return 0;
}