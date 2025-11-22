#pragma once
#include <vector>
#include <string>
#include <functional>
#include "../DAL/Student.h"
#include "../DAL/EntityContext.h"
#include "DomainException.h"
using namespace std;

class StudentService {
private:
    EntityContext* ctx;

public:
    StudentService(EntityContext* c);

    void AddStudent(vector<Student>& list, const Student& s);
    int CountIdealWeight(const vector<Student>& list) const;
    vector<Student> GetStudentsWithIdealWeight(const vector<Student>& list) const;

    void Save(const vector<Student>& list, const string& filename);
    vector<Student> Load(const string& filename);

    void AdjustWeight(Student& s, int delta, function<void(const Student&)> callback = nullptr);
};
