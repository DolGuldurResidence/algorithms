#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

const double pi = acos(-1.0);

using namespace std;

struct point {
	double x, y;
};

// ax + by + c = 0;
struct line {
	double a, b, c;
};

struct segment {
	point p1, p2;
};

struct circle {
	point center;
	double radius;
};


bool equalDouble(double a, double b, double eps = 1e-9) {
    if (a * b < 0) {
        return fabs(a) < eps && fabs(b) < eps;
    }
    return fabs(a - b) < eps;
}

// P1P2=(x2-x1,y2 - y1), P1P3=(x3-x1,y3-y1)
double crossProduct(const point& p1, const point& p2, const point& p3) {
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

//проверка на коллинеарность + учитка погрешности
bool isPointOnSegment(const point& p, const segment& seg) {
	if (!equalDouble(crossProduct(seg.p1, seg.p2, p), 0)) return false;

	return p.x >= min(seg.p1.x, seg.p2.x) - 1e-9 &&
		p.x <= max(seg.p1.x, seg.p2.x) + 1e-9 &&
		p.y >= min(seg.p1.y, seg.p2.y) - 1e-9 &&
		p.y <= max(seg.p1.y, seg.p2.y) + 1e-9;
}

double distance(const point& p1, const point& p2) {
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

//метод Крамера
bool intersectTwoLines(const line& l1, const line& l2, point& result) {
	double det = l1.a * l2.b - l2.a * l2.b;

	if (equalDouble(det, 0)) return false;

	result.x = (l2.b * l2.c - l2.b * l1.c) / det;
	result.y = (l2.a * l1.c - l1.a * l2.c) / det;
	return true;
}
//Норм:(y2 - y1, -(x2 - x1)) = (AB); C= x2y1 - x1y2
bool intersectLineAndSegment(const line& lin, const segment& seg, point& result) {
	line segLine;

	segLine.a = seg.p2.y - seg.p1.y;
	segLine.b = seg.p1.x - seg.p2.x;
	segLine.c = seg.p2.x * seg.p1.y - seg.p1.x * seg.p2.y;

	if (!intersectTwoLines(lin, segLine, result)) return false;

	return isPointOnSegment(result, seg);
}

bool intersectTwoSegments(const segment& seg1, const segment& seg2, point& result) { 
    //смотрим накладываютс ли друг на друга проеккции
    if (max(seg1.p1.x, seg1.p2.x) < min(seg2.p1.x, seg2.p2.x) ||
        max(seg2.p1.x, seg2.p2.x) < min(seg1.p1.x, seg1.p2.x) ||
        max(seg1.p1.y, seg1.p2.y) < min(seg2.p1.y, seg2.p2.y) ||
        max(seg2.p1.y, seg2.p2.y) < min(seg1.p1.y, seg1.p2.y)) {
        return false;
    }
       
    line l1, l2;
    l1.a = seg1.p2.y - seg1.p1.y;
    l1.b = seg1.p1.x - seg1.p2.x;
    l1.c = seg1.p2.x * seg1.p1.y - seg1.p1.x * seg1.p2.y;

    l2.a = seg2.p2.y - seg2.p1.y;
    l2.b = seg2.p1.x - seg2.p2.x;
    l2.c = seg2.p2.x * seg2.p1.y - seg2.p1.x * seg2.p2.y;
    
    if (!intersectTwoLines(l1, l2, result)) {
        return false;
    }

    //смотрим лежит ли точка пересечения на отрезке
    return isPointOnSegment(result, seg1) && isPointOnSegment(result, seg2);
}

vector<point> intersectCircleLine(const line& lin, const circle& circl) {
    vector<point> result;

    if (!equalDouble(lin.b, 0)) {
        // Преобразование Ax + By + C = 0 к y = kx + t
        double k = -lin.a / lin.b;
        double t = -lin.c / lin.b;

        // Коэффициенты квадратного уравнения 
        double a = 1 + k * k;
        double b = 2 * (k * t - k * circl.center.y - circl.center.x);
        double c = circl.center.x * circl.center.x +
            pow(t - circl.center.y, 2) -
            pow(circl.radius, 2);

        double d = b * b - 4 * a * c;

        if (equalDouble(d, 0)) { 
            double x = -b / (2 * a);
            double y = k * x + t;
            result.push_back(point(x, y));
        }
        else if (d > 0) { 
            double x1 = (-b + sqrt(d)) / (2 * a);
            double y1 = k * x1 + t;
            result.push_back(point(x1, y1));

            double x2 = (-b - sqrt(d)) / (2 * a);
            double y2 = k * x2 + t;
            result.push_back(point(x2, y2));
        }
    }
    else { 
        double x = -lin.c / lin.a;
        double d = pow(circl.radius, 2) - pow(x - circl.center.x, 2);

        if (equalDouble(d, 0)) {
            result.push_back(point(x, circl.center.y));
        }
        else if (d > 0) {
            result.push_back(point(x, circl.center.y + sqrt(d)));
            result.push_back(point(x, circl.center.y - sqrt(d)));
        }
    }

    return result;
}

vector<point> intersectSegCircle(const segment& seg, const circle& circl) {
    vector<point> result;

    line lin;
    lin.a = seg.p2.y - seg.p1.y;
    lin.b = seg.p1.x - seg.p2.x;
    lin.c = seg.p2.x * seg.p1.y - seg.p1.x * seg.p2.y; 

    vector<point> linePoints = intersectCircleLine(lin, circl);

    for (const point& p : linePoints) {
        if (isPointOnSegment(p, seg)) {
            result.push_back(p);
        }
    }

    return result;
}

vector<point> intersectTwoCircles(const circle& c1, const circle& c2) {
    vector<point> result;

    double d = distance(c1.center, c2.center);

    if (equalDouble(d, 0) && equalDouble(c1.radius, c2.radius)) {
        return result;
    }

    if (d > c1.radius + c2.radius + 1e-9 ||
        d < fabs(c1.radius - c2.radius) - 1e-9) {
        return result;
    }

    if (equalDouble(d, c1.radius + c2.radius) || equalDouble(d, fabs(c1.radius - c2.radius))) {
        double t = c1.radius / d;
        point p(c1.center.x + t * (c2.center.x - c1.center.x), c1.center.y + t * (c2.center.y - c1.center.y));
        result.push_back(p);
        return result;

    }
    
    double a = (pow(c1.radius, 2) - pow(c2.radius, 2)) / (2 * d); 
    double h = sqrt(pow(c1.radius, 2) - pow(a, 2)); 

    point p0(c1.center.x + a * (c2.center.x - c1.center.x) / d,
        c1.center.y + a * (c2.center.y - c1.center.y) / d);

    point p1(p0.x + h * (c2.center.y - c1.center.y) / d,
        p0.y - h * (c2.center.x - c1.center.x) / d);

    point p2(p0.x - h * (c2.center.y - c1.center.y) / d,
        p0.y + h * (c2.center.x - c1.center.x) / d);

    result.push_back(p1);
    result.push_back(p2);

    return result;
}

bool isTriangleInside(const vector<point>& t1, const vector<point>& t2) {
    //проверка вершин внутри треугольника
    for (const point& p : t1) {
        double totalAngle = 0;
        for (int i = 0; i < 3; i++) {
            point v1 = t2[i];
            point v2 = t2[(i + 1) % 3];

            double angle = atan2(v2.y - p.y, v2.x - p.x) - atan2(v1.y - p.y, v1.x - p.x);
            if (angle > pi) angle -= 2 * pi;
            if (angle < -pi) angle += 2 * pi;
            totalAngle += angle;
        }

        if (fabs(totalAngle) < 1e-9) return false;
    }

    //проверка лежат ли отрезки друг на друге
    for (int i = 0; i < 3; i++) {
        segment s1(t1[i], t1[(i + 1) % 3]);
        for (int j = 0; j < 3; j++) {
            segment s2(t2[j], t2[(j + 1) % 3]);
            point dummy; 
            if (intersectTwoSegments(s1, s2, dummy)) {
                return false;
            }
        }
    }
    return true;
}


bool hasNestedTriangles(const vector<point>& points) {
    size_t n = points.size();
    if (n < 6) return false;
    
    for (int i1 = 0; i1 < n; ++i1) {
        for (int i2 = i1 + 1; i2 < n; ++i2) {
            for (int i3 = i2 + 1; i3 < n; ++i3) {
                vector<point> t1 = { points[i1], points[i2], points[i3] };

                //проверка на вырожденность
                if (equalDouble(crossProduct(t1[0], t1[1], t1[2]), 0)) continue;
                
                for (int j1 = 0; j1 < n; ++j1) {
                    if (j1 == i1 || j1 == i2 || j1 == i3) continue;
                    for (int j2 = j1 + 1; j2 < n; ++j2) {
                        if (j2 == i1 || j2 == i2 || j2 == i3) continue;
                        for (int j3 = j2 + 1; j3 < n; ++j3) {
                            if (j3 == i1 || j3 == i2 || j3 == i3) continue;

                            vector<point> t2 = { points[j1], points[j2], points[j3] };

                            if (equalDouble(crossProduct(t2[0], t2[1], t2[2]), 0)) continue;

                            if (isTriangleInside(t1, t2) || isTriangleInside(t2, t1)) {
                                return true;
                            }
                        }
                    }
                }
                
             }
        }
    }

    return false; 
}

int main()
{
    setlocale(LC_ALL, "russian");

    vector<point> firstCaseTrue = { {8,10}, {1,6}, {3,1} ,
        {2,6}, {3,3}, {6,8},
        {3,6}, {3,4}, {5,7} };

    vector<point> secondCaseTrue = { {-8,10}, {-1,6}, {-3,1} ,
        {-2,6}, {-3,3}, {-6,8},
        {-3,6}, {-3,4}, {-5,7} };

    vector<point> thirdCaseTrue = { {-8,-10}, {-1,-6}, {-3,-1} ,
        {-2,-6}, {-3,-3}, {-6,-8},
        {-3,-6}, {-3,-4}, {-5,-7} };

    vector<point> fourthCaseTrue = { {8,-10}, {1,-6}, {3,-1} ,
        {2,-6}, {3,-3}, {6,-8},
        {3,-6}, {3,-4}, {5,-7} };

    cout << hasNestedTriangles(firstCaseTrue) << endl;
    cout << hasNestedTriangles(secondCaseTrue) << endl;
    cout << hasNestedTriangles(thirdCaseTrue) << endl;
    cout << hasNestedTriangles(fourthCaseTrue) << endl;

    vector<point> firstCaseCheck = {{1,7}, {6,7}, {2,1}, 
        {3,5}, {7,2}, {8,6}, 
        {4,5}, {6,5}, {6,3}};

    vector<point> secondCaseCheck = { {-1,7}, {-6,7}, {-2,1},
       {-3,5}, {-7,2}, {-8,6},
       {-4,5}, {-6,5}, {-6,3} };

    vector<point> thirdCaseCheck = { {-1,-7}, {-6,-7}, {-2,-1},
       {-3,-5}, {-7,-2}, {-8,-6},
       {-4,-5}, {-6,-5}, {-6,-3} };

    vector<point> fourthCaseCheck = { {1,-7}, {6,-7}, {2,-1},
       {3,-5}, {7,-2}, {8,-6},
       {4,-5}, {6,-5}, {6,-3} };

    cout << hasNestedTriangles(firstCaseCheck) << endl;
    cout << hasNestedTriangles(secondCaseCheck) << endl;
    cout << hasNestedTriangles(thirdCaseCheck) << endl;
    cout << hasNestedTriangles(fourthCaseCheck) << endl;

    vector<point> firstCaseFalse = { {1,9}, {5,9}, {1,4},
        {3,5}, {7,7}, {7,3}, 
        {2,4}, {2,1}, {7,1} };

    vector<point> secondCaseFalse = { {-1,9}, {-5,9}, {-1,4},
        {-3,5}, {-7,7}, {-7,3},
        {-2,4}, {-2,1}, {-7,1} };

    vector<point> thirdCaseFalse = { {-1,-9}, {-5,-9}, {-1,-4},
        {-3,-5}, {-7,-7}, {-7,-3},
        {-2,-4}, {-2,-1}, {-7,-1} };
    
    vector<point> fourthCaseFalse = { {1,-9}, {5,-9}, {1,-4},
        {3,-5}, {7,-7}, {7,-3},
        {2,-4}, {2,-1}, {7,-1} };

    cout << hasNestedTriangles(firstCaseFalse) << endl;
    cout << hasNestedTriangles(secondCaseFalse) << endl;
    cout << hasNestedTriangles(thirdCaseFalse) << endl;
    cout << hasNestedTriangles(fourthCaseFalse) << endl;

    int N;
    cout << "Введите количество точек: ";
    cin >> N;

    vector<point> points(N);
    cout << "Введите координаты точек X Y: " << endl;
    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
    }

    if (hasNestedTriangles(points)) {
        cout << "В множестве есть вложенные треугольники" << endl;
    }
    else {
        cout << "В множестве нет вложенных треугольников" << endl;
    }

    return 0;
}
