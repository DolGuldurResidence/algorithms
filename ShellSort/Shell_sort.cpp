#include <iostream>
#include <vector>

using namespace std;

void ShellSort(vector<int>& array)
{
	int pregap = array.size();
	
	for(int gap = pregap / 2; gap > 0; gap /= 2)
		for (int i = gap; i < pregap; i++)
		{
			int temp = array[i];
			int j = i;
			while (j >= gap and array[j - gap] > temp)
			{
				array[j] = array[j - gap];
				j -= gap;
			}
			array[j] = temp;
		}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	vector<int> mas;
	int num;
	int count;
	
	cout << "Введите количество чисел ";
	cin >> count; 

	cout << "Введите " << count << " чисел ";
	for (int i = 0; i < count; i++)
	{
		cin >> num;
		mas.push_back(num);
	}

	ShellSort(mas); 

	cout << "Отсортированный список "; 
	for (int num : mas)
	{
		cout << num << ' ';
	}
	cout << endl;

	return 0;
}
