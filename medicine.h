#ifndef MEDICINE_H
#define MEDICINE_H

typedef enum {
    PAINKILLER,
    ANTIBIOTIC,
    VITAMIN,
    
} MedicineCategories;

extern const char *MEDICINE_FILE;  // External declaration of medicine file

typedef struct Medicine {
    int medicineID;
    char medicineName[200];
    char manufacturer[100];
    double price;
    int stockAmount;
    char expirationDate[20];
    MedicineCategories category;
} Medicine;

int addMedicine(Medicine medicine);
int writeMedicinesToFile();
void readMedicinesFromFile();
Medicine *createNewMedicine(int medicineID, const char *medicineName, const char *manufacturer, double price, int stockAmount, const char *expirationDate, MedicineCategories category);
void showMedicine(const Medicine *medicine);
void listMedicines();
Medicine *findMedicine(int medicineID);
int deleteMedicine(int medicineID);
int updateMedicine(int medicineID, int newStockAmount, double newPrice);
#endif 
