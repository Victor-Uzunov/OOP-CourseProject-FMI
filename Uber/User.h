#pragma once
#include "MyString.h"
#include <fstream>

class User {
private:
    MyString username;
    MyString password;
    MyString firstName;
    MyString surname;
public:
    User();
    User(std::ifstream& file);
    User(const char* newUser, const char* newPass, const char* newName, const char* newSurname);
    const MyString& getUserName()const;
    const MyString& getFirstName()const;
    const MyString& getSurname()const;

    bool logIn(const char* yourName, const char* yourPassword)const;

    void writeUser(std::ofstream& file)const;
    void readUser(std::ifstream& file);


    friend std::ostream& operator<<(std::ostream& os, const User& user);

private:
    void setUsername(const char* newUserName);
    void setPassword(const char* newPassword);
    void setSurname(const char* newSurname);
    void setFirstName(const char* newFirstName);
};





