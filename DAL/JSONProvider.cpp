#include "JSONProvider.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void JSONProvider::Save(const vector<Student>& data, const string& filename) {
    ofstream f(filename);
    if (!f) throw runtime_error("JSONProvider: cannot open file for writing: " + filename);
    f << "[\n";
    for (size_t i = 0; i < data.size(); ++i) {
        f << "  " << data[i].ToJSON();
        if (i + 1 < data.size()) f << ",";
        f << "\n";
    }
    f << "]\n";
    f.close();
}

vector<Student> JSONProvider::Load(const string& filename) {
    ifstream f(filename);
    if (!f) throw runtime_error("JSONProvider: cannot open file for reading: " + filename);
    string all;
    {
        stringstream ss;
        ss << f.rdbuf();
        all = ss.str();
    }
    vector<Student> out;
    size_t pos = 0;
    while (true) {
        size_t l = all.find('{', pos);
        if (l == string::npos) break;
        size_t r = all.find('}', l);
        if (r == string::npos) break;
        string obj = all.substr(l, r - l + 1);
        out.push_back(Student::FromJSON(obj));
        pos = r + 1;
    }
    return out;
}
