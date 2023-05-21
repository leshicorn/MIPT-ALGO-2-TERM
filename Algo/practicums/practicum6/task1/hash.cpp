#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <functional>
#include <unordered_map>
#include <cstring>
#include <zlib.h>

// Хэш-функция для целых чисел: Остаток от деления на 1000
unsigned int hashIntegerModulo(unsigned int key) {
    return key % 1000;
}

// Хэш-функция для целых чисел: Битовое представление в unsigned
unsigned int hashIntegerBitwise(unsigned int key) {
    return static_cast<unsigned int>(key);
}

// Хэш-функция для целых чисел: Мультипликативная
unsigned int hashIntegerMultiplicative(unsigned int key) {
    const double A = 0.6180339887;  // Константа "золотого сечения"
    return static_cast<unsigned int>(1000 * (key * A - static_cast<unsigned int>(key * A)));
}

// Хэш-функция для чисел с плавающей точкой: (int) битовое представление в unsigned
unsigned int hashFloatToIntBitwise(float key) {
    unsigned int hash;
    std::memcpy(&hash, &key, sizeof(key));
    return hash;
}

// Хэш-функция для строк: Длина строки
unsigned int hashStringLength(const std::string& key) {
    return static_cast<unsigned int>(key.length());
}

// Хэш-функция для строк: Сумма букв
unsigned int hashStringSum(const std::string& key) {
    unsigned int sum = 0;
    for (char c : key) {
        sum += static_cast<unsigned int>(c);
    }
    return sum;
}

// Хэш-функция для строк: Полиномиальный
unsigned int hashStringPolynomial(const std::string& key) {
    const unsigned int P = 31;  // Простое число
    unsigned int hash = 0;
    unsigned int power = 1;
    for (char c : key) {
        hash += (static_cast<unsigned int>(c) - 'a' + 1) * power;
        power *= P;
    }
    return hash;
}

// Хэш-функция для строк: crc32
unsigned int hashStringCRC32(const std::string& key) {
    unsigned int hash = crc32(0L, Z_NULL, 0);
    hash = crc32(hash, reinterpret_cast<const Bytef*>(key.c_str()), key.length());
    return hash;
}

int main() {
    const int numKeys = 1000000;
    const std::string outputFileName = "hash_collisions.txt";

    std::random_device rd;
    std::mt19937 rng(rd());

    // Генерация случайных целых чисел
    std::uniform_int_distribution<unsigned int> intDistribution(1, std::numeric_limits<unsigned int>::max());
    std::vector<unsigned int> intKeys(numKeys);
    for (int i = 0; i < numKeys; ++i) {
        intKeys[i] = intDistribution(rng);
    }

    // Генерация случайных чисел с плавающей точкой
    std::uniform_real_distribution<float> floatDistribution(1.0f, std::numeric_limits<float>::max());
    std::vector<float> floatKeys(numKeys);
    for (int i = 0; i < numKeys; ++i) {
        floatKeys[i] = floatDistribution(rng);
    }

    // Генерация случайных строк
    std::uniform_int_distribution<int> stringLengthDistribution(1, 100);
    std::uniform_int_distribution<char> charDistribution('a', 'z');
    std::vector<std::string> stringKeys(numKeys);
    for (int i = 0; i < numKeys; ++i) {
        int length = stringLengthDistribution(rng);
        std::string str;
        for (int j = 0; j < length; ++j) {
            str += charDistribution(rng);
        }
        stringKeys[i] = str;
    }

    std::unordered_map<unsigned int, int> collisions;  // Хранит количество коллизий для каждого хэша

    // Вычисление коллизий для хэш-функций целых чисел
    for (unsigned int key : intKeys) {
        unsigned int hashModulo = hashIntegerModulo(key);
        collisions[hashModulo]++;
        unsigned int hashBitwise = hashIntegerBitwise(key);
        collisions[hashBitwise]++;
        unsigned int hashMultiplicative = hashIntegerMultiplicative(key);
        collisions[hashMultiplicative]++;
    }

    // Вычисление коллизий для хэш-функции чисел с плавающей точкой
    for (float key : floatKeys) {
        unsigned int hashFloat = hashFloatToIntBitwise(key);
        collisions[hashFloat]++;
    }

    // Вычисление коллизий для хэш-функций строк
    for (const std::string& key : stringKeys) {
        unsigned int hashLength = hashStringLength(key);
        collisions[hashLength]++;
        unsigned int hashSum = hashStringSum(key);
        collisions[hashSum]++;
        unsigned int hashPolynomial = hashStringPolynomial(key);
        collisions[hashPolynomial]++;
        unsigned int hashCRC32 = hashStringCRC32(key);
        collisions[hashCRC32]++;
    }

    // Запись данных о коллизиях в файл
    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        for (const auto& entry : collisions) {
            outputFile << entry.first << " " << entry.second << "\n";
        }
        outputFile.close();
        std::cout << "Данные о коллизиях записаны в файл: " << outputFileName << std::endl;
    } else {
        std::cerr << "Ошибка при открытии файла: " << outputFileName << std::endl;
    }

    return 0;
}
