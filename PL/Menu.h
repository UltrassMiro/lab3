#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <limits>

#include "../BLL/StudentService.h"
#include "../DAL/JSONProvider.h"
#include "../DAL/BinaryProvider.h"
#include "../DAL/CustomProvider.h"

using namespace std;

class Menu {
public:
    static void MainMenu() {
        cout << "Students:\n";
        cout << "Select provider:\n";
        cout << "1) JSON\n2) Binary\n3) Custom (CSV)\n";
        cout << "Choice: ";
        int choice = 1;
        if (!(cin >> choice)) choice = 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        unique_ptr<DataProvider> provider;
        switch (choice) {
            case 1: provider = make_unique<JSONProvider>(); break;
            case 2: provider = make_unique<BinaryProvider>(); break;
            case 3: provider = make_unique<CustomProvider>(); break;
            default: provider = make_unique<JSONProvider>(); break;
        }

        cout << "Enter filename (e.g. students.json): ";
        string filename;
        getline(cin, filename);
        if (filename.empty()) filename = (choice == 2 ? "students.bin" : (choice==3 ? "students.csv" : "students.json"));

        EntityContext ctx(provider.get());
        StudentService service(&ctx);

        vector<Student> arr;
        arr.emplace_back("Ivanov", "Ivan", 180, 70, "ST1001", "AB", "123456");
        arr.emplace_back("Petrov", "Petr", 175, 65, "ST1002", "CD", "654321");
        arr.emplace_back("Sidorov", "Sidr", 170, 60, "ST1003", "EF", "111222");
        arr.emplace_back("Ideal", "Ivan", 170, 60, "ST1004", "GH", "333444");

        try {
            service.Save(arr, filename);
            cout << "Saved " << arr.size() << " students to '" << filename << "'\n";
        } catch (const exception& ex) {
            cout << "Error while saving: " << ex.what() << "\n";
            return;
        }

        vector<Student> loaded;
        try {
            loaded = service.Load(filename);
            cout << "Loaded " << loaded.size() << " students from '" << filename << "'\n";
        } catch (const exception& ex) {
            cout << "Error while loading: " << ex.what() << "\n";
            return;
        }

        int idealCount = service.CountIdealWeight(loaded);
        cout << "Number of students with ideal weight: " << idealCount << "\n";

        auto idealStudents = service.GetStudentsWithIdealWeight(loaded);
        if (!idealStudents.empty()) {
            cout << "Students with ideal weight:\n";
            for (const auto& s : idealStudents) {
                cout << s.lastName << " " << s.firstName
                     << " (h=" << s.height << " w=" << s.weight << ")\n";
            }
        }
    }
};
