#include <iostream>
#include <iomanip>

void printRussianAlphabetCodes() {
    // Unicode ranges for Russian alphabet
    const wchar_t lowercase_start = L'а'; // 'а'
    const wchar_t lowercase_end = L'я';   // 'я'
    const wchar_t uppercase_start = L'А'; // 'А'
    const wchar_t uppercase_end = L'Я';   // 'Я'

    // Print header
    std::wcout << std::setw(10) << L"Symbol"
               << std::setw(15) << L"Hex Code"
               << std::setw(15) << L"Octal Code" << std::endl;
    std::wcout << std::wstring(40, L'-') << std::endl;

    // Print uppercase letters
    for (wchar_t c = uppercase_start; c <= uppercase_end; ++c) {
        std::wcout << std::setw(10) << c
                   << std::setw(15) << std::hex << std::showbase << (int)c
                   << std::setw(15) << std::oct << std::showbase << (int)c << std::endl;
    }

    std::wcout << std::endl;

    // Print lowercase letters
    for (wchar_t c = lowercase_start; c <= lowercase_end; ++c) {
        std::wcout << std::setw(10) << c
                   << std::setw(15) << std::hex << std::showbase << (int)c
                   << std::setw(15) << std::oct << std::showbase << (int)c << std::endl;
    }
}

int main() {
    // Set locale to support wide characters
    std::locale::global(std::locale("ru_RU.utf8"));
    std::wcout.imbue(std::locale());

    // Print the Russian alphabet codes
    printRussianAlphabetCodes();

    return 0;
}
