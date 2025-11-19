#pragma once
#include "../DataProvider.h"
#include <fstream>
using namespace std;

class JSONProvider : public DataProvider {
public:
    void Save(const vector<Student>& data, const string& filename) override {
        ofstream file(filename);
        file << "[\n";
        for (size_t i = 0; i < data.size(); i++) {
            file << "  {\n";
            file << "    \"lastName\": \"" << data[i].lastName << "\",\n";
            file << "    \"firstName\": \"" << data[i].firstName << "\",\n";
            file << "    \"height\": " << data[i].height << ",\n";
            file << "    \"weight\": " << data[i].weight << ",\n";
            file << "    \"studentID\": \"" << data[i].studentID << "\",\n";
            file << "    \"passportSeries\": \"" << data[i].passportSeries << "\",\n";
            file << "    \"passportNumber\": \"" << data[i].passportNumber << "\"\n";
            file << "  }" << (i + 1 < data.size() ? "," : "") << "\n";
        }
        file << "]";
        file.close();
    }

    vector<Student> Load(const string& filename) override {
        // Щоб не ускладнювати: повертаємо порожній список
        return {};
    }
};
