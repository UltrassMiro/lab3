#pragma once
#include "DataProvider.h"
#include <fstream>
using namespace std;

class BinaryProvider : public DataProvider {
public:
    void Save(const vector<Student>& data, const string& filename) override {
        ofstream f(filename, ios::binary);
        if (!f) throw std::runtime_error("Cannot open file for writing: " + filename);
        uint32_t count = static_cast<uint32_t>(data.size());
        f.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& s : data) s.WriteBinary(f);
    }

    vector<Student> Load(const string& filename) override {
        ifstream f(filename, ios::binary);
        if (!f) throw runtime_error("Cannot open file for reading: " + filename);
        uint32_t count = 0;
        f.read(reinterpret_cast<char*>(&count), sizeof(count));
        vector<Student> out;
        for (uint32_t i = 0; i < count; ++i) {
            out.push_back(Student::ReadBinary(f));
        }
        return out;
    }
};
