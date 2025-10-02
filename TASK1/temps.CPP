#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double> temps = {8.5, 12.0, 21.3, 18.7, 5.2, 23.8, 15.6};
    for (double t : temps) {
        cout << t << " ";
    }
    cout << endl;
    return 0;
}
