#include<iostream>
#include<cmath>


using namespace std;



int main()
{
	setlocale(LC_ALL, "Rus");

	float x;
	cout << "Введите число X " << endl;
	cin >> x;

	int max_factor = 0;
	int x_1 = x;
	while (x_1 >= 3)
	{
		x_1 = x_1 / 3;
		max_factor++;
	}

	int mid_factor = 0;
	int x_2 = x;
	while (x_2 >= 5)
	{
		x_2 = x_2 / 5;
		mid_factor++;
	}

	int low_factor = 0; 
	int x_3 = x;
	while (x_3 >= 7)
	{
		x_3 = x_3 / 7;
		low_factor++;
	}

	for (int i = 0; i <= max_factor; i++)
	{
		int fir = pow(3, i);
		for (int j = 0; j <= mid_factor; j++)
		{
			int sec =pow(5, j);
			for (int k = 0; k <= max_factor; k++)
			{
				int thir = pow(7, k);
				if (thir * sec * fir <= x)
				{
					cout << thir * sec * fir << endl;
				}
			}
		}
	}

	return 0;
}
