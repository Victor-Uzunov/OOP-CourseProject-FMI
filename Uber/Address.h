#pragma once
#include <iostream>
#include "Point.h"
#include "MyString.h"
#include <fstream>

class Address {
private:
    Point point;
    MyString address;
public:
    Address() = default;
    Address(std::ifstream& file);
    Address(const char* newAddress, int x, int y);
    const Point& getPoint()const;

    void write(std::ofstream& file)const;
    void read(std::ifstream& file);

    friend std::ostream& operator<<(std::ostream& os, const Address& object);
};
std::ostream& operator<<(std::ostream& os, const Address& object);

