#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Donor {
    char name[50];
    char bloodType[3];
    char rhFactor[2];
    int age;
    char address[100];
};

void addDonor() {
    FILE *file = fopen("donors.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    struct Donor donor;

    printf("Enter donor details:\n");
    printf("Name: ");
    scanf("%s", donor.name);
    printf("Blood Type: ");
    scanf("%s", donor.bloodType);
    printf("Rh Factor: ");
    scanf("%s", donor.rhFactor);
    printf("Age: ");
    scanf("%d", &donor.age);
    printf("Address: ");
    scanf(" %[^\n]", donor.address);

    fprintf(file, "%s %s %s %d %s\n", donor.name, donor.bloodType, donor.rhFactor, donor.age, donor.address);

    fclose(file);
    printf("Donor added successfully!\n");
}

void displayDonors() {
    FILE *file = fopen("donors.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    struct Donor donor;

    printf("\nDonor Information:\n");
    printf("--------------------------------------------------------------\n");
    printf("Name\t\tBlood Type\tRh Factor\tAge\t\tAddress\n");

    while (fscanf(file, "%s %s %s %d %[^\n]", donor.name, donor.bloodType, donor.rhFactor,
                  &donor.age, donor.address) == 5) {
        printf("%s\t\t%s\t\t%s\t\t%d\t\t%s\n", donor.name, donor.bloodType, donor.rhFactor,
               donor.age, donor.address);
    }

    fclose(file);
}

void deleteDonor() {
    FILE *file = fopen("donors.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        exit(1);
    }

    struct Donor donor;
    char deleteName[50];
    int found = 0;

    printf("Enter the name of the donor to delete: ");
    scanf("%s", deleteName);

    while (fscanf(file, "%s %s %s %d %[^\n]", donor.name, donor.bloodType, donor.rhFactor,
                  &donor.age, donor.address) == 5) {
        if (strcmp(donor.name, deleteName) == 0) {
            found = 1;
            printf("Deleted donor:\n");
            printf("Name\t\tBlood Type\tRh Factor\tAge\t\tAddress\n");
            printf("%s\t\t%s\t\t%s\t\t%d\t\t%s\n", donor.name, donor.bloodType, donor.rhFactor,
                   donor.age, donor.address);
        } else {
            fprintf(tempFile, "%s %s %s %d %s\n", donor.name, donor.bloodType, donor.rhFactor,
                    donor.age, donor.address);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove("donors.txt") != 0) {
        printf("Error deleting file.\n");
        exit(1);
    }

    if (rename("temp.txt", "donors.txt") != 0) {
        printf("Error renaming file.\n");
        exit(1);
    }

    if (!found) {
        printf("Donor not found.\n");
    }
}

void updateDonor() {
    FILE *file = fopen("donors.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        exit(1);
    }

    struct Donor donor;
    char updateName[50];
    int found = 0;

    printf("Enter the name of the donor to update: ");
    scanf("%s", updateName);

    while (fscanf(file, "%s %s %s %d %[^\n]", donor.name, donor.bloodType, donor.rhFactor,
                  &donor.age, donor.address) == 5) {
        if (strcmp(donor.name, updateName) == 0) {
            found = 1;
            printf("Update donor:\n");
            printf("Name\t\tBlood Type\tRh Factor\tAge\t\tAddress\n");
            printf("%s\t\t%s\t\t%s\t\t%d\t\t%s\n", donor.name, donor.bloodType, donor.rhFactor,
                   donor.age, donor.address);

            printf("Enter updated details:\n");
            printf("Blood Type: ");
            scanf("%s", donor.bloodType);
            printf("Rh Factor: ");
            scanf("%s", donor.rhFactor);
            printf("Age: ");
            scanf("%d", &donor.age);
            printf("Address: ");
            scanf(" %[^\n]", donor.address);
        }

        fprintf(tempFile, "%s %s %s %d %s\n", donor.name, donor.bloodType, donor.rhFactor,
                donor.age, donor.address);
    }

    fclose(file);
    fclose(tempFile);

    if (remove("donors.txt") != 0) {
        printf("Error deleting file.\n");
        exit(1);
    }

    if (rename("temp.txt", "donors.txt") != 0) {
        printf("Error renaming file.\n");
        exit(1);
    }

    if (!found) {
        printf("Donor not found.\n");
    } else {
        printf("Donor updated successfully!\n");
    }
}

void searchDonor() {
    FILE *file = fopen("donors.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    struct Donor donor;
    char searchName[50];
    int found = 0;

    printf("Enter the name of the donor to search: ");
    scanf("%s", searchName);

    printf("\nSearch Results:\n");
    printf("--------------------------------------------------------------\n");
    printf("Name\t\tBlood Type\tRh Factor\tAge\t\tAddress\n");

    while (fscanf(file, "%s %s %s %d %[^\n]", donor.name, donor.bloodType, donor.rhFactor,
                  &donor.age, donor.address) == 5) {
        if (strcmp(donor.name, searchName) == 0) {
            found = 1;
            printf("%s\t\t%s\t\t%s\t\t%d\t\t%s\n", donor.name, donor.bloodType, donor.rhFactor,
                   donor.age, donor.address);
        }
    }

    fclose(file);

    if (!found) {
        printf("Donor not found.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\nBlood Donation Project\n");
        printf("1. Add Donor\n");
        printf("2. Delete Donor\n");
        printf("3. Update Donor\n");
        printf("4. Display Donors\n");
        printf("5. Search Donor\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDonor();
                break;
            case 2:
                deleteDonor();
                break;
            case 3:
                updateDonor();
                break;
            case 4:
                displayDonors();
                break;
            case 5:
                searchDonor();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
