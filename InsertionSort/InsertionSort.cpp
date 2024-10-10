#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 and arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main() {
    
    setlocale(LC_ALL, "Russian");

    int len;
    std::cout << "Введите количество элементов: ";
    std::cin >> len;

    std::vector<int> arr(len);
    std::cout << "Введите " << len << " элементов:\n";
    for (int i = 0; i < len; ++i) {
        std::cin >> arr[i];
    }

    std::cout << "Несортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    insertionSort(arr);

    std::cout << "Отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
