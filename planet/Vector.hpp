// Vector.hpp

#pragma once

#include <cstddef>

namespace Vector {
struct VecInt {
    size_t size{};
    size_t capacity{};
    int* vector{};
};

struct VecChar {
    size_t size{};
    size_t capacity{};
    char* vector{};
};

[[nodiscard]] VecInt CreateIntVector();
[[nodiscard]] VecChar CreateCharVector();
void DeleteVector(VecInt& vector);
void DeleteCharVector(VecChar& vector);

[[nodiscard]] int& GetElement(VecInt& vector, size_t index);
[[nodiscard]] char& GetElement(VecChar& vector, size_t index);
[[nodiscard]] int GetElement(const VecInt& vector, size_t index);
[[nodiscard]] char GetElement(const VecChar& vector, size_t index);
void PushBack(VecInt& vector, int element);
void PushBack(VecChar& vector, char element);
}  // namespace Vector
