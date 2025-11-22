#pragma once
#include "Student.h"

class SoftwareDeveloper : public Student {
public:
    bool knowsCPlusPlus = false;
    SoftwareDeveloper() = default;
    SoftwareDeveloper(const Student& s, bool knows) : Student(s), knowsCPlusPlus(knows) {}
    void LearnOnline(bool internetAvailable) override {
        if (internetAvailable) cout << firstName << " (Developer) is learning online.\n";
    }
};
