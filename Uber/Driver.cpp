#include "Driver.h"
#include "constants.h"
Driver::Driver():User(), location(0,0) {
    isFree = true;
    moneyBank = MONEY_BANK;
    rating = 0;
    opinionCount = 0;
    carNumber = "";
    phoneNumber = "";
    }
Driver::Driver(const char* newUserName,const char* newPassword, const char* newFirstName, const char* newSurname,
       const char* newCarNumber, const char* phoneNumber):
       User(newUserName, newPassword, newFirstName, newSurname), location(0,0){
    setCarNumber(newCarNumber);
    setPhoneNumber(phoneNumber);
    isFree = true;
    moneyBank = MONEY_BANK;
    rating = 0;
    opinionCount = 0;
}
void Driver::setCarNumber(const char* newCarNumber){
    carNumber = newCarNumber;
}
void Driver::setPhoneNumber(const char* newPhoneNumber){
    phoneNumber = newPhoneNumber;
}

const MyString& Driver::getCarNumber()const{
    return carNumber;
}
const MyString& Driver::getPhoneNumber()const{
    return phoneNumber;
}
const Point& Driver::getLocation()const{
    return location;
}
void Driver::setLocation(int x, int y){
    location = Point(x,y);
}

double Driver::getRating()const{
    if(opinionCount == 0){
        return 0;
    }
    return rating / (double)opinionCount;
}
void Driver::printDriver()const{
    std::cout << getFirstName() << " " << getSurname() << ", " << "Username: " << getUserName() << std::endl;
    std::cout << "Car number: " << getCarNumber() << std::endl;
    std::cout << "Phone number: " << getPhoneNumber() << std::endl;
    if(getRating() != 0) {
        std::cout << "Rating: " << getRating() << std::endl;
    }
    else{
        std::cout << "Rating: Rated from no one yet"<< std::endl;
    }
}
void Driver::getPaid(size_t money){
    moneyBank += money;
}
void Driver::setDriveBusy(){
    isFree = false;
}
void Driver::setDriverFree(){
    isFree = true;
}
void Driver::setRating(double rate){
    rating += rate;
    opinionCount++;
}
void Driver::write(std::ofstream& file)const{
    writeUser(file);
    file.write((const char*)&isFree, sizeof(bool));
    file.write((const char*)&moneyBank, sizeof(size_t));
    file.write((const char*)&rating, sizeof(double));
    file.write((const char*)&opinionCount, sizeof(size_t));

    size_t len1 = carNumber.length();
    file.write((const char*)&len1, sizeof (size_t));
    file.write(carNumber.c_str(), sizeof (char) * len1);

    size_t len2 = phoneNumber.length();
    file.write((const char*)&len2, sizeof (size_t));
    file.write(phoneNumber.c_str(), sizeof (char) * len2);

    location.write(file);

}
 SharedPointer<Driver> Driver::read(std::ifstream& file){
    readUser(file);
    file.read((char*)&isFree, sizeof (bool));
    file.read((char*)&moneyBank, sizeof (size_t));
    file.read((char*)&rating, sizeof (double));
    file.read((char*)&opinionCount, sizeof (size_t));

    size_t len1 = 0;
    file.read((char*)&len1, sizeof (size_t));
    char* buff = new char[len1 + 1];
    file.read(buff, sizeof (char) * len1);
    buff[len1] = '\0';
    carNumber = buff;
    delete[] buff;

    size_t len2 = 0;
    file.read((char*)&len2, sizeof (size_t));
    char* buff2 = new char[len2 + 1];
    file.read(buff2, sizeof (char) * len2);
    buff2[len2] = '\0';
    phoneNumber = buff2;
    delete[] buff2;

    location.read(file);
     SharedPointer<Driver> newObj = new Driver(*this);
    return newObj;
}
Driver::Driver(std::ifstream& file):User(file){
    bool b = false;
    file.read((char*)&b, sizeof (bool));
    isFree = b;
    size_t m = 0;
    file.read((char*)&m, sizeof (size_t));
    moneyBank = m;
    double r = 0;
    file.read((char*)&r, sizeof (double));
    rating = r;
    size_t op = 0;
    file.read((char*)&op, sizeof (size_t));
    opinionCount = op;

    size_t len1 = 0;
    file.read((char*)&len1, sizeof (size_t));
    char* buff = new char[len1 + 1];
    file.read(buff, sizeof (char) * len1);
    buff[len1] = '\0';
    carNumber = buff;
    delete[] buff;

    size_t len2 = 0;
    file.read((char*)&len2, sizeof (size_t));
    char* buff2 = new char[len2 + 1];
    file.read(buff2, sizeof (char) * len2);
    buff2[len2] = '\0';
    phoneNumber = buff2;
    delete[] buff2;

    location.read(file);
}