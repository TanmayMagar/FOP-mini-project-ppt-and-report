#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    char gender[10];
    int age;
    char treatment[100];
    char doctor[50];
    int wardNo;      
    int bedNo;       
};


struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char contact[20];
};

struct Patient patients[100];
struct Doctor doctors[100];

int totalPatients = 0;
int totalDoctors = 0;

// Function declarations
void displayHomePage();
void admitPatient();
void patientList();
void addDoctor();
void doctorList();
void billing();
void assignDoctor();

//file for doctor
void loadDoctors() {

    FILE *fp;
    fp = fopen("doctors.dat", "rb");   

    if(fp == NULL)
        return;

    while(fread(&doctors[totalDoctors], sizeof(struct Doctor), 1, fp)) {
        totalDoctors++;
    }

    fclose(fp);
}
//file for patient
void loadPatients() {

    FILE *fp;
    fp = fopen("patients.dat", "rb");

    if(fp == NULL)
        return;

    while(fread(&patients[totalPatients], sizeof(struct Patient), 1, fp)) {
        totalPatients++;
    }

    fclose(fp);
}


int main() {

    int choice;
    loadPatients();
    loadDoctors();

    while(1) {

        displayHomePage();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1: admitPatient(); break;
            case 2: patientList(); break;
            case 3: addDoctor(); break;
            case 4: doctorList(); break;
            case 5: billing(); break;
            case 6: assignDoctor(); break;
            case 7: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}




// Home Page
void displayHomePage() {

    printf("\n===== Hospital Management System =====\n");
    printf("1. Admit Patient\n");
    printf("2. Patient List\n");
    printf("3. Add Doctor\n");
    printf("4. Doctor List\n");
    printf("5. Billing\n");
    printf("6. Assign Doctor to Patient\n");
    printf("7. Exit\n");
}

// Add Doctor
void addDoctor() {

    printf("\n--- Add Doctor ---\n");

    printf("Enter Doctor ID: ");
    scanf("%d", &doctors[totalDoctors].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", doctors[totalDoctors].name);

    printf("Enter Specialization: ");
    scanf(" %[^\n]", doctors[totalDoctors].specialization);

    printf("Enter Contact: ");
    scanf("%s", doctors[totalDoctors].contact);

  totalDoctors++;

  FILE *fp;
  fp = fopen("doctors.dat", "ab");

  if(fp != NULL) {
    fwrite(&doctors[totalDoctors - 1], sizeof(struct Doctor), 1, fp);
    fclose(fp);
  }

printf("Doctor Added Successfully!\n");


}

// Show Doctor List
void doctorList() {

    printf("\n--- Doctor List ---\n");

    if(totalDoctors == 0) {
        printf("No Doctors Available\n");
        return;
    }

    for(int i = 0; i < totalDoctors; i++) {
        printf("\nID: %d", doctors[i].id);
        printf("\nName: %s", doctors[i].name);
        printf("\nSpecialization: %s", doctors[i].specialization);
        printf("\nContact: %s\n", doctors[i].contact);
        printf("----------------------\n");
    }
}
//Admit patient
void admitPatient() {

    printf("\n--- Admit Patient ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patients[totalPatients].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", patients[totalPatients].name);

    printf("Enter Gender: ");
    scanf("%s", patients[totalPatients].gender);

    printf("Enter Age: ");
    scanf("%d", &patients[totalPatients].age);

    printf("Enter Treatment: ");
    scanf(" %[^\n]", patients[totalPatients].treatment);

    printf("Enter Ward Number: ");
    scanf("%d", &patients[totalPatients].wardNo);

    printf("Enter Bed Number: ");
    scanf("%d", &patients[totalPatients].bedNo);


    for(int i = 0; i < totalPatients; i++) {

        if(patients[i].wardNo == patients[totalPatients].wardNo &&
           patients[i].bedNo == patients[totalPatients].bedNo) {

            printf("Bed already occupied! Try another ward/bed.\n");
            return;
        }
    }

    totalPatients++;

    printf("Patient Admitted Successfully!\n");
    FILE *fp;
fp = fopen("patients.dat", "ab");  

fwrite(&patients[totalPatients-1], sizeof(struct Patient), 1, fp);

fclose(fp);

}


// Show Patient List
void patientList() {

    printf("\n--- Patient List ---\n");

    if(totalPatients == 0) {
        printf("No Patients Available\n");
        return;
    }

    for(int i = 0; i < totalPatients; i++) {

        printf("\nID: %d", patients[i].id);
        printf("\nName: %s", patients[i].name);
        printf("\nGender: %s", patients[i].gender);
        printf("\nAge: %d", patients[i].age);
        printf("\nTreatment: %s", patients[i].treatment);
        printf("\nDoctor: %s", patients[i].doctor);
        printf("\nWard No: %d", patients[i].wardNo);
        printf("\nBed No: %d\n", patients[i].bedNo);
        printf("----------------------\n");
    }
}

// Assign Doctor
void assignDoctor() {

    int patientId, doctorId;
    int patientIndex = -1;
    int doctorIndex = -1;

    if(totalDoctors == 0 || totalPatients == 0) {
        printf("Add doctors and patients first.\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &patientId);

    printf("Enter Doctor ID: ");
    scanf("%d", &doctorId);

    for(int i = 0; i < totalPatients; i++) {
        if(patients[i].id == patientId) {
            patientIndex = i;
            break;
        }
    }

    for(int i = 0; i < totalDoctors; i++) {
        if(doctors[i].id == doctorId) {
            doctorIndex = i;
            break;
        }
    }

    if(patientIndex == -1 || doctorIndex == -1) {
        printf("Invalid ID entered.\n");
        return;
    }

    strcpy(patients[patientIndex].doctor, doctors[doctorIndex].name);
    FILE *fp;
fp = fopen("patients.dat", "wb");  

if(fp != NULL) {
    fwrite(patients, sizeof(struct Patient), totalPatients, fp);
    fclose(fp);
}


    printf("Doctor Assigned Successfully!\n");
}

// Billing
void billing() {

    float roomPerDay, medicineCost, doctorFee;
    int days;
    float roomTotal, serviceCharge, discount = 0, total;

    printf("\n--- Billing Section ---\n");

    printf("Enter Room Charge Per Day: ");
    scanf("%f", &roomPerDay);

    printf("Enter Number of Days Stayed: ");
    scanf("%d", &days);

    printf("Enter Medicine Charges: ");
    scanf("%f", &medicineCost);

    printf("Enter Doctor Fee: ");
    scanf("%f", &doctorFee);

    roomTotal = roomPerDay * days;
    total = roomTotal + medicineCost + doctorFee;

    serviceCharge = total * 0.05;
    total = total + serviceCharge;

    if(total > 50000) {
        discount = total * 0.10;
        total = total - discount;
    }

    printf("\nRoom Cost: %.2f", roomTotal);
    printf("\nService Charge (5%%): %.2f", serviceCharge);

    if(discount > 0)
        printf("\nDiscount (10%%): %.2f", discount);

    printf("\nTotal Bill = %.2f\n", total);
}S
