#include <iostream>
#include <vector>

using namespace std;

void SelectionSort(vector<int>& array)
{
    int len = array.size();
    for (int i = 0; i < len-1; i++)
    {
        int min = array[i];
        int index = i;
        
        for (int j = i + 1; j < len; j++)
        {
            if (min > array[j])
            {
                min = array[j];
                index = j;
            }
        }

        if (index != i)
        {
            int temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }
    }
}



int main() {

    setlocale(LC_ALL, "Russian");

    int len;
    std::cout << "Введите количество элементов: ";
    std::cin >> len;

    std::vector<int> arr(len);
    std::cout << "Введите " << len << " элементов: " << endl;
    for (int i = 0; i < len; ++i) {
        std::cin >> arr[i];
    }

    std::cout << "Несортированный массив: " << endl;
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    SelectionSort(arr);

    cout << "Отсортированный массив: " << endl;
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
