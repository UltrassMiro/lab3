// CustomProvider.h
#pragma once
#include "DataProvider.h"
#include <fstream>
using namespace std;

class CustomProvider : public DataProvider {
public:
    void Save(const std::vector<Student>& data, const std::string& filename) override {
        std::ofstream f(filename);
        if (!f) throw std::runtime_error("Cannot open file for writing: " + filename);
        // header
        f << "lastName,firstName,height,weight,studentID,passportSeries,passportNumber\n";
        for (const auto& s : data) f << s.ToCSVLine() << "\n";
    }

    std::vector<Student> Load(const std::string& filename) override {
        std::ifstream f(filename);
        if (!f) throw std::runtime_error("Cannot open file for reading: " + filename);
        std::vector<Student> out;
        std::string line;
        bool first = true;
        while (std::getline(f, line)) {
            if (first) { first = false; continue; } // skip header
            if (line.empty()) continue;
            out.push_back(Student::FromCSVLine(line));
        }
        return out;
    }
};
