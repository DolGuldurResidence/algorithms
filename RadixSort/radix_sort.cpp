#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void CountSort(vector<int>& array, int exp)
{
	int lenght = array.size();
	vector<int> output(lenght);
	vector<int> count(10, 0);

	for (int i = 0; i < lenght; i++)
	{
		count[(array[i] / exp) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	
	for (int i = lenght - 1; i >= 0; i--)
	{
		int digit = (array[i] / exp) % 10;
		output[count[digit] - 1] = array[i];
		count[digit]--;
	}

	for (int i = 0; i < lenght; i++)
	{
		array[i] = output[i];
	}
}

void  RadixSort(vector<int>& array)
{
	int MaxVal = *max_element(array.begin(), array.end());
	
	for (int exp = 1; MaxVal / exp > 0; exp *= 10)
	{
		CountSort(array, exp);
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

	RadixSort(array);

	cout << "Отсортированный список: ";
	for (int num : array)
	{
		cout << num << ' ';
	}
	cout << endl;

	return 0;
}
