#include <iostream> 
#include <fstream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 
 
void prepareInputFile(const std::string& inputFileName) { 
    std::ofstream inputFile(inputFileName); 
    if (!inputFile) { 
        std::cerr << "Ошибка открытия входного файла!" << std::endl; 
        return; 
    } 
 
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
    for (int i = 0; i < 100; ++i) { 
        int randomNum = std::rand() % 101 - 50; 
        inputFile << randomNum << std::endl; 
    } 
 
    inputFile.close(); 
} 
 
void processInputFile(const std::string& inputFileName, const std::string& outputFileName) { 
    std::ifstream inputFile(inputFileName); 
    if (!inputFile) { 
        std::cerr << "Ошибка открытия входного файла!" << std::endl; 
        return; 
    } 
 
    std::ofstream outputFile(outputFileName); 
    if (!outputFile) { 
        std::cerr << "Ошибка открытия выходного файла!" << std::endl; 
        return; 
    } 
 
    int number; 
    int firstNegative = 0; 
    bool foundNegative = false; 
 
    while (inputFile >> number) { 
        if (number < 0 && !foundNegative) { 
            firstNegative = number; 
            foundNegative = true; 
        } 
    } 
 
    // Сбросим указатель на начало файла для повторного чтения 
    inputFile.clear(); 
    inputFile.seekg(0); 
 
    while (inputFile >> number) { 
        if (foundNegative && number % 2 == 0) { 
            outputFile << number * firstNegative << std::endl; 
        } else { 
            outputFile << number << std::endl; 
        } 
    } 
 
    inputFile.close(); 
    outputFile.close(); 
} 
 
int main() { 
    const std::string inputFileName = "input.txt"; 
    const std::string outputFileName = "output.txt"; 
 
    prepareInputFile(inputFileName); 
    processInputFile(inputFileName, outputFileName); 
 
    std::cout << "Входной файл и выходной файл успешно созданы." << std::endl; 
    return 0; 
}