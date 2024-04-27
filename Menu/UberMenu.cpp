#include "UberMenu.h"
#include "UberProject.h"
#include "constants.h"
#include <iostream>
#include <cstring>
#include "Validations.h"


void run(){
    std::ifstream file("CompanyInfo.dat");
    UberProject uber(file);
    file.close();

    while(true){
        std::cout << "Welcome to Uber:" << std::endl;
        std::cout << "Press 1 to register as a client." << std::endl;
        std::cout << "Press 2 to register as a driver" << std::endl;
        std::cout << "Press 3 to log in as a client" << std::endl;
        std::cout << "Press 4 to log in as a driver" << std::endl;
        std::cout << "Press 5 to exit from Uber" << std::endl;

        char num[16];
        std::cout << "Enter your choice: ";
        std::cin >> num;
        while((num[0] != '1' && num[0] != '2' && num[0] != '3' && num[0] != '4' && num[0] != '5') || stringSize(num) > 1){
            std::cout << "Invalid input. Please enter a correct number:" << std::endl;
            std::cin >> num;
        }
        if(num[0] == '1'){
            registerClient(uber);
        }
        else if(num[0] == '2'){
            registerDriver(uber);
        }
        else if(num[0] == '3'){
            logInClient(uber);
        }
        else if(num[0] == '4'){
            logInDriver(uber);
        }
        else if(num[0] == '5'){
            exitFromUber(uber);
            break;
        }

    }
}

