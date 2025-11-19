#pragma once
#include <iostream>
#include "../BLL/StudentService.h"
using namespace std;

class Menu {
public:
    static void MainMenu(StudentService& service) {
        vector<Student> arr;

        arr.push_back(Student("Ivanov", "Ivan", 180, 70, "ST1001", "AB", "123456"));
        arr.push_back(Student("Petrov", "Petr", 175, 65, "ST1002", "CD", "654321"));
        arr.push_back(Student("Sidorov", "Sidr", 170, 60, "ST1003", "EF", "111222"));

        service.Save(arr, "students.json");

        int idealCount = service.CountIdealWeight(arr);
        cout << "Ideal weight students: " << idealCount << endl;
    }
};
