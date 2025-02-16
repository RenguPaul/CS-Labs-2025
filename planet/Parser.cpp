#include <fstream>
#include "Vector.hpp"
#include "planet.h"

namespace {
    const int kDefaultBufferSize = 1024;
    const int kDefaultReadSymbolsCount = 8;
}

void OpenFile(const char* name, Vector::VecChar& data) {
    std::ifstream file;
    file.open(name, std::ios::binary);
    char buffer[kDefaultBufferSize];
    while (!file.eof()) {
        file.read(buffer, kDefaultReadSymbolsCount);

        int symbols = static_cast<int>(file.gcount());
        for (int i = 0; i < symbols; ++i) {
            Vector::PushBack(data, buffer[i]);
        }
    }

    file.close();
    return;
}

[[nodiscard]] Vector::VecInt CreateKeys(const char* fileName, planet::Planet* data) {
    Vector::VecChar buffer = Vector::CreateCharVector();
    Vector::VecChar word = Vector::CreateCharVector();
    Vector::VecInt keysVector = Vector::CreateIntVector();

    OpenFile(fileName, buffer);
    int wordLength = 0;
    int key = 0;

    char** parametres = new char*[4];

    int dataType = 0;
    /*короч, добавь считывание по словам (datatype - тип данных в табличке) и запиши в массивчик с классами.*/
    for (int i = 0; i < static_cast<int>(buffer.size); ++i) {
        if (std::ispunct(buffer.vector[i]) || buffer.vector[i] == ' ' || buffer.vector[i] == '\n') {
            if (wordLength > 0) {
                Vector::PushBack(keysVector, key);
                wordLength = 0;
                key = 0;
            }

        } else {
            ++wordLength;
            key += static_cast<int>(buffer.vector[i]);
            Vector::PushBack(word, buffer.vector[i]);
        }
    }
    return {.size = keysVector.size, .vector = keysVector.vector};
}

int main() {
    return 0;
}
