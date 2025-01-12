#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

void generateInputFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Unable to open input file for writing");
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 100; ++i) {
        int randomNum = rand() % 101 - 50;
        outFile << randomNum << endl;
    }

    outFile.close();
}

void processFiles(const string& inputFilename, const string& outputFilename) {
    ifstream inFile(inputFilename);
    if (!inFile) {
        throw runtime_error("Unable to open input file for reading");
    }

    vector<int> numbers;
    int firstOdd = 0;
    bool foundFirstOdd = false;

    int number;
    while (inFile >> number) {
        numbers.push_back(number);
        if (!foundFirstOdd && abs(number) % 2 == 1) {
            firstOdd = number;
            foundFirstOdd = true;
        }
    }

    inFile.close();

    if (!foundFirstOdd) {
        throw runtime_error("No odd number found in the input file");
    }

    ofstream outFile(outputFilename);
    if (!outFile) {
        throw runtime_error("Unable to open output file for writing");
    }

    for (int num : numbers) {
        outFile << (num + firstOdd) << endl;
    }

    outFile.close();
}

int main() {
    const string inputFilename = "input.txt";
    const string outputFilename = "output.txt";

    try {
        generateInputFile(inputFilename);
        
        processFiles(inputFilename, outputFilename);

        cout << "Processing complete. Check '" << outputFilename << "' for results." << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
