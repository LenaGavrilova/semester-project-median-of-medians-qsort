#include "quick_sort.hpp"

#include <cassert>  // assert
#include <algorithm>

static constexpr auto kGroupSize = 10;

namespace itis {

    /* In case someone wants to pass in the pivValue, I broke partition into 2 pieces.
 */
    int pivot(std::vector<int> &vec, int pivot, int start, int end) {

        /* Now we need to go into the array with a starting left and right value. */
        int left = start, right = end - 1;
        while (left < right) {
            /* Increase the left and the right values until inappropriate value comes */
            while (vec.at(left) < pivot && left <= right) left++;
            while (vec.at(right) > pivot && right >= left) right--;

            /* In case of duplicate values, we must take care of this special case. */
            if (left >= right) break;
            else if (vec.at(left) == vec.at(right)) {
                left++;
                continue;
            }

            /* Do the normal swapping */
            int temp = vec.at(left);
            vec.at(left) = vec.at(right);
            vec.at(right) = temp;
        }
        return right;
    }


/* Returns the k-th element of this array. */
    int median_of_medians(std::vector<int> &vec, int k, int start, int end) {
        /* Start by base case: Sort if less than 10 size
         * E.x.: Size = 9, 9 - 0 = 9.
         */
        if (end - start < 10) {
            sort(vec.begin() + start, vec.begin() + end);
            return vec.at(k);
        }

        std::vector<int> medians;
        /* Now sort every consecutive 5 */
        for (int i = start; i < end; i += 5) {
            if (end - i < 10) {
                sort(vec.begin() + i, vec.begin() + end);
                medians.push_back(vec.at((i + end) / 2));
            } else {
                sort(vec.begin() + i, vec.begin() + i + 5);
                medians.push_back(vec.at(i + 2));
            }
        }

        int median = median_of_medians(medians, medians.size() / 2, 0, medians.size());

        /* use the median to pivot around */
        int piv = pivot(vec, median, start, end);
        int length = piv - start + 1;

        if (k < length) {
            return median_of_medians(vec, k, start, piv);
        } else if (k > length) {
            return median_of_medians(vec, k - length, piv + 1, end);
        } else
            return vec[k];
    }

    int partition(std::vector<int> &arr, int start, int stop, int pivot) {

        // Tips:
        // 1. Переместите опорный элемент в конец области (потом вернем на нужно место)
        // 2. Заведите переменную "индекс опорного элемента" = начало области (он будет обновляться)
        // 3. Пройдитесь в цикле по всем индексам (конец исключительно) и произведите разбиение,
        //    передвигая "индекс опорного элемента" в определенных случая вправо.
        // 4. По завершении цикла в "индексе опорного элемента" находится значение корректной позиции для опорного элемента,
        //    переместите опорный элемент на корректную позицию.

        // значение опорного элемента
        const int pivot_value = arr[pivot];

        // переместить опорный элемент в конец (чтобы не мешался)
        std::swap(arr[pivot], arr[stop]);

        // индекс опорного элемента (будет вычисляться далее, изначально находится в начале области)
        int curr_pivot_index = start;

        // вычисление индекса опорного элемента и перемещение элементов по правилу разбиения
        for (int index = start; index < stop; index++) {

            if (arr[index] < pivot_value) {
                std::swap(arr[index], arr[curr_pivot_index]);
                curr_pivot_index++;
            }
        }

        // разбиение завершилось, перемещаем выбранный опорный элемент на вычисленное ранее место
        std::swap(arr[curr_pivot_index], arr[stop]);

        // возвращаем индекс опорного элемента
        return curr_pivot_index;
    }


    void QuickSort::Sort(std::vector<int> &arr) const {
        quick_sort(arr, 0, static_cast<int>(arr.size()) - 1);
    }

    void QuickSort::quick_sort(std::vector<int> &arr, int start, int stop) const {
        assert(start >= 0);

        if (start >= stop) {
            return;
        }

        // вычисляем индекс опорного элемента ... median_of_medians ...
        int pivot_index = median_of_medians(arr, arr.size() / 2 - 1, start, stop);

        // производим разбиение относительно опорного элемента ...  partition ...
        int partition_index = partition(arr, start, stop, pivot_index);

        // рекурсивно повторяем процедуру над левой и правой частью ...
        quick_sort(arr, start, partition_index - 1);
        quick_sort(arr, partition_index + 1, stop);
    }

}  // namespace itis
