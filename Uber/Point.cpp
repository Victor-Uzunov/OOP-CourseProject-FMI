#include "Point.h"
#include <cmath>
#include <fstream>

Point::Point(){
    x = 0;
    y = 0;
}
Point::Point(int newX, int newY){
    x = newX;
    y = newY;
}

int Point::getX()const{
    return x;
}
int Point::getY()const{
    return y;
}

double Point::getDist(const Point& point) const{
    int dx = x - point.x;
    int dy = y - point.y;

    return sqrt(dx * dx + dy * dy);
}

std::ostream& operator<<(std::ostream& os, const Point& point){
    os << "(" << point.getX() << "," << point.getY() << ")";
    return os;
}
void Point::write(std::ofstream& file)const{
    file.write((const char*)&x,sizeof(int));
    file.write((const char*)&y, sizeof(int));
}
void Point::read(std::ifstream& file){
    file.read((char*)&x, sizeof(int));
    file.read((char*)&y, sizeof(int));
}
Point::Point(std::ifstream& file){
    int a = 0;
    file.read((char*)&a, sizeof(int));
    x = a;
    int b = 0;
    file.read((char*)&b, sizeof(int));
    y = b;
}