#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void registerUser(struct User newUser) {
    FILE *file = fopen("users.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", newUser.username, newUser.password);
        fclose(file);
        printf("Registration successful!\n");
    } else {
        printf("Error opening file for registration.\n");
    }
}

int loginUser(char username[], char password[]) {
    FILE *file = fopen("users.txt", "r");
    if (file != NULL) {
        struct User currentUser;
        while (fscanf(file, "%s %s", currentUser.username, currentUser.password) == 2) {
            if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }
    return 0; // Login failed
}

int main() {
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    do {
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                struct User newUser;
                strcpy(newUser.username, username);
                strcpy(newUser.password, password);
                registerUser(newUser);
                break;

            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (loginUser(username, password)) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed. Invalid username or password.\n");
                }
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
