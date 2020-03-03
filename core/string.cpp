#include "core/string.h"

namespace core {

bool String::Compare(const Char* left, const Char* right) {
    if (left == right)
        return true;

    while ((*left != '\0') && (*right != '\0')) {
        if (*left != *right)
            return false;
        left++;
        right++;
    }

    return true;
}

}  // namespace core