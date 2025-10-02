#include <iostream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    vector<double> temps = {8.5, 12.0, 21.3, 18.7, 5.2, 23.8, 15.6};

    tuple<string, double> warmest = make_tuple(days[0], temps[0]);

    for (size_t i = 1; i < days.size(); i++) {
        if (temps[i] > get<1>(warmest)) {
            warmest = make_tuple(days[i], temps[i]);
        }
    }

    cout << "Warmest day: " << get<0>(warmest) << " with " << get<1>(warmest) << "°C" << endl;
    return 0;
}
