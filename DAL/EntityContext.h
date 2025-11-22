#pragma once
#include <vector>
#include <string>
#include "DataProvider.h"
using namespace std;

class EntityContext {
private:
    DataProvider* provider; // не володіє

public:

    EntityContext(DataProvider* dp) : provider(dp) {
        if (!provider) throw std::runtime_error("EntityContext: provider is null");
    }

    virtual void SaveAll(const vector<Student>& data, const string& filename);
    virtual vector<Student> LoadAll(const string& filename);
};
