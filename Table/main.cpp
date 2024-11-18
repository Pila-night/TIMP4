#include "modTableCipher.h"

#include <iostream>
#include <limits>
#include <locale>
#include <string>


using namespace std;

void check(const wstring& Text, const int& key, const bool destructCipherText = false) {
    try {
        wstring cipherText;
        wstring decryptedText;
        TableCipher cipher(key, Text); 
        cipherText = cipher.encrypt(Text); 
        if(destructCipherText) {
            cipherText.front() = towlower(cipherText.front());
        }
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"Ключ = " << key << endl;
        wcout << L"Введенный текст: " << Text << endl;
        wcout << L"Зашифрованный текст: " << cipherText << endl;
        wcout << L"Расшифрованный текст: " << decryptedText << endl;

    } catch(const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);

    wcout << L"==============================" << endl;
    wcout << L"     Тестирование шифрования   " << endl;
    wcout << L"==============================" << endl << endl;

    wcout << L"Проверка на ключ:" << endl;
    check(L"Высоко в горы вполз Уж и лег там в сыром ущелье, свернувшись в узел и глядя в море.", -5); // проверка на ключ
    wcout << endl;

    wcout << L"Проверка на преобразование:" << endl;
    check(L"Высоко в горы вполз Уж и лег там в сыром ущелье, свернувшись в узел и глядя в море.", 8);
    wcout << endl;
    
    wcout << L"Тут показан пример того, что после фильтрации текста ничего не осталось:" << endl;
    check(L"123242532452345342343", 8);
    wcout << endl;

    wcout << L"Проверка на неправильный шифрованный текст:" << endl;
    check(L"Высоко в горы вполз Уж и лег там в сыром ущелье, свернувшись в узел и глядя в море.", 8, true);
    wcout << endl;

    wcout << L"==============================" << endl;
    wcout << L"     Тестирование завершено" << endl;
    wcout << L"==============================" << endl;

    return 0;
}
