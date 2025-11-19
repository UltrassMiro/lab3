#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

class Student {
public:
    string lastName;
    string firstName;
    int height = 0;
    int weight = 0;
    string studentID;
    string passportSeries;
    string passportNumber;

    Student() = default;
    Student(const string& ln, const string& fn, int h, int w,
            const string& id, const string& ps, const string& pn)
        : lastName(ln), firstName(fn), height(h), weight(w),
          studentID(id), passportSeries(ps), passportNumber(pn) {}

    bool IsIdealWeight() const {
        return weight == height - 110;
    }

    string ToJSON() const {
        ostringstream ss;
        ss << "{";
        ss << "\"lastName\":\"" << EscapeJson(lastName) << "\",";
        ss << "\"firstName\":\"" << EscapeJson(firstName) << "\",";
        ss << "\"height\":" << height << ",";
        ss << "\"weight\":" << weight << ",";
        ss << "\"studentID\":\"" << EscapeJson(studentID) << "\",";
        ss << "\"passportSeries\":\"" << EscapeJson(passportSeries) << "\",";
        ss << "\"passportNumber\":\"" << EscapeJson(passportNumber) << "\"";
        ss << "}";
        return ss.str();
    }

    static Student FromJSON(const string& json) {
        Student s;
        auto getVal = [&](const string& key)->string {
            size_t pos = json.find("\"" + key + "\"");
            if (pos == string::npos) return "";
            pos = json.find(':', pos);
            if (pos == string::npos) return "";
            pos++;
            while (pos < json.size() && isspace((unsigned char)json[pos])) pos++;
            if (json[pos] == '"') {
                pos++;
                string out;
                while (pos < json.size() && json[pos] != '"') {
                    if (json[pos] == '\\' && pos + 1 < json.size()) {
                        pos++;
                        out.push_back(json[pos]);
                    } else out.push_back(json[pos]);
                    pos++;
                }
                return out;
            } else {
                string num;
                while (pos < json.size() && (json[pos] == '-' || isdigit((unsigned char)json[pos]))) {
                    num.push_back(json[pos++]);
                }
                return num;
            }
        };
        s.lastName = getVal("lastName");
        s.firstName = getVal("firstName");
        s.height = s.safeStoi(getVal("height"));
        s.weight = s.safeStoi(getVal("weight"));
        s.studentID = getVal("studentID");
        s.passportSeries = getVal("passportSeries");
        s.passportNumber = getVal("passportNumber");
        return s;
    }

    string ToCSVLine() const {

        ostringstream ss;
        ss << EscapeCsv(lastName) << "," << EscapeCsv(firstName) << "," << height << "," << weight << ","
           << EscapeCsv(studentID) << "," << EscapeCsv(passportSeries) << "," << EscapeCsv(passportNumber);
        return ss.str();
    }

    static Student FromCSVLine(const string& line) {
        Student s;
        vector<string> parts;
        string cur;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == ',') { parts.push_back(cur); cur.clear(); }
            else cur.push_back(c);
        }
        parts.push_back(cur);
        if (parts.size() >= 7) {
            s.lastName = UnescapeCsv(parts[0]);
            s.firstName = UnescapeCsv(parts[1]);
            s.height = s.safeStoi(parts[2]);
            s.weight = s.safeStoi(parts[3]);
            s.studentID = UnescapeCsv(parts[4]);
            s.passportSeries = UnescapeCsv(parts[5]);
            s.passportNumber = UnescapeCsv(parts[6]);
        }
        return s;
    }

    void WriteBinary(ostream& os) const {
        writeString(os, lastName);
        writeString(os, firstName);
        writeInt(os, height);
        writeInt(os, weight);
        writeString(os, studentID);
        writeString(os, passportSeries);
        writeString(os, passportNumber);
    }

    static Student ReadBinary(istream& is) {
        Student s;
        s.lastName = readString(is);
        s.firstName = readString(is);
        s.height = readInt(is);
        s.weight = readInt(is);
        s.studentID = readString(is);
        s.passportSeries = readString(is);
        s.passportNumber = readString(is);
        return s;
    }

private:
    static string EscapeJson(const string& in) {
        string out;
        for (char c : in) {
            if (c == '"') out += "\\\"";
            else if (c == '\\') out += "\\\\";
            else out += c;
        }
        return out;
    }

    static string EscapeCsv(const string& in) {

        string out = in;
        for (char &c : out) if (c == '\n' || c == '\r') c = ' ';
        return out;
    }

    static string UnescapeCsv(const string& in) {
        return in;
    }

    static void writeInt(ostream& os, int v) {
        os.write(reinterpret_cast<const char*>(&v), sizeof(v));
    }
    static int readInt(istream& is) {
        int v = 0; is.read(reinterpret_cast<char*>(&v), sizeof(v)); return v;
    }
    static void writeString(ostream& os, const string& s) {
        uint32_t len = static_cast<uint32_t>(s.size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len) os.write(s.data(), len);
    }
    static string readString(istream& is) {
        uint32_t len = 0;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        string s;
        if (len) {
            s.resize(len);
            is.read(&s[0], len);
        }
        return s;
    }

    int safeStoi(const string& s) {
        try { return stoi(s); } catch (...) { return 0; }
    }
};
