#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void selection_sort(T arr[], int n) {
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}

template <typename T>
void display_array(const char* name, const T arr[], int n) {
    std::cout << name << ": [";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;
}

int main() {
    int size;

    std::cout << "--- Testing with Integer Array ---" << std::endl;
    std::cout << "Enter the size of the integer array: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid size. Exiting integer test." << std::endl;
    } else {
        std::vector<int> intArray(size); 
        std::cout << "Enter " << size << " integers, separated by spaces: ";
        for (int i = 0; i < size; ++i) {
            std::cin >> intArray[i];
        }

        display_array("Original Int Array", intArray.data(), size);

        selection_sort(intArray.data(), size);

        display_array("Sorted Int Array", intArray.data(), size);
    }
    
    std::cout << "\n----------------------------------\n";

    std::cout << "--- Testing with Float Array ---" << std::endl;
    std::cout << "Enter the size of the float array: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid size. Exiting float test." << std::endl;
    } else {
        std::vector<float> floatArray(size); 
        std::cout << "Enter " << size << " floating-point numbers, separated by spaces: ";
        for (int i = 0; i < size; ++i) {
            std::cin >> floatArray[i];
        }

        display_array("Original Float Array", floatArray.data(), size);

        selection_sort(floatArray.data(), size);

        display_array("Sorted Float Array", floatArray.data(), size);
    }

    return 0;
}