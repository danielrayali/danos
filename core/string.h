#pragma once

#include "core/types.h"

namespace core {

// TODO(dali) Implement deep copy
class String {
 public:
    String() = default;

    ~String() = default;

    // Returns true if both strings are equal, false otherwise
    static bool Compare(const Char* left, const Char* right);
};

}  // namespace core
