#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void generateInputFile(const  string& filename) {
     ofstream outFile(filename);
    if (!outFile) {
         cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

     srand( time(nullptr));
    for (int i = 0; i < 100; ++i) {
        int randomNumber =  rand() % 101 - 50;
        outFile << randomNumber << "\n";
    }

    outFile.close();
}

void processFiles(const  string& inputFile, const  string& outputFile) {
     ifstream inFile(inputFile);
    if (!inFile) {
         cerr << "Failed to open input file: " << inputFile << "\n";
        return;
    }

     vector<int> numbers;
    int number;

    while (inFile >> number) {
        numbers.push_back(number);
    }
    inFile.close();

    if (numbers.empty()) {
         cerr << "The input file is empty.\n";
        return;
    }

    int maxNumber = * max_element(numbers.begin(), numbers.end());

     ofstream outFile(outputFile);
    if (!outFile) {
         cerr << "Failed to open file for writing: " << outputFile << "\n";
        return;
    }

    for (int num : numbers) {
        outFile << num - maxNumber << "\n";
    }

    outFile.close();
}

int main() {
    const  string inputFile = "input.txt";
    const  string outputFile = "output.txt";

    generateInputFile(inputFile);

    processFiles(inputFile, outputFile);

     cout << "Processing complete. Results written to file: " << outputFile << "\n";
    return 0;
}