void registerClient(UberProject& uber){
    std::cout <<"Register:" << std::endl;
    char username[MAX_SIZE];
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    char password[MAX_SIZE];

    std::cout << "Insert your username: ";
    std::cin >> username;
    std::cout << std::endl;

    std::cout << "Insert your firstname: ";
    std::cin >> name;
    while(!(correctName(name))){
        std::cout << "Please enter correct name that starts with capital letter and contains only letters!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> name;
    }
    std::cout << std::endl;

    std::cout << "Insert your surname: ";
    std::cin >> surname;
    while(!(correctName(surname))){
        std::cout << "Please enter correct surname that starts with capital letter and contains only letters!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> surname;
    }
    std::cout << std::endl;

    std::cout << "Insert your password: ";
    std::cin >> password;
    std::cout << std::endl;

    uber.addClient(username, password, name, surname);
    std::cout << "Your client account is successfully registered!" << std::endl;
}
void registerDriver(UberProject& uber){
    std::cout <<"Register:" << std::endl;
    char username[MAX_SIZE];
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    char password[MAX_SIZE];
    char phoneNumber[MAX_SIZE];
    char carNumber[MAX_SIZE];

    std::cout << "Insert your username: ";
    std::cin >> username;
    std::cout << std::endl;

    std::cout << "Insert your firstname: ";
    std::cin >> name;
    while(!(correctName(name))){
        std::cout << "Please enter correct name that starts with capital letter and contains only letters!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> name;
    }
    std::cout << std::endl;

    std::cout << "Insert your surname: ";
    std::cin >> surname;
    while(!(correctName(surname))){
        std::cout << "Please enter correct surname that starts with capital letter and contains only letters!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> surname;
    }
    std::cout << std::endl;

    std::cout << "Insert your password: ";
    std::cin >> password;
    std::cout << std::endl;

    std::cout << "Insert your phone number:";
    std::cin >> phoneNumber;
    while(!(correctPhoneNumber(phoneNumber))){
        std::cout << "Please enter correct phone number that contains only numbers and is longer than 5 digits!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> phoneNumber;
    }
    std::cout << std::endl;

    std::cout << "Insert your car number:";
    std::cin >> carNumber;
    while(!(correctCarNumber(carNumber))){
        std::cout << "Please enter correct car number. Example: A234HN" << std::endl;
        std::cout << "Try again: ";
        std::cin >> carNumber;
    }
    std::cout << std::endl;

    uber.addDriver(username, password, name, surname, carNumber, phoneNumber);
    std::cout << "Your driver account is successfully registered!" << std::endl;
}
void logInClient(UberProject& uber){
    char username[MAX_SIZE];
    char password[MAX_SIZE];

    std::cout << "Log in as a client:" << std::endl;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << std::endl;

    std::cout << "Enter your password: ";
    std::cin >> password;
    std::cout << std::endl;

    uber.logInClient(username, password);
    if(uber.isClientLoggedIN()) {
        while (true) {
            std::cout << "Press 1 to make an order" << std::endl;
            std::cout << "Press 2 to check your order" << std::endl;
            std::cout << "Press 3 to cancel order" << std::endl;
            std::cout << "Press 4 to pay for order" << std::endl;
            std::cout << "Press 5 to rate a driver" << std::endl;
            std::cout << "Press 6 to add money in your account" << std::endl;
            std::cout << "Press 7 to log out from your account" << std::endl;
            char num;
            std::cout << "Enter your option:";
            std::cin >> num;
            while (num != '1' && num != '2' && num != '3' && num != '4' && num != '5' && num != '6' && num != '7') {
                std::cout << "Invalid input. Please enter a correct number:" << std::endl;
                std::cin >> num;
            }
            if (num == '1') {
                makeOrder(uber);
            } else if (num == '2') {
                checkOrder(uber);
            } else if (num == '3') {
                cancelOrder(uber);
            } else if (num == '4') {
                payForOrder(uber);
            } else if (num == '5') {
                rateDriver(uber);
            } else if (num == '6') {
                addMoney(uber);
            } else if (num == '7') {
                logOutClient(uber);
                break;
            }

        }
    }
    else{
            std::cout << "Incorrect username or password!" << std::endl;
    }

}
void logOutDriver(UberProject& uber){
    uber.logOutDriver();
    std::cout << "You successfully logged out!" << std::endl;
}
void logInDriver(UberProject& uber){
    char username[MAX_SIZE];
    char password[MAX_SIZE];

    std::cout << "Log in as a driver:" << std::endl;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << std::endl;

    std::cout << "Enter your password: ";
    std::cin >> password;
    std::cout << std::endl;

    uber.logInDriver(username, password);
    if(uber.isDriverLoggedIN()) {

        while (true) {
            std::cout << "Press 1 to change your address" << std::endl;
            std::cout << "Press 2 to check your messages" << std::endl;
            std::cout << "Press 3 to accept order" << std::endl;
            std::cout << "Press 4 to decline order" << std::endl;
            std::cout << "Press 5 to finish order" << std::endl;
            std::cout << "Press 6 to accept payment" << std::endl;
            std::cout << "Press 7 to log out from your account" << std::endl;
            char num;
            std::cout << "Enter your option:";
            std::cin >> num;
            while (num != '1' && num != '2' && num != '3' && num != '4' && num != '5' && num != '6' && num != '7') {
                std::cout << "Invalid input. Please enter a correct number:" << std::endl;
                std::cin >> num;
                std::cout << std::endl;
            }
            if (num == '1') {
                changeAddress(uber);
            } else if (num == '2') {
                checkMessages(uber);
            } else if (num == '3') {
                acceptOrder(uber);
            } else if (num == '4') {
                declineOrder(uber);
            } else if (num == '5') {
                finishOrder(uber);
            } else if (num == '6') {
                acceptPayment(uber);
            } else if (num == '7') {
                logOutDriver(uber);
                break;
            }
        }
    }
    else {
        std::cout << "Incorrect username or password!" << std::endl;
    }
}
void logOutClient(UberProject& uber){
    uber.logOutClient();
    std::cout << "You successfully logged out!" << std::endl;
}
void makeOrder(UberProject& uber){
    char addressFrom[MAX_SIZE];
    int x;
    int y;
    char addressTo[MAX_SIZE];
    int x1;
    int y1;
    int passengers;
    char moreInfo[MAX_SIZE];

    std::cout << "Enter the name of the address where you are: ";
    std::cin >> addressFrom;
    std::cout << std::endl;

    std::cout << "Enter the X of the location: ";
    std::cin >> x;
    std::cout << std::endl;

    std::cout << "Enter the Y of the location: ";
    std::cin >> y;
    std::cout << std::endl;

    std::cout << "Enter the name of the address you want to go: ";
    std::cin >> addressTo;
    std::cout << std::endl;

    std::cout << "Enter the X: ";
    std::cin >> x1;
    std::cout << std::endl;

    std::cout << "Enter the Y: ";
    std::cin >> y1;
    std::cout << std::endl;

    std::cout << "Enter the number of the passengers: ";
    std::cin >> passengers;
    while(!correctPassengersCount(passengers)){
        std::cout << "The count of the passengers can be maximum 4!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> passengers;
    }
    std::cout << std::endl;

    std::cout << "If you do not want to add extra information enter 0.";
    std::cout << "Enter extra info: ";
    std::cin >> moreInfo;
    std::cout << std::endl;

    if(strcmp(moreInfo, "0") == 0){
        uber.makeOrder(addressFrom, x, y, addressTo, x1, y1,passengers,"");
    }
    else {
        uber.makeOrder(addressFrom, x, y, addressTo, x1, y1, passengers, moreInfo);
    }

}
void checkOrder(UberProject& uber){
    size_t num;
    std::cout << "Enter the order ID: ";
    std::cin >> num;
    std::cout << std::endl;

    uber.checkOrder(num);
}
void cancelOrder(UberProject& uber){
    size_t num;
    std::cout << "Enter the order ID that you want to cancel: ";
    std::cin >> num;
    std::cout << std::endl;

    uber.cancelOrder(num);
}
void payForOrder(UberProject& uber){
    size_t num;
    std::cout << "Enter the order ID that you want to pay for: ";
    std::cin >> num;
    std::cout << std::endl;
    size_t money;
    std::cout << "Enter the amount you want to pay: ";
    std::cin >> money;
    while(money < 20){
        std::cout << "The minimum amount to pay is 20. Be cool and leave a tip: ";
        std::cin >> money;
    }
    std::cout << std::endl;

    uber.pay(num, money);
}
void rateDriver(UberProject& uber){
    char nameDriver[MAX_SIZE];
    std::cout << "Enter the username of the driver you want to rate: ";
    std::cin >> nameDriver;

    std::cout << std::endl;

    double rating;
    std::cout << "Enter the rating(from 0 to 10): ";
    std::cin >> rating;
    while(!(correctRating(rating))){
        std::cout << "Please enter valid rating between 0 and 10!" << std::endl;
        std::cout << "Try again: ";
        std::cin >> rating;
    }

    uber.rateDriver(nameDriver, rating);
}
void addMoney(UberProject& uber){
    size_t money;
    std::cout << "Enter the money you want to add: ";
    std::cin >> money;
    std::cout << std::endl;

    uber.addMoney(money);
}

