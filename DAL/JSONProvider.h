#pragma once
#include "DataProvider.h"
#include <fstream>
#include <sstream>

using namespace std;

class JSONProvider : public DataProvider {
public:
    void Save(const vector<Student>& data, const string& filename) override;
    vector<Student> Load(const string& filename) override;
};
