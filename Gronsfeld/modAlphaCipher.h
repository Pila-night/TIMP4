/**
 * @file modAlphaCipher.h
 * @author Грачев В.В.
 * @version 1.0
 * @brief Описание класса modAlphaCipher
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */

#pragma once
#include <codecvt>
#include <cwctype>
#include <locale>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/** @brief Шифрование методом Гронсфельда
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для русского языка
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //!< Русский алфавит по порядку
    std::map<char, int> alphaNum; //!< Ассоциативный массив "номер по символу
    std::vector<int> key;         //!< Ключ для шифрования
    std::vector<int> convert(const std::wstring& s); //!< Преобразование "строка-вектор"
    std::wstring convert(const std::vector<int>& v); //!< Преобразование "вектор-строка"

    /**
     * @brief Валидация ключа
     * @throw cipher_error, если ключ пустой или в ключе находится символ не принадлежащий алфавиту
     */
    std::wstring getValidKey(const std::wstring& s);

    /**
     * @brief Метод валидации открытого текста.
     *
     * Эта функция принимает строку открытого текста в качестве входных данных и возвращает новую строку,
     * содержащую только буквы верхнего регистра из исходной строки.  Строка очищается от всех символов, отличных от
     * букв русского алфавита. Если результирующая строка пуста, выбрасывается исключение.
     *
     * @param ws Входная строка открытого текста.
     * @return std::wstring Строка,содержащая только буквы верхнего регистра.
     * @throw cipher_error Если строка пришла пустая или осталась пустой после валидации.
     */
    std::wstring getValidOpenText(const std::wstring& ws);

    /**
     * @brief  Валидация зашифрованного текста.
     *
     * Функция проверяет, что строка не пуста и содержит только символы прописных букв.
     *
     * @param ws Входная строка зашифрованного текста.
     * @return std::wstring Строка зашифрованного текста (копия входной строки), если она корректна.
     * @throw cipher_error Если строка пуста или содержит символы, отличные от прописных букв.
     */
    std::wstring getValidCipherText(const std::wstring& ws);

public:
    modAlphaCipher() = delete; //!< Конструктор по умолчанию запрещен.
    /**
     * @brief Конструктор для ключа.
     * @details Инициализирует алфавит, ассоциативный массив "номер по символу" и ключ.
     * @param skey Ключ для шифрования типа "wstring".
     */
    modAlphaCipher(const std::wstring& skey);

    /**
     * @brief Метод шифрования открытого текста методом Гронсфельда.
     * @param open_text Строка открытого текста для шифрования.
     * @return std::wstring Зашифрованный текст.
     * @throw cipher_error Если открытый текст некорректен (пустой или содержит недопустимые символы).
     */
    std::wstring encrypt(const std::wstring& open_text);
    /**
     * @brief Метод для расшифрования текса, зашифрованного методом Гронсфельда.
     * @param cipher_text Строка зашифрованного текста для расшифровки.
     * @return std::wstring  Расшифрованный текст.
     * @throw cipher_error Если зашифрованный текст некорректен (пустой или содержит недопустимые символы).
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};

/**
 * @class cipher_error
 * @brief Исключение для ошибок в классе modAlphaCipher.
 */

class cipher_error : public std::invalid_argument
{
public:
    /**
     * @brief Конструктор исключения с сообщением об.
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg)
    {
    }
    /**
     * @brief Конструктор исключения с сообщением об ошибке.
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg)
    {
    }
};
