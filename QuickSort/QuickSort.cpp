#include <iostream>
#include <vector>

using namespace std;



int partition(vector<int>& array, int low, int high)
{
	int pivot = array[high];
	int  i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (array[j] < pivot)
		{
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[high]);
	return i + 1;

}


void quickSort(vector<int>& array, int low, int high)
{
	if (low < high)
	{
		int pi = partition(array, low, high);

		quickSort(array, low, pi - 1);
		quickSort(array, pi, high);
	}
}



int main()
{

	setlocale(LC_ALL, "Russian");

	vector<int> array;
	int num;
	int count;

	cout << "Введите количество чисел";
	cin >> count;

	cout << "Введите " << count << " чисел";
	for (int i = 0; i < count; i++)
	{
		cin >> num;
		array.push_back(num);
	}


	quickSort(array, 0, array.size() - 1);

	cout << "Отсортированный список";
	for (int num : array)
	{
		cout << num << ' ';
	}

	return 0;

}
