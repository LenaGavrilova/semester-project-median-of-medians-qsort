#include <iostream>

#include "quick_sort.hpp"

using namespace std;
using namespace itis;

int main() {
    std::vector<int> arr = {3, 5, 7, 6, 1, 2, 4, 8};

    QuickSort sort;
    sort.Sort(arr);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
}
