#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    vector<double> temps = {8.5, 12.0, 21.3, 18.7, 5.2, 23.8, 15.6};

    for (size_t i = 0; i < days.size(); i++) {
        cout << days[i] << ": " << temps[i] << "°C" << endl;
    }
    return 0;
}
