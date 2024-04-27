#include "OrderU.h"

size_t OrderU::ID = 0;
OrderU::OrderU(size_t index, const char* address1, int x1, int y1, const char* address2,
             int x2, int y2, size_t passCount, const char* info):addressFrom(address1, x1, y1),
                                                                 addressTo(address2, x2, y2),
                                                                 declineDrivers(){
    client = index;
    driver = -1;
    passengersCount = passCount;
    OrderU::ID++;
    id = ID;
    extraInformation = info;
    isFinished = false;
    minutes = 0;
    moneyToTransfer = 0;
}

size_t OrderU::getID()const{
    return id;
}
bool OrderU::isOrderAccepted()const{
    return driver != -1;
}
bool OrderU::isOrderFinished()const{
    return isFinished;
}
size_t OrderU::getMinutes()const{
    return minutes;
}
size_t OrderU::getClient()const{
    return client;
}
int OrderU::getDriver()const{
    return driver;
}
void OrderU::addDeclineDriver(size_t index){
    declineDrivers.pushBack(index);
}
const Point& OrderU::getAddressPoint()const{
    return addressFrom.getPoint();
}
const Point& OrderU::getDestinationPoint()const{
    return addressTo.getPoint();
}
size_t OrderU::getDeclineArrSize()const{
    return declineDrivers.getSize();
}

void OrderU::acceptOrder(size_t object){
    driver = object;
}
void OrderU::setMinutes(size_t time){
    minutes = time;
}
void OrderU::finishOrder(){
    isFinished = true;
}
void OrderU::transferMoney(size_t sum){
    moneyToTransfer += sum;
}
size_t OrderU::getMoneyToTransfer()const{
    return moneyToTransfer;
}
void OrderU::setClient(size_t index){
    client = index;
}
bool OrderU::isIndexIn(size_t index)const{
    for(int i = 0; i < declineDrivers.getSize(); i++){
        if(index == declineDrivers[i]){
            return true;
        }
    }
    return false;
}
const Address& OrderU::getAddressFrom()const{
    return addressFrom;
}
const Address& OrderU::getAddressTo()const{
    return addressTo;
}
const MyString& OrderU::getInfo()const{
    return extraInformation;
}
size_t OrderU::getPassengersCount()const{
    return passengersCount;
}
void OrderU::writeOrder(std::ofstream& file)const{
    addressFrom.write(file);
    addressTo.write(file);


    file.write((const char*)&passengersCount, sizeof (size_t));
    file.write((const char*)&isFinished, sizeof (bool));
    file.write((const char*)&minutes, sizeof (size_t));
    file.write((const char*)&moneyToTransfer, sizeof (size_t));
    file.write((const char*)&driver, sizeof(int));
    file.write((const char*)&client, sizeof (size_t));

    file.write((const char*)&id, sizeof (size_t));

    size_t len = extraInformation.length();
    file.write((const char*)&len, sizeof (size_t));
    file.write(extraInformation.c_str(), sizeof (char)* len);



    size_t size = declineDrivers.getSize();
    file.write((const char*)&size, sizeof(size_t));
    for(int i = 0; i < size; i++){
        file.write((const char*)&declineDrivers[i], sizeof (size_t));
    }
}

OrderU::OrderU(std::ifstream& file): addressFrom(file), addressTo(file){

    file.read((char*)&passengersCount, sizeof (size_t));
    file.read((char*)&isFinished, sizeof (bool));
    file.read((char*)&minutes, sizeof (size_t));
    file.read((char*)&moneyToTransfer, sizeof (size_t));
    file.read((char*)&driver, sizeof (int));
    file.read((char*)&client, sizeof (size_t));

    file.read((char*)&id, sizeof (size_t));


    size_t len = 0;
    file.read((char*)&len, sizeof (size_t));
    char* buff = new char[len+1];
    file.read(buff, sizeof (char) * len);
    buff[len] = '\0';
    extraInformation = buff;
    delete[] buff;


    size_t size = 0;
    file.read((char*)&size, sizeof (size_t));
    Vector<size_t> vector(size);
    declineDrivers = vector;
    for(int i = 0; i < size; i++){
        size_t num1 = 0;
        file.read((char*)&num1, sizeof(size_t));
        declineDrivers.pushBack(num1);
    }

}
void OrderU::setID(size_t num){
    ID = num;
}
