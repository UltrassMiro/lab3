#include "PL/Menu.h"
#include <iostream>
using namespace std;

int main() {
    try {
        Menu::MainMenu();
    } catch (const exception& ex) {
        cerr << "Application error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
