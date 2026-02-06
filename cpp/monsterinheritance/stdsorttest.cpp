#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

class Point
{
public:
    Point(double n1, double n2)
        : x{n1}, y{n2}
    {}

    double magnitude() const
    {
        return std::sqrt(x*x + y*y);
    }

    friend bool operator==(const Point& p1, const Point& p2)    { return p1.x == p2.x && p1.y == p2.y; }
    friend bool operator!=(const Point& p1, const Point& p2)    { return !(p1 == p2); }
    friend bool operator>(const Point& p1, const Point& p2)     { return p1.magnitude() > p2.magnitude(); }
    friend bool operator<(const Point& p1, const Point& p2)     { return p1.magnitude() < p2.magnitude(); }
    friend bool operator>=(const Point& p1, const Point& p2)    { return !(p1 < p2); }
    friend bool operator<=(const Point& p1, const Point& p2)    { return !(p1 > p2); }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << '(' << p.x << ", " << p.y << ')';
        return out;
    }

    double x{};
    double y{};
};

template <typename T>
void printArray(const std::vector<T>& arr)
{
    for(const T& e : arr)
        std::cout << e << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector<Point> points{ {2,3}, {4,3}, {5,16}, {0,0}, {0,1} };
    printArray(points);

    std::ranges::sort(points);
    printArray(points);

}