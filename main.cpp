#include <iostream>

#include "quick_sort.hpp"

using namespace std;
using namespace itis;

int main() {
    std::vector<int> arr = {5,4,3,2,1};

    QuickSort sort;
    sort.Sort(arr);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
}