void changeAddress(UberProject& uber){
    int x;
    int y;
    std::cout << "Enter the X: ";
    std::cin >> x;
    std::cout << std::endl;
    std::cout << "Enter the Y: ";
    std::cin >> y;
    std::cout << std::endl;

    uber.changeAddress(x,y);
}
void checkMessages(UberProject& uber){
    uber.checkMessages();
}
void acceptOrder(UberProject& uber){
    size_t id;
    std::cout << "Enter the order ID that you want to accept: ";
    std::cin >> id;
    std::cout << std::endl;

    size_t minutes;
    std::cout << "Enter the minutes needed to go there: ";
    std::cin >> minutes;
    while(!(correctMinutes(minutes))){
        std::cout << "We cannot let our clients to wait more than 30 minutes :)" << std::endl;
        std::cout << "Try again: ";
        std::cin >> minutes;
    }
    std::cout << std::endl;

    uber.acceptOrder(id, minutes);
}
void declineOrder(UberProject& uber){
    std::cout << "Enter the order ID you want to decline: ";
    size_t id;
    std::cin >> id;
    std::cout << std::endl;

    uber.declineOrder(id);
}
void finishOrder(UberProject& uber){
    std::cout << "Enter the order ID you want to finish: ";
    size_t id;
    std::cin >> id;
    std::cout << std::endl;

    uber.finishOrder(id);
}
void acceptPayment(UberProject& uber){
    std::cout << "Enter the order ID you want to be payed for: ";
    size_t id;
    std::cin >> id;
    std::cout << std::endl;

    uber.acceptPayment(id);
}
void exitFromUber(const UberProject& uber){
    std::ofstream myFile("CompanyInfo.dat");
    uber.writeUber(myFile);
    myFile.close();
    std::cout << "You successfully exit from UBER!" << std::endl;
}


