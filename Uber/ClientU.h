#pragma once
#include "MyString.h"
#include "User.h"
#include "Vector.hpp"
#include "SharedPointer.hpp"
#include "OrderU.h"
#include <fstream>

class Order;

class ClientU: public User {
private:
    size_t money;
    Vector<size_t> orders;
public:
    ClientU();
    ClientU(std::ifstream& file);

    ClientU(const char *newUserName, const char *newPassword, const char *newFirstName, const char *newSurname);

    void addMoney(size_t plusMoney);
    void addOrder(size_t id);
    size_t getSize()const;
    size_t getMoney()const;
    void pay(size_t amount);
    bool isOrderYours(size_t index)const;

    bool correctPassword(const char* name, const char* password)const;
    void removeOrder(size_t id);

    void writeClient(std::ofstream& file)const;


    ClientU &operator=(const ClientU &client) = delete;
    ClientU &operator=(ClientU &&client) = delete;

private:
    ClientU(ClientU &&client) = default;
    ClientU(const ClientU& client) = default;

};
