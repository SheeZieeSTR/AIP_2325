#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Функция для генерации и записи случайных чисел в файл
void generate_input_file(const string& filename) {
    ofstream input_file(filename);
    
    if (!input_file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    
    srand(time(0));  // Инициализация генератора случайных чисел
    
    // Запись 100 случайных целых чисел от -50 до +50
    for (int i = 0; i < 100; ++i) {
        int random_number = rand() % 101 - 50;  // Генерация числа от -50 до 50
        input_file << random_number << endl;
    }
    
    input_file.close();
}

// Функция для преобразования чисел и записи в выходной файл
void transform_and_write_output_file(const string& input_filename, const string& output_filename) {
    ifstream input_file(input_filename);
    ofstream output_file(output_filename);
    
    if (!input_file || !output_file) {
        cerr << "Ошибка открытия файлов!" << endl;
        return;
    }
    
    vector<int> numbers;
    int num;
    
    // Чтение чисел из входного файла
    while (input_file >> num) {
        numbers.push_back(num);
    }
    
    // Найдем первое отрицательное число и 50-е число
    int first_negative = 0;
    int fiftieth = 0;
    
    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] < 0 && first_negative == 0) {
            first_negative = numbers[i];
        }
        if (i == 49) {
            fiftieth = numbers[i];
        }
    }
    
    if (first_negative == 0 || fiftieth == 0) {
        cerr << "Не удалось найти первое отрицательное или 50-е число!" << endl;
        return;
    }
    
    // Полусумма первого отрицательного числа и 50-го числа
    double half_sum = (first_negative + fiftieth) / 2.0;
    
    // Преобразование и запись чисел в выходной файл
    for (int i = 0; i < numbers.size(); ++i) {
        output_file << numbers[i] / half_sum << endl;
    }
    
    input_file.close();
    output_file.close();
}

int main() {
    string input_filename = "input.txt";
    string output_filename = "output.txt";
    
    // Генерация входного файла
    generate_input_file(input_filename);
    
    // Преобразование данных и запись в выходной файл
    transform_and_write_output_file(input_filename, output_filename);
    
    cout << "Программа завершена. Результаты записаны в файл " << output_filename << endl;
    
    return 0;
}
