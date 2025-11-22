#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Lab35/BLL/StudentService.h"
#include "Lab35/DAL/EntityContext.h"

using ::testing::Return;
using ::testing::_;

// Mock DataProvider
class MockDataProvider : public DataProvider {
public:
    MOCK_METHOD(void, Save, (const vector<Student>&, const string&), (override));
    MOCK_METHOD(vector<Student>, Load, (const string&), (override));
};

// Mock EntityContext – робимо proxy до MockDataProvider
class MockEntityContext : public EntityContext {
public:
    MockDataProvider* dp;

    explicit MockEntityContext(MockDataProvider* provider)
        : EntityContext(provider), dp(provider) {}

    void SaveAll(const vector<Student>& data, const string& filename) override {
        dp->Save(data, filename);
    }

    vector<Student> LoadAll(const string& filename) override {
        return dp->Load(filename);
    }
};


TEST(StudentService_CountAndFilter, Basic) {
    MockDataProvider dp;
    MockEntityContext ctx(&dp);
    StudentService svc(&ctx);

    vector<Student> list = {
        {"A","a",170,60,"","",""},
        {"B","b",180,70,"","",""},
        {"C","c",160,50,"","",""}
    };

    EXPECT_EQ(svc.CountIdealWeight(list), 3);
    auto ideal = svc.GetStudentsWithIdealWeight(list);
    EXPECT_EQ(ideal.size(), 3);
}

TEST(StudentService_SaveLoad_WithDI_Mock, SaveLoad) {
    MockDataProvider dp;
    MockEntityContext ctx(&dp);
    StudentService svc(&ctx);

    vector<Student> list = {{"X","x",170,60,"","",""}};

    EXPECT_CALL(dp, Save(list, "f.txt")).Times(1);
    svc.Save(list, "f.txt");

    EXPECT_CALL(dp, Load("f.txt")).Times(1).WillOnce(Return(list));
    auto loaded = svc.Load("f.txt");

    EXPECT_EQ(loaded.size(), 1);
}

TEST(StudentService_AdjustWeight_Callback, CallbackCalled) {
    MockDataProvider dp;
    MockEntityContext ctx(&dp);
    StudentService svc(&ctx);

    Student s("P","p",170,60,"","","");
    bool called = false;

    svc.AdjustWeight(s, 5, [&](const Student& st){
        called = true;
        EXPECT_EQ(st.weight, 65);
    });

    EXPECT_TRUE(called);
}
