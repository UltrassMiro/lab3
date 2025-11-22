#pragma once
#include "Student.h"

class Librarian : public Student {
public:
    bool knowsBookCatalog = false;
    Librarian() = default;
    Librarian(const Student& s, bool knows) : Student(s), knowsBookCatalog(knows) {}
    void LearnOnline(bool internetAvailable) override {
        if (internetAvailable) cout << firstName << " (Librarian) is learning online.\n";
    }
};
