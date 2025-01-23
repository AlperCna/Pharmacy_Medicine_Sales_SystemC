#ifndef ADMIN_H
#define ADMIN_H

// Structure to store customer information
typedef struct {
    int customerID;
    char name[50];
    char address[100];
    char contactInfo[100];
    
} Customer;

int addCustomer(Customer customer);
int writeCustomerToFile(const Customer *customer);
void readCustomersFromFile();
Customer *createCustomer(int customerID, const char *name, const char *address, const char *contactInfo);
void showCustomer(const Customer *customer);
void listAllCustomers();
Customer *findCustomerByID(int customerID);

#endif 
