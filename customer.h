#ifndef CUSTOMER_H
#define CUSTOMER_H

// Using the struct definition Medicine from medicine.h file
#include "medicine.h"


typedef struct {
    int orderID;
    int customerID;
    int medicineID;
    int quantity;
    double totalPrice;
    
} CustomerOrder;


extern Medicine Medicines[]; // Array of structures Medicine from medicine.c file
extern int numMedicines; // Variable for the number of medicines in medicine.c file

// Prototype of the function for purchasing medicine
void buyMedicine(int medicineID, int quantity);
void updateStockInFile(int medicineID, int newStockAmount);

#endif 
