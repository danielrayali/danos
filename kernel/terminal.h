#pragma once

namespace danos {

class Terminal {
 public:
    virtual void Print(const char* message) = 0;
};

}  // namespace danos
