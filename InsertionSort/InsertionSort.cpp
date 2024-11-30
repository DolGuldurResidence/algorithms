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
    cout << "Введите количество элементов: ";
    cin >> len;

    vector<int> arr(len);
    cout << "Введите " << len << " элементов:\n";
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }

    cout << "Несортированный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    insertionSort(arr);

    cout << "Отсортированный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
