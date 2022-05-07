#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream
#include <vector>

// подключаем вашу структуру данных
#include "quick_sort.hpp"

using namespace std;
using namespace itis;

// константы всякие
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};
static constexpr auto kTrialsCount = 10;
static constexpr auto kMethodsNamesList = {"Sort"};
static constexpr auto kDatasetNamesList = {"01", "02", "03", "04", "05"};
static constexpr auto kDatasetCountsList = {"100", "500", "1000", "5000", "10000", "50000", "100000", "500000", "1000000"};

vector<int> createVectorFromCSV(string &path) {
    fstream fin;
    fin.open(path, ios::in);

    string temp;
    fin >> temp;
    istringstream ss(temp);

    string token;
    vector<int> numbers;

    while (getline(ss, token, ',')) {
        numbers.push_back(stoi(token));
    }
    return numbers;
}

void Sorting_benchmark(vector<int>& arr) {
    QuickSort quickSort;
    const auto time_point_before = chrono::steady_clock::now();

    quickSort.Sort(arr);

    const auto time_point_after = chrono::steady_clock::now();

    const auto time_diff = time_point_after - time_point_before;
    const auto time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
    cout << "Time elapsed (ns): " << time_elapsed_ns << '\n';
}

int main() {
    const auto path = string(kDatasetPath);
    cout << "Path to the 'dataset/' folder: " << path << endl;

    for (string method: kMethodsNamesList) {
        for (string dataset_name: kDatasetNamesList) {
            for (string count: kDatasetCountsList) {
                for (int trial = 1; trial < kTrialsCount + 1; trial++) {
                    string path_to_csv = path + "/" + method + "/" + dataset_name + "/" + count + ".csv";
                    auto vect = createVectorFromCSV(path_to_csv);
                    cout << "Method-" << method << " dataset-" << dataset_name << " datacount-" << count << " trial-";
                    cout << trial << "\t";

                    Sorting_benchmark(vect);
                }
                cout << endl;
            }
        }
    }

    return 0;
}
