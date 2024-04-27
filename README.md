# OOP-CourseProject-FMI
# Taxi Management System

## Description

This application is a simplified taxi management system that supports two types of users: clients and drivers. Users can register, log in, and perform various actions based on their role.

## Features

### For Clients

- `register <type> <username> <password> <first_name> <last_name>`: Registers a new client account.
- `login <username> <password>`: Logs in to the system.
- `logout`: Logs out of the system.
- `order <address> <destination>`: Places a taxi order with the specified current address and destination.
- `check_order <id>`: Checks the status of a specific order.
- `cancel_order <id>`: Cancels a specific order.
- `pay <id> <amount>`: Pays for a completed order.
- `rate <name_of_driver> <rating>`: Rates a driver for a completed order.
- `add_money <amount>`: Adds money to the client's account.

### For Drivers

- `register <type> <username> <password> <first_name> <last_name> <car_number> <phone_number>`: Registers a new driver account.
- `login <username> <password>`: Logs in to the system.
- `logout`: Logs out of the system.
- `change_address <address>`: Changes the current address of the driver.
- `check_messages`: Checks messages sent by the system.
- `accept_order <id> <minutes>`: Accepts a specific order and provides an estimated arrival time.
- `decline_order <id>`: Declines a specific order.
- `finish_order <id>`: Marks a specific order as completed.
- `accept_payment <id> <amount>`: Accepts payment for a completed order.

## Usage

### Client Usage

1. Register a new client account.
2. Log in to the system.
3. Place a taxi order with the current address and destination.
4. Check the status of the order.
5. Pay for the completed order.
6. Rate the driver for the completed order.

### Driver Usage

1. Register a new driver account.
2. Log in to the system.
3. Change the current address if necessary.
4. Check messages for new orders.
5. Accept or decline orders as needed.
6. Mark orders as completed and accept payments.

## Example Usage

Here's an example of how the application can be used:

1. A client registers a new account, logs in, and places a taxi order.
2. The driver logs in, checks messages, accepts the order, and completes the trip.
3. The client pays for the trip, and the driver accepts the payment.

## Files

The application stores user information, trip data, and earnings in files for easy access and management.

## Testing

To test the application, follow these steps:

1. Register a client account, log in, and place a taxi order.
2. Log out of the client account and log in to the driver account.
3. Check messages, accept or decline the order, and complete the trip.
4. Log out of the driver account and log back in to the client account to continue testing.

## Note

This is a simplified version of a taxi management system and may require further enhancements for production use.


