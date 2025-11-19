#pragma once
#include "Student.h"

class SoftwareDeveloper : public Student {
public:
    bool knowsCPlusPlus = false;

    SoftwareDeveloper() = default;

    SoftwareDeveloper(const Student& s, bool knows)
        : Student(s), knowsCPlusPlus(knows) {}
};
