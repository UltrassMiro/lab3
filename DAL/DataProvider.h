#pragma once
#include <vector>
#include "Student.h"
using namespace std;

class DataProvider {
public:
    virtual void Save(const vector<Student>& data, const string& filename) = 0;
    virtual vector<Student> Load(const string& filename) = 0;
    virtual ~DataProvider() = default;
};
