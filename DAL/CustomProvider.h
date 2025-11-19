#pragma once
#include "DataProvider.h"
#include <fstream>
using namespace std;

class CustomProvider : public DataProvider {
public:
    void Save(const vector<Student>& data, const string& filename) override {
        ofstream f(filename);
        if (!f) throw runtime_error("Cannot open file for writing: " + filename);

        f << "lastName,firstName,height,weight,studentID,passportSeries,passportNumber\n";
        for (const auto& s : data) f << s.ToCSVLine() << "\n";
    }

    vector<Student> Load(const string& filename) override {
        ifstream f(filename);
        if (!f) throw runtime_error("Cannot open file for reading: " + filename);
        vector<Student> out;
        string line;
        bool first = true;
        while (getline(f, line)) {
            if (first) { first = false; continue; }
            if (line.empty()) continue;
            out.push_back(Student::FromCSVLine(line));
        }
        return out;
    }
};
