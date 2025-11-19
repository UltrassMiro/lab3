#include "StudentService.h"

StudentService::StudentService(EntityContext* c) : ctx(c) {
    if (!ctx) throw DomainException("StudentService: context is null");
}

void StudentService::AddStudent(vector<Student>& list, const Student& s) {
    list.push_back(s);
}

int StudentService::CountIdealWeight(const vector<Student>& list) const {
    int count = 0;
    for (const auto& s : list) if (s.IsIdealWeight()) ++count;
    return count;
}

vector<Student> StudentService::GetStudentsWithIdealWeight(const vector<Student>& list) const {
    vector<Student> out;
    for (const auto& s : list) if (s.IsIdealWeight()) out.push_back(s);
    return out;
}

void StudentService::Save(const vector<Student>& list, const string& filename) {
    ctx->SaveAll(list, filename);
}

vector<Student> StudentService::Load(const string& filename) {
    return ctx->LoadAll(filename);
}
