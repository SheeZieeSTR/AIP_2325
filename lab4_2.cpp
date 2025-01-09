#include <iostream> 
#include <fstream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 
 

    std::ofstream outFile(filename); 
    if (!outFile) { 
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl; 
        return; 
    } 
 
    std::srand(std::time(0)); // Инициализация генератора случайных чисел 
 
    for (int i = 0; i < 100; ++i) { 
        int number = std::rand() % 101 - 50; // Генерация случайного числа в диапазоне от -50 до +50 
        outFile << number << std::endl; 
    } 
 
    outFile.close(); 
} 
 
void processFiles(const std::string& inputFilename, const std::string& outputFilename) { 
    std::ifstream inFile(inputFilename); 
    std::ofstream outFile(outputFilename); 
 
    if (!inFile) { 
        std::cerr << "Ошибка при открытии файла для чтения: " << inputFilename << std::endl; 
        return; 
    } 
 
    if (!outFile) { 
        std::cerr << "Ошибка при открытии файла для записи: " << outputFilename << std::endl; 
        return; 
    } 
 
    std::vector<int> numbers; 
    int number; 
 
    while (inFile >> number) { 
        numbers.push_back(number); 
    } 
 
    if (numbers.empty()) { 
        std::cerr << "Файл пуст или не содержит корректных данных." << std::endl; 
        return; 
    } 
 
    int lastNumber = numbers.back(); 
 
    for (int num : numbers) { 
        outFile << num + lastNumber << std::endl; 
    } 
 
    inFile.close(); 
    outFile.close(); 
} 
 
int main() { 
    const std::string inputFilename = "input.txt"; 
    const std::string outputFilename = "output.txt"; 
 
    generateInputFile(inputFilename); 
    processFiles(inputFilename, outputFilename); 
 
    std::cout << "Файлы успешно обработаны." << std::endl; 
    return 0; 
}
