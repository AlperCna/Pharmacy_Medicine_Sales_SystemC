#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "medicine.h"

float totalMedicinePrice = 0.0; // Variable to store the total price of medicines

void buyMedicine(int medicineID, int quantity) {
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            if (Medicines[i].stockAmount >= quantity) {
                float totalPrice = Medicines[i].price * quantity;
                printf("Purchased %d units of %s. Total Price: %lf\n", 
                       quantity, Medicines[i].medicineName, totalPrice);
                totalMedicinePrice = totalPrice + totalMedicinePrice;
                Medicines[i].stockAmount -= quantity;

                // Update stock amount in the file
                updateStockInFile(medicineID, Medicines[i].stockAmount);
                
                char answer[3];
                printf("Do you want to buy another medicine? (Yes/No): ");
                scanf("%s", answer);
                if (strcmp(answer, "Yes") == 0 || strcmp(answer, "yes") == 0) {
                    printf("Enter the ID of the medicine you want to buy: ");
                    scanf("%d", &medicineID);
                    printf("How many units do you want to buy? ");
                    scanf("%d", &quantity);
                    buyMedicine(medicineID, quantity);
                } else if (strcmp(answer, "No") == 0 || strcmp(answer, "no") == 0) {
                    
                    // Update pharmacy balance and display total price
                    updatePharmacyBalance(totalMedicinePrice);
                    updatePharmacyBalance(totalMedicinePrice);
                    printf("Total price of medicines purchased previously: %lf\n", totalMedicinePrice);
                    printf("Exiting the program...\n");
                    return;
                } else {
                    printf("You made an invalid choice. Program is terminating...\n");
                    return;
                }
                return;
            } else {
                printf("There is not enough stock of %s medicine.\n", Medicines[i].medicineName);
                return;
            }
        }
    }
    printf("Medicine with ID %d was not found.\n", medicineID);
}

// Function to update stock information in the file
void updateStockInFile(int medicineID, int newStockAmount) {
    FILE *tempFile = fopen("temp.txt", "w");
    FILE *file = fopen(MEDICINE_FILE, "r");

    if (file != NULL && tempFile != NULL) {
        Medicine tempMedicine;
        while (fscanf(file, "%d %s %s %lf %d %s %d", &tempMedicine.medicineID,
                      tempMedicine.medicineName, tempMedicine.manufacturer, &tempMedicine.price,
                      &tempMedicine.stockAmount, tempMedicine.expirationDate, &tempMedicine.category) == 7) {
            if (tempMedicine.medicineID == medicineID) {
                tempMedicine.stockAmount = newStockAmount;
            }
            fprintf(tempFile, "%d %s %s %.2f %d %s %d\n", tempMedicine.medicineID,
                    tempMedicine.medicineName, tempMedicine.manufacturer, tempMedicine.price,
                    tempMedicine.stockAmount, tempMedicine.expirationDate, tempMedicine.category);
        }    // No changes will be made in the new line, only the category information will remain the same.
        fclose(file);
        fclose(tempFile);

        remove(MEDICINE_FILE);  
        rename("temp.txt", MEDICINE_FILE);  
    } else {
        printf("File opening error.\n");
    }
}

