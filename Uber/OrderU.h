#pragma once
#include "Address.h"
#include "MyString.h"
#include "Vector.hpp"
#include "SharedPointer.hpp"

class OrderU {
private:
    static size_t ID;
    size_t id;
    Address addressFrom;
    Address addressTo;
    MyString extraInformation;
    size_t passengersCount = 0;

public:
    OrderU() = default;
    OrderU(std::ifstream& file);
    OrderU(size_t clientIndex, const char* address1, int x1, int y1, const char* address2, int x2, int y2, size_t passCount, const char* info);
    size_t getID()const;
    bool isOrderAccepted()const;
    bool isOrderFinished()const;
    size_t getMinutes()const;

    void addDeclineDriver(size_t index);
    size_t getDeclineArrSize()const;
    void setClient(size_t index);

    void acceptOrder(size_t index);
    void setMinutes(size_t time);
    void finishOrder();
    void transferMoney(size_t sum);
    size_t getMoneyToTransfer()const;

    bool isIndexIn(size_t index)const;
    const Address& getAddressFrom()const;
    const Address& getAddressTo()const;
    const MyString& getInfo()const;
    size_t getPassengersCount()const;

    const Point& getAddressPoint()const;
    const Point& getDestinationPoint()const;
    int getDriver()const;
    size_t getClient()const;

    void writeOrder(std::ofstream& file)const;

    void setID(size_t num);

private:
    bool isFinished = false;
    size_t minutes = 0;
    size_t moneyToTransfer = 0;

    int driver = -1;
    size_t client = 0;

    Vector<size_t> declineDrivers;
};



