#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "Lab35/DAL/Student.h"
#include "Lab35/DAL/Librarian.h"
#include "Lab35/DAL/SoftwareDeveloper.h"

using namespace std;

class CoutGuard {
    streambuf* old;
    ostringstream ss;
public:
    CoutGuard() { old = cout.rdbuf(ss.rdbuf()); }
    ~CoutGuard() { cout.rdbuf(old); }
    string str() const { return ss.str(); }
};

TEST(Student_JsonRoundtrip, JsonRoundtrip) {
    Student s1("Doe", "John", 180, 70, "ST1", "AA", "111");

    string json = s1.ToJSON();
    Student s2 = Student::FromJSON(json);

    EXPECT_EQ(s1.lastName, s2.lastName);
    EXPECT_EQ(s1.firstName, s2.firstName);
    EXPECT_EQ(s1.height, s2.height);
    EXPECT_EQ(s1.weight, s2.weight);
    EXPECT_EQ(s1.studentID, s2.studentID);
    EXPECT_EQ(s1.passportSeries, s2.passportSeries);
    EXPECT_EQ(s1.passportNumber, s2.passportNumber);
}

TEST(Student_Binary_Roundtrip, BinaryRoundtrip) {
    Student s1("Binary", "Bob", 190, 80, "ST3", "CC", "333");

    string fname = "tmp_student.bin";
    {
        ofstream ofs(fname, ios::binary);
        ASSERT_TRUE(ofs.good());
        s1.WriteBinary(ofs);
    }
    Student s2;
    {
        ifstream ifs(fname, ios::binary);
        ASSERT_TRUE(ifs.good());
        s2 = Student::ReadBinary(ifs);
    }

    EXPECT_EQ(s1.lastName, s2.lastName);
    EXPECT_EQ(s1.firstName, s2.firstName);
    EXPECT_EQ(s1.height, s2.height);
    EXPECT_EQ(s1.weight, s2.weight);
    EXPECT_EQ(s1.studentID, s2.studentID);
    EXPECT_EQ(s1.passportSeries, s2.passportSeries);
    EXPECT_EQ(s1.passportNumber, s2.passportNumber);

    remove(fname.c_str());
}

TEST(Student_IsIdealWeight, TrueAndFalse) {
    Student s1("A","B",170,60,"","","");
    Student s2("C","D",180,65,"","","");
    EXPECT_TRUE(s1.IsIdealWeight());
    EXPECT_FALSE(s2.IsIdealWeight());
}

TEST(Student_LearnOnline_Virtual, DerivedBehavior) {
    Student base("x","y",0,0,"","","");

    Librarian lib(base, true);
    SoftwareDeveloper dev(base, true);

    CoutGuard g;
    lib.LearnOnline(true);
    dev.LearnOnline(true);

    string out = g.str();

    EXPECT_NE(out.find("(Librarian) is learning online."), string::npos);
    EXPECT_NE(out.find("(Developer) is learning online."), string::npos);
}
