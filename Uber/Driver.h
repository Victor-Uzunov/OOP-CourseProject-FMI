#pragma once
#include "User.h"
#include "Point.h"
#include "OrderU.h"
#include "Vector.hpp"

class Driver: public User {
private:
    bool isFree;
    size_t moneyBank;
    double rating;
    size_t opinionCount;
    MyString carNumber;
    MyString phoneNumber;
    Point location;

public:
    Driver();
    Driver(std::ifstream& file);
    Driver(const char* newUserName,const char* newPassword, const char* newFirstName, const char* newSurname,
           const char* newCarNumber, const char* phoneNumber);

    Driver(Driver&& driver) = delete;
    Driver& operator=(const Driver& driver) = delete;
    Driver& operator=(Driver&& driver) = delete;

    void setDriveBusy();
    void setDriverFree();

    const MyString& getCarNumber()const;
    const MyString& getPhoneNumber()const;

    const Point& getLocation()const;
    void setLocation(int x, int y);
    void printDriver()const;
    void setRating(double rate);
    double getRating()const;
    void getPaid(size_t money);

    void write(std::ofstream& file)const;
    SharedPointer<Driver> read(std::ifstream& file);


private:
    Driver(const Driver& driver) = default;
    void setCarNumber(const char* newCarNumber);
    void setPhoneNumber(const char* newPhoneNumber);
};





