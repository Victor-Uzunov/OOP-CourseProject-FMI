#include "User.h"


User::User():User("", "","",""){

}
User::User(const char* newUser, const char* newPass, const char* newName, const char* newSurname){
    setUsername(newUser);
    setPassword(newPass);
    setFirstName(newName);
    setSurname(newSurname);
}
bool User::logIn(const char* yourName, const char* yourPassword)const{
    if(yourName == username && yourPassword == password){
        return true;
    }
    return false;
}
void User::setUsername(const char* newUserName){
    username = newUserName;
}
void User::setPassword(const char* newPassword){
    password = newPassword;
}
void User::setFirstName(const char* newFirstName){
    firstName = newFirstName;
}
void User::setSurname(const char* newSurname){
    surname = newSurname;
}
const MyString& User::getFirstName()const{
    return firstName;
}
const MyString& User::getSurname()const{
    return surname;
}
const MyString& User::getUserName()const{
    return username;
}
std::ostream& operator<<(std::ostream& os, const User& user){
    os << user.username << ": " << user.firstName << " " << user.surname;
    return os;
}
void User::writeUser(std::ofstream& file)const{
    size_t len1 = firstName.length();
    file.write((const char*)&len1, sizeof (size_t));
    file.write(firstName.c_str(), sizeof (char) * len1);

    size_t len2 = surname.length();
    file.write((const char*)&len2, sizeof (size_t));
    file.write(surname.c_str(), sizeof (char) * len2);

    size_t len3 = username.length();
    file.write((const char*)&len3, sizeof (size_t));
    file.write(username.c_str(), sizeof (char) * len3);

    size_t len4 = password.length();
    file.write((const char*)&len4, sizeof (size_t));
    file.write(password.c_str(), sizeof (char) * len4);
}
void User::readUser(std::ifstream& file){
    size_t len1 = 0;
    file.read((char*)&len1, sizeof (size_t));
    char* buff = new char[len1 + 1];
    file.read(buff, sizeof (char) * len1);
    buff[len1] = '\0';
    firstName = buff;
    delete[] buff;

    size_t len2 = 0;
    file.read((char*)&len2, sizeof (size_t));
    char* buff2 = new char[len2 + 1];
    file.read(buff2, sizeof (char) * len2);
    buff2[len2] = '\0';
    surname = buff2;
    delete[] buff2;

    size_t len3 = 0;
    file.read((char*)&len3, sizeof (size_t));
    char* buff3 = new char[len3 + 1];
    file.read(buff3, sizeof (char) * len3);
    buff3[len3] = '\0';
    username = buff3;
    delete[] buff3;

    size_t len4 = 0;
    file.read((char*)&len4, sizeof (size_t));
    char* buff4 = new char[len4 + 1];
    file.read(buff4, sizeof (char) * len4);
    buff4[len4] = '\0';
    password = buff4;
    delete[] buff4;

}
User::User(std::ifstream& file){
    size_t len1 = 0;
    file.read((char*)&len1, sizeof (size_t));
    char* buff = new char[len1 + 1];
    file.read(buff, sizeof (char) * len1);
    buff[len1] = '\0';
    firstName = buff;
    delete[] buff;

    size_t len2 = 0;
    file.read((char*)&len2, sizeof (size_t));
    char* buff2 = new char[len2 + 1];
    file.read(buff2, sizeof (char) * len2);
    buff2[len2] = '\0';
    surname = buff2;
    delete[] buff2;

    size_t len3 = 0;
    file.read((char*)&len3, sizeof (size_t));
    char* buff3 = new char[len3 + 1];
    file.read(buff3, sizeof (char) * len3);
    buff3[len3] = '\0';
    username = buff3;
    delete[] buff3;

    size_t len4 = 0;
    file.read((char*)&len4, sizeof (size_t));
    char* buff4 = new char[len4 + 1];
    file.read(buff4, sizeof (char) * len4);
    buff4[len4] = '\0';
    password = buff4;
    delete[] buff4;
}
