#include "UberProject.h"
#include "constants.h"

bool UberProject::logInClient(const char* name, const char* password){
    for(int i = 0; i < clients.getSize(); i++){
        if(this->clients[i]->correctPassword(name,password)){
            currentClient = clients[i];
            return true;
        }
    }
    return false;
}
bool UberProject::logInDriver(const char* name, const char* password){
    for(int i = 0; i < drivers.getSize(); i++){
        if(drivers[i]->logIn(name, password)){
            currentDriver = drivers[i];
            return true;
        }
    }
    return false;
}
void UberProject::logOutClient(){
    currentClient = nullptr;
}
void UberProject::logOutDriver(){
    currentDriver = nullptr;
}
void UberProject::addClient(const char* username, const char* password, const char* name, const char* lastName){
    SharedPointer<ClientU> ptr;
    ptr = new ClientU(username, password, name, lastName);
    clients.pushBack(ptr);
}
void UberProject::addDriver(const char* username, const char* password, const char* name, const char* lastName, const char* carNumber, const char* phoneNumber){
    Driver* ptr;
    ptr = new Driver(username,password,name, lastName, carNumber, phoneNumber);
    drivers.pushBack(ptr);
}

void UberProject::setDriverFree(size_t orderIndex){
    for(int i = 0; i < orders.getSize(); i++){
        if(orderIndex == orders[i]->getID()){
            for(int j = 0; j < drivers.getSize(); j++){
                if(j == orders[i]->getDriver()){
                    drivers[j]->setDriverFree();
                    break;
                }
            }
        }
    }
}

void UberProject::makeOrder(const char* address1, int x1, int y1, const char* address2, int x2, int y2, size_t passCount, const char* info){
    if(currentClient) {
        SharedPointer<OrderU> newOrder;
        newOrder = new OrderU(getIndexOfClient(currentClient), address1, x1, y1, address2, x2, y2, passCount, info);

        currentClient->addOrder(newOrder->getID());
        std::cout << "Your ID is: " << newOrder->getID() << std::endl;
        orders.pushBack(newOrder);
    }
}

void UberProject::checkOrder(size_t id){
    if(currentClient){
        for(int i = 0; i < orders.getSize(); i++){
            if(currentClient->isOrderYours(orders[i]->getID()) && id == orders[i]->getID()){
                if(getIndexOrderByID(id)->isOrderFinished()){
                    std::cout << "Order was finished by: " << std::endl;
                    drivers[getIndexOrderByID(id)->getDriver()]->printDriver();
                }
                else if(getIndexOrderByID(id)->isOrderAccepted()){
                    std::cout << "The order is accepted from:" << std::endl;
                    drivers[getIndexOrderByID(id)->getDriver()]->printDriver();
                    std::cout << "The Uber will come after " << getIndexOrderByID(id)->getMinutes() << " minutes";
                }
                else{
                    std::cout << "The order is not accepted yet";
                }
                break;
            }
        }
    }
}
void UberProject::pay(size_t id, size_t amount){
    if(currentClient){
        for(int i = 0; i < orders.getSize(); i++){
            if(currentClient->isOrderYours(orders[i]->getID()) && getIndexOrderByID(id)->isOrderFinished()){
                if(orders[i]->getID() == id){
                    while(currentClient->getMoney() < amount){
                        std::cout << "You do not have enough money to pay! Please add money to your account." << std::endl;
                        size_t money;
                        std::cout << "Enter the amount you want to deposit: ";
                        std::cin >> money;
                        addMoney(money);
                    }
                    currentClient->pay(amount);
                    orders[i]->transferMoney(amount);
                    companyBudget += (double)amount;
                    break;
                }
            }
        }
    }

}
void UberProject::cancelOrder(size_t id){
    if(currentClient) {
        for (int i = 0; i < orders.getSize(); i++) {
            if (id == orders[i]->getID() && currentClient->isOrderYours(id)) {
                if(orders[i]->getDriver()) {
                            setDriverFree(id);
                }
                currentClient->removeOrder(id);
                orders.popAt(i);
                break;
            }
        }
    }
}
void UberProject::addMoney(size_t amount){
    if(currentClient){
        currentClient->addMoney(amount);
    }
}
void UberProject::rateDriver(const char* name, double rating){
    if(currentClient){
        for(int i = 0; i < orders.getSize(); i++){
            if(!(orders[i]->isOrderAccepted())){
                return;
            }
            if(currentClient->isOrderYours(orders[i]->getID()) && drivers[orders[i]->getDriver()]->getUserName() == name && orders[i]->isOrderFinished()){
                drivers[orders[i]->getDriver()]->setRating(rating);

            }
        }
    }
}

