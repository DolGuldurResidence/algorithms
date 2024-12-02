#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArray(n1), rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        }
        else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

int main() 
{
    setlocale(LC_ALL, "Rus");

    vector<int> mas;
    int num, count;

    cout << "Введите количество чисел: ";
    cin >> count;

    cout << "Введите " << count << " чисел: ";
    for (int i = 0; i < count; i++) {
        cin >> num;
        mas.push_back(num);
    }

    mergeSort(mas, 0, mas.size() - 1);

    cout << "Отсортированный список: ";
    for (int num : mas) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}

