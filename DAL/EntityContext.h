#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "../DataProvider.h"
using namespace std;

class EntityContext {
private:
    DataProvider* provider;
public:
    EntityContext(DataProvider* dp) : provider(dp) {}

    void SaveAll(const vector<Student>& data, const string& filename) {
        provider->Save(data, filename);
    }

    vector<Student> LoadAll(const string& filename) {
        return provider->Load(filename);
    }
};
