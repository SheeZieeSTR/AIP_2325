#include <iostream>
#include <iomanip>

void printRussianAlphabetCodes() {
    
    const wchar_t lowercase_start = L'а'; 
    const wchar_t lowercase_end = L'я';   
    const wchar_t uppercase_start = L'А'; 
    const wchar_t uppercase_end = L'Я';   

    std::wcout << std::setw(10) << L"Symbol"
               << std::setw(15) << L"Hex Code"
               << std::setw(15) << L"Octal Code" << std::endl;
    std::wcout << std::wstring(40, L'-') << std::endl;

    for (wchar_t c = uppercase_start; c <= uppercase_end; ++c) {
        std::wcout << std::setw(10) << c
                   << std::setw(15) << std::hex << std::showbase << (int)c
                   << std::setw(15) << std::oct << std::showbase << (int)c << std::endl;
    }

    std::wcout << std::endl;

    for (wchar_t c = lowercase_start; c <= lowercase_end; ++c) {
        std::wcout << std::setw(10) << c
                   << std::setw(15) << std::hex << std::showbase << (int)c
                   << std::setw(15) << std::oct << std::showbase << (int)c << std::endl;
    }
}

int main() {
    
    std::locale::global(std::locale("ru_RU.utf8"));
    std::wcout.imbue(std::locale());

    printRussianAlphabetCodes();

    return 0;
}
