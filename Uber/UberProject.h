#pragma once
#include "Driver.h"
#include "ClientU.h"
#include "OrderU.h"
#include "Vector.hpp"
#include "SharedPointer.hpp"
class UberProject {
private:
    double companyBudget = 0;
    SharedPointer<Driver> currentDriver = nullptr;
    SharedPointer<ClientU> currentClient = nullptr;
    Vector<SharedPointer<ClientU>> clients;
    Vector<SharedPointer<Driver>> drivers;
    Vector<SharedPointer<OrderU>> orders;

public:
    UberProject(std::ifstream& file);

    bool logInClient(const char* name, const char* password);
    bool logInDriver(const char* name, const char* password);
    void logOutClient();
    void logOutDriver();

    UberProject() = default;
    UberProject(const UberProject& other) = delete;
    UberProject(UberProject&& other) = delete;
    UberProject& operator=(const UberProject& other) = delete;
    UberProject& operator=(UberProject&& other) = delete;

    void addClient(const char* username, const char* password, const char* name, const char* lastName);
    void addDriver(const char* username, const char* password, const char* name, const char* lastName, const char* carNumber, const char* phoneNumber);

    void makeOrder(const char* address1, int x1, int y1, const char* address2, int x2, int y2, size_t passCount, const char* info);
    void checkOrder(size_t id);
    void pay(size_t id, size_t amount);
    void cancelOrder(size_t id);
    void addMoney(size_t amount);
    void rateDriver(const char* name, double rating);

    void changeAddress(int x, int y);
    void checkMessages()const;
    void acceptOrder(size_t id, size_t minutes);
    void declineOrder(size_t id);
    void finishOrder(size_t id);
    void acceptPayment(size_t id);


    bool isClientLoggedIN()const;
    bool isDriverLoggedIN()const;

    size_t getIndexOfClient(const SharedPointer<ClientU>& client)const;
    size_t getIndexOfDriver(const SharedPointer<Driver>& driver)const;
    const SharedPointer<OrderU>& getIndexOrderByID(size_t id)const;

    void printOrder(const SharedPointer<OrderU>& ptr)const;

    void writeUber(std::ofstream& file)const;

private:
    bool isTheClosestOne(const SharedPointer<OrderU>& ptr)const;
    void setDriverFree(size_t orderIndex);
    size_t getIndexOfDriver(const MyString& name)const;
    size_t getIndexOfClient(const MyString& name)const;
};
size_t getFileSize(std::ifstream& in);



