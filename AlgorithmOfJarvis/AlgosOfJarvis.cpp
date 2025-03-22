#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

struct point {
	int x, y;
};

int orientation(const point& p, const point& q, const point& r) {
	int value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (value == 0) return 0;
	return (value > 0) ? 1 : 2; 
}

vector<point> convexHull(const vector<point>& points) {
	size_t n = points.size();
	if (n < 3) return {};

	int leftmost = 0;
	for (int i = 1; i < n; i++) {
		if (points[i].x < points[leftmost].x) {
			leftmost = i;
		}
	}

	vector<point> hull;
	int p = leftmost, q;
	do {
		hull.push_back(points[p]);
		
		q = (p + 1) % n;
		for (int i = 0; i < n; i++) {
			if (orientation(points[p], points[i], points[q]) == 2) {
				q = i;
			}
		}

		p = q;
	} while (p != leftmost);

	return hull;
}

void printPoints(const vector<point>& points) {
	for (const auto& p : points) {
		cout << "(" << p.x << "," << p.y << ")" << endl;
	}

}

void inputPoints(vector<point>& points, int n) {
	for (int i = 1; i < n + 1; i++) {
		int x, y;
		cout << "Введите " << i << "-ую точку" << endl;
		cin >> x >> y;
		points.push_back({ x, y });
	}
}

int main()
{
	setlocale(LC_ALL, "Russian"); 

	int n;
	vector<point> points;
	cout << "Введите кол-во точек на плоскости!" << endl;
	cin >> n;

	inputPoints(points, n);
	
	vector<point> hull = convexHull(points);

	cout << "Точки выпуклой оболочки: " << endl;
	printPoints(hull);

	return 0;
}
