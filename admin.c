
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

#define MAX_CUSTOMERS 100
Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

const char *CUSTOMER_FILE = "customer.txt";
const char *BALANCE_FILE = "balance.txt";
double pharmacyBalance = 10000.0;

// Function to add a customer to the array
int addCustomer(Customer customer) {
    if (customerCount < MAX_CUSTOMERS) {
        customers[customerCount] = customer;
        customerCount++;
        return 1;  // Successful
    } else {
        return 0;  // Failed to add, array full
    }
}

// Function to write customer information to a file
int writeCustomerToFile(const Customer *customer) {
    FILE *file = fopen(CUSTOMER_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%d %s %s %s\n", customer->customerID, customer->name, customer->address, customer->contactInfo);
        fclose(file);
        return 1;  // Successful
    } else {
        return 0;  // Failed to open file
    }
}

// Function to read customer information from a file
void readCustomersFromFile() {
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %s %s", &customers[customerCount].customerID,
                      customers[customerCount].name, customers[customerCount].address,
                      customers[customerCount].contactInfo) == 4) {
            customerCount++;
            if (customerCount >= MAX_CUSTOMERS) {
                break;
            }
        }
        fclose(file);
    }
}

// Function to create a new customer and add it to the array and file
Customer *createCustomer(int customerID, const char *name, const char *address, const char *contactInfo) {
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));

    if (newCustomer != NULL) {
        // Set customer details
        newCustomer->customerID = customerID;
        snprintf(newCustomer->name, sizeof(newCustomer->name), "%s", name);
        snprintf(newCustomer->address, sizeof(newCustomer->address), "%s", address);
        snprintf(newCustomer->contactInfo, sizeof(newCustomer->contactInfo), "%s", contactInfo);

        // Try to add the customer and write to file
        if (addCustomer(*newCustomer) && writeCustomerToFile(newCustomer)) {
            return newCustomer;
        } else {
            free(newCustomer);  // Free memory if adding or writing fails
            return NULL;
        }
    }

    return NULL;
}

// Function to display a customer's details
void showCustomer(const Customer *customer) {
    printf("Customer ID: %d\n", customer->customerID);
    printf("Name: %s\n", customer->name);
    printf("Address: %s\n", customer->address);
    printf("Contact Info: %s\n", customer->contactInfo);
    // Display other attributes when needed
}

// Function to list all customers
void listAllCustomers() {
    printf("=== Customer List ===\n");
    for (int i = 0; i < customerCount; i++) {
        showCustomer(&customers[i]);
        printf("\n");
    }
}

// Function to find a customer by their ID
Customer *findCustomerByID(int customerID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == customerID) {
            return &customers[i];
        }
    }
    return NULL;  // Customer not found
}

// Function to update the pharmacy's balance and write to a file
void updatePharmacyBalance(double amount) {
    pharmacyBalance += amount;
    FILE *balanceFile = fopen(BALANCE_FILE, "w");
    if (balanceFile != NULL) {
        fprintf(balanceFile, "%.2f", pharmacyBalance);
        fclose(balanceFile);
    } else {
        printf("Failed to open balance file for writing.\n");
    }
}

// Function to read the pharmacy's balance from a file
void readPharmacyBalance() {
    FILE *balanceFile = fopen(BALANCE_FILE, "r");
    if (balanceFile != NULL) {
        fscanf(balanceFile, "%lf", &pharmacyBalance);
        fclose(balanceFile);
    } else {
        printf("Failed to open balance file for reading.\n");
    }
}

// Function to print the pharmacy's balance
void printPharmacyBalance() {
    printf("Pharmacy Balance: $%.2f\n", pharmacyBalance);
}
