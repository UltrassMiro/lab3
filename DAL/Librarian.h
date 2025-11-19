#pragma once
#include "Student.h"

class Librarian : public Student {
public:
    bool knowsBookCatalog = false;

    Librarian() = default;

    Librarian(const Student& s, bool knows)
        : Student(s), knowsBookCatalog(knows) {}
};
