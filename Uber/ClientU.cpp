#pragma once
#include "ClientU.h"
#include "constants.h"

ClientU::ClientU():User(), orders(){
    money = STARTING_MONEY;
}
ClientU::ClientU(const char* newUserName,const char* newPassword, const char* newFirstName,
               const char* newSurname): User(newUserName, newPassword, newFirstName, newSurname),
                                        orders(){
    money = STARTING_MONEY;
}
void ClientU::addMoney(size_t plusMoney){
    money += plusMoney;
}
void ClientU::addOrder(size_t id){
    orders.pushBack(id);
}
bool ClientU::isOrderYours(size_t id)const{
    for(int i = 0; i < orders.getSize(); i++){
        if(id == orders[i]){
            return true;
        }
    }
    return false;
}
void ClientU::removeOrder(size_t id){
    for(int i = 0; i < orders.getSize(); i++){
        if(id == orders[i]){
            orders.popAt(i);
        }
    }
}
size_t ClientU::getSize()const{
    return orders.getSize();
}
bool ClientU::correctPassword(const char* name, const char* password)const{
    return logIn(name,password);
}
void ClientU::writeClient(std::ofstream& file)const{
    writeUser(file);
    file.write((const char*)&money, sizeof (size_t));

    size_t len = orders.getSize();
    file.write((const char*)&len, sizeof (size_t));
    for(int i = 0; i < len; i++){
        file.write((const char*)&orders[i], sizeof (size_t));
    }

}

ClientU::ClientU(std::ifstream& file): User(file){
    size_t m = 0;
    file.read((char*)&m, sizeof (size_t));
    money = m;
    size_t len = 0;
    file.read((char*)&len, sizeof (size_t));
    Vector<size_t> vector(len);
    orders = vector;
    for(int i = 0; i < len; i++){
        size_t num = 0;
        file.read((char*)&num, sizeof (size_t));
        orders.pushBack(num);
    }
}
size_t ClientU::getMoney()const{
    return money;
}
void ClientU::pay(size_t amount){
    money -= amount;
}
