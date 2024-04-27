#include "UberProject.h"
#include <iostream>

void run();

void registerDriver(UberProject& uber);
void logInDriver(UberProject& uber);
void logOutDriver(UberProject& uber);
void registerClient(UberProject& uber);
void logInClient(UberProject& uber);
void logOutClient(UberProject& uber);

void makeOrder(UberProject& uber);
void checkOrder(UberProject& uber);
void cancelOrder(UberProject& uber);
void payForOrder(UberProject& uber);
void rateDriver(UberProject& uber);
void addMoney(UberProject& uber);

void changeAddress(UberProject& uber);
void checkMessages(UberProject& uber);
void acceptOrder(UberProject& uber);
void declineOrder(UberProject& uber);
void finishOrder(UberProject& uber);
void acceptPayment(UberProject& uber);

void exitFromUber(const UberProject& uber);