void UberProject::changeAddress(int x, int y){
    if(currentDriver){
        currentDriver->setLocation(x,y);
    }
}
bool UberProject::isTheClosestOne(const SharedPointer<OrderU>& ptr)const {
    bool theClosestOne = true;
    double distance = currentDriver->getLocation().getDist(ptr->getAddressPoint());
    for(int i = 0; i < drivers.getSize(); i++){
        bool isDeclined = false;
        for(int j = 0; j < ptr->getDeclineArrSize(); j++){
            if(ptr->isIndexIn(getIndexOfDriver(drivers[i]))){
                isDeclined = true;
            }
        }
        if(distance > drivers[i]->getLocation().getDist(ptr->getAddressPoint()) && (!isDeclined)){
            theClosestOne = false;
        }
    }
    return theClosestOne;
}
void UberProject::checkMessages()const{
    if(currentDriver){
        for(int i = 0; i < orders.getSize(); i++){
            if(isTheClosestOne(orders[i]) && !(orders[i]->isOrderAccepted())){
                if(!(orders[i]->isIndexIn(getIndexOfDriver(currentDriver)))) {
                    printOrder(orders[i]);
                }
            }
        }
    }
}
void UberProject::acceptOrder(size_t id, size_t minutes){
    if(currentDriver){
        for(int i = 0; i < orders.getSize(); i++) {
            if (isTheClosestOne(orders[i]) && id == orders[i]->getID() && !(orders[i]->isOrderAccepted())) {
                orders[i]->acceptOrder(getIndexOfDriver(currentDriver));
                orders[i]->setMinutes(minutes);
                currentDriver->setDriveBusy();
            }
        }
    }
}
void UberProject::declineOrder(size_t id){
    if(currentDriver) {
        for (int i = 0; i < orders.getSize(); i++) {
            if (isTheClosestOne(orders[i]) && !(orders[i]->isOrderAccepted()) && id == orders[i]->getID()) {
                orders[i]->addDeclineDriver(getIndexOfDriver(currentDriver));
                break;
            }
        }
    }
}
void UberProject::finishOrder(size_t id){
    if(currentDriver){
        for(int i = 0; i < orders.getSize(); i++){
            if(orders[i]->getDriver() == getIndexOfDriver(currentDriver) && id == orders[i]->getID()){
                orders[i]->finishOrder();
                currentDriver->setLocation(orders[i]->getDestinationPoint().getX(), orders[i]->getDestinationPoint().getY());
            }
        }
    }
}
void UberProject::acceptPayment(size_t id){
    if(currentDriver){
        for(int i = 0; i < orders.getSize(); i++){
            if(orders[i]->getDriver() == getIndexOfDriver(currentDriver) && (orders[i]->getMoneyToTransfer() != 0) && id == orders[i]->getID()){
                currentDriver->getPaid(orders[i]->getMoneyToTransfer());
                break;
            }
        }
    }
}
size_t UberProject::getIndexOfDriver(const MyString& name)const{
    for(int i = 0; i < drivers.getSize(); i++){
        if(drivers[i]->getUserName() == name){
            return i;
        }
    }
    return 0;
}
size_t UberProject::getIndexOfClient(const MyString& name)const{
    for(int i = 0; i < clients.getSize(); i++){
        if(clients[i]->getUserName() == name){
            return i;
        }
    }
    return 0;
}
bool UberProject::isClientLoggedIN()const{
    return !(currentClient == nullptr);
}
bool UberProject::isDriverLoggedIN()const{
    return !(currentDriver == nullptr);
}
size_t UberProject::getIndexOfClient(const SharedPointer<ClientU>& client)const{
    for(int i = 0; i < clients.getSize(); i++){
        if(client == clients[i]){
            return i;
        }
    }
    return 10;
}
size_t UberProject::getIndexOfDriver(const SharedPointer<Driver>& driver)const{
    for(int i = 0; i < drivers.getSize(); i++){
        if(driver == drivers[i]){
            return i;
        }
    }
    return 10;
}
const SharedPointer<OrderU>& UberProject::getIndexOrderByID(size_t id)const{
    for(int i = 0; i < orders.getSize(); i++){
        if(orders[i]->getID() == id){
            return orders[i];
        }
    }
    throw std::runtime_error("Error");
}
void UberProject::printOrder(const SharedPointer<OrderU>& ptr)const{
    std::cout << clients[ptr->getClient()]->getFirstName() << " " << clients[ptr->getClient()]->getSurname() <<
    " has made an order" << " " << "for " << ptr->getPassengersCount() <<
    " passengers"<<" from:" << std::endl;
    std::cout << ptr->getAddressFrom() << " " << ptr->getInfo() << std::endl;
    std::cout << "To:" << std::endl;
    std::cout << ptr->getAddressTo();
    std::cout << "Order`s ID is: " << ptr->getID() << std::endl;
}
void UberProject::writeUber(std::ofstream& file)const{
    if(orders.getSize() != 0) {
        size_t len = orders[orders.getSize() - 1]->getID();
        file.write((const char *) &len, sizeof(size_t));
    }
    else{
        size_t len = 0;
        file.write((const char*)&len, sizeof (size_t));
    }
    file.write((const char*)&companyBudget, sizeof (size_t));

    size_t lenClients = clients.getSize();
    file.write((const char*)&lenClients, sizeof (size_t));
    for(int i = 0; i < lenClients;i++){
        clients[i]->writeClient(file);
    }

    size_t lenOrders = orders.getSize();
    file.write((const char*)&lenOrders, sizeof(size_t));
    for(int i = 0; i < lenOrders; i++){
        orders[i]->writeOrder(file);
    }

    size_t lenDrivers = drivers.getSize();
    file.write((const char*)&lenDrivers, sizeof (size_t));
    for(int i = 0; i < lenDrivers; i++){
        drivers[i]->write(file);
    }

}
UberProject::UberProject(std::ifstream& file){
    if(getFileSize(file) == 0){
        UberProject();
    }
    else {

        size_t len = 0;
        file.read((char *) &len, sizeof(size_t));
        file.read((char *) &companyBudget, sizeof(size_t));

        size_t sizeClients = 0;
        file.read((char *) &sizeClients, sizeof(size_t));
        Vector<SharedPointer<ClientU>> vector(sizeClients);
        clients = vector;
        for (int i = 0; i < sizeClients; i++) {
            SharedPointer<ClientU> ptr = new ClientU(file);
            clients.pushBack(ptr);
        }

        size_t sizeOrders = 0;
        file.read((char *) &sizeOrders, sizeof(size_t));
        Vector<SharedPointer<OrderU>> vector3(sizeOrders);
        orders = vector3;
        for (int i = 0; i < sizeOrders; i++) {
            SharedPointer<OrderU> ptr3 = new OrderU(file);
            orders.pushBack(ptr3);
            orders[0]->setID(len);
        }
        size_t sizeDrivers = 0;
        file.read((char *) &sizeDrivers, sizeof(size_t));
        Vector<SharedPointer<Driver>> vector2(sizeClients);
        drivers = vector2;
        for (int i = 0; i < sizeDrivers; i++) {
            SharedPointer<Driver> ptr2 = new Driver(file);
            drivers.pushBack(ptr2);
        }
    }

}
size_t getFileSize(std::ifstream& in){
    size_t current = in.tellg();
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    in.seekg(current, std::ios::beg);

    return size;
}