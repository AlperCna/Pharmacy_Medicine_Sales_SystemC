#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicine.h"


#define ALLOC_MEMORY(ptr, type, size) \
    do { \
        ptr = (type *)malloc((size) * sizeof(type)); \
        if (ptr == NULL) { \
            fprintf(stderr, "Memory allocation failed.\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)



#define MAX_MEDICINES 100
Medicine Medicines[MAX_MEDICINES];
int numMedicines = 0;

const char *MEDICINE_FILE = "medicine.txt";

// Function to add medicine
int addMedicine(Medicine medicine) {
    if (numMedicines < MAX_MEDICINES) {
        Medicines[numMedicines] = medicine;
        numMedicines++;
        return 1;  // Successful
    } else {
        return 0;  // Unsuccessful, array full
    }
}

// Function to write medicines to file
int writeMedicinesToFile(const Medicine *medicine) {
    FILE *file = fopen(MEDICINE_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%d %s %s %.2f %d %s %d\n", medicine->medicineID, medicine->medicineName, medicine->manufacturer, medicine->price, medicine->stockAmount, medicine->expirationDate, medicine->category);
        fclose(file);
        return 1;
    } else {
        return 0;  // File opening failed
    }
}

void readMedicinesFromFile() {


    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file != NULL) {
        Medicine tempMedicine; // Declare tempMedicine here
        int tempCategory;
        while (fscanf(file, "%d %s %s %lf %d %s %d", &Medicines[numMedicines].medicineID,
                      Medicines[numMedicines].medicineName, Medicines[numMedicines].manufacturer,
                      &Medicines[numMedicines].price, &Medicines[numMedicines].stockAmount,
                      Medicines[numMedicines].expirationDate, &tempCategory) == 7) {
                      Medicines[numMedicines].category = (MedicineCategories)tempCategory;
            numMedicines++;
            if (numMedicines >= MAX_MEDICINES) {
                break;
    }
}

        fclose(file);
    }
}


// Function to create a new medicine
Medicine *createNewMedicine(int medicineID, const char *medicineName, const char *manufacturer, double price, int stockAmount, const char *expirationDate, MedicineCategories category) {
    Medicine *newMedicine = (Medicine *)malloc(sizeof(Medicine));

    if (newMedicine != NULL) {
        newMedicine->medicineID = medicineID;
        snprintf(newMedicine->medicineName, sizeof(newMedicine->medicineName), "%s", medicineName);
        snprintf(newMedicine->manufacturer, sizeof(newMedicine->manufacturer), "%s", manufacturer);
        newMedicine->price = price;
        newMedicine->stockAmount = stockAmount;
        snprintf(newMedicine->expirationDate, sizeof(newMedicine->expirationDate), "%s", expirationDate);
        newMedicine->category = category;

        if (addMedicine(*newMedicine) && writeMedicinesToFile(newMedicine)) {
            return newMedicine;
        } else {
            free(newMedicine);  // Free memory if addition fails
            return NULL;
        }
    }

    return NULL;
}

// Function to display medicine information
void showMedicine(const Medicine *medicine) {
    printf("Medicine ID: %d\n", medicine->medicineID);
    printf("Name: %s\n", medicine->medicineName);
    printf("Manufacturer: %s\n", medicine->manufacturer);
    printf("Price: %.2f\n", medicine->price);
    printf("Stock Quantity: %d\n", medicine->stockAmount);
    printf("Expiration Date: %s\n", medicine->expirationDate);
    printf("Category: %d\n", medicine->category);
}

// Function to list all medicines
void listMedicines() {
    printf("=== Medicine List ===\n");
    for (int i = 0; i < numMedicines; i++) {
        showMedicine(&Medicines[i]);
        printf("\n");
    }
}

Medicine *findMedicine(int medicineID) {
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            return &Medicines[i];
        }
    }
    return NULL;  // Medicine not found
}

// Function to delete medicine by ID
int deleteMedicine(int medicineID) {
    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return 0;
    }

    int found = 0;
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d %s %s %.2f %d %s %d\n", 
                Medicines[i].medicineID, 
                Medicines[i].medicineName, 
                Medicines[i].manufacturer,
                Medicines[i].price,
                Medicines[i].stockAmount,
                Medicines[i].expirationDate,
                Medicines[i].category);
    }

    fclose(file);
    fclose(tempFile);

    remove(MEDICINE_FILE);
    rename("temp.txt", MEDICINE_FILE);

    if (found) {
        numMedicines--;
    }

    return found;
}

// Function to update medicine information
int updateMedicine(int medicineID, int newStockAmount, double newPrice) {
    FILE *tempFile = fopen("temp.txt", "w");
    FILE *file = fopen(MEDICINE_FILE, "r");

    if (file != NULL && tempFile != NULL) {
        Medicine tempMedicine;
        while (fscanf(file, "%d %s %s %lf %d %s %d", &tempMedicine.medicineID,
                      tempMedicine.medicineName, tempMedicine.manufacturer, &tempMedicine.price,
                      &tempMedicine.stockAmount, tempMedicine.expirationDate, &tempMedicine.category) == 7) {
            if (tempMedicine.medicineID == medicineID) {
                tempMedicine.stockAmount = newStockAmount;
                tempMedicine.price = newPrice;
            }
            fprintf(tempFile, "%d %s %s %.2f %d %s %d\n", tempMedicine.medicineID,
                    tempMedicine.medicineName, tempMedicine.manufacturer, tempMedicine.price,
                    tempMedicine.stockAmount, tempMedicine.expirationDate, tempMedicine.category);
        }
        fclose(file);
        fclose(tempFile);

        remove(MEDICINE_FILE);  
        rename("temp.txt", MEDICINE_FILE);  
    } else {
        printf("File opening error.\n");
    }
}


