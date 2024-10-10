#include<iostream>
#include<vector>

using namespace std;

void CombSort(vector<int>& array)
{
	int n = array.size();
	int gap = n;
	bool swapped = true;

	while (gap != 1 or swapped)
	{
		gap = (gap * 10) / 13;
		if (gap < 1) gap = 1;

		swapped = false;

		for (int i = 0; i < n - gap; i++)
		{
			if (array[i] > array[i + gap])
			{
				swap(array[i], array[i + gap]);
				swapped = true;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	vector<int> array;
	int num;
	int count;

	cout << "введите количество чисел ";
	cin >> count;

	cout << "Введите " << count << " чисел";
	for (int i = 0; i < count; i++)
	{
		cin >> num;
		array.push_back(num);
	}

	CombSort(array);

	cout << "Отсортированный список: ";
	for (int num : array)
	{
		cout << num << ' ';
	}
	cout << endl;

	return 0;
}
