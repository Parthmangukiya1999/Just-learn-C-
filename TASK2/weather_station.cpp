#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iomanip>
using namespace std;

template <typename T>
T computeAverage(const T* arr, size_t n) {
    if (n == 0) {
        throw runtime_error("Cannot compute average of zero elements");
    }
    T sum{};
    for (size_t i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

class WeatherStation {
private:
    string location;
    float* readings;
    size_t capacity;
    size_t count;

    void resize() {
        size_t newCap = capacity * 2;
        float* newArr = new float[newCap];
        for (size_t i = 0; i < count; i++) newArr[i] = readings[i];
        delete[] readings;
        readings = newArr;
        capacity = newCap;
    }

public:
    WeatherStation(const string& loc, size_t cap = 5)
        : location(loc), capacity(cap), count(0) {
        readings = new float[capacity];
    }

    ~WeatherStation() {
        delete[] readings;
    }

    void addReading(float value) {
        if (count == capacity) resize();
        readings[count++] = value;
    }

    void printReadings() const {
        cout << "Location: " << location << "\nReadings: ";
        for (size_t i = 0; i < count; i++) {
            cout << readings[i] << " ";
        }
        cout << "\n";
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) {
            throw runtime_error("Could not open file for writing: " + filename);
        }
        out << location << "\n";
        for (size_t i = 0; i < count; i++) {
            out << readings[i];
            if (i + 1 < count) out << ",";
        }
        out << "\n";
        out.close();
        cout << "Saved to file: " << filename << "\n";
    }

    static WeatherStation* loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            throw runtime_error("Could not open file for reading: " + filename);
        }

        string loc;
        getline(in, loc);

        vector<float> vals;
        float value;
        char sep;
        while (in >> value) {
            vals.push_back(value);
            in >> sep; 
        }
        in.close();

        WeatherStation* ws = new WeatherStation(loc, vals.size() + 5);
        for (float v : vals) ws->addReading(v);
        return ws;
    }

    void sortReadings() {
        sort(readings, readings + count);
    }

    size_t countAbove(float threshold) const {
        return count_if(readings, readings + count,
                        [threshold](float x) { return x > threshold; });
    }

    float getAverage() const {
        return computeAverage(readings, count);
    }
};

int main() {
    try {
        WeatherStation ws("Lahti");

        ws.addReading(22.5);
        ws.addReading(24.0);
        ws.addReading(26.3);
        ws.addReading(21.8);
        ws.addReading(25.7);

        ws.printReadings();

        ws.sortReadings();

        cout << fixed << setprecision(2);
        cout << "Average: " << ws.getAverage() << "\n";
        cout << "Readings above 25°C: " << ws.countAbove(25.0f) << "\n";

        string filename = "lahti_readings.txt";
        ws.saveToFile(filename);

        WeatherStation* loaded = WeatherStation::loadFromFile(filename);
        cout << "\nReconstructed WeatherStation:\n";
        loaded->printReadings();
        delete loaded;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
