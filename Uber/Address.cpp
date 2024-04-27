#include "Address.h"

Address::Address(const char* newAddress, int x, int y): point(x,y){
    address = newAddress;
}
const Point& Address::getPoint()const{
    return point;
}
std::ostream& operator<<(std::ostream& os, const Address& object){
    os << object.address << " " << object.point << std::endl;
    return os;
}
void Address::write(std::ofstream& file)const{
    point.write(file);
    size_t len = address.length();
    file.write((const char*)&len, sizeof(size_t));
    file.write(address.c_str(), sizeof(char)*len);
}
void Address::read(std::ifstream& file){
    point.read(file);
    size_t len = 0;
    file.read((char*)&len, sizeof(size_t));
    char* buff = new char[len + 1];
    file.read((char*)&buff, sizeof(char) * len);
    buff[len] = '\0';
    address = buff;
    delete[] buff;
}
Address::Address(std::ifstream& file): point(file), address(file){

}