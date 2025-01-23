#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "medicine.h"
#include "customer.h"

void customerOperations() {
    int choice, medicineID, quantity;
    do {
        printf("\n--- Medicine Purchase System ---\n");
        printf("1. List Medicines\n");
        printf("2. Buy Medicine\n");
        printf("3. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listMedicines(); // List medicines
                break;
            case 2:
                printf("Enter the ID of the medicine you want to buy: ");
                scanf("%d", &medicineID);
                printf("How many units do you want to buy? ");
                scanf("%d", &quantity);
                buyMedicine(medicineID, quantity); // Purchase medicine
                break;
            case 3:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void managerOperations() {
    int choice;
    do {
        printf("\nSelect an operation to perform:\n");
        printf("1. Add Customer\n");
        printf("2. List All Customers\n");
        printf("3. Find Customer by ID\n");
        printf("4. Add Medicine\n");
        printf("5. Delete Medicine:\n");
        printf("6. Update Medicine:\n");
        printf("7. List All Medicines\n");
        printf("8. Find Medicine by ID\n");
        printf("9. View Pharmacy Balance\n");
        printf("10. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int customerID;
                char name[50];
                char address[100];
                char contactInfo[50];

                printf("Customer ID: ");
                scanf("%d", &customerID);
                printf("Name: ");
                scanf("%s", name);
                printf("Address: ");
                scanf("%s", address);
                printf("Contact Information: ");
                scanf("%s", contactInfo);

                Customer *newCustomer = createCustomer(customerID, name, address, contactInfo);
                if (newCustomer != NULL) {
                    printf("Customer added successfully.\n");
                    showCustomer(newCustomer);
                } else {
                    printf("Failed to add customer.\n");
                }
                break;
            }
            case 2:
                listAllCustomers();
                break;
            case 3: {
                int searchedCustomerID;
                printf("Search Customer ID: ");
                scanf("%d", &searchedCustomerID);
                Customer *foundCustomer = findCustomerByID(searchedCustomerID);
                if (foundCustomer != NULL) {
                    printf("Customer found:\n");
                    showCustomer(foundCustomer);
                } else {
                    printf("Customer not found.\n");
                }
                break;
            }
            case 4: {
                // Add Medicine
                int medicineID, stockAmount;
                char medicineName[200], manufacturer[100], expirationDate[20];
                double price;
                MedicineCategories category;
                printf("Medicine ID: ");
                scanf("%d", &medicineID);
                printf("Medicine Name: ");
                scanf("%s", medicineName);
                printf("Manufacturer: ");
                scanf("%s", manufacturer);
                printf("Price: ");
                scanf("%lf", &price);
                printf("Stock Amount: ");
                scanf("%d", &stockAmount);
                printf("Expiration Date: ");
                scanf("%s", expirationDate);
                printf("Category (0 for A, 1 for B, 2 for C): ");
                int categorySelection;
                scanf("%d", &categorySelection);
                category = (MedicineCategories)categorySelection;

                Medicine *newMedicine = createNewMedicine(medicineID, medicineName, manufacturer, price, stockAmount, expirationDate, category);
                if (newMedicine != NULL) {
                    printf("Medicine creation successful.\n");
                    showMedicine(newMedicine);
                } else {
                    printf("Medicine creation failed.\n");
                }
                break;
            }
            case 5:{ // Medicine Delete
                int medicineIDToDelete;
                printf("Enter Medicine ID to delete: ");
                scanf("%d", &medicineIDToDelete);
                int deleteResult = deleteMedicine(medicineIDToDelete);
                if (deleteResult) {
                    printf("Medicine with ID %d has been deleted.\n", medicineIDToDelete);
                } else {
                    printf("Medicine with ID %d was not found.\n", medicineIDToDelete);
                }
                break;
            }
            case 6: { // Medicine Uptade
                int medicineIDToUpdate;
                printf("Enter Medicine ID to update: ");
                scanf("%d", &medicineIDToUpdate);

                Medicine *medicineToUpdate = findMedicine(medicineIDToUpdate);
                if (medicineToUpdate != NULL) {
                    int stockAmount;
                    double price;
                    printf("Update Stock Amount: ");
                    scanf("%d", &stockAmount);
                    printf("Update Price: ");
                    scanf("%lf", &price);

                    medicineToUpdate->stockAmount = stockAmount;
                    medicineToUpdate->price = price;

                    int updateResult = updateMedicine(medicineIDToUpdate, stockAmount, price);

                    if (updateResult) {
                        printf("Medicine with ID %d has been updated.\n", medicineIDToUpdate);
                    } else {
                        printf("Failed to update medicine with ID %d.\n", medicineIDToUpdate);
                    }
                } else {
                    printf("Medicine with ID %d was not found.\n", medicineIDToUpdate);
                }
                break;
            }
            case 7:
                listMedicines();
                break;
            case 8: {
                int searchedMedicineID;
                printf("Search Medicine ID: ");
                scanf("%d", &searchedMedicineID);
                Medicine *foundMedicine = findMedicine(searchedMedicineID);
                if (foundMedicine != NULL) {
                    printf("Medicine Found:\n");
                    showMedicine(foundMedicine);
                } else {
                    printf("Medicine Not Found.\n");
                }
                break;
            }
             case 9:{
                printPharmacyBalance();
                continue;;
             }
            case 10:{
                printf("Exiting Manager operations.\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 10);
}

int menuSelection() {
    int choice;
    char username[20];
    char password[20];
    char manager_username[] = "admin";
    char manager_password[] = "1234";
    
     readPharmacyBalance();

    
    printf("Please make your selection:\n");
    printf("1. Customer\n");
    printf("2. Manager\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Logged in as a Customer.\n");
        readMedicinesFromFile(); // Read medicines from file
        customerOperations();
    } else if (choice == 2) {
        printf("To log in as a Manager, please enter your username and password.\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, manager_username) == 0 && strcmp(password, manager_password) == 0) {
            printf("Successfully logged in as Manager.\n");
            readCustomersFromFile();
            readMedicinesFromFile();
            managerOperations();
           
            
        } else {
            printf("Invalid username or password. Login failed.\n");
        }
    } else {
        printf("Invalid choice. Exiting the program.\n");
    }

    return 0;
}
