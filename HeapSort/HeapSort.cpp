#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) 
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    int len;
    cout << "Введите количество элементов: ";
    cin >> len;

    vector<int> arr(len);
    cout << "Введите " << len << " элементов: " << endl;
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }

    cout << "Несортированный массив: " << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << std::endl;

    heapSort(arr);

    cout << "Отсортированный массив: " << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
