#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (const string &day : days) {
        cout << day << endl;
    }
    return 0;
}
