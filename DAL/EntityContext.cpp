#include "EntityContext.h"

void EntityContext::SaveAll(const vector<Student>& data, const string& filename) {
    provider->Save(data, filename);
}

vector<Student> EntityContext::LoadAll(const string& filename) {
    return provider->Load(filename);
}
