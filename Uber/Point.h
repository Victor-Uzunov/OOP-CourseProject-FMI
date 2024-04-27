#pragma once
#include <iostream>

class Point {
private:
    int x;
    int y;
public:
    Point();
    Point(std::ifstream& file);
    Point(int newX, int newY);

    int getX()const;
    int getY()const;

    double getDist(const Point& point)const;

    void write(std::ofstream& file)const;
    void read(std::ifstream& file);

};
std::ostream& operator<<(std::ostream& os, const Point& point);




